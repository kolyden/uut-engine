#pragma once
#include "Object.h"

namespace uut
{
	class Engine : public Object
	{
		UUT_OBJECT(uut, Engine, Object)
	public:
		Engine();
		virtual ~Engine();

		bool Initialize();
		void RunFrame();

		void Exit();

		bool IsInitialized() const { return _inited; }
		bool IsExiting() const { return _exiting; }

	protected:
		bool _inited;
		bool _exiting;

		void DoExit();
	};
}