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

		Texture2D* GetTexture(int index) const override;
		bool PrintToQuad(Vector2& pos, uint32_t code, uint32_t next, IntRect& rect, Rect& tex, uint8_t& page) const override;

	protected:
		struct FaceInfo
		{
			uint16_t lineHeight;
			uint16_t base;
			uint16_t scaleW;
			uint16_t scaleH;
			uint16_t pages;
			uint8_t bitField;
			uint8_t alphaChnl;
			uint8_t redChnl;
			uint8_t greenChnl;
			uint8_t blueChnl;
		};

		List<FontGlyph> _glyphs;
		List<FontKerningPair> _kerningPairs;
		Dictionary<uint32_t, uint16_t> _glyphMap;
		Dictionary<uint32_t, Rect> _glyphRect;
		Dictionary<uint32_t, Dictionary<uint32_t, uint16_t>> _kerningMap;
		List<SharedPtr<Texture2D>> _textures;
		FaceInfo _info;

		void UpdateGlyphsMap();
		void UpdateKerningMap();

		friend class BitmapFontLoader;
	};
}
