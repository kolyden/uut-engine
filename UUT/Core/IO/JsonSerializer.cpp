#include "JsonSerializer.h"
#include <Core/Reflection/Type.h>
#include <Core/Reflection/PropertyInfo.h>
#include <Core/Variant.h>

namespace uut
{
	bool JsonSerializer::Serialize(const Object* obj, JsonNode& node)
	{
		if (obj == nullptr)
			return false;

		return InternalSerialize(obj->GetType(), *obj, node);
	}

	//////////////////////////////////////////////////////////////////////////
	bool JsonSerializer::InternalSerialize(const Type* type, const BaseObject& obj, JsonNode& node)
	{
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
			switch (data.GetVariantType())
			{
			case VariantType::Fundamental:
				SerializeVariant(data, node);
				continue;
			}
		}

		return true;
	}

	bool JsonSerializer::SerializeVariant(const Variant& data, JsonNode& node)
	{
		bool b;
		if (data.TryGet(b))
		{
			return true;
		}

		float f;
		if (data.TryGet(f))
		{
			return true;
		}

		int i;
		if (data.TryGet(i))
		{
			return true;
		}

		String str;
		if (data.TryGet(str))
		{
			return true;
		}

		return false;
	}
}