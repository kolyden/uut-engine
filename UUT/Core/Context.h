#pragma once
#include <Core/HashString.h>
#include <Core/Collections/Dictionary.h>
#include <Core/Collections/HashSet.h>
#include <Core/Reflection/Type.h>
#include <Core/Ptr.h>
#include <Core/Math/Hash.h>
#include <typeindex>

namespace uut
{
	class Plugin;
	class Type;
	class Object;
	class Module;
	class Attribute;

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

		typedef List<std::pair<const Type*, const Attribute*>> AttributeList;
		typedef Dictionary<const Type*, Dictionary<HashValue, Attribute*>> AttributePool;
		typedef Dictionary<const Type*, AttributeList> AttributeTypes;

		// OBJECT CREATION
		static SharedPtr<Object> CreateObject(const Type* type);
		static SharedPtr<Object> CreateObject(const HashString& name);
		template<class C> static SharedPtr<C> CreateObject() { return DynamicCast<C>(CreateObject(TypeOf<C>())); }

		// PLUGINS
		static void AddPlugin(const SharedPtr<Plugin>& plugin);
		//static void RemovePlugin()
		static const PluginList& GetPlugins() { return _plugins; }

		template<class C, typename... Args,
			class = typename std::enable_if<std::is_base_of<Plugin, C>::value, void>::type,
			class = typename std::enable_if<std::is_constructible<C, Args...>::value, void>::type>
		static void CreatePlugin(Args&&... args)
		{
			auto plugin = MakeShared<C>(std::forward<Args>(args)...);
			AddPlugin(plugin);
		}

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
		static void AddModule(const SharedPtr<Module>& module);
		static Module* FindModule(const Type* type);
		static Module* FindModule(const HashString& name);
		template<class C>static C* FindModule()
		{ return dynamic_cast<C*>(FindModule(TypeOf<C>())); }

		template<class C, typename... Args,
			class = typename std::enable_if<std::is_base_of<Module, C>::value, void>::type,
			class = typename std::enable_if<std::is_constructible<C, Args...>::value, void>::type>
		static C* CreateModule(Args&&... args)
		{
			auto module = MakeShared<C>(std::forward<Args>(args)...);
			AddModule(module);
			return module;
		}

		// ATTRIBUTES
		static const Context::AttributeList& GetAttributes(const Type* type);

		template<class C, typename... Args,
			class = typename std::enable_if<std::is_base_of<Attribute, C>::value, void>::type,
			class = typename std::enable_if<std::is_constructible<C, Args...>::value, void>::type>
		static const Attribute* CreateAttribute(Args... args)
		{
			const size_t hash = Hash::Make(args...);
			const Type* type = C::GetTypeStatic();
			auto it = _attributesPool.Find(type);
			if (it != _attributesPool.End())
			{
				auto jt = it->second.Find(hash);
				if (jt != it->second.End())
					return jt->second;
			}

			auto attr = new C(args...);
			_attributesPool[type][hash] = attr;
			return attr;
		}


		template<class C> static const Context::AttributeList& GetAttributes()
		{ return GetAttributes(C::GetTypeStatic()); }

	protected:
		static bool _inited;
		static PluginList _plugins;
		static TypeDict _types;
		static ConstTypeDict _constTypes;
		static DerivedDict _derived;
		static ModuleDict _modules;
		static ModuleInstMap _moduleInst;
		static AttributePool _attributesPool;
		static AttributeTypes _attributeTypes;

		static void Init();
		static void Done();

		friend class Engine;
		friend class Application;
	};
}