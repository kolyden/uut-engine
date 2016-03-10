#pragma once
#include "Core/Object.h"
#include "Topology.h"
#include "Color32.h"
#include "RenderState.h"

namespace uut
{
	class Rect;
	class Vector3;
	struct Vertex;
	class Renderer;
	class Texture2D;
	class VertexBuffer;
	class VertexDeclaration;

	class Graphics : public Object
	{
	public:
		explicit Graphics(Renderer* renderer);

		void DrawPoint(const Vector3& point, const Color32& color = Color32::WHITE);
		void DrawLine(const Vector3& p0, const Vector3& p1, const Color32& color = Color32::WHITE);

		void DrawSolidTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color32& color = Color32::WHITE);
		void DrawTrinagle(const Vertex& v0, const Vertex& v1, const Vertex& v2, Texture2D* texture = nullptr);

		void DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, Texture2D* texture = nullptr);
		void DrawQuad(const Rect& rect, float z = 0.0f, Texture2D* texture = nullptr, const Color32& color = Color32::WHITE);

		void DrawSolidCube(const Vector3& center, float side, const Color32& color = Color32::WHITE);
		void DrawCube(const Vector3& center, float side, const Color32& color = Color32::WHITE, Texture2D* texture = nullptr);

		void Flush();

	protected:
		SharedPtr<Renderer> _renderer;
		SharedPtr<VertexBuffer> _vbuf;
		SharedPtr<VertexDeclaration> _vdec;

		int _vbufCount;

		Topology _topology;
		SharedPtr<Texture2D> _texture;
		Vertex* _vertices;
		int _vdxIndex;
		RenderState _renderState;

		void TestBatch(Topology topology, Texture2D* tex, int vrtCount);
		void DrawAll();
	};
}
