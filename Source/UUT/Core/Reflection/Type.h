#pragma once
#include <Core/HashString.h>
#include <Core/String.h>
#include <Core/Ptr.h>

namespace uut
{
	class Object;
	class ObjectFactory;

	class Type
	{
	public:
		using REGFUNC = void(*)();

		Type(const HashString& name, const Type* base, REGFUNC regfunc);
		virtual ~Type();

		const HashString& GetName() const;
		String ToString() const;

		const Type* GetBase() const;
		ObjectFactory* GetFactory() const;

		SharedPtr<Object> Create() const;

		bool IsDerived(const Type* from) const;
		bool CanConvert(const Type* to) const;

	protected:
		SharedPtr<ObjectFactory> _factory;
		HashString _name;
		const Type* _base;
		REGFUNC _regfunc;
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
	virtual const Type* GetType() const; \
	private: \
	static void _RegisterInternal(); \
	static Type& GetTypeInternal(); \
	template<class C> friend const Type* typeof();

#define UUT_OBJECT_IMPLEMENT(type) \
	Type& type::GetTypeInternal() \
	{ static Type t(#type, nullptr, &type::_RegisterInternal); return t; } \
	const Type* type::GetType() const { return &GetTypeInternal(); } \
	void type::_RegisterInternal()
}
