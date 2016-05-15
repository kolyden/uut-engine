#include "Context.h"
#include <Core/Reflection/Type.h>
#include "Debug.h"
#include "Plugin.h"
#include "Module.h"

namespace uut
{
	bool Context::_inited = false;
	Context::PluginList Context::_plugins;
	Context::TypeInfoDict Context::_typeInfos;
	Dictionary<HashString, const Type*> Context::_types;
	Dictionary<const Type*, Context::DerivedSet> Context::_derived;
	Context::ModuleDict Context::_modules;

	SharedPtr<Object> Context::CreateObject(const Type* type)
	{
		if (type == nullptr)
			return SharedPtr<Object>::Empty;

// 		if (type->GetFactory() == nullptr)
// 			return type->Create();
// 
// 		for (auto& it : _types)
// 		{
// 			if (IsDerived(type, it.second) && it.second->GetFactory() == nullptr)
// 				return it.second->Create();
// 		}
// 
// 		Debug::LogError("No factory for '%s' type", type->GetName());

		return SharedPtr<Object>::Empty;
	}

	SharedPtr<Object> Context::CreateObject(const HashString& name)
	{
		return CreateObject(FindType(name));
	}

	//////////////////////////////////////////////////////////////////////////////
	void Context::AddPlugin(Plugin* plugin)
	{
		if (plugin == nullptr)
			return;

		SharedPtr<Plugin> store(plugin);
		for (auto& it : _plugins)
		{
			if (it->GetPluginName() != plugin->GetPluginName())
				continue;

			Debug::LogError("Same plugin '%s' already added", plugin->GetPluginName().GetData());
			return;
		}

		_plugins.Add(store);
	}

	//////////////////////////////////////////////////////////////////////////////
	Type* Context::RegisterType(TypeInfo info, const HashString& name,
		const type_info& typeInfo, const type_info& parentInfo, Type::REGFUNC func, size_t size)
	{
		if (_typeInfos.Contains(typeInfo))
			return _typeInfos[typeInfo];

		if (name.IsEmpty())
			return nullptr;

		const Type* parentType = nullptr;
		if (parentInfo != typeInfo)
		{
			auto it = _typeInfos.Find(parentInfo);
			if (it == _typeInfos.End())
			{
				Debug::LogError("Parent type '%s' not registered", parentInfo.name());
				return nullptr;
			}
			parentType = it->second;
		}

		auto type = new Type(info, name, parentType, func, size);
		_typeInfos[typeInfo] = type;
		_types.Add(type->GetName(), type);

		for (; parentType != nullptr; parentType = parentType->GetBaseType())
			_derived[parentType].Add(type);

		if (func)
			func(type);

		return type;
	}

	const Type* Context::FindType(const HashString& name)
	{
		auto it = _types.Find(name);
		return it != _types.End() ? it->second : nullptr;
	}

	bool Context::IsDerived(const Type* basetype, const Type* derived)
	{
		if (basetype == nullptr || derived == nullptr)
			return false;

		if (basetype == derived)
			return true;

		auto it = _derived.Find(basetype);
		return it != _derived.End() && it->second.Contains(derived);
	}

	bool Context::IsDerived(const HashString& basetype, const HashString& derived)
	{
		return IsDerived(FindType(basetype), FindType(derived));
	}

	bool Context::CanConvert(const Type* fromtype, const Type* totype)
	{
		if (fromtype == nullptr || totype == nullptr)
			return false;

		return IsDerived(fromtype, totype) || IsDerived(totype, fromtype);
	}

	bool Context::CanConvert(const HashString& fromtype, const HashString& totype)
	{
		return CanConvert(FindType(fromtype), FindType(totype));
	}

	//////////////////////////////////////////////////////////////////////////////
	void Context::RegisterModule(Module* module)
	{
		if (module == nullptr)
			return;

		const Type* type = module->GetType();
		if (_modules.Contains(type->GetName()))
		{
			Debug::LogError("Module %s already registered",
				type->GetName());
			return;
		}

		_modules.Add(type->GetName(), SharedPtr<Module>(module));
		module->OnRegister();
	}

	Module* Context::FindModule(const Type* type)
	{
		if (type == nullptr)
			return nullptr;

		auto it = _modules.Find(type->GetName());
		if (it != _modules.End())
			return it->second;

		for (auto& module : _modules)
		{
			if (module.second->GetType()->IsDerived(type))
				return module.second;
		}

		return nullptr;
	}

	Module* Context::FindModule(const HashString& name)
	{
		return FindModule(FindType(name));
	}

	//////////////////////////////////////////////////////////////////////////////
	void Context::Init()
	{
		if (_inited)
			return;

		_inited = true;
		for (auto& it : _plugins)
			it->OnRegister();

		for (auto& it : _modules)
			it.second->OnInit();
	}

	void Context::Done()
	{

	}

}