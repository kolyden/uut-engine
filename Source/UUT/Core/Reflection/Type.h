#pragma once
#include <Core/HashString.h>
#include <Core/String.h>
#include <Core/Ptr.h>

namespace uut
{
	class Object;
	class ObjectFactory;
	class MemberInfo;
	class PropertyInfo;

	enum class TypeInfo
	{
		Class,
		Struct,
		Method,
		Enum,
	};

	class Type
	{
	public:
		using REGFUNC = void(*)(Type*);

		Type(TypeInfo info, const HashString& name, const Type* base, REGFUNC regfunc);
		virtual ~Type();

		const HashString& GetName() const;
		String ToString() const;

		TypeInfo GetInfo() const;
		bool IsClass() const;
		bool IsMethod() const;
		bool IsEnum() const;

		void AddMember(MemberInfo* member);
		const List<const MemberInfo*>& GetMembers() const;
		List<const PropertyInfo*> GetFields() const;

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
		return C::__internalType;
	}

#define UUT_TYPE(typeName, parentType) \
	public: \
	typedef typeName ClassName; \
	typedef parentType Super; \
	static const uut::Type* GetType() { return __internalType; } \
	static void _RegisterInternal(Type* internalType); \
	private: \
	static Type* __internalType; \
	template<class C> friend const uut::Type* typeof(); \
	friend class Context;

#define UUT_TYPE_IMPLEMENT(type) \
	Type* type::__internalType = nullptr; \
	void type::_RegisterInternal(Type* internalType)

#define UUT_REGISTER_TYPE(info, type, name) Context::RegisterType<type>(info, name, &type::_RegisterInternal)
}