#include "Context.h"
#include <Core/Reflection/Type.h>
#include "Debug.h"
#include "Plugin.h"
#include "Module.h"
#include "Attribute.h"
#include "AttributeUsage.h"

namespace uut
{
	bool Context::_inited = false;
	Context::PluginList Context::_plugins;
	Context::TypeDict Context::_types;
	Context::ConstTypeDict Context::_constTypes;
	Context::DerivedDict Context::_derived;
	Context::ModuleDict Context::_modules;
	Context::ModuleInstMap Context::_moduleInst;
	Context::AttributeTypes Context::_attributeTypes;
	Context::AttributeAttach Context::_attributeAttach;

	SharedPtr<Object> Context::CreateObject(const Type* type)
	{
		if (type == nullptr)
			return nullptr;

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

		return nullptr;
	}

	SharedPtr<Object> Context::CreateObject(const HashString& name)
	{
		return CreateObject(FindType(name));
	}

	//////////////////////////////////////////////////////////////////////////////
	void Context::AddPlugin(const SharedPtr<Plugin>& plugin)
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
	bool Context::RegisterType(Type* type)
	{
		if (type == nullptr)
			return false;

		if (_types.Contains(type->GetHash()))
			return true;

		const Type* parentType = type->GetBaseType();
		if (parentType != nullptr && !_types.Contains(parentType->GetHash()))
			return false;
// 		if (parentType != type)
// 			RegisterType(parentType);

		_types.Add(type->GetHash(), type);
		_constTypes.Add(type->GetHash(), type);

		for (; parentType != nullptr; parentType = parentType->GetBaseType())
			_derived[parentType].Add(type);

		type->Register();
		if (parentType != nullptr)
		{
			for (auto& attr : parentType->GetAttributes())
			{
				auto attrType = attr->GetType();
				auto attrUsage = attrType->FindAttribute<AttributeUsage>();
				if (attrUsage == nullptr || !attrUsage->IsInherited())
					continue;
				if (!attrUsage->IsAllowMultiple() && type->FindAttribute(attrType) != nullptr)
					continue;

				type->AddAttribute(attr);
			}
		}

		for (auto& attr : type->GetAttributes())
		{
			_attributeTypes[attr->GetType()] << attr;
			_attributeAttach[attr] = type;
		}

		return true;
	}

	const Type* Context::FindType(const HashString& name)
	{
		auto it = _types.Find(name.GetHash());
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
	void Context::AddModule(const SharedPtr<Module>& module)
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

		for (auto base = type; base != nullptr && base != Module::GetTypeStatic(); base = base->GetBaseType())
		{
			_moduleInst[base] = module;
		}

		module->OnRegister();
		if (_inited)
			module->OnInit();
	}

	Module* Context::FindModule(const Type* type)
	{
		if (type == nullptr)
			return nullptr;

		auto it = _moduleInst.Find(type);
		return it == _moduleInst.End() ? nullptr : it->second;
	}

	Module* Context::FindModule(const HashString& name)
	{
		return FindModule(FindType(name));
	}

	const Context::AttributeList& Context::GetAttributes(const Type* type)
	{
		if (type == nullptr)
			return AttributeList::Empty;

		auto it = _attributeTypes.Find(type);
		return it != _attributeTypes.End() ? it->second : AttributeList::Empty;
	}

	const Type* Context::GetAttributeAttach(const Attribute* attr)
	{
		if (attr == nullptr)
			return nullptr;

		auto it = _attributeAttach.Find(attr);
		return it != _attributeAttach.End() ? it->second : nullptr;
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
