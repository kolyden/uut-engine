#pragma once
#include <Core/Math/Matrix4.h>
#include <Core/Module.h>
#include "Topology.h"
#include "Color32.h"
#include "PipelineState.h"

namespace uut
{
	class PipelineState;
	class CommandList;
	class Font;
	class Mesh;
	class Rect;
	class Vector3;
	struct Vertex;
	class Renderer;
	class Texture2D;
	class VertexBuffer;
	class Viewport;

	class Graphics : public Object
	{
		UUT_OBJECT(uut, Graphics, Module)
	public:
		enum ProjectionMode
		{
			PM_NONE,
			PM_2D,
			PM_3D,
		};

		enum MaterialType
		{
			MT_OPAQUE,
			MT_TRANSPARENT,
		};

		Graphics(MaterialType material, ProjectionMode projection, FillMode fillMode = FillMode::Solid);
		virtual ~Graphics();

		void SetViewport(const Viewport& viewport);
		void Clear(const Color32& color = Color32::White, float z = 1.0f, uint32_t stencil = 0);

		void DrawPoint(const Vector3& point, const Color32& color = Color32::White);
		void DrawLine(const Vector3& p0, const Vector3& p1, const Color32& color = Color32::White);
		void DrawPolyLine(const List<Vector3>& points, const Color32& color = Color32::White);

		void DrawSolidTriangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color32& color = Color32::White);
		void DrawTrinagle(const Vertex& v0, const Vertex& v1, const Vertex& v2, const SharedPtr<Texture2D>& texture = nullptr);

		void DrawQuad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3, const SharedPtr<Texture2D>& texture = nullptr);
		void DrawQuad(const Rect& rect, float z = 0.0f, const SharedPtr<Texture2D>& texture = nullptr, const Color32& color = Color32::White);
		void DrawQuad(const Rect& rect, float z, const SharedPtr<Texture2D>& texture, const Rect& texRect, const Color32& color = Color32::White);

		void DrawSolidCube(const Vector3& center, float side, const Color32& color = Color32::White);
		void DrawWireCube(const Vector3& center, float side, const Color32& color = Color32::White);
		void DrawCube(const Vector3& center, float side, const Color32& color = Color32::White, const SharedPtr<Texture2D>& texture = nullptr);

		void DrawMesh(const Matrix4& transform, const SharedPtr<Mesh>& mesh, const SharedPtr<Texture2D>& texture = nullptr);

		void DrawPrimitive(Topology topology, const List<Vertex>& vertexes, const SharedPtr<Texture2D>& texture = nullptr);
		void DrawIndexedPrimitive(Topology topology, const List<Vertex>& vertexes, const List<uint16_t>& indexes, const SharedPtr<Texture2D>& texture = nullptr);

		void PrintText(const Vector2& position, float z, const String& text, Font* font, const Color32& color = Color32::White);

		void BeginRecord();
		void EndRecord();

		void Draw();

	protected:
		ProjectionMode _projection;
		SharedPtr<PipelineState> _renderState;
		SharedPtr<CommandList> _commandList;
		SharedPtr<VertexBuffer> _vbuffer;
		SharedPtr<Texture2D> _texture;

		Vertex* _vertices = nullptr;
		uint _vdxIndex = 0;
		uint _offset = 0;

		uint _vbufCount;

		bool TestBatch(Topology topology, const SharedPtr<Texture2D>& tex, int vrtCount);
		int GetPrimitiveCount(int vertexCount) const;
	};
}