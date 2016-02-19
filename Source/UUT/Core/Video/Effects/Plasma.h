#pragma once
#include "Core/Object.h"
#include "Core/Math/IntVector2.h"
#include "Core/Video/Color32.h"

namespace uut
{
	class Texture2D;

	class Plasma : public Object
	{
	public:
		Plasma(const IntVector2& size);
		virtual ~Plasma();

		void SetPaletteColor(int index, const Color32& color);

		bool Apply(Texture2D* texture, int shift = 0);

	protected:
		IntVector2 _size;
		uint32_t _lookupCount;
		int* _lookupTable;
		uint32_t _palette[256];
	};
}