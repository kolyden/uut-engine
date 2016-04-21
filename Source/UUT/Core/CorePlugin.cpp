#include "CorePlugin.h"
#include "Context.h"
#include "IO/Stream.h"
#include "IO/FileStream.h"
#include "IO/MemoryStream.h"
#include "IO/TextReader.h"
#include "IO/Input.h"
#include "Resources/Resource.h"
#include "Resources/ResourceLoader.h"
#include "Resources/ResourceCache.h"
#include "Windows/Window.h"
#include "Attribute.h"
#include "AttributeUsage.h"
#include "Engine.h"

namespace uut
{
	CorePlugin::CorePlugin()
		: Plugin("Core", PluginVersion(0, 1))
	{
	}

	void CorePlugin::OnRegister()
	{
		// CORE
		UUT_REGISTER_OBJECT(Object);
		UUT_REGISTER_OBJECT(Attribute);
		UUT_REGISTER_OBJECT(AttributeUsage);
		UUT_REGISTER_OBJECT(Engine);
		UUT_REGISTER_OBJECT(Module);

		// IO
		UUT_REGISTER_OBJECT(Stream);
		UUT_REGISTER_OBJECT(FileStream);
		UUT_REGISTER_OBJECT(MemoryStream);
		UUT_REGISTER_OBJECT(TextReader);
		UUT_REGISTER_MODULE(Input);

		// RESOURCES
		UUT_REGISTER_OBJECT(Resource);
		UUT_REGISTER_OBJECT(ResourceLoader);
		UUT_REGISTER_MODULE(ResourceCache);

		// WINDOWS
		UUT_REGISTER_OBJECT(Window);
	}

	void CorePlugin::OnUnregister()
	{
	}
}