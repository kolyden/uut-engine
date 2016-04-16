#pragma once
#include <Video/Texture2D.h>
#include "DX9Defs.h"

namespace uut
{
	class DX9Texture2D : public Texture2D
	{
		UUT_OBJECT(DX9Texture2D, Texture2D)
	public:
		DX9Texture2D();
		virtual ~DX9Texture2D();

		virtual void* Lock(int* pitch) override;
		virtual void Unlock() override;

		virtual uintptr_t GetNativeHandle() const override;

	protected:
		LPDIRECT3DTEXTURE9 _data;

		friend class DX9Renderer;
	};
}
