#include "DX9Command.h"
#include <Video/Texture2D.h>
#include <Video/VertexBuffer.h>
#include <Video/IndexBuffer.h>

namespace uut
{
	/*
	HRESULT ClearDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->Clear(0, nullptr, flags, color, z, stencil);
	}

	HRESULT ViewportDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->SetViewport(&viewport);
	}

	HRESULT TextureDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		if (texture == nullptr)
			return device->SetTexture(stage, nullptr);
			
		auto data = texture ? reinterpret_cast<LPDIRECT3DTEXTURE9>(texture->GetNativeHandle()) : nullptr;
		return device->SetTexture(stage, data);
	}

	HRESULT VBufferDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		auto data = buffer ? reinterpret_cast<LPDIRECT3DVERTEXBUFFER9>(buffer->GetInternalHandle()) : nullptr;
		return device->SetStreamSource(0, data, offset, stride);
	}

	HRESULT IBufferDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		auto data = buffer ? reinterpret_cast<LPDIRECT3DINDEXBUFFER9>(buffer->GetInternalHandle()) : nullptr;
		return device->SetIndices(data);
	}

	HRESULT ScissorDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->SetScissorRect(&rect);
	}

	HRESULT DrawDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->DrawPrimitive(primitiveType, offset, primitiveCount);
	}

	HRESULT DrawIndexedDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->DrawIndexedPrimitive(primitiveType,
			baseVertexIndex, minVertexIndex, numVertices, startIndex, primitiveCount);
	}*/

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