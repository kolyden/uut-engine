#pragma once
#include <Core/Collections/List.h>

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
			DT_DWORD, // uint32
			DT_UBYTE4,
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

		VertexElement();
		VertexElement(DeclareType _type, UsageType _usage, uint16_t _offset = 0);
	};
}