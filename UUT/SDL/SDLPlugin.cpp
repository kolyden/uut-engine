#include "SDLPlugin.h"
#include <Core/Context.h>
#include "SDLInput.h"

namespace uut
{
	SDLPlugin::SDLPlugin()
		: Plugin("SDL", Version(0, 1))
	{
	}

	void SDLPlugin::OnRegister()
	{
		UUT_REGISTER_OBJECT(SDLInput);
	}
}