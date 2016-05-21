#pragma once
#include "Font.h"
#include <Core/Collections/Array.h>
#include <Core/Collections/Dictionary.h>
#include <Core/Math/IntRect.h>
#include <Core/Math/Rect.h>
#include <Core/Math/Vector2.h>

namespace uut
{
	class Texture2D;

	struct FontGlyph
	{
		uint32_t id;
		uint16_t x, y;
		uint16_t w, h;
		int16_t offsetX, offsetY;
		int16_t advanceX;
		uint8_t page;
		uint8_t chnl;
	};

	struct FontKerningPair
	{
		uint32_t first, second;
		int16_t amount;
	};

	class BitmapFont : public Font
	{
		UUT_OBJECT(BitmapFont, Font)
	public:
		BitmapFont();

		const FontGlyph* GetGlyph(uint32_t id) const;
		int16_t GetKerning(uint32_t a, uint32_t b) const;
		Texture2D* GetTexture(int index) const;

		bool PrintToQuad(Vector2& pos, uint32_t code, uint32_t next, IntRect& rect, Rect& tex, uint8_t& page) const;

	protected:
		List<FontGlyph> _glyphs;
		List<FontKerningPair> _kerningPairs;
		Dictionary<uint32_t, uint16_t> _glyphMap;
		Dictionary<uint32_t, Dictionary<uint32_t, uint16_t>> _kerningMap;
		List<SharedPtr<Texture2D>> _textures;

		void UpdateGlyphsMap();
		void UpdateKerningMap();

		friend class BitmapFontLoader;
	};
}
