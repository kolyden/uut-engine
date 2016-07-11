#include "Attribute.h"
#include <Core/Reflection/Type.h>
#include "Debug.h"
#include "AttributeUsage.h"

namespace uut
{
	UUT_OBJECT_IMPLEMENT(Attribute)
	{
	}

	Attribute::Attribute()
	{
	}

	Attribute::~Attribute()
	{
		
	}

// 	Attribute* Attribute::GetAttribute(const Type* type, bool inherit)
// 	{
// 		if (type == nullptr)
// 			return nullptr;
// 
// 		for (; type != nullptr; type = inherit ? type->GetBaseType() : nullptr)
// 		{
// 			auto it = _attributes.Find(type);
// 			if (it == _attributes.End())
// 				continue;
// 
// 			for (auto& jt : it->second)
// 			{
// 				auto attrType = jt->GetType();
// 				if (attrType->CanConvert(type))
// 					return jt;
// 			}
// 		}
// 
// 		return nullptr;
// 	}
// 
// 	void Attribute::GetAttributes(const Type* type, List<Attribute*>& attributes, bool inherit)
// 	{
// 		if (type == nullptr)
// 			return;
// 
// 		for (; type != nullptr; type = inherit ? type->GetBaseType() : nullptr)
// 		{
// 			auto it = _attributes.Find(type);
// 			if (it == _attributes.End())
// 				continue;
// 
// 			for (auto& jt : it->second)
// 			{
// 				auto attrType = jt->GetType();
// 				if (attrType->CanConvert(type))
// 					attributes.Add(jt);
// 			}
// 		}
// 	}

	//////////////////////////////////////////////////////////////////////////////
// 	void Attribute::AddAtributeToList(List<SharedPtr<Attribute>>& attributeList, Attribute* attribute)
// 	{
// 		SharedPtr<Attribute> store(attribute);
// 		auto type = attribute->GetType();
// 		SharedPtr<AttributeUsage> usage;
// 		_attributeUsages.TryGetValue(type, usage);
// 		if (!usage)
// 		{
// 			usage = GetAttributeUsage(type);
// 			_attributeUsages[type] = usage;
// 			if (usage->IsInherited())
// 				attributeList.Add(store);
// 		}
// 		else if (usage->IsInherited() && usage->IsAllowMultiple())
// 			attributeList.Add(store);
// 	}
// 
// 	void Attribute::AddAtributesToList(List<SharedPtr<Attribute>>& attributeList, List<SharedPtr<Attribute>>& attributes)
// 	{
// 		for (uint i = 0; i < attributes.Count(); i++)
// 			AddAtributeToList(attributeList, attributes[i]);
// 	}
// 
// 	AttributeUsage* Attribute::GetAttributeUsage(const Type* type)
// 	{
// 		for (; type != nullptr; type = type->GetBaseType())
// 		{
// 			auto it = _attributeUsages.Find(type);
// 			if (it != _attributeUsages.End())
// 				return it->second;
// 		}
// 
// 		Debug::LogError("No AttributeUsage Attribute for %s type", type->GetName());
// 		return nullptr;
// 	}
}