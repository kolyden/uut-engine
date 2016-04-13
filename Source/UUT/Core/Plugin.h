#pragma once
#include "RefCounted.h"
#include "String.h"

namespace uut
{
	struct PluginVersion
	{
		PluginVersion();
		PluginVersion(uint16_t _major, uint16_t _minor);

		bool operator ==(const PluginVersion& version) const;

		bool operator != (const PluginVersion& version) const;

		bool operator <(const PluginVersion& version) const;

		String ToString() const;

		uint16_t major;
		uint16_t minor;
	};

	class Plugin : public RefCounted
	{
	public:
		Plugin(const String& name, const PluginVersion& version);

		const String& GetPluginName() const;
		const PluginVersion& GetPluginVersion() const;

		String ToString() const;

	protected:
		virtual void OnRegister() {}
		virtual void OnUnregister() {}

		friend class Context;

	private:
		String _pluginName;
		PluginVersion _pluginVersion;
	};
}