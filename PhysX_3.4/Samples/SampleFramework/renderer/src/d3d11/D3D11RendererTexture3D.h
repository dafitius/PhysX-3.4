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
#ifndef D3D11_RENDERER_TEXTURE_3D_H
#define D3D11_RENDERER_TEXTURE_3D_H

#include <RendererConfig.h>

#if defined(RENDERER_ENABLE_DIRECT3D11)

#include <RendererTexture.h>

#include "D3D11Renderer.h"
#include "D3D11RendererTextureCommon.h"

namespace SampleRenderer
{

class D3D11RendererTexture3D : public RendererTexture3D, public D3D11RendererResource
{
	friend class D3D11RendererTarget;
	friend class D3D11RendererSpotLight;
public:
	D3D11RendererTexture3D(ID3D11Device& d3dDevice, ID3D11DeviceContext& d3dDeviceContext, const RendererTexture3DDesc& desc);
	virtual ~D3D11RendererTexture3D(void);

public:
	virtual void* lockLevel(PxU32 level, PxU32& pitch);
	virtual void  unlockLevel(PxU32 level);

	void bind(PxU32 samplerIndex, PxU32 flags = BIND_PIXEL);

	virtual void select(PxU32 stageIndex)
	{
		bind(stageIndex);
	}

private:
	virtual void onDeviceLost(void);
	virtual void onDeviceReset(void);

	void loadTextureDesc(const RendererTexture3DDesc&);
	void loadSamplerDesc(const RendererTexture3DDesc&);
	void loadResourceDesc(const RendererTexture3DDesc&);

private:
	ID3D11Device&               m_d3dDevice;
	ID3D11DeviceContext&        m_d3dDeviceContext;
	ID3D11Texture3D*            m_d3dTexture;
	D3D11_TEXTURE3D_DESC        m_d3dTextureDesc;

	ID3D11SamplerState*         m_d3dSamplerState;
	D3D11_SAMPLER_DESC          m_d3dSamplerDesc;

	ID3D11ShaderResourceView*       m_d3dSRV;
	D3D11_SHADER_RESOURCE_VIEW_DESC m_d3dSRVDesc;

	PxU8**                      m_data;
	D3D11_SUBRESOURCE_DATA*     m_resourceData;
};

} // namespace SampleRenderer

#endif // #if defined(RENDERER_ENABLE_DIRECT3D11)
#endif
