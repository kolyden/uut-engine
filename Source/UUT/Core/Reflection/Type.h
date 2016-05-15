#pragma once
#include <Core/Collections/List.h>

namespace uut
{
	class String;
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

		Type(TypeInfo info, const char* name, const Type* base, REGFUNC regfunc, size_t size);
		virtual ~Type();

		const char* GetName() const;
		size_t GetHash() const;
		String ToString() const;

		TypeInfo GetInfo() const;
		size_t GetSize() const;
		bool IsClass() const;
		bool IsMethod() const;
		bool IsEnum() const;

		void AddMember(MemberInfo* member);
		const List<const MemberInfo*>& GetMembers() const;
		const MemberInfo* FindMember(const String& name) const;
		List<const PropertyInfo*> GetProperties() const;

		const Type* GetBaseType() const;

		bool IsDerived(const Type* from) const;
		bool CanConvert(const Type* to) const;

	protected:
		std::string _name;
		const size_t _hash;
		const Type* _base;
		REGFUNC _regfunc;
		TypeInfo _info;
		size_t _size;
		List<const MemberInfo*> _members;
	};

	template<class C>
	static const Type* typeof() {
		return C::__internalType;
	}

	template<>
	static const Type* typeof<void>() {
		return nullptr;
	}

	template<typename T>
	static constexpr const T& GetDefault() {
		return T::Default;
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

#define UUT_DEFAULT(type, value) \
	template<> static constexpr const type& GetDefault<type>() \
	{ return value; }

#define UUT_VALUE_TYPE(type, value) \
	template<> static const Type* typeof<type>() \
	{ return typeof<value>(); }
}