#pragma once
#include "RefCounted.h"
#include "String.h"
#include "HashString.h"

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
		Plugin(const HashString& name, const PluginVersion& version);

		const HashString& GetPluginName() const;
		const PluginVersion& GetPluginVersion() const;

		String ToString() const;

	protected:
		virtual void OnRegister() {}
		virtual void OnUnregister() {}

		friend class Context;

	private:
		HashString _pluginName;
		PluginVersion _pluginVersion;
	};

#define UUT_REGISTER_OBJECT(type) Context::RegisterType(typeof<type>())
#define UUT_REGISTER_MODULE(type) UUT_REGISTER_OBJECT(type)
}