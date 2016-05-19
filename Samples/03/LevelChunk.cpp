#include "LevelChunk.h"
#include "Level.h"

namespace uut
{
	LevelChunk::LevelChunk(Level* level, const IntVector2& index)
		: _level(level)
		, _index(index)
	{
		_position = Vector3(
			LevelCell::Size * (index.x * COUNT), 0,
			LevelCell::Size * (index.y * COUNT));
	}

	LevelChunk::~LevelChunk()
	{

	}

	const LevelCell& LevelChunk::GetCell(int x, int y) const
	{
		return _cells[GetIndex(x, y)];
	}

	IntVector2 LevelChunk::GetGlobalPos(int x, int y) const
	{
		return IntVector2(
			x + _index.x * COUNT,
			y + _index.y * COUNT);
	}

	IntVector2 LevelChunk::GetGlobalPos(const IntVector2& localPos) const
	{
		return IntVector2(
			localPos.x + _index.x * COUNT,
			localPos.y + _index.y * COUNT);
	}

	///////////////////////////////////////////////////////////////////////////
// 	void LevelChunk::DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color)
// 	{
// 		graphics->DrawQuad(
// 			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::Up),
// 			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Zero),
// 			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Right),
// 			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::One),
// 			texture);
// 	}

// 	void LevelChunk::DrawWall(Graphics* graphics, const Vector3& center, Direction dir, Texture2D* texture, const Color32& color)
// 	{
// 		static const Matrix4 rotMat[4] =
// 		{
// 			Matrix4::Identity,
// 			Matrix4::RotationY(Degree(90)),
// 			Matrix4::RotationY(Degree(180)),
// 			Matrix4::RotationY(Degree(270)),
// 		};
// 
// 		static const Vector3 v0(-LevelCell::HALF_SIZE, LevelCell::SIZE, +LevelCell::HALF_SIZE);
// 		static const Vector3 v1(+LevelCell::HALF_SIZE, LevelCell::SIZE, +LevelCell::HALF_SIZE);
// 		static const Vector3 v2(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE);
// 		static const Vector3 v3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE);
// 
// 		const int i = static_cast<int>(dir);
// 		graphics->DrawQuad(
// 			Vertex(center + rotMat[i].VectorTransform(v0), color, Vector2::Zero),
// 			Vertex(center + rotMat[i].VectorTransform(v1), color, Vector2::Right),
// 			Vertex(center + rotMat[i].VectorTransform(v2), color, Vector2::One),
// 			Vertex(center + rotMat[i].VectorTransform(v3), color, Vector2::Up),
// 			texture);
// 	}
}