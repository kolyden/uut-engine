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
		typedef List<const Attribute*> AttributeList;
		typedef Dictionary<const Type*, AttributeList> AttributesTypes;

		Attribute();
		virtual ~Attribute();

		const Type* GetAttachedType() const;

		static const AttributeList& GetAttributes(const Type* type);

		template<class C> static const AttributeList& GetAttributes()
		{ return GetAttributes(TypeOf<C>()); }
	};
}