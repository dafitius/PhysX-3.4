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

#ifndef GU_GJKTYPE_H
#define GU_GJKTYPE_H

#include "GuVecConvex.h"
#include "PsVecTransform.h"

namespace physx
{
namespace Gu
{
	class ShrunkBoxV;
	class ShrunkConvexHullV;
	class ShrunkConvexHullNoScaleV;
	class ConvexHullV;
	class ConvexHullNoScaleV;
	class BoxV;

	template <typename Convex> struct Shrink { typedef Convex Type; };
	template <> struct Shrink<ConvexHullV> { typedef ShrunkConvexHullV Type; };
	template <> struct Shrink<ConvexHullNoScaleV> { typedef ShrunkConvexHullNoScaleV Type; };
	template <> struct Shrink<BoxV> { typedef ShrunkBoxV Type; };

	struct GjkConvexBase
	{
		
		GjkConvexBase(const ConvexV& convex) : mConvex(convex){}
		PX_FORCE_INLINE Ps::aos::FloatV	getMinMargin()		const { return mConvex.getMinMargin();		} 
		PX_FORCE_INLINE Ps::aos::BoolV	isMarginEqRadius()	const { return mConvex.isMarginEqRadius();	}
		PX_FORCE_INLINE bool			getMarginIsRadius()	const { return mConvex.getMarginIsRadius();	}
		PX_FORCE_INLINE Ps::aos::FloatV	getMargin()			const { return mConvex.getMargin();			}
		

		template <typename Convex>
		PX_FORCE_INLINE const Convex& getConvex() const { return static_cast<const Convex&>(mConvex); }

		virtual Ps::aos::Vec3V supportPoint(const PxI32 index, Ps::aos::FloatV* marginDif) const = 0;
		virtual Ps::aos::Vec3V support(const Ps::aos::Vec3VArg v) const = 0;
		virtual Ps::aos::Vec3V support(const Ps::aos::Vec3VArg dir, PxI32& index, Ps::aos::FloatV* marginDif) const = 0;
		virtual Ps::aos::FloatV getSweepMargin() const = 0;
		virtual Ps::aos::Vec3V	getCenter() const = 0;
		virtual ~GjkConvexBase(){}
	
	
	private:
		GjkConvexBase& operator = (const GjkConvexBase&);
	protected:
		const ConvexV& mConvex;
	};

	struct GjkConvex : public GjkConvexBase
	{
		GjkConvex(const ConvexV& convex) : GjkConvexBase(convex) { }

		virtual Ps::aos::Vec3V supportPoint(const PxI32 index, Ps::aos::FloatV* marginDif) const { return doVirtualSupportPoint(index, marginDif); }
		virtual Ps::aos::Vec3V support(const Ps::aos::Vec3VArg v) const { return doVirtualSupport(v); }
		virtual Ps::aos::Vec3V support(const Ps::aos::Vec3VArg dir, PxI32& index, Ps::aos::FloatV* marginDif) const{ return doVirtualSupport(dir, index, marginDif); }

		virtual Ps::aos::FloatV getSweepMargin() const { return doVirtualGetSweepMargin(); }

	private:
		Ps::aos::Vec3V doVirtualSupportPoint(const PxI32 index,Ps::aos::FloatV* marginDif) const
		{
			return supportPoint(index, marginDif); //Call the v-table
		}
		Ps::aos::Vec3V doVirtualSupport(const Ps::aos::Vec3VArg v) const
		{
			return support(v); //Call the v-table
		}
		Ps::aos::Vec3V doVirtualSupport(const Ps::aos::Vec3VArg dir, PxI32& index, Ps::aos::FloatV* marginDif) const
		{
			return support(dir, index, marginDif); //Call the v-table
		}

		Ps::aos::FloatV doVirtualGetSweepMargin() const { return getSweepMargin(); }

		GjkConvex& operator = (const GjkConvex&);
	};

