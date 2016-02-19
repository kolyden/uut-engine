#pragma once

namespace uut
{
	class IntVector2;

	class Vector2
	{
	public:
		Vector2();
		Vector2(float x, float y);
		explicit Vector2(float val);
		Vector2(const IntVector2& vec);

		static const Vector2 ZERO;
		static const Vector2 ONE;
		static const Vector2 AXIS_X;
		static const Vector2 AXIS_Y;

		union
		{
			float data[2];
			struct
			{
				float x;
				float y;
			};
		};
	};
}