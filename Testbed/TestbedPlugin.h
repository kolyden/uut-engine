#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class TestbedPlugin : public Plugin
	{
	public:
		TestbedPlugin();

	protected:
		virtual void OnRegister() override;

	};
}