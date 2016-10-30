#include "BitmapFont.h"
#include <Core/Math/Vector2.h>
#include <Core/Math/IntRect.h>
#include <Core/Math/Math.h>
#include "Texture2D.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(BitmapFont)
	{}

	BitmapFont::BitmapFont()
	{}

	const FontGlyph* BitmapFont::GetGlyph(uint32_t id) const
	{
		auto it = _glyphMap.Find(id);
		if (it == _glyphMap.End())
			return nullptr;

		return &_glyphs[it->second];
	}

	int16_t BitmapFont::GetKerning(uint32_t a, uint32_t b) const
	{
		auto it = _kerningMap.Find(a);
		if (it == _kerningMap.End())
			return 0;

		auto jt = it->second.Find(b);
		if (jt == it->second.End())
			return 0;

		return jt->second;
	}

	const SharedPtr<Texture2D>& BitmapFont::GetTexture(int index) const
	{
		return _textures[index];
	}

	bool BitmapFont::PrintToQuad(Vector2& pos, uint32_t code, uint32_t next, IntRect& rect, Rect& tex, uint8_t& page) const
	{
		auto glyph = GetGlyph(code);
		if (glyph == nullptr)
			return false;

		page = glyph->page;

		rect = IntRect(
			Math::RoundToInt(pos.x + glyph->offsetX),
			Math::RoundToInt(pos.y + _info.lineHeight - glyph->offsetY - glyph->h),
			glyph->w, glyph->h);


		_glyphRect.TryGetValue(code, tex);

		pos.x += glyph->advanceX + GetKerning(code, next);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void BitmapFont::UpdateGlyphsMap()
	{
		_glyphMap.Clear();
		for (uint i = 0; i < _glyphs.Count(); i++)
		{
			const auto& glyph = _glyphs[i];
			_glyphMap.Add(glyph.id, i);

			auto page = glyph.page;
			auto tex = GetTexture(page);
			const float invTexW = 1.0f / (tex->GetSize().x - 1);
			const float invTexH = 1.0f / (tex->GetSize().y - 1);

			_glyphRect.Add(glyph.id,
				Rect(invTexW * glyph.x, invTexH * glyph.y,
					 invTexW * glyph.w, invTexH * glyph.h));
		}
	}

	void BitmapFont::UpdateKerningMap()
	{
		_kerningMap.Clear();
		for (auto& kp : _kerningPairs)
			_kerningMap[kp.first][kp.second] = kp.amount;
	}
}