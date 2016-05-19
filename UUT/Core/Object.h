#pragma once
#include <Core/BaseObject.h>
#include <Core/IEquatable.h>
#include <Core/String.h>
#include <Core/Ptr.h>

namespace uut
{
#define UUT_OBJECT(typeName, parentType) \
	UUT_TYPE(typeName, parentType) \
	public: \
	virtual const Type* GetType() const { return GetTypeStatic(); } \
	private:

#define UUT_OBJECT_IMPLEMENT(type) \
	UUT_TYPE_IMPLEMENT(type)

	class Object : public BaseObject, public IEquatable, public RefCounted
	{
		UUT_OBJECT(Object, BaseObject)
	public:
		virtual ~Object() {}

		virtual bool Equals(const Object* obj) const override;
		virtual String ToString();
	};
}