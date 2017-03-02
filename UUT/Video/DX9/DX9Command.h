#pragma once
#include <Video/Color32.h>
#include <Core/Variant.h>
#include "DX9Defs.h"

namespace uut
{
	class VertexBuffer;
	class IndexBuffer;
	class Texture2D;

	struct DX9Command
	{
		enum Type
		{
			TYPE_CLEAR,
			TYPE_VIEWPORT,
			TYPE_SCISSOR,
			TYPE_PIPELINE,
			TYPE_TEXTURE,
			TYPE_VBUFFER,
			TYPE_IBUFFER,
			TYPE_DRAW,
			TYPE_DRAWIND,
		};

		Type type;

		union
		{
			D3DCOLOR color;
			D3DVIEWPORT9 viewport;
			D3DPRIMITIVETYPE primitiveType;
			RECT rect;
		};
		union
		{
			DWORD flags;
			int stage;
			int baseVertexIndex;
			uint16_t stride;
		};
		union
		{
			float z;
			uint32_t offset;
			uint32_t minVertexIndex;
		};
		union
		{
			DWORD stencil;
			uint32_t offset;
			uint32_t numVertices;
		};

		uint32_t startIndex;
		uint32_t primitiveCount;

		SharedPtr<Object> object;

		HRESULT Execute(LPDIRECT3DDEVICE9 device) const;
	};
}