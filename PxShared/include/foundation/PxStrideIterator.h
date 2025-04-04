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

#ifndef PXFOUNDATION_PXSTRIDEITERATOR_H
#define PXFOUNDATION_PXSTRIDEITERATOR_H

#include "foundation/Px.h"
#include "foundation/PxAssert.h"

/** \addtogroup foundation
  @{
*/

#if !PX_DOXYGEN
namespace physx
{
#endif

/**
\brief Iterator class for iterating over arrays of data that may be interleaved with other data.

This class is used for iterating over arrays of elements that may have a larger element to element
offset, called the stride, than the size of the element itself (non-contiguous).

The template parameter T denotes the type of the element accessed. The stride itself
is stored as a member field so multiple instances of a PxStrideIterator class can have
different strides. This is useful for cases were the stride depends on runtime configuration.

The stride iterator can be used for index based access, e.g.:
\code
    PxStrideIterator<PxVec3> strideArray(...);
    for (unsigned i = 0; i < 10; ++i)
    {
        PxVec3& vec = strideArray[i];
        ...
    }
\endcode
or iteration by increment, e.g.:
\code
    PxStrideIterator<PxVec3> strideBegin(...);
    PxStrideIterator<PxVec3> strideEnd(strideBegin + 10);
    for (PxStrideIterator<PxVec3> it = strideBegin; it < strideEnd; ++it)
    {
        PxVec3& vec = *it;
        ...
    }
\endcode

Two special cases:
- A stride of sizeof(T) represents a regular c array of type T.
- A stride of 0 can be used to describe re-occurrence of the same element multiple times.

*/
template <typename T>
class PxStrideIterator
{

#if !PX_DOXYGEN
	template <typename X>
	struct StripConst
	{
		typedef X Type;
	};

	template <typename X>
	struct StripConst<const X>
	{
		typedef X Type;
	};
#endif

  public:
	/**
	\brief Constructor.

	Optionally takes a pointer to an element and a stride.

	\param[in] ptr pointer to element, defaults to NULL.
	\param[in] stride stride for accessing consecutive elements, defaults to the size of one element.
	*/
	explicit PX_INLINE PxStrideIterator(T* ptr = NULL, PxU32 stride = sizeof(T)) : mPtr(ptr), mStride(stride)
	{
		PX_ASSERT(mStride == 0 || sizeof(T) <= mStride);
	}

	/**
	\brief Copy constructor.

	\param[in] strideIterator PxStrideIterator to be copied.
	*/
	PX_INLINE PxStrideIterator(const PxStrideIterator<typename StripConst<T>::Type>& strideIterator)
	: mPtr(strideIterator.ptr()), mStride(strideIterator.stride())
	{
		PX_ASSERT(mStride == 0 || sizeof(T) <= mStride);
	}

	PX_INLINE PxStrideIterator& operator=(const PxStrideIterator& other) = default;


	/**
	\brief Get pointer to element.
	*/
	PX_INLINE T* ptr() const
	{
		return mPtr;
	}

	/**
	\brief Get stride.
	*/
	PX_INLINE PxU32 stride() const
	{
		return mStride;
	}

	/**
	\brief Indirection operator.
	*/
	PX_INLINE T& operator*() const
	{
		return *mPtr;
	}

	/**
	\brief Dereferencing operator.
	*/
	PX_INLINE T* operator->() const
	{
		return mPtr;
	}

	/**
	\brief Indexing operator.
	*/
	PX_INLINE T& operator[](unsigned int i) const
	{
		return *byteAdd(mPtr, i * stride());
	}

	/**
	\brief Pre-increment operator.
	*/
	PX_INLINE PxStrideIterator& operator++()
	{
		mPtr = byteAdd(mPtr, stride());
		return *this;
	}

	/**
	\brief Post-increment operator.
	*/
	PX_INLINE PxStrideIterator operator++(int)
	{
		PxStrideIterator tmp = *this;
		mPtr = byteAdd(mPtr, stride());
		return tmp;
	}

	/**
	\brief Pre-decrement operator.
	*/
	PX_INLINE PxStrideIterator& operator--()
	{
		mPtr = byteSub(mPtr, stride());
		return *this;
	}

