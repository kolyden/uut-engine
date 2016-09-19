#include "Input.h"
#include <Core/IO/InputSystem.h>

namespace uut
{
	bool Input::IsMouseButton(int button)
	{
		return InputSystem::Instance()->IsMouseButton(button);
	}

	const uut::IntVector2& Input::GetMousePos()
	{
		return InputSystem::Instance()->GetMousePos();
	}

	float Input::GetMouseDelta()
	{
		return InputSystem::Instance()->GetMouseDelta();
	}

	bool Input::IsKey(Scancode key)
	{
		return InputSystem::Instance()->IsKey(key);
	}

	bool Input::IsKeyDown(Scancode key)
	{
		return InputSystem::Instance()->IsKeyDown(key);
	}

	bool Input::IsKeyUp(Scancode key)
	{
		return InputSystem::Instance()->IsKeyUp(key);
	}
}
