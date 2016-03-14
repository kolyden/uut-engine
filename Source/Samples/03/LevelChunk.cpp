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

			static const Direction order[4] = { Direction::North, Direction::East, Direction::South, Direction::West };
			if (!cell.IsFloorEmpty())
			{
				auto& tile = tileset->GetFloor(cell.floor);
				graphics->SetMaterial(Graphics::MT_OPAQUE);
				DrawFloor(graphics, center, tile.texture, Color32::White);
			}

			for (int j = 0; j < 4; j++)
			{
				const Direction dir = order[j];
				if (cell.IsWallEmpty(dir))
					continue;

				auto& tile = tileset->GetWall(cell.GetWall(dir));
				graphics->SetMaterial(tile.alpha ? Graphics::MT_TRANSPARENT : Graphics::MT_OPAQUE);
				DrawWall(graphics, center, dir, tile.texture, Color32::White);
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

	void LevelChunk::DrawFloor(Graphics* graphics, const Vector3& center, Texture2D* texture, const Color32& color)
	{
		graphics->DrawQuad(
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::Up),
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Zero),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Right),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::One),
			texture);
	}

	void LevelChunk::DrawWall(Graphics* graphics, const Vector3& center, Direction dir, Texture2D* texture, const Color32& color)
	{
		static const Matrix4 rotMat[4] =
		{
			Matrix4::Identity,
			Matrix4::RotationY(Degree(90)),
			Matrix4::RotationY(Degree(180)),
			Matrix4::RotationY(Degree(270)),
		};

		static const Vector3 v0(-LevelCell::HALF_SIZE, LevelCell::SIZE, +LevelCell::HALF_SIZE);
		static const Vector3 v1(+LevelCell::HALF_SIZE, LevelCell::SIZE, +LevelCell::HALF_SIZE);
		static const Vector3 v2(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE);
		static const Vector3 v3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE);

		const int i = static_cast<int>(dir);
		graphics->DrawQuad(
			Vertex(center + rotMat[i].VectorTransform(v0), color, Vector2::Zero),
			Vertex(center + rotMat[i].VectorTransform(v1), color, Vector2::Right),
			Vertex(center + rotMat[i].VectorTransform(v2), color, Vector2::One),
			Vertex(center + rotMat[i].VectorTransform(v3), color, Vector2::Up),
			texture);
	}
}