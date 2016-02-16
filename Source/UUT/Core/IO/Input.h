#pragma once
#include "Core/Object.h"
#include "Core/Math/IntVector2.h"

namespace uut
{
	class Input : public Object
	{
	public:
		Input();

		static bool IsMouseButton(int button);
		static const IntVector2& GetMousePos();

		void UpdateState();

	protected:
		IntVector2 _mousePos;
		bool _mouseButton[3];
	};
}