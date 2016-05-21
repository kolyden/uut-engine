#pragma once
#include <Resources/Resource.h>

namespace uut
{
	class Rect;
	class Geometry;

	class Font : public Resource
	{
		UUT_OBJECT(Font, Resource)
	public:
		Font();
	};
}