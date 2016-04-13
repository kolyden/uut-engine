#pragma once
#include "HashString.h"
#include <Core/Collections/Dictionary.h>
#include <Core/Collections/HashSet.h>
#include "Ptr.h"

namespace uut
{
	class Plugin;
	class Type;
	class Object;
	class Module;

	class Context
	{
	public:
		typedef HashSet<SharedPtr<Plugin>> PluginSet;
		typedef Dictionary<HashString, const Type*> TypeDict;
		typedef HashSet<const Type*> DerivedSet;
		typedef Dictionary<const Type*, DerivedSet> DerivedDict;
		typedef Dictionary<HashString, SharedPtr<Module>> ModuleDict;

		// OBJECT CREATION
		static SharedPtr<Object> CreateObject(const Type* type);
		static SharedPtr<Object> CreateObject(const HashString& name);

		// PLUGINS
		static void AddPlugin(Plugin* plugin);
		//static void RemovePlugin()

		// TYPES
		static void RegisterType(const Type* type);
		static const Type* FindType(const HashString& name);

		static bool IsDerived(const Type* basetype, const Type* derived);
		static bool IsDerived(const HashString& basetype, const HashString& derived);

		static bool CanConvert(const Type* fromtype, const Type* totype);
		static bool CanConvert(const HashString& fromtype, const HashString& totype);

		// MODULES
		static void RegisterModule(Module* module);
		static Module* FindModule(const Type* type);
		static Module* FindModule(const HashString& name);

		// INITIALIZATION
		static void Init();

	protected:
		static bool _inited;
		static PluginSet _plugins;
		static TypeDict _types;
		static DerivedDict _derived;
		static ModuleDict _modules;
	};
}