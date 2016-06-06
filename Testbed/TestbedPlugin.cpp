#include "TestbedPlugin.h"
#include <Core/Context.h>
#include "BaseTest.h"
#include "TestContext.h"
#include "TestItemAttribute.h"

namespace uut
{
	TestbedPlugin::TestbedPlugin()
		: Plugin("Testbed", PluginVersion(0, 1))
	{
	}

	void TestbedPlugin::OnRegister()
	{
		UUT_REGISTER_OBJECT(TestItemAttribute);

		UUT_REGISTER_OBJECT(BaseTest);
// 		UUT_REGISTER_OBJECT(TestContext);
	}
}