#pragma once
#include <Core/String.h>
#include <Core/HashString.h>
#include <Core/Version.h>

namespace uut
{
	class Plugin
	{
	public:
		Plugin(const HashString& name, const Version& version);
		virtual ~Plugin() {}

		const HashString& GetPluginName() const;
		const Version& GetPluginVersion() const;

		String ToString() const;

	protected:
		virtual void OnRegister() {}
		virtual void OnUnregister() {}

		friend class Context;

	private:
		HashString _pluginName;
		Version _pluginVersion;
	};

#define UUT_REGISTER_OBJECT(type) UUT_REGISTER_TYPE(type)
#define UUT_REGISTER_MODULE(type) UUT_REGISTER_OBJECT(type)
}