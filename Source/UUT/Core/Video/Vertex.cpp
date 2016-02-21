#include "Vertex.h"

namespace uut
{
	const Vertex Vertex::EMPTY;
	const uint16_t Vertex::SIZE = sizeof(Vertex);

	const List<VertexElement> Vertex::DECLARE = {
		VertexElement(VertexElement::DT_FLOAT3, VertexElement::UT_POSITION),
		VertexElement(VertexElement::DT_DWORD, VertexElement::UT_COLOR, offsetof(Vertex, color)),
		VertexElement(VertexElement::DT_FLOAT2, VertexElement::UT_TEXCOORD, offsetof(Vertex, tex)),
	};

	Vertex::Vertex()
	{
	}

	Vertex::Vertex(const Vector3& _pos)
		: pos(_pos), color(0xFFFFFFFF)
	{
	}

	Vertex::Vertex(const Vector3& _pos, const Color32& _color)
		: pos(_pos), color(_color.ToInt())
	{
	}

	Vertex::Vertex(const Vector3& _pos, const Vector2& _tex)
		: pos(_pos), color(0xFFFFFFFF), tex(_tex)
	{
	}

	Vertex::Vertex(const Vector3& _pos, const Color32& _color, const Vector2& _tex)
		: pos(_pos), color(_color.ToInt()), tex(_tex)
	{
	}
}