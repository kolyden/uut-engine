#include "Plugin.h"

namespace uut
{
	PluginVersion::PluginVersion()
		: major()
		, minor(0)
	{}

	PluginVersion::PluginVersion(uint16_t _major, uint16_t _minor)
		: major(_major)
		, minor(_minor)
	{}

	bool PluginVersion::operator==(const PluginVersion& version) const
	{
		return major == version.major && minor == version.minor;
	}

	bool PluginVersion::operator!=(const PluginVersion& version) const
	{
		return major != version.major || minor != version.minor;
	}

	bool PluginVersion::operator<(const PluginVersion& version) const
	{
		if (major == version.major)
			return minor < version.minor;

		return major < version.major;
	}

	String PluginVersion::ToString() const
	{
		return String::Format("%d.%d", major, minor);
	}

	///////////////////////////////////////////////////////////////////
	Plugin::Plugin(const String& name, const PluginVersion& version)
		: _pluginName(name)
		, _pluginVersion(version)
	{
	}

	const String& Plugin::GetPluginName() const
	{
		return _pluginName;
	}

	const PluginVersion& Plugin::GetPluginVersion() const
	{
		return _pluginVersion;
	}

	String Plugin::ToString() const
	{
		return _pluginName + " " + _pluginVersion.ToString();
	}
}