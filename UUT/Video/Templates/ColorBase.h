#pragma once

namespace uut
{
	template <typename Type>
	class ColorBase
	{
	public:
		constexpr ColorBase(Type _r, Type _g, Type _b, Type _a)
			: r(_r), g(_g), b(_b), a(_a)
		{}

		union
		{
			Type data[4];
			struct
			{
				Type a;
				Type r;
				Type g;
				Type b;
			};
		};
	};
}