#pragma once
#include <Core/HashString.h>
#include <Core/String.h>
#include <Core/Ptr.h>
#include "TypeInfo.h"

namespace uut
{
	class Object;
	class ObjectFactory;
	class MemberInfo;
	class FieldInfo;

	class Type
	{
	public:
		using REGFUNC = void(*)();

		Type(TypeInfo info, const HashString& name, const Type* base, REGFUNC regfunc);
		virtual ~Type();

		const HashString& GetName() const;
		String ToString() const;

		TypeInfo GetInfo() const;
		bool IsClass() const;
		bool IsMethod() const;
		bool IsEnum() const;

		const List<const MemberInfo*>& GetMembers() const;
		List<const FieldInfo*> GetFields() const;

		const Type* GetBaseType() const;
		ObjectFactory* GetFactory() const;

		SharedPtr<Object> Create() const;

		bool IsDerived(const Type* from) const;
		bool CanConvert(const Type* to) const;

	protected:
		SharedPtr<ObjectFactory> _factory;
		HashString _name;
		const Type* _base;
		REGFUNC _regfunc;
		TypeInfo _info;
		List<const MemberInfo*> _members;
	};

	template<class C>
	static const Type* typeof()
	{
		return &C::GetTypeInternal();
	}

#define UUT_TYPE(type) typeof<type>()

#define UUT_OBJECT(typeName, parentType) \
	public: \
	typedef typeName ClassName; \
	typedef parentType Super; \
	virtual const uut::Type* GetType() const { return &GetTypeInternal(); } \
	private: \
	static void _RegisterInternal(); \
	static uut::Type& GetTypeInternal(); \
	template<class C> friend const uut::Type* typeof();

#define UUT_OBJECT_IMPLEMENT(type) \
	uut::Type& type::GetTypeInternal() \
	{ static uut::Type t(TypeInfo::Class, #type, typeof<Super>(), &type::_RegisterInternal); return t; } \
	void type::_RegisterInternal()
}