#pragma once
#include "Texture.h"

namespace uut
{
	class Texture2D : public Texture
	{
	public:
		virtual ~Texture2D() {}

		virtual void* Lock(int* pitch = nullptr) = 0;
		virtual void Unlock() = 0;
	};
}