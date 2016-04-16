#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class DX9Plugin : public Plugin
	{
	public:
		DX9Plugin();
	protected:
		void OnRegister() override;
		void OnUnregister() override;
	};
}