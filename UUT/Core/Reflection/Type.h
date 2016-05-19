#pragma once
#include <Core/Collections/List.h>

namespace uut
{
	class String;
	class MemberInfo;
	class PropertyInfo;
	class Object;
	class ValueType;

	enum class TypeInfo
	{
		Struct,
		Class,
		Enum,
		Property,
		Method,
	};

	class Type
	{
	public:
		using REGFUNC = void(*)(Type*);

		Type(const char* name, const Type* base, REGFUNC regfunc);
		virtual ~Type();

		const char* GetName() const;
		size_t GetHash() const;
		String ToString() const;

// 		bool IsClass() const;
// 		bool IsMethod() const;
// 		bool IsEnum() const;

		void AddMember(MemberInfo* member);
		const List<const MemberInfo*>& GetMembers() const;
		const MemberInfo* FindMember(const String& name) const;
		List<const PropertyInfo*> GetProperties() const;

		const Type* GetBaseType() const;

		bool IsDerived(const Type* from) const;
		bool CanConvert(const Type* to) const;

		bool Convert(const ValueType& source, const Type* resultType, ValueType& result) const;
		template<class C> bool Convert(const ValueType& source, C& result) const
		{ return Convert(source, typeof<C>(), result);}

		virtual size_t GetSize() const = 0;
		virtual void PlacementDtor(void* ptr) const = 0;

		static size_t StringToHast(const char* str);

	protected:
		std::string _name;
		const size_t _hash;
		const Type* _base;
		REGFUNC _regfunc;
// 		TypeInfo _info;
		List<const MemberInfo*> _members;

		void Register();

		friend class Context;
	};

	template<class C>
	class TypeImpl : public Type
	{
	public:
		TypeImpl(const char* name, const Type* base, REGFUNC regfunc)
			: Type(name, base, regfunc)
		{
		}

		TypeImpl(const char* name, REGFUNC regfunc)
			: Type(name, CtorGetBaseType(), regfunc)
		{
		}

		virtual size_t GetSize() const override { return sizeof(C); }
		virtual void PlacementDtor(void* ptr) const override
		{
			static_cast<C*>(ptr)->~C();
		}

	protected:
		static constexpr const Type* CtorGetBaseType()
		{
			return std::is_same<C, typename C::Super>::value ? nullptr : C::Super::GetTypeStatic();
		}
	};

	template<class C>
	static const Type* typeof() {
		return C::GetTypeStatic();
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
	static const Type* GetTypeStatic() { return _GetTypeInternal(); } \
	private: \
	static Type* _GetTypeInternal(); \
	static void _RegisterInternal(Type* internalType); \
	friend class Context;

#define UUT_TYPE_IMPLEMENT(type) \
	UUT_TYPE_IMPLEMENT_EX(type, #type)

#define UUT_TYPE_IMPLEMENT_EX(type, name) \
	Type* type::_GetTypeInternal() \
	{ static TypeImpl<type> type(name, &type::_RegisterInternal); return &type; } \
	void type::_RegisterInternal(Type* internalType)


#define UUT_REGISTER_TYPE(type) Context::RegisterType<type>()

#define UUT_DEFAULT(type, value) \
	template<> static constexpr const type& GetDefault<type>() \
	{ return value; }

#define UUT_VALUE_TYPE(type, value) \
	template<> static const Type* typeof<type>() \
	{ return typeof<value>(); }
}