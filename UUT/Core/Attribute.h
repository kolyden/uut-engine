#pragma once
#include <Core/Object.h>
#include <Core/Collections/Dictionary.h>

namespace uut
{
	class AttributeUsage;

	class Attribute : public Object
	{
		UUT_OBJECT(Attribute, Object)
	public:
		Attribute();
		virtual ~Attribute();

		static void AddAttribute(const Type* type, Attribute* attribute);
		static Attribute* GetAttribute(const Type* type, bool inherit);
		static void GetAttributes(const Type* type, List<Attribute*>& attributes, bool inherit);

		template<typename T>
		static T* GetAttribute(bool inherit) { return static_cast<T*>(GetAttribute(typeof<T>(), inherit)); }

	private:
		static Dictionary<const Type*, List<SharedPtr<Attribute>>> _attributes;
		static Dictionary<const Type*, SharedPtr<AttributeUsage>> _attributeUsages;

		static void AddAtributeToList(List<SharedPtr<Attribute>>& attributeList, Attribute* attribute);
		static void AddAtributesToList(List<SharedPtr<Attribute>>& attributeList, List<SharedPtr<Attribute>>& attributes);
		static AttributeUsage* GetAttributeUsage(const Type* type);		
	};
}