#pragma once
#include <Core/Collections/List.h>
#include <Core/Ptr.h>
#include <Core/Collections/Dictionary.h>

namespace uut
{
	class Attribute;
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
		typedef List<SharedPtr<Attribute>> AttributeList;
		using REGFUNC = void(*)(Type*);

		Type(const char* name, const Type* base, REGFUNC regfunc, const char* filename);
		virtual ~Type();

		const char* GetName() const;
		const char* GetNamespace() const;
		const char* GetFullName() const;

		size_t GetHash() const;
		String ToString() const;

// 		bool IsClass() const;
// 		bool IsMethod() const;
// 		bool IsEnum() const;

		SharedPtr<Object> CreateObject() const;
		template<class C> SharedPtr<C> CreateObject() const { return DynamicCast<C>(CreateObject()); }

		// ATTRIBUTES
		bool AddAttribute(const SharedPtr<Attribute>& attr);
		const Attribute* FindAttribute(const Type* type) const;
		size_t FindAttributes(const Type* type, List<const Attribute*>& list) const;
		List<const Attribute*> FindAttributes(const Type* type) const;
		const AttributeList& GetAttributes() const { return _attributes; }

		template<class C> const C* FindAttribute() const
		{ return static_cast<const C*>(FindAttribute(TypeOf<C>())); }

		// MEMBERS
		void AddMember(MemberInfo* member);
		const List<const MemberInfo*>& GetMembers() const;
		const MemberInfo* FindMember(const String& name) const;
		List<const PropertyInfo*> GetProperties() const;

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
		std::string _namespace;
		std::string _fullname;

		const size_t _hash;
		const Type* _base;
		REGFUNC _regfunc;
		List<const MemberInfo*> _members;
		AttributeList _attributes;

		void Register();

		static std::string GetNamespaceFromFile(const char* filename);
		static std::string CreateFullName(const std::string& namesp, const std::string& name);

		friend class Context;
	};

	template<class C>
	class TypeImpl : public Type
	{
	public:
		TypeImpl(const char* name, const Type* base, REGFUNC regfunc, const char* filename)
			: Type(name, base, regfunc, filename)
		{
		}

		TypeImpl(const char* name, REGFUNC regfunc, const char* filename)
			: Type(name, CtorGetBaseType(), regfunc, filename)
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
			return std::is_same<C, typename C::Super>::value ? nullptr : C::Super::GetTypeStatic();
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

#define UUT_BASETYPE(typeName, parentType) \
	public: \
	typedef typeName ClassName; \
	typedef parentType Super; \
	static const Type* GetTypeStatic() { return _GetTypeInternal(); } \
	private: \
	static Type* _GetTypeInternal(); \
	static void _RegisterInternal(Type* internalType); \
	friend class Context;

#define UUT_BASETYPE_IMPLEMENT(type) \
	UUT_BASETYPE_IMPLEMENT_EX(type, #type)

#define UUT_BASETYPE_IMPLEMENT_EX(type, name) \
	Type* type::_GetTypeInternal() \
	{ static TypeImpl<type> type(name, &type::_RegisterInternal, __FILE__); return &type; } \
	void type::_RegisterInternal(Type* internalType)

#define UUT_REGISTER_TYPE(type) Context::RegisterType<type>()

#define UUT_DEFAULT(type, value) \
	template<> static const type& GetDefault<type>() \
	{ static type ret(value); return ret; }

#define UUT_VALUE_TYPE(type, value) \
	template<> static const Type* TypeOf<type>() \
	{ return TypeOf<value>(); }
}