#pragma once
#include "JSONFile.h"
#include <Core/Variant.h>

namespace uut
{
	class JsonSerializer
	{
	public:
		static bool Serialize(const Object* obj, JsonNode& node);

	protected:
		static bool InternalSerialize(const Type* type, const BaseObject& obj, JsonNode& node);
		static bool SerializeVariant(const Variant& data, JsonNode& node);
	};
}