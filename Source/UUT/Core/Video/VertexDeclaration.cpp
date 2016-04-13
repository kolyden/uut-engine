#include "VertexDeclaration.h"

namespace uut
{
	VertexElement::VertexElement()
		: stream(0)
		, offset(0)
		, type(DT_FLOAT1)
		, usage(UT_POSITION)
		, usageIndex(0)
	{}

	VertexElement::VertexElement(DeclareType _type, UsageType _usage, uint16_t _offset)
		: stream(0)
		, offset(_offset)
		, type(_type)
		, usage(_usage)
		, usageIndex(0)
	{}

	UUT_OBJECT_IMPLEMENT(VertexDeclaration)
	{}

	VertexDeclaration::VertexDeclaration()
	{
	}

	VertexDeclaration::~VertexDeclaration()
	{
	}
}