#include "DX9Command.h"
#include <Video/Texture2D.h>
#include <Video/VertexBuffer.h>
#include <Video/IndexBuffer.h>
#include "DX9PipelineState.h"

namespace uut
{
	static void CheckRenderState(LPDIRECT3DDEVICE9 dev, D3DRENDERSTATETYPE state, DWORD value)
	{
		DWORD old;
		if (dev->GetRenderState(state, &old) != D3D_OK || old != value)
			dev->SetRenderState(state, value);
	}

	static void SetTextureStageState(LPDIRECT3DDEVICE9 dev, DWORD stage, D3DTEXTURESTAGESTATETYPE state, DWORD value)
	{
		DWORD old;
		if (dev->GetTextureStageState(stage, state, &old) != D3D_OK || old != value)
			dev->SetTextureStageState(stage, state, value);
	}

	static void SetSamplerState(LPDIRECT3DDEVICE9 dev, DWORD sampler, D3DSAMPLERSTATETYPE state, DWORD value)
	{
		DWORD old;
		if (dev->GetSamplerState(sampler, state, &old) != D3D_OK || old != value)
			dev->SetSamplerState(sampler, state, value);
	}

	HRESULT DX9Command::Execute(LPDIRECT3DDEVICE9 device) const
	{
		switch (type)
		{
		case TYPE_CLEAR:
			return device->Clear(0, nullptr, flags, color, z, stencil);

		case TYPE_VIEWPORT:
			return device->SetViewport(&viewport);

		case TYPE_SCISSOR:
			return device->SetScissorRect(&rect);

		case TYPE_PIPELINE:
			{
				auto pipeline = DynamicCast<DX9PipelineState>(object);
				auto& newDesc = pipeline->GetDesc();

				device->SetVertexDeclaration(pipeline->_vd);

				CheckRenderState(device, D3DRS_ZENABLE, dx9::Convert(newDesc.zbuffer));
				CheckRenderState(device, D3DRS_ZWRITEENABLE, newDesc.zwriteEnable);
				CheckRenderState(device, D3DRS_ZFUNC, dx9::Convert(newDesc.zfunc));

				CheckRenderState(device, D3DRS_ALPHABLENDENABLE, newDesc.alphaBlend);
				CheckRenderState(device, D3DRS_ALPHATESTENABLE, newDesc.alphaTest);
				CheckRenderState(device, D3DRS_ALPHAREF, newDesc.alphaRef);
				CheckRenderState(device, D3DRS_ALPHAFUNC, dx9::Convert(newDesc.alphaFunc));

				CheckRenderState(device, D3DRS_BLENDOP, dx9::Convert(newDesc.blendOp));
				CheckRenderState(device, D3DRS_SRCBLEND, dx9::Convert(newDesc.srcBlend));
				CheckRenderState(device, D3DRS_DESTBLEND, dx9::Convert(newDesc.destBlend));
				CheckRenderState(device, D3DRS_BLENDOPALPHA, dx9::Convert(newDesc.blendOpAlpha));
				CheckRenderState(device, D3DRS_SRCBLENDALPHA, dx9::Convert(newDesc.srcBlendAlpha));
				CheckRenderState(device, D3DRS_DESTBLENDALPHA, dx9::Convert(newDesc.destBlendAlpha));

				CheckRenderState(device, D3DRS_LIGHTING, newDesc.lightning);
				CheckRenderState(device, D3DRS_AMBIENT, newDesc.ambientColor.ToInt());

				CheckRenderState(device, D3DRS_FOGENABLE, newDesc.fogEnabled);
				CheckRenderState(device, D3DRS_FOGCOLOR, newDesc.fogColor.ToInt());
				CheckRenderState(device, D3DRS_FOGTABLEMODE, dx9::Convert(newDesc.fogMode));
				CheckRenderState(device, D3DRS_FOGDENSITY, *((DWORD*)(&newDesc.fogDensity)));
				CheckRenderState(device, D3DRS_FOGSTART, *((DWORD*)(&newDesc.fogStart)));
				CheckRenderState(device, D3DRS_FOGEND, *((DWORD*)(&newDesc.fogEnd)));
				CheckRenderState(device, D3DRS_RANGEFOGENABLE, newDesc.fogRangeEnabled);

				CheckRenderState(device, D3DRS_FILLMODE, dx9::Convert(newDesc.fillMode));
				CheckRenderState(device, D3DRS_SHADEMODE, dx9::Convert(newDesc.shadeMode));
				CheckRenderState(device, D3DRS_CULLMODE, dx9::Convert(newDesc.cullMode));
				CheckRenderState(device, D3DRS_SCISSORTESTENABLE, newDesc.scissorTest);

				for (int i = 0; i < PipelineStateDesc::TEXTURE_STAGE_COUNT; i++)
				{
					SetTextureStageState(device, i, D3DTSS_COLOROP, dx9::Convert(newDesc.textureStage[i].colorOp));
					SetTextureStageState(device, i, D3DTSS_COLORARG1, dx9::Convert(newDesc.textureStage[i].colorArg1));
					SetTextureStageState(device, i, D3DTSS_COLORARG2, dx9::Convert(newDesc.textureStage[i].colorArg2));
					SetTextureStageState(device, i, D3DTSS_ALPHAOP, dx9::Convert(newDesc.textureStage[i].alphaOp));
					SetTextureStageState(device, i, D3DTSS_ALPHAARG1, dx9::Convert(newDesc.textureStage[i].alphaArg1));
					SetTextureStageState(device, i, D3DTSS_ALPHAARG2, dx9::Convert(newDesc.textureStage[i].alphaArg2));
				}

				for (int i = 0; i < PipelineStateDesc::SAMPLER_COUNT; i++)
				{
					SetSamplerState(device, i, D3DSAMP_ADDRESSU, dx9::Convert(newDesc.sampler[i].addressu));
					SetSamplerState(device, i, D3DSAMP_ADDRESSV, dx9::Convert(newDesc.sampler[i].addressv));
					SetSamplerState(device, i, D3DSAMP_ADDRESSW, dx9::Convert(newDesc.sampler[i].addressw));
					SetSamplerState(device, i, D3DSAMP_BORDERCOLOR, newDesc.sampler[i].borderColor.ToInt());
					SetSamplerState(device, i, D3DSAMP_MINFILTER, dx9::Convert(newDesc.sampler[i].minFilter));
					SetSamplerState(device, i, D3DSAMP_MAGFILTER, dx9::Convert(newDesc.sampler[i].magFilter));
					SetSamplerState(device, i, D3DSAMP_MIPFILTER, dx9::Convert(newDesc.sampler[i].mipFilter));
				}

				return D3D_OK;
			}
			break;

		case TYPE_TEXTURE:
			if (object == nullptr)
				return device->SetTexture(stage, nullptr);

			return device->SetTexture(stage, reinterpret_cast<LPDIRECT3DTEXTURE9>(
				DynamicCast<Texture2D>(object)->GetNativeHandle()));

		case TYPE_VBUFFER:
			if (object == nullptr)
				return device->SetStreamSource(0, nullptr, offset, stride);

			return device->SetStreamSource(0,
				reinterpret_cast<LPDIRECT3DVERTEXBUFFER9>(DynamicCast<VertexBuffer>(object)->GetInternalHandle()), offset, stride);
			break;

		case TYPE_IBUFFER:
			if (object == nullptr)
				device->SetIndices(nullptr);

			return device->SetIndices(
				reinterpret_cast<LPDIRECT3DINDEXBUFFER9>(DynamicCast<IndexBuffer>(object)->GetInternalHandle()));
			break;

		case TYPE_DRAW:
			return device->DrawPrimitive(primitiveType, offset, primitiveCount);
			break;

		case TYPE_DRAWIND:
			return device->DrawIndexedPrimitive(primitiveType,
				baseVertexIndex, minVertexIndex, numVertices, startIndex, primitiveCount);
			break;
		}

		return S_FALSE;
	}
}