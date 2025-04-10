#ifndef SCENE_VEHICLE_H
#define SCENE_VEHICLE_H

#include "SceneKapla.h"
#include "vehicle/PxVehicleWheels.h"
#include "RawLoader.h"
#include "VehicleManager.h"
#include "VehicleController.h"
#include "VehicleControlInputs.h"
#include "VehicleCameraController.h"

using namespace physx;

// ---------------------------------------------------------------------
class SceneVehicle : public SceneKapla, public RAWImportCallback
{
public:
	SceneVehicle(PxPhysics* pxPhysics, PxCooking *pxCooking, bool isGrb,
		Shader *defaultShader, const char *resourcePath, float slowMotionFactor);

	virtual ~SceneVehicle(){}

	///////////////////////////////////////////////////////////////////////////////

	// Implements RAWImportCallback
	virtual	void	newMaterial(const RAWMaterial&);
	virtual	void	newMesh(const RAWMesh&);
	virtual	void	newTexture(const RAWTexture&);
	virtual	void	newShape(const RAWShape&){}
	virtual	void	newHelper(const RAWHelper&){}
	
	///////////////////////////////////////////////////////////////////////////////


	virtual void handleMouseButton(int button, int state, int x, int y);
	virtual void handleMouseMotion(int x, int y);

	virtual void handleKeyDown(unsigned char key, int x, int y);
	virtual void handleKeyUp(unsigned char key, int x, int y);
	virtual void handleSpecialKey(unsigned char key, int x, int y);

	virtual void handleGamepadButton(int button, bool state);
	virtual void handleGamepadAxis(int axis, float x);
	virtual void handleGamepadTrigger(int trigger, float x);

	virtual void getCamera(PxVec3& pos, PxVec3& dir);

	virtual void preSim(float dt);
	virtual void postSim(float dt);

	virtual void render(bool useShader);

	virtual void customizeSceneDesc(PxSceneDesc& desc);

	virtual void onInit(PxScene* pxScene);

	virtual void setScene(PxScene* pxScene);

private:

	void renderCar(bool useShader);
	void createStandardMaterials();
	void createVehicle(PxPhysics* pxPhysics);
	void createTerrain(PxU32 size, float width, float chaos);
	void importRAWFile(const char* relativePath, PxReal scale, bool recook = false);

	enum
	{
		MAX_NUM_INDEX_BUFFERS = 16
	};
	PxU32							mNbIB;
	PxU32*							mIB[MAX_NUM_INDEX_BUFFERS];
	PxU32							mNbTriangles[MAX_NUM_INDEX_BUFFERS];
	PxU32							mRenderMaterial[MAX_NUM_INDEX_BUFFERS];

	PxVehicleDrivableSurfaceType	mVehicleDrivableSurfaceTypes[MAX_NUM_INDEX_BUFFERS];
	PxMaterial*						mStandardMaterials[MAX_NUM_INDEX_BUFFERS];

	PxMaterial*		mChassisMaterialDrivable;
	PxMaterial*		mChassisMaterialNonDrivable;

	VehicleManager				mVehicleManager;
	VehicleController			mVehicleController;
	VehicleControlInputs		mControlInputs;
	VehicleCameraController		mCameraController;

	//Terrain
	PxF32*							mTerrainVB;
	PxU32							mNbTerrainVerts;

	//render car 
	GLuint						mTextureIds[2];
	ShaderMaterial				mCarPartMaterial[2];

	PxU32						mNumMaterials;
	PxU32						mNumTextures;
};
#endif  // SCENE_BOXES_H
