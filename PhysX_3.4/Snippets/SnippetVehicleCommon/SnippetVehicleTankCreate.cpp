// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2008-2017 NVIDIA Corporation. All rights reserved.
// Copyright (c) 2004-2008 AGEIA Technologies, Inc. All rights reserved.
// Copyright (c) 2001-2004 NovodeX AG. All rights reserved.  

#include "SnippetVehicleCreate.h"
#include "SnippetVehicleTireFriction.h"
#include "SnippetVehicleSceneQuery.h"

namespace snippetvehicle
{
namespace tank
{

void computeWheelCenterActorOffsets
(const PxF32 wheelFrontZ, const PxF32 wheelRearZ, const PxVec3& chassisDims, const PxF32 wheelWidth, const PxF32 wheelRadius, const PxU32 numWheels, PxVec3* wheelCentreOffsets)
{
	//chassisDims.z is the distance from the rear of the chassis to the front of the chassis.
	//The front has z = 0.5*chassisDims.z and the rear has z = -0.5*chassisDims.z.
	//Compute a position for the front wheel and the rear wheel along the z-axis.
	//Compute the separation between each wheel along the z-axis.
	const PxF32 numLeftWheels = numWheels/2.0f;
	const PxF32 deltaZ = (wheelFrontZ - wheelRearZ)/(numLeftWheels-1.0f);
	//Set the outside of the left and right wheels to be flush with the chassis.
	//Set the top of the wheel to be just touching the underside of the chassis.
	for(PxU32 i = 0; i < numWheels; i+=2)
	{
		//Left wheel offset from origin.
		wheelCentreOffsets[i + 0] = PxVec3((-chassisDims.x + wheelWidth)*0.5f, -(chassisDims.y/2 + wheelRadius), wheelRearZ + i*deltaZ*0.5f);
		//Right wheel offsets from origin.
		wheelCentreOffsets[i + 1] = PxVec3((+chassisDims.x - wheelWidth)*0.5f, -(chassisDims.y/2 + wheelRadius), wheelRearZ + i*deltaZ*0.5f);
	}
}

void setupWheelsSimulationData
(const PxF32 wheelMass, const PxF32 wheelMOI, const PxF32 wheelRadius, const PxF32 wheelWidth, 
 const PxU32 numWheels, const PxVec3* wheelCenterActorOffsets,
 const PxVec3& chassisCMOffset, const PxF32 chassisMass,
 PxVehicleWheelsSimData* wheelsSimData)
{

	 //Set up the wheels.
	 PxVehicleWheelData wheels[PX_MAX_NB_WHEELS];
	{
		//Set up the wheel data structures with mass, moi, radius, width.
		//Increase the damping on the wheel.
		for(PxU32 i = 0; i < numWheels; i++)
		{
			wheels[i].mMass = wheelMass;
			wheels[i].mMOI = wheelMOI;
			wheels[i].mRadius = wheelRadius;
			wheels[i].mWidth = wheelWidth;
			wheels[i].mDampingRate = 2.0f;
		}
	}

	//Set up the tires.
	PxVehicleTireData tires[PX_MAX_NB_WHEELS];
	{
		//Set all tire types to "normal" type.
		for(PxU32 i = 0; i < numWheels; i++)
		{
			tires[i].mType = TIRE_TYPE_NORMAL;
		}
	}

	//Set up the suspensions
	PxVehicleSuspensionData suspensions[PX_MAX_NB_WHEELS];
	{
		//Compute the mass supported by each suspension spring.
		PxF32 suspSprungMasses[PX_MAX_NB_WHEELS];
		PxVehicleComputeSprungMasses(numWheels, wheelCenterActorOffsets, chassisCMOffset, chassisMass, 1, suspSprungMasses);

		//Set the suspension data.
		for(PxU32 i = 0; i < numWheels; i++)
		{
			suspensions[i].mMaxCompression = 0.3f;
			suspensions[i].mMaxDroop = 0.1f;
			suspensions[i].mSpringStrength = 10000.0f;	
			suspensions[i].mSpringDamperRate = 1500.0f;
			suspensions[i].mSprungMass = suspSprungMasses[i];
		}
	}

	//Set up the wheel geometry.
	PxVec3 suspTravelDirections[PX_MAX_NB_WHEELS];
	PxVec3 wheelCentreCMOffsets[PX_MAX_NB_WHEELS];
	PxVec3 suspForceAppCMOffsets[PX_MAX_NB_WHEELS];
	PxVec3 tireForceAppCMOffsets[PX_MAX_NB_WHEELS];
	{
		for(PxU32 i = 0; i < numWheels; i++)
		{
			//Vertical suspension travel.
			suspTravelDirections[i] = PxVec3(0,-1,0);

			//Wheel center offset is offset from rigid body center of mass.
			wheelCentreCMOffsets[i] = wheelCenterActorOffsets[i] - chassisCMOffset;

			//Suspension force application point 0.3 metres below rigid body center of mass.
			suspForceAppCMOffsets[i]=PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);

			//Tire force application point 0.3 metres below rigid body center of mass.
			tireForceAppCMOffsets[i]=PxVec3(wheelCentreCMOffsets[i].x,-0.3f,wheelCentreCMOffsets[i].z);
		}
	}

	//Set up the filter data of the raycast that will be issued by each suspension.
	PxFilterData qryFilterData;
	setupNonDrivableSurface(qryFilterData);

