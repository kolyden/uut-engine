#pragma once
#include <Core/Math/IntVector2.h>
#include <Core/IO/Scancode.h>

namespace uut
{
	class Input
	{
	public:
		static bool IsMouseButton(int button);
		static const IntVector2& GetMousePos();
		static float GetMouseDelta();

		static bool IsKey(Scancode key);
		static bool IsKeyDown(Scancode key);
		static bool IsKeyUp(Scancode key);
	};
}
