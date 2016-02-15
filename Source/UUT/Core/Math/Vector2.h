#pragma once

namespace uut
{
	class Vector2
	{
	public:
		union
		{
			float data[2];
			struct
			{
				float x;
				float y;
			};
		};

		Vector2();
		Vector2(float x, float y);
		explicit Vector2(float val);
	};
}