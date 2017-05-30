#pragma once
#include <Core/Math/Vector2i.h>
#include <Core/IO/Scancode.h>

namespace uut
{
	class Input
	{
	public:
		static bool IsMouseButton(int button);
		static const Vector2i& GetMousePos();
		static float GetMouseDelta();

		static bool IsKey(Scancode key);
		static bool IsKeyDown(Scancode key);
		static bool IsKeyUp(Scancode key);
	};
}
