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
	/*
	class IDX9Command
	{
	public:
		virtual ~IDX9Command() {}
		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) = 0;
	};

	class ClearDX9Command : public IDX9Command
	{
	public:
		DWORD flags;
		D3DCOLOR color;
		float z;
		DWORD stencil;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class ViewportDX9Command : public IDX9Command
	{
	public:
		D3DVIEWPORT9 viewport;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class TextureDX9Command : public IDX9Command
	{
	public:
		int stage;
		SharedPtr<Texture2D> texture;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class VBufferDX9Command : public IDX9Command
	{
	public:
		uint16_t stride;
		uint32_t offset;
		SharedPtr<VertexBuffer> buffer;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class IBufferDX9Command : public IDX9Command
	{
	public:
		SharedPtr<IndexBuffer> buffer;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class ScissorDX9Command : public IDX9Command
	{
	public:
		RECT rect;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class DrawDX9Command : public IDX9Command
	{
	public:
		D3DPRIMITIVETYPE primitiveType;
		uint32_t primitiveCount;
		uint32_t offset;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};

	class DrawIndexedDX9Command : public IDX9Command
	{
	public:
		D3DPRIMITIVETYPE primitiveType;
		int baseVertexIndex;
		uint32_t minVertexIndex;
		uint32_t numVertices;
		uint32_t startIndex;
		uint32_t primitiveCount;

		virtual HRESULT Execute(LPDIRECT3DDEVICE9 device) override;
	};*/
}