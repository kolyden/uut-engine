#pragma once
#include <Core/Collections/List.h>
#include <Core/Ptr.h>

namespace uut
{
	class String;
	class IMemberInfo;
	class IPropertyInfo;
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

		Type(const char* library, const char* name, const Type* base, REGFUNC regfunc);
		virtual ~Type();

		const char* GetName() const;
		const char* GetLibrary() const;
		const char* GetFullName() const;

		size_t GetHash() const;
		String ToString() const;

// 		bool IsClass() const;
// 		bool IsMethod() const;
// 		bool IsEnum() const;

		SharedPtr<Object> CreateObject() const;
		template<class C> SharedPtr<C> CreateObject() const { return DynamicCast<C>(CreateObject()); }

		// MEMBERS
		void AddMember(IMemberInfo* member);
		const List<const IMemberInfo*>& GetMembers() const;
		const IMemberInfo* FindMember(const String& name) const;
		List<const IPropertyInfo*> GetProperties() const;

		const Type* GetBaseType() const;

		bool IsDerived(const Type* from) const;
		bool CanConvert(const Type* to) const;
		bool Convert(const ValueType& source, const Type* resultType, ValueType& result) const;

		template<class C> bool IsDerived() const { return IsDerived(TypeOf<C>()); }
		template<class C> bool Convert(const ValueType& source, C& result) const
		{ return Convert(source, TypeOf<C>(), result);}

		virtual size_t GetSize() const = 0;
		virtual void PlacementDtor(void* ptr) const = 0;

		static size_t StringToHast(const char* str);

	protected:
		std::string _name;
		std::string _library;
		std::string _fullname;

		const size_t _hash;
		const Type* _base;
		REGFUNC _regfunc;
		List<const IMemberInfo*> _members;

		void Register();

		friend class Context;
	};

	template<class C>
	class TypeImpl : public Type
	{
	public:
		explicit TypeImpl(const char* library, const char* name, REGFUNC regfunc)
			: Type(library, name, CtorGetBaseType(), regfunc)
		{
		}

		size_t GetSize() const override { return sizeof(C); }

		void PlacementDtor(void* ptr) const override
		{
			static_cast<C*>(ptr)->~C();
		}

	protected:
		static constexpr const Type* CtorGetBaseType()
		{
			return std::is_same<C,		typename C::Super>::value ? nullptr : C::Super::GetTypeStatic();
		}
	};

	template<class C>
	static const Type* TypeOf() {
		return C::GetTypeStatic();
	}

	template<>
	static const Type* TypeOf<void>() {
		return nullptr;
	}

	template<typename T>
	static const T& GetDefault() {
		return T::Default;
	}

#define UUT_BASETYPE(library, typeName, parentType) \
	public: \
	typedef typeName ClassName; \
	typedef parentType Super; \
	static const Type* GetTypeStatic() { return _GetTypeInternal(); } \
	private: \
	static Type* _GetTypeInternal() \
	{ static TypeImpl<typeName> type(_LibraryName(), \
	  #typeName, &typeName::_RegisterInternal); return &type; } \
	static void _RegisterInternal(Type* internalType); \
	static const char* _LibraryName() { return #library; } \
	friend class Context;

#define UUT_BASETYPE_IMPLEMENT(type) \
	void type::_RegisterInternal(Type* internalType)

#define UUT_REGISTER_TYPE(type) Context::RegisterType<type>()

#define UUT_DEFAULT_VALUE(type, value) \
	template<> static const type& GetDefault<type>() \
	{ static type ret(value); return ret; }

#define UUT_TYPEOF_VALUE(type, value) \
	template<> static const Type* TypeOf<type>() \
	{ return TypeOf<value>(); }
}