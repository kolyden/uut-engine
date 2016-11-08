#include "YamlSerializer.h"
#include <Core/Reflection/Type.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Variant.h>

namespace uut
{
	YamlNode YamlSerializer::Serialize(const SharedPtr<YamlFile>& doc, const Object* obj)
	{
		if (obj == nullptr)
			return YamlNode::Empty;

		return SerializeObject(doc, obj->GetType(), *obj);
	}

	YamlNode YamlSerializer::SerializeVariant(const SharedPtr<YamlFile>& doc, const Variant& data)
	{
		switch (data.GetVariantType())
		{
		case VariantType::Fundamental:
			return doc->AddScalar(data.Get<String>());
			break;

		case VariantType::Struct:
			return SerializeObject(doc, data.GetType(), *data.GetStruct());
		}

// 		bool b;
// 		if (data.TryGet(b))
// 			return doc->AddScalar(b ? Boolean::TrueHash.GetData() : Boolean::FalseHash.GetData());
// 
// 		float f;
// 		if (data.TryGet(f))
// 			return doc->AddScalar(std::to_string(f).c_str());
// 
// 		int i;
// 		if (data.TryGet(i))
// 			return doc->AddScalar(std::to_string(i).c_str());
// 
// 		String str;
// 		if (data.TryGet(str))
// 			return doc->AddScalar(str);

		return YamlNode::Empty;
	}

	//////////////////////////////////////////////////////////////////////////
	YamlNode YamlSerializer::SerializeObject(const SharedPtr<YamlFile>& doc, const Type* type, const BaseObject& obj)
	{
		auto root = doc->AddMapping(YAML_BLOCK_MAPPING_STYLE);

		for (auto prop : type->GetProperties())
		{
			if (!prop->CanSet())
				continue;

			const auto& attrs = prop->GetAttributes();
			if (attrs.HasFlag(FieldAttribute::NotSerialized))
				continue;

			Variant data = prop->GetValue(&obj);
			if (data.IsEmpty())
				continue;

			auto& name = prop->GetName();
			root.AppendMapping(name,
				SerializeVariant(doc, data));
		}

		return root;
	}
}