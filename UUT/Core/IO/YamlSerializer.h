#pragma once
#include "YamlFile.h"

namespace uut
{
	class YamlSerializer
	{
	public:
		static YamlNode Serialize(const SharedPtr<YamlFile>& doc, const Object* obj);
		static YamlNode SerializeVariant(const SharedPtr<YamlFile>& doc, const Variant& data);

		template<typename T>
		static YamlNode Serialize(const SharedPtr<YamlFile>& doc, const T& value)
		{
			return SerializeObject(doc, TypeOf<T>(), value);
		}

	protected:
		static YamlNode SerializeObject(const SharedPtr<YamlFile>& doc, const Type* type, const BaseObject& obj);
	};
}