#pragma once
#include <Core/Plugin.h>

namespace uut
{
	class VideoPlugin : public Plugin
	{
	public:
		VideoPlugin();

	protected:
		void OnRegister() override;
		void OnUnregister() override;
	};
}