	template <typename Convex>
	struct LocalConvex : public GjkConvex
	{
		LocalConvex(const Convex& convex) : GjkConvex(convex){}


		PX_FORCE_INLINE Ps::aos::Vec3V supportPoint(const PxI32 index, Ps::aos::FloatV* marginDif) const { return getConvex<Convex>().supportPoint(index, marginDif); }
		Ps::aos::Vec3V support(const Ps::aos::Vec3VArg v) const { return getConvex<Convex>().supportLocal(v); }
		Ps::aos::Vec3V support(const Ps::aos::Vec3VArg dir, PxI32& index, Ps::aos::FloatV* marginDif) const
		{
			return getConvex<Convex>().supportLocal(dir, index, marginDif);
		}

		virtual Ps::aos::Vec3V getCenter() const { return getConvex<Convex>().getCenter(); }

		//ML: we can't force inline function, otherwise win modern will throw compiler error
		PX_INLINE LocalConvex<typename Shrink<Convex>::Type > getShrunkConvex() const 
		{ 
			return LocalConvex<typename Shrink<Convex>::Type >(static_cast<const typename Shrink<Convex>::Type&>(GjkConvex::mConvex)); 
		}

		PX_INLINE Ps::aos::FloatV getSweepMargin() const { return getConvex<Convex>().getSweepMargin(); }

		typedef LocalConvex<typename Shrink<Convex>::Type > ShrunkConvex;

		typedef Convex	Type;


	private:
		LocalConvex<Convex>& operator = (const LocalConvex<Convex>&);
	};

	template <typename Convex>
	struct RelativeConvex : public GjkConvex
	{
		RelativeConvex(const Convex& convex, const Ps::aos::PsMatTransformV& aToB) : GjkConvex(convex), mAToB(aToB), mAToBTransposed(aToB)
		{
			shdfnd::aos::V3Transpose(mAToBTransposed.rot.col0, mAToBTransposed.rot.col1, mAToBTransposed.rot.col2);
		}

		PX_FORCE_INLINE Ps::aos::Vec3V supportPoint(const PxI32 index, Ps::aos::FloatV* marginDif) const { return mAToB.transform(getConvex<Convex>().supportPoint(index, marginDif)); }
		Ps::aos::Vec3V support(const Ps::aos::Vec3VArg v) const { return getConvex<Convex>().supportRelative(v, mAToB, mAToBTransposed); }
		Ps::aos::Vec3V support(const Ps::aos::Vec3VArg dir, PxI32& index, Ps::aos::FloatV* marginDif) const
		{
			return getConvex<Convex>().supportRelative(dir, mAToB, mAToBTransposed, index, marginDif);
		}

		virtual Ps::aos::Vec3V getCenter() const { return mAToB.transform(getConvex<Convex>().getCenter()); }

		// PX_FORCE_INLINE Ps::aos::PsMatTransformV& getRelativeTransform(){ return mAToB; }
		PX_FORCE_INLINE const Ps::aos::PsMatTransformV& getRelativeTransform() const { return mAToB; }

		//ML: we can't force inline function, otherwise win modern will throw compiler error
		PX_INLINE RelativeConvex<typename Shrink<Convex>::Type > getShrunkConvex() const 
		{ 
			return RelativeConvex<typename Shrink<Convex>::Type >(static_cast<const typename Shrink<Convex>::Type&>(GjkConvex::mConvex), mAToB); 
		}

		PX_INLINE Ps::aos::FloatV getSweepMargin() const { return getConvex<Convex>().getSweepMargin(); }

		typedef RelativeConvex<typename Shrink<Convex>::Type > ShrunkConvex;

		typedef Convex	Type;

	private:
		RelativeConvex<Convex>& operator = (const RelativeConvex<Convex>&);
		const Ps::aos::PsMatTransformV& mAToB;
		Ps::aos::PsMatTransformV mAToBTransposed;	// PT: precomputed mAToB transpose (because 'rotate' is faster than 'rotateInv')
	};

}
}

#endif
