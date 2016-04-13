#pragma once
#include "Object.h"

namespace uut
{
#define UUT_MODULE(typeName, parentType) \
	UUT_OBJECT(typeName, parentType)

#define UUT_MODULE_IMPLEMENT(type) \
	UUT_OBJECT_IMPLEMENT(type)

	class Module : public Object
	{
		UUT_OBJECT(Module, Object)
	public:
		Module();
		virtual ~Module();

	protected:
		virtual void OnRegister() {}
		virtual void OnUnregister() {}

		virtual bool OnInit() { return true; }
		virtual void OnDone() {}

		friend class Context;
	};
}