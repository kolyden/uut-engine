#pragma once
#include <Core/Module.h>
#include <Core/IO/Scancode.h>
#include <Core/Math/Vector2i.h>

namespace uut
{
	class InputSystem : public Module
	{
		UUT_MODULE(uut, InputSystem, Module)
	public:
		virtual bool IsMouseButton(int button) const = 0;
		virtual const Vector2i& GetMousePos() const = 0;
		virtual float GetMouseDelta() const = 0;

		virtual bool IsKey(Scancode key) const = 0;
		virtual bool IsKeyDown(Scancode key) const = 0;
		virtual bool IsKeyUp(Scancode key) const = 0;
	};
}