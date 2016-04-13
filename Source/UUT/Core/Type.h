#pragma once
#include "HashString.h"
#include "Ptr.h"

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

#define UUT_OBJECT(typeName, parentType) \
	public: \
	typedef typeName ClassName; \
	typedef parentType Super; \
	virtual const Type* GetType() const; \
	private: \
	static void _RegisterInternal(); \
	static Type& GetTypeInternal();

#define UUT_OBJECT_IMPLEMENT(type) \
	Type& type::GetTypeInternal() \
	{ static Type t(#type, nullptr, &type::_RegisterInternal); return t; } \
	const Type* type::GetType() const { return &GetTypeInternal(); } \
	void type::_RegisterInternal()
}