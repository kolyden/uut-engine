#pragma once
#include "Object.h"
#include "SDL2/SDL.h"

namespace uut
{
	class Engine : public Object
	{
		UUT_OBJECT(Engine, Object)
	public:
		Engine();
		virtual ~Engine();

		bool Init();
		void Done();

		bool Run();

	protected:
		bool _inited;
		bool _quited;
	};
}