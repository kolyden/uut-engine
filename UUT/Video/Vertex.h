#pragma once
#include <Core/Collections/List.h>
#include <Core/Math/Vector3.h>
#include <Core/Math/Vector2.h>
#include <Video/Color32.h>
#include "VertexDeclaration.h"

namespace uut
{
	struct Vertex
	{
		Vector3 pos;
		uint32_t color;
		Vector2 tex;

		Vertex();
		explicit Vertex(const Vector3& pos);
		Vertex(const Vector3& pos, const Color32& color);
		Vertex(const Vector3& pos, const Vector2& tex);
		Vertex(const Vector3& pos, const Color32& color, const Vector2& tex);

		static const Vertex EMPTY;
		static const uint16_t SIZE;
		static const List<VertexElement> DECLARE;
	};
}