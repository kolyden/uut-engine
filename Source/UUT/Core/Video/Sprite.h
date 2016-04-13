#pragma once
#include <Core/Resources/Resource.h>

namespace uut
{
	class Sprite : public Resource
	{
		UUT_OBJECT(Sprite, Resource)
	public:
		Sprite();
		virtual ~Sprite();
	};
}