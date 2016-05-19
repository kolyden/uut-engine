#pragma once
#include <Resources/Resource.h>

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