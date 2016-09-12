#pragma once
#include "Texture.h"

namespace uut
{
	class Texture2D : public Texture
	{
		UUT_OBJECT(uut, Texture2D, Texture);
	public:
		Texture2D();
		virtual ~Texture2D();

		virtual void* Lock(int* pitch = nullptr) = 0;
		virtual void Unlock() = 0;
	};
}