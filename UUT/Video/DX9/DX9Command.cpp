#include "DX9Command.h"
#include <Video/Texture2D.h>
#include <Video/VertexBuffer.h>
#include <Video/IndexBuffer.h>

namespace uut
{
	HRESULT ClearDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->Clear(0, nullptr, flags, color, z, stencil);
	}

	HRESULT DrawDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->DrawPrimitive(primitiveType, offset, primitiveCount);
	}

	HRESULT DrawIndexedDX9Command::Execute(LPDIRECT3DDEVICE9 device)
	{
		return device->DrawIndexedPrimitive(primitiveType,
			baseVertexIndex, minVertexIndex, numVertices, startIndex, primitiveCount);
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
}