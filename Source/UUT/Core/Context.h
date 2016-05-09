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
		typedef Dictionary<std::type_index, Type*> TypeInfoDict;
		typedef Dictionary<HashString, const Type*> TypeDict;
		typedef HashSet<const Type*> DerivedSet;
		typedef Dictionary<const Type*, DerivedSet> DerivedDict;
		typedef Dictionary<HashString, SharedPtr<Module>> ModuleDict;

		// OBJECT CREATION
		static SharedPtr<Object> CreateObject(const Type* type);
		static SharedPtr<Object> CreateObject(const HashString& name);
		template<class C> static SharedPtr<Object> CreateObject() { return CreateObject(typeof<C>()); }

		// PLUGINS
		static void AddPlugin(Plugin* plugin);
		//static void RemovePlugin()
		static const PluginList& GetPlugins() { return _plugins; }

		// TYPES
		static Type* RegisterType(TypeInfo info, const HashString& name, const type_info& typeInfo, const type_info& parentInfo, Type::REGFUNC func);
		static const Type* FindType(const HashString& name);
		static const TypeDict& GetTypes() { return _types; }

		template<class C>static Type* RegisterType(TypeInfo info, const HashString& name, Type::REGFUNC func)
		{
			C::__internalType = RegisterType(info, name, typeid(C), typeid(C::Super), func);
			return C::__internalType;
		}

		static bool IsDerived(const Type* basetype, const Type* derived);
		static bool IsDerived(const HashString& basetype, const HashString& derived);

		static bool CanConvert(const Type* fromtype, const Type* totype);
		static bool CanConvert(const HashString& fromtype, const HashString& totype);

		// MODULES
		static void RegisterModule(Module* module);
		static Module* FindModule(const Type* type);
		static Module* FindModule(const HashString& name);

	protected:
		static bool _inited;
		static PluginList _plugins;
		static TypeInfoDict _typeInfos;
		static TypeDict _types;
		static DerivedDict _derived;
		static ModuleDict _modules;

		static void Init();
		static void Done();

		friend class Engine;
	};
}
