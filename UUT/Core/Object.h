#pragma once
#include <Core/BaseObject.h>
#include <Core/IEquatable.h>
#include <Core/String.h>
#include <Core/Ptr.h>

namespace uut
{
#define UUT_OBJECT(library, typeName, parentType) \
	UUT_BASETYPE(library, typeName, parentType) \
	public: \
	virtual const Type* GetType() const { return GetTypeStatic(); } \
	SharedPtr<ClassName> GetSharedThis() { return DynamicCast<ClassName>(GetThisObject()); } \
	private:

#define UUT_OBJECT_IMPLEMENT(type) \
	UUT_BASETYPE_IMPLEMENT(type)

	class Object : public BaseObject, public IEquatable, public std::enable_shared_from_this<Object>
	{
		UUT_OBJECT(uut, Object, BaseObject)
	public:
		virtual ~Object() {}

		virtual bool Equals(const Object* obj) const override;
		virtual String ToString();

		SharedPtr<Object> GetThisObject() { return shared_from_this(); }
	};
}