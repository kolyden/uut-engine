#include "Vector2.h"

namespace uut
{
	Vector2::Vector2()
	{
	}

	Vector2::Vector2(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	Vector2::Vector2(float val)
		: x(val), y(val)
	{
	}
}