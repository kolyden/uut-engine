#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class CorePlugin : public Plugin
	{
	public:
		CorePlugin();

	protected:
		void OnRegister() override;
		void OnUnregister() override;
	};
}