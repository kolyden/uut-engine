#include "Plasma.h"
#include "Core/Math/Math.h"
#include "Core/Video/Texture2D.h"

namespace uut
{
	Plasma::Plasma(const IntVector2& size)
		: _size(size)
		, _lookupCount(_size.Area())
	{
		_lookupTable = new int[_lookupCount];
		for (int y = 0; y < _size.y; y++)
		for (int x = 0; x < _size.x; x++)
		{
			const int color = int(
				128.0f + (128.0f*sinf(x / 16.0f)) +
				128.0f + (128.0f*sinf(y / 16.0f)));
			_lookupTable[x + y*_size.x] = color;
		}

		for (int i = 0; i < 256; i++)
		{
			const int r = Math::RoundToInt(128.0f + 128.0f*sinf(Math::PI * i / 32));
			const int g = Math::RoundToInt(128.0f + 128.0f*sinf(Math::PI * i / 64));
			const int b = Math::RoundToInt(128.0f + 128.0f*sinf(Math::PI * i / 128));
			_palette[i] = Color32(Math::Clamp(r, 0, 255), Math::Clamp(g, 0, 255), Math::Clamp(b, 0, 255)).ToInt();
		}
	}

	Plasma::~Plasma()
	{
		delete[] _lookupTable;
	}

	void Plasma::SetPaletteColor(int index, const Color32& color)
	{
		_palette[index] = color.ToInt();
	}

	bool Plasma::Apply(Texture2D* texture, int shift /* = 0 */)
	{
		if (texture == nullptr || texture->GetSize() != _size)
			return false;

		int pitch;
		void* buf = texture->Lock(&pitch);
		if (buf == nullptr)
			return false;

		for (int y = 0; y < _size.y; y++)
		for (int x = 0; x < _size.x; x++)
		{
			auto ptr = (uint32_t*)((char*)buf + x * 4 + y *pitch);
			*ptr = _palette[(_lookupTable[x + y*_size.x] + shift) % 256];
		}
		texture->Unlock();

		return true;
	}
}