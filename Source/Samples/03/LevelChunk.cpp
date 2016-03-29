#include "LevelChunk.h"
#include "Level.h"
#include <Core/Math/Math.h>
#include <Core/Video/Graphics.h>
#include <Core/Video/Texture2D.h>
#include <Core/Math/Vector2.h>
#include <Core/Video/Vertex.h>
#include <Core/Collections/BitArray.h>
#include "Tileset.h"
#include "Tile.h"

namespace uut
{
	LevelChunk::LevelChunk(Level* level, const IntVector2& index)
		: _level(level)
		, _index(index)
	{
		_position = Vector3(
			LevelCell::SIZE * (index.x * COUNT), 0,
			LevelCell::SIZE * (index.y * COUNT));

		Clear();
	}

	LevelChunk::~LevelChunk()
	{
		for (int i = 0; i < 4; i++)
		{
			if (!_neighbor[i])
				continue;

			const auto dir = static_cast<Direction>((i + 2) % 4);
			SetNeighbor(dir, _neighbor[i]);
		}
	}

	void LevelChunk::Update(float deltaTime)
	{
		UpdateBitmask();
	}

	void LevelChunk::Draw(Graphics* graphics) const
	{
		if (graphics == nullptr)
			return;

		auto tileset = _level->GetTileset();
		static const Direction order[4] = { Direction::North, Direction::East, Direction::South, Direction::West };

		for (int i = 0; i < TOTAL_COUNT; i++)
		{
			const LevelCell& cell = _cells[i];
			const auto ret = Math::Div(i, COUNT);
			const int x = ret.rem;
			const int y = ret.quot;
			const Vector3 center(
				LevelCell::SIZE*x + LevelCell::HALF_SIZE + _position.x, _position.y,
				LevelCell::SIZE*y + LevelCell::HALF_SIZE + _position.z);

			if (cell.IsEmpty())
			{
				graphics->SetMaterial(Graphics::MT_OPAQUE);
				DrawFloor(graphics, center + Vector3(0, LevelCell::SIZE, 0), nullptr, Color32::Black);
				continue;
			}

			if (!cell.IsFloorEmpty())
			{
				auto tile = tileset->GetFloor(cell.floor);
				tile->DrawFloor(graphics, center);
			}

			for (unsigned j = 0; j < 4; j++)
			{
				const Direction dir = static_cast<Direction>(j);
				if (cell.IsWallEmpty(dir))
					continue;

				auto tile = tileset->GetWall(cell.GetWall(dir));
				tile->DrawWall(graphics, center, _wallmask[i], dir);
			}
		}
	}

	void LevelChunk::Clear()
	{
		for (int i = 0; i < TOTAL_COUNT; i++)
			_cells[i].Clear();
	}

	LevelCell& LevelChunk::GetCell(int x, int y)
	{
		return _cells[GetIndex(x, y)];
	}

	const LevelCell& LevelChunk::GetCell(int x, int y) const
	{
		return _cells[GetIndex(x, y)];
	}

	IntVector2 LevelChunk::GetGlobalPos(const IntVector2& localPos) const
	{
		return IntVector2(
			localPos.x + _index.x * COUNT,
			localPos.y + _index.y * COUNT);
	}

	///////////////////////////////////////////////////////////////////////////
	void LevelChunk::UpdateBitmask()
	{
		using bit = BitArray<uint8_t>;

		for (int y = 0; y < COUNT; y++)
		{
			for (int x = 0; x < COUNT; x++)
			{
				uint8_t flag = 0;
				const LevelCell& cell = GetCell(x, y);
				if (!cell.IsWallEmpty(Direction::North))
					bit::Set<1>(flag);

				if (!cell.IsWallEmpty(Direction::West))
					bit::Set<2>(flag);

				if (!cell.IsWallEmpty(Direction::East))
					bit::Set<4>(flag);

				if (!cell.IsWallEmpty(Direction::South))
					bit::Set<8>(flag);

				_wallmask[GetIndex(x, y)] = flag;
			}
		}
	}

	void LevelChunk::ForeachCell(List<LevelCell>::Iterate func)
	{
		for (int i = 0; i < TOTAL_COUNT; i++)
			func(_cells[i]);
	}

	void LevelChunk::ForeachCell(List<LevelCell>::ConstIterate func) const
	{
		for (int i = 0; i < TOTAL_COUNT; i++)
			func(_cells[i]);
	}

	void LevelChunk::SetNeighbor(Direction dir, LevelChunk* chunk)
	{
		const int index = static_cast<int>(dir);
		_neighbor[index] = chunk;
		if (chunk != nullptr)
			chunk->_neighbor[(index + 4) % 2] = this;
	}

	void LevelChunk::DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color)
	{
		graphics->DrawQuad(
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::Up),
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Zero),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Right),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::One),
			texture);
	}

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