#include "BitmapFont.h"
#include <Core/Math/Vector2.h>
#include <Core/Math/IntRect.h>
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

	Texture2D* BitmapFont::GetTexture(int index) const
	{
		return _textures[index];
	}

	bool BitmapFont::PrintToQuad(Vector2& pos, uint32_t code, uint32_t next, IntRect& rect, Rect& tex, uint8_t& page) const
	{
		auto glyph = GetGlyph(code);
		if (glyph == nullptr)
			return false;

		auto texture = GetTexture(glyph->page);
		page = glyph->page;

		rect = IntRect(
			pos.x + glyph->offsetX,
			pos.y + glyph->offsetY,
			glyph->w, glyph->h);

		const float invTexW = 1.0f / texture->GetSize().x;
		const float invTexH = 1.0f / texture->GetSize().y;

		tex = Rect(
			invTexW * glyph->x,
			invTexH * glyph->y,
			invTexW * glyph->w,
			invTexH * glyph->h);

		pos.x += glyph->advanceX + GetKerning(code, next);
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void BitmapFont::UpdateGlyphsMap()
	{
		_glyphMap.Clear();
		for (uint i = 0; i < _glyphs.Count(); i++)
			_glyphMap.Add(_glyphs[i].id, i);
	}

	void BitmapFont::UpdateKerningMap()
	{
		_kerningMap.Clear();
		for (auto& kp : _kerningPairs)
			_kerningMap[kp.first][kp.second] = kp.amount;
	}
}