	//Set the wheel, tire and suspension data.
	//Set the geometry data.
	//Set the query filter data
	for(PxU32 i = 0; i < numWheels; i++)
	{
		wheelsSimData->setWheelData(i, wheels[i]);
		wheelsSimData->setTireData(i, tires[i]);
		wheelsSimData->setSuspensionData(i, suspensions[i]);
		wheelsSimData->setSuspTravelDirection(i, suspTravelDirections[i]);
		wheelsSimData->setWheelCentreOffset(i, wheelCentreCMOffsets[i]);
		wheelsSimData->setSuspForceAppPointOffset(i, suspForceAppCMOffsets[i]);
		wheelsSimData->setTireForceAppPointOffset(i, tireForceAppCMOffsets[i]);
		wheelsSimData->setSceneQueryFilterData(i, qryFilterData);
		wheelsSimData->setWheelShapeMapping(i, PxI32(i));
	}
}

}// namespace tank

PxVehicleDriveTank* createVehicleTank(const VehicleDesc& tankDesc, PxPhysics* physics, PxCooking* cooking)
{
	const PxVec3 chassisDims = tankDesc.chassisDims;
	const PxF32 wheelWidth = tankDesc.wheelWidth;
	const PxF32 wheelRadius = tankDesc.wheelRadius;
	const PxU32 numWheels = tankDesc.numWheels;

	const PxFilterData& chassisSimFilterData = tankDesc.chassisSimFilterData;
	const PxFilterData& wheelSimFilterData = tankDesc.wheelSimFilterData;

	//Construct a physx actor with shapes for the chassis and wheels.
	//Set the rigid body mass, moment of inertia, and center of mass offset.
	PxRigidDynamic* tankActor = NULL;
	{
		//Construct a convex mesh for a cylindrical wheel.
		PxConvexMesh* wheelMesh = createWheelMesh(wheelWidth, wheelRadius, *physics, *cooking);
		//Assume all wheels are identical for simplicity.
		PxConvexMesh* wheelConvexMeshes[PX_MAX_NB_WHEELS];
		PxMaterial* wheelMaterials[PX_MAX_NB_WHEELS];
		for(PxU32 i = 0; i < numWheels; i++)
		{
			wheelConvexMeshes[i] = wheelMesh;
			wheelMaterials[i] = tankDesc.wheelMaterial;
		}

		//Chassis just has a single convex shape for simplicity.
		PxConvexMesh* chassisConvexMesh = createChassisMesh(chassisDims, *physics, *cooking);
		PxConvexMesh* chassisConvexMeshes[1] = {chassisConvexMesh};
		PxMaterial* chassisMaterials[1] = {tankDesc.chassisMaterial};

		//Rigid body data.
		PxVehicleChassisData rigidBodyData;
		rigidBodyData.mMOI = tankDesc.chassisMOI;
		rigidBodyData.mMass = tankDesc.chassisMass;
		rigidBodyData.mCMOffset = tankDesc.chassisCMOffset;

		tankActor = createVehicleActor
			(rigidBodyData,
			wheelMaterials, wheelConvexMeshes, numWheels, wheelSimFilterData,
			chassisMaterials, chassisConvexMeshes, 1, chassisSimFilterData,
			*physics);
	}

	//Set up the sim data for the wheels.
	PxVehicleWheelsSimData* wheelsSimData = PxVehicleWheelsSimData::allocate(numWheels);
	{
		//Compute the wheel center offsets from the origin.
		PxVec3 wheelCentreActorOffsets[PX_MAX_NB_WHEELS];
		const PxF32 frontZ = chassisDims.z*0.35f;
		const PxF32 rearZ = -chassisDims.z*0.35f;
		tank::computeWheelCenterActorOffsets(frontZ, rearZ, chassisDims, wheelWidth, wheelRadius, numWheels, wheelCentreActorOffsets);

		tank::setupWheelsSimulationData
			(tankDesc.wheelMass, tankDesc.wheelMOI, wheelRadius, wheelWidth, 
			 numWheels, wheelCentreActorOffsets,
			 tankDesc.chassisCMOffset, tankDesc.chassisMass,
			 wheelsSimData);
	}

	//Set up the sim data for the tank drive model.
	PxVehicleDriveSimData driveSimData;
	{
		//Set up the engine to be more powerful but also more damped than the default engine.
		PxVehicleEngineData engineData = driveSimData.getEngineData();
		engineData.mPeakTorque *= 2.0f;
		engineData.mDampingRateZeroThrottleClutchEngaged = 2.0f;
		engineData.mDampingRateZeroThrottleClutchDisengaged = 0.5f;
		engineData.mDampingRateFullThrottle = 0.5f;
		driveSimData.setEngineData(engineData);
	}

	//Create a tank from the wheels and drive sim data.
	PxVehicleDriveTank* vehDriveTank = PxVehicleDriveTank::allocate(numWheels);
	vehDriveTank->setup(physics, tankActor, *wheelsSimData, driveSimData, numWheels);

	//Configure the userdata
	configureUserData(vehDriveTank, tankDesc.actorUserData, tankDesc.shapeUserDatas);

	//Free the sim data because we don't need that any more.
	wheelsSimData->free();

	return vehDriveTank;
}

} // namespace snippetvehicle
