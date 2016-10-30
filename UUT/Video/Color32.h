#pragma once
#include <Core/ValueType.h>
#include "Templates/ColorBase.h"

namespace uut
{
	class Color;

	class Color32
		: public ValueType
		, public ColorBase<uint8_t>
	{
		UUT_VALUETYPE(uut, Color32, ValueType)
	public:
		constexpr Color32() : ColorBase<uint8_t>(255, 255, 255, 255) {}
		constexpr Color32(int _r, int _g, int _b, int _a = 255)
			: ColorBase<uint8_t>(_r, _g, _b, _a) {}
		Color32(const Color& color);
		explicit Color32(uint32_t argb);

		bool operator==(const Color32& color) const;
		bool operator!=(const Color32& color) const;

		uint32_t ToInt() const; // ARGB

		static Color32 FromRGBA(uint32_t argb);
		static Color32 FromABGR(uint32_t abgr);

		static const Color32 Clear;        // (  0,   0,   0, 255)
		static const Color32 Transparent;  // (  255,   255,   255, 255)

		static const Color32 White;  // (255, 255, 255, 255)
		static const Color32 Black;  // (  0,   0,   0, 255)
		static const Color32 Red;    // (255,   0,   0, 255)
		static const Color32 Green;  // (  0, 255,   0, 255)
		static const Color32 Blue;   // (  0,   0, 255, 255)

		static const Color32 Yellow; // (255, 255,   0, 255)
		static const Color32 Magenta;// (255,   0, 255, 255)
		static const Color32 Cyan;   // (  0, 255, 255, 255)

		static const Color32 Grey;   // (128, 128, 128, 255)
		static const Color32 Silver; // (192, 192, 192, 255)
	};
}