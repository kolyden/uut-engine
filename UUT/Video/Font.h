#pragma once
#include <Resources/Resource.h>

namespace uut
{
	class Texture2D;
	class Recti;
	class Vector2;
	class Rect;
	class Mesh;

	class Font : public Resource
	{
		UUT_OBJECT(uut, Font, Resource)
	public:
		Font();

		virtual bool PrintToQuad(Vector2& pos, uint32_t code, uint32_t next, Recti& rect, Rect& tex, uint8_t& page) const = 0;
		virtual const SharedPtr<Texture2D>& GetTexture(int index) const = 0;
	};
}