#include "Plugin.h"

namespace uut
{
	Plugin::Plugin(const HashString& name, const Version& version)
		: _pluginName(name)
		, _pluginVersion(version)
	{
	}

	const HashString& Plugin::GetPluginName() const
	{
		return _pluginName;
	}

	const Version& Plugin::GetPluginVersion() const
	{
		return _pluginVersion;
	}

	String Plugin::ToString() const
	{
		return String::Format("%s %s", _pluginName.GetData(), _pluginVersion.ToString().GetData());
	}
}