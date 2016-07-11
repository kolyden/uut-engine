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

// 		static Attribute* GetAttribute(const Type* type, bool inherit);
// 		static void GetAttributes(const Type* type, List<Attribute*>& attributes, bool inherit);
// 		
// 		template<typename T>
// 		static void AddAttribute(Attribute* attribute) { AddAttribute(typeof<T>(), attribute); }
// 
// 		template<typename T>
// 		static T* GetAttribute(bool inherit) { return static_cast<T*>(GetAttribute(typeof<T>(), inherit)); }	
	};
}