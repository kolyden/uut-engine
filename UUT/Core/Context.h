#pragma once
#include <Core/HashString.h>
#include <Core/Collections/Dictionary.h>
#include <Core/Collections/HashSet.h>
#include <Core/Reflection/Type.h>
#include <Core/Ptr.h>
#include <typeindex>

namespace uut
{
	class Plugin;
	class Type;
	class Object;
	class Module;

	class Context
	{
	public:
		typedef List<SharedPtr<Plugin>> PluginList;
		typedef Dictionary<size_t, Type*> TypeDict;
		typedef Dictionary<size_t, const Type*> ConstTypeDict;
		typedef HashSet<const Type*> DerivedSet;
		typedef Dictionary<const Type*, DerivedSet> DerivedDict;
		typedef Dictionary<HashString, SharedPtr<Module>> ModuleDict;
		typedef Dictionary<const Type*, Module*> ModuleInstMap;

		// OBJECT CREATION
		static SharedPtr<Object> CreateObject(const Type* type);
		static SharedPtr<Object> CreateObject(const HashString& name);
		template<class C> static SharedPtr<Object> CreateObject() { return CreateObject(typeof<C>()); }

		// PLUGINS
		static void AddPlugin(SharedPtr<Plugin> plugin);
		//static void RemovePlugin()
		static const PluginList& GetPlugins() { return _plugins; }

		// TYPES
		static bool RegisterType(Type* type);
		static const Type* FindType(const HashString& name);
		static const ConstTypeDict& GetTypes() { return _constTypes; }

		static bool IsDerived(const Type* basetype, const Type* derived);
		static bool IsDerived(const HashString& basetype, const HashString& derived);

		static bool CanConvert(const Type* fromtype, const Type* totype);
		static bool CanConvert(const HashString& fromtype, const HashString& totype);

		template<class C> static bool RegisterType() { return RegisterType(C::_GetTypeInternal()); }

		// MODULES
		static void RegisterModule(const SharedPtr<Module>& module);
		static Module* FindModule(const Type* type);
		static Module* FindModule(const HashString& name);
		template<class C>static C* FindModule()
		{ return dynamic_cast<C*>(FindModule(typeof<C>())); }

	protected:
		static bool _inited;
		static PluginList _plugins;
		static TypeDict _types;
		static ConstTypeDict _constTypes;
		static DerivedDict _derived;
		static ModuleDict _modules;
		static ModuleInstMap _moduleInst;

		static void Init();
		static void Done();

		friend class Engine;
	};
}
