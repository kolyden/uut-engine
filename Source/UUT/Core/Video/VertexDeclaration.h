#pragma once
#include "Core/Object.h"
#include <vector>

namespace uut
{
	struct VertexElement
	{
		enum DeclareType
		{
			DT_FLOAT1,
			DT_FLOAT2,
			DT_FLOAT3,
			DT_FLOAT4,
			DT_COLOR, // uint32
		};

		enum UsageType
		{
			UT_POSITION,
			UT_NORMAL,
			UT_TEXCOORD,
			UT_COLOR,
		};

		uint16_t stream;
		uint16_t offset;
		DeclareType type;
		UsageType usage;
		uint8_t usageIndex;

		VertexElement() {}
		VertexElement(DeclareType _type, UsageType _usage, uint16_t _offset = 0)
			: stream(0), offset(_offset), type(_type), usage(_usage), usageIndex(0)
		{}
	};

	class VertexDeclaration : public Object
	{
	public:
		virtual uintptr_t GetInternalHandle() const = 0;

		const std::vector<VertexElement>& GetElements() const { return _elements; }

	protected:
		std::vector<VertexElement> _elements;
	};
}