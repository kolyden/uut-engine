#include "EditorLevelChunk.h"
#include <Core/Collections/BitArray.h>
#include <Core/Math/Math.h>
#include <Core/Video/Graphics.h>
#include <Core/Video/Texture2D.h>
#include <Core/Math/Vector2.h>
#include <Core/Video/Vertex.h>
#include "Level.h"
#include "Tileset.h"

namespace uut
{
	EditorLevelChunk::EditorLevelChunk(Level* level, const IntVector2& index)
		: LevelChunk(level, index)
	{
		Clear();

		for (int i = 0; i < 4; i++)
		{
			if (!_neighbor[i])
				continue;

			const auto dir = static_cast<Direction>((i + 2) % 4);
			SetNeighbor(dir, _neighbor[i]);
		}
	}

	void EditorLevelChunk::Update(float deltaTime)
	{
		UpdateBitmask();
	}

	void EditorLevelChunk::Draw(Graphics* graphics) const
	{
		if (graphics == nullptr)
			return;

		auto tileset = _level->GetTileset();
// 		static const Direction order[4] = { Direction::North, Direction::East, Direction::South, Direction::West };

		for (int i = 0; i < TOTAL_COUNT; i++)
		{
			const LevelCell& cell = _cells[i];
			if (cell.IsEmpty())
				continue;

			const auto ret = Math::Div(i, COUNT);
			const int x = ret.rem;
			const int y = ret.quot;
			const Vector3 center(
				LevelCell::Size*x + LevelCell::HalfSize + _position.x, _position.y,
				LevelCell::Size*y + LevelCell::HalfSize + _position.z);

			if (cell.IsSolid())
			{
				graphics->SetMaterial(Graphics::MT_OPAQUE);
				DrawFloor(graphics, center + Vector3(0, LevelCell::Size, 0), nullptr, Color32::Black);
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

	LevelChunk* EditorLevelChunk::GetNeighbor(Direction dir) const
	{
		return _neighbor[static_cast<int>(dir)];
	}

	void EditorLevelChunk::SetSolid(const IntVector2& index, int walltile)
	{
		if (index.x < 0 || index.x >= COUNT ||
			index.y < 0 || index.y >= COUNT)
			return;

		const unsigned rawIndex = GetIndex(index.x, index.y);
		_cells[rawIndex].SetSolid(walltile);
		if (index.x > 0 && !_cells[rawIndex - 1].IsSolid())
			_cells[rawIndex - 1].SetWall(Direction::East, walltile);
		if (index.x < COUNT - 1 && !_cells[rawIndex + 1].IsSolid())
			_cells[rawIndex + 1].SetWall(Direction::West, walltile);
		if (index.y > 0 && !_cells[rawIndex - COUNT].IsSolid())
			_cells[rawIndex - COUNT].SetWall(Direction::North, walltile);
		if (index.y < COUNT - 1 && !_cells[rawIndex + COUNT].IsSolid())
			_cells[rawIndex + COUNT].SetWall(Direction::South, walltile);
	}

	void EditorLevelChunk::SetWall(const IntVector2& index, int walltile)
	{
		if (index.x < 0 || index.x >= COUNT ||
			index.y < 0 || index.y >= COUNT)
			return;

		const unsigned rawIndex = GetIndex(index.x, index.y);
		LevelCell& cell = _cells[rawIndex];
		cell.SetFloor(walltile);

		if (index.x > 0 && _cells[rawIndex - 1].IsBlocked())
			cell.SetWall(Direction::West, walltile);
		else cell.SetWall(Direction::West, LevelCell::EmptyTile);

		if (index.x < COUNT - 1 && _cells[rawIndex + 1].IsBlocked())
			cell.SetWall(Direction::East, walltile);
		else cell.SetWall(Direction::East, LevelCell::EmptyTile);

		if (index.y > 0 && _cells[rawIndex - COUNT].IsBlocked())
			cell.SetWall(Direction::South, walltile);
		else cell.SetWall(Direction::South, LevelCell::EmptyTile);

		if (index.y < COUNT - 1 && _cells[rawIndex + COUNT].IsBlocked())
			cell.SetWall(Direction::North, walltile);
		else cell.SetWall(Direction::North, LevelCell::EmptyTile);
	}

	void EditorLevelChunk::Clear()
	{
		for (int i = 0; i < TOTAL_COUNT; i++)
			_cells[i].Clear();
	}

	LevelCell& EditorLevelChunk::GetCell(int x, int y)
	{
		return _cells[GetIndex(x, y)];
	}

	///////////////////////////////////////////////////////////////////////////
	void EditorLevelChunk::DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color)
	{
		graphics->DrawQuad(
			Vertex(center + Vector3(-LevelCell::HalfSize, 0, -LevelCell::HalfSize), color, Vector2::Up),
			Vertex(center + Vector3(-LevelCell::HalfSize, 0, +LevelCell::HalfSize), color, Vector2::Zero),
			Vertex(center + Vector3(+LevelCell::HalfSize, 0, +LevelCell::HalfSize), color, Vector2::Right),
			Vertex(center + Vector3(+LevelCell::HalfSize, 0, -LevelCell::HalfSize), color, Vector2::One),
			texture);
	}

	void EditorLevelChunk::UpdateBitmask()
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

	void EditorLevelChunk::SetNeighbor(Direction dir, EditorLevelChunk* chunk)
	{
		const int index = static_cast<int>(dir);
		_neighbor[index] = chunk;
		if (chunk != nullptr)
			chunk->_neighbor[(index + 4) % 2] = this;
	}
}