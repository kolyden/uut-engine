#pragma once
#include <Core/Ptr.h>

namespace uut
{
	class Type;
	class Object;

	class ObjectFactory
	{
	public:
		ObjectFactory();
		virtual ~ObjectFactory();

		virtual SharedPtr<Object> Create() = 0;
		virtual const Type* GetType() const = 0;
	};

	//////////////////////////////////////////////////////////////////////////////
	template<class C>
	class BaseObjectFactory : public ObjectFactory
	{
	public:
		virtual SharedPtr<Object> Create() override { return SharedPtr<C>::Make(); }
		virtual const Type* GetType() const override { return TypeOf<C>(); }
	};
}