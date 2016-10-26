#pragma once
#include <Core/ValueType.h>

namespace uut
{
	template<typename Type>
	class RangeBase
	{
	public:
		constexpr RangeBase(Type _min, Type _max)
			: min(_min), max(_max) {}

		union
		{
			Type m[2];
			struct
			{
				Type min;
				Type max;
			};
		};
	};
}