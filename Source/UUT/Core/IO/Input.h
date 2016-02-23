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

		static bool IsKey(int key);

		void UpdateState();

	protected:
		IntVector2 _mousePos;
		const uint8_t* _kbState;
		int _kbMod;
		bool _mouseButton[3];
	};
}