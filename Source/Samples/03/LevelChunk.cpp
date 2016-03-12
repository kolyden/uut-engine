#include "LevelChunk.h"
#include "Level.h"
#include <Core/Math/Math.h>
#include <Core/Video/Graphics.h>
#include "Tileset.h"
#include <Core/Math/Vector2.h>
#include <Core/Video/Vertex.h>

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

	void LevelChunk::Update(float deltaTime)
	{
	}

	void LevelChunk::Draw(Graphics* graphics) const
	{
		if (graphics == nullptr)
			return;

		auto tileset = _level->GetTileset();

		for (int i = 0; i < TOTAL_COUNT; i++)
		{
			const LevelCell& cell = _cells[i];
			if (cell.type == CellType::Empty)
				continue;

			const auto ret = Math::Div(i, COUNT);
			const int x = ret.rem;
			const int y = ret.quot;
			const Vector3 center(
				LevelCell::SIZE*x + LevelCell::HALF_SIZE + _position.x, _position.y,
				LevelCell::SIZE*y + LevelCell::HALF_SIZE + _position.z);
			static const Direction order[4] = { Direction::North, Direction::East, Direction::South, Direction::West };

			switch (cell.type)
			{
			case CellType::Solid:
				if (!cell.IsFloorEmpty())
				{
					auto& tile = tileset->GetFloor(cell.floor);
					DrawFloor(graphics, tile, center + Vector3(0, LevelCell::SIZE, 0));
				}

				for (int j = 0; j < 4; j++)
				{
					const Direction dir = order[j];
					if (cell.IsWallEmpty(dir))
						continue;

					auto& tile = tileset->GetWall(cell.GetWall(dir));
					DrawSolidWall(graphics, tile, center, dir);
				}
				break;

			case CellType::Normal:

				if (!cell.IsFloorEmpty())
				{
					auto& tile = tileset->GetFloor(cell.floor);
					DrawFloor(graphics, tile, center);
				}


				for (int j = 0; j < 4; j++)
				{
					const Direction dir = order[j];
					if (cell.IsWallEmpty(dir))
						continue;

					auto& tile = tileset->GetWall(cell.GetWall(dir));
					DrawWall(graphics, tile, center, dir);
				}
				break;
			}
		}
	}

	void LevelChunk::Clear()
	{
		for (int i = 0; i < TOTAL_COUNT; i++)
			_cells[i].Clear();
	}

	///////////////////////////////////////////////////////////////////////////
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

	void LevelChunk::DrawFloor(Graphics* graphics, const FloorTile& tile, const Vector3& center)
	{
		graphics->SetMaterial(Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), Vector2::Up),
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), Vector2::Zero),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), Vector2::Right),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), Vector2::One),
			tile.texture);
	}

	void LevelChunk::DrawSolidWall(Graphics* graphics, const WallTile& tile, const Vector3& center, Direction dir)
	{
		static const Matrix4 rotMat[4] =
		{
			Matrix4::RotationY(Degree(180)),
			Matrix4::RotationY(Degree(270)),
			Matrix4::Identity,
			Matrix4::RotationY(Degree(90)),
		};

		static const Vector3 v0(-LevelCell::HALF_SIZE, LevelCell::SIZE, -LevelCell::HALF_SIZE);
		static const Vector3 v1(+LevelCell::HALF_SIZE, LevelCell::SIZE, -LevelCell::HALF_SIZE);
		static const Vector3 v2(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE);
		static const Vector3 v3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE);

		const int i = static_cast<int>(dir);
		graphics->SetMaterial(Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + rotMat[i].VectorTransform(v0), Vector2::Zero),
			Vertex(center + rotMat[i].VectorTransform(v1), Vector2::Right),
			Vertex(center + rotMat[i].VectorTransform(v2), Vector2::One),
			Vertex(center + rotMat[i].VectorTransform(v3), Vector2::Up),
			tile.texture);
	}

	void LevelChunk::DrawWall(Graphics* graphics, const WallTile& tile, const Vector3& center, Direction dir)
	{
		static const Matrix4 rotMat[4] =
		{
			Matrix4::RotationY(Degree(180)),
			Matrix4::RotationY(Degree(270)),
			Matrix4::Identity,
			Matrix4::RotationY(Degree(90)),
		};

		static const Vector3 v0(-LevelCell::HALF_SIZE, LevelCell::SIZE, -LevelCell::HALF_SIZE);
		static const Vector3 v1(+LevelCell::HALF_SIZE, LevelCell::SIZE, -LevelCell::HALF_SIZE);
		static const Vector3 v2(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE);
		static const Vector3 v3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE);

		const int i = static_cast<int>(dir);
		graphics->SetMaterial(Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + rotMat[i].VectorTransform(v0), Vector2::Zero),
			Vertex(center + rotMat[i].VectorTransform(v1), Vector2::Right),
			Vertex(center + rotMat[i].VectorTransform(v2), Vector2::One),
			Vertex(center + rotMat[i].VectorTransform(v3), Vector2::Up),
			tile.texture);
	}
}