	/**
	\brief Post-decrement operator.
	*/
	PX_INLINE PxStrideIterator operator--(int)
	{
		PxStrideIterator tmp = *this;
		mPtr = byteSub(mPtr, stride());
		return tmp;
	}

	/**
	\brief Addition operator.
	*/
	PX_INLINE PxStrideIterator operator+(unsigned int i) const
	{
		return PxStrideIterator(byteAdd(mPtr, i * stride()), stride());
	}

	/**
	\brief Subtraction operator.
	*/
	PX_INLINE PxStrideIterator operator-(unsigned int i) const
	{
		return PxStrideIterator(byteSub(mPtr, i * stride()), stride());
	}

	/**
	\brief Addition compound assignment operator.
	*/
	PX_INLINE PxStrideIterator& operator+=(unsigned int i)
	{
		mPtr = byteAdd(mPtr, i * stride());
		return *this;
	}

	/**
	\brief Subtraction compound assignment operator.
	*/
	PX_INLINE PxStrideIterator& operator-=(unsigned int i)
	{
		mPtr = byteSub(mPtr, i * stride());
		return *this;
	}

	/**
	\brief Iterator difference.
	*/
	PX_INLINE int operator-(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		int byteDiff = static_cast<int>(reinterpret_cast<const PxU8*>(mPtr) - reinterpret_cast<const PxU8*>(other.mPtr));
		return byteDiff / static_cast<int>(stride());
	}

	/**
	\brief Equality operator.
	*/
	PX_INLINE bool operator==(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		return mPtr == other.mPtr;
	}

	/**
	\brief Inequality operator.
	*/
	PX_INLINE bool operator!=(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		return mPtr != other.mPtr;
	}

	/**
	\brief Less than operator.
	*/
	PX_INLINE bool operator<(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		return mPtr < other.mPtr;
	}

	/**
	\brief Greater than operator.
	*/
	PX_INLINE bool operator>(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		return mPtr > other.mPtr;
	}

	/**
	\brief Less or equal than operator.
	*/
	PX_INLINE bool operator<=(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		return mPtr <= other.mPtr;
	}

	/**
	\brief Greater or equal than operator.
	*/
	PX_INLINE bool operator>=(const PxStrideIterator& other) const
	{
		PX_ASSERT(isCompatible(other));
		return mPtr >= other.mPtr;
	}

  private:
	PX_INLINE static T* byteAdd(T* ptr, PxU32 bytes)
	{
		return const_cast<T*>(reinterpret_cast<const T*>(reinterpret_cast<const PxU8*>(ptr) + bytes));
	}

	PX_INLINE static T* byteSub(T* ptr, PxU32 bytes)
	{
		return const_cast<T*>(reinterpret_cast<const T*>(reinterpret_cast<const PxU8*>(ptr) - bytes));
	}

	PX_INLINE bool isCompatible(const PxStrideIterator& other) const
	{
		int byteDiff = static_cast<int>(reinterpret_cast<const PxU8*>(mPtr) - reinterpret_cast<const PxU8*>(other.mPtr));
		return (stride() == other.stride()) && (abs(byteDiff) % stride() == 0);
	}

	T* mPtr;
	PxU32 mStride;
};

/**
\brief Addition operator.
*/
template <typename T>
PX_INLINE PxStrideIterator<T> operator+(int i, PxStrideIterator<T> it)
{
	it += i;
	return it;
}

/**
\brief Stride iterator factory function which infers the iterator type.
*/
template <typename T>
PX_INLINE PxStrideIterator<T> PxMakeIterator(T* ptr, PxU32 stride = sizeof(T))
{
	return PxStrideIterator<T>(ptr, stride);
}

/**
\brief Stride iterator factory function which infers the iterator type.
*/
template <typename T>
PX_INLINE PxStrideIterator<const T> PxMakeIterator(const T* ptr, PxU32 stride = sizeof(T))
{
	return PxStrideIterator<const T>(ptr, stride);
}

#if !PX_DOXYGEN
} // namespace physx
#endif

/** @} */
#endif // PXFOUNDATION_PXSTRIDEITERATOR_H
