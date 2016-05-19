#include "Entity.h"
#include <Core/Video/Graphics.h>
#include <Core/Video/Vertex.h>
#include <Core/Video/Texture2D.h>
#include <Core/Video/FreeCamera.h>
#include "Level.h"
#include "LevelChunk.h"
#include "LevelCell.h"

namespace uut
{
	Entity::Entity()
		: _position(IntVector2::Zero)
		, _levelPosition(CalcPosition(_position))
		, _time(0)
		, _moving(false)
	{
	}

	void Entity::SetPosition(const IntVector2& pos)
	{
		if (_position == pos)
			return;

		_moving = false;
		_position = pos;
		_levelPosition = CalcPosition(_position);
	}

	bool Entity::Move(Direction dir)
	{
		if (_moving || !_level)
			return false;

		static const IntVector2 delta[4] =
		{
			+IntVector2::Up, +IntVector2::Right,
			-IntVector2::Up, -IntVector2::Right,
		};

		IntVector2 cellPos;
		auto chunk = _level->FindChunkAt(_position, &cellPos);
		if (chunk == nullptr)
			return false;

		auto& cell = chunk->GetCell(cellPos);
		if (cell.IsBlocked(dir, _level->GetTileset()))
			return false;

		const IntVector2 newPos = _position + delta[static_cast<int>(dir)];
		chunk = _level->FindChunkAt(newPos, &cellPos);
		if (chunk == nullptr)
			return false;

		if (chunk->GetCell(cellPos).IsBlocked())
			return false;

		_moving = true;
		_time = 0;
		_position = newPos;

		_movingStart = _levelPosition;
		_movingEnd = CalcPosition(_position);
		return true;
	}

	void Entity::SetTexture(Texture2D* texture)
	{
		_texture = texture;
	}

	void Entity::Update(float deltaTime)
	{
		if (!_moving)
			return;

		static const float moveTime = 0.2f;

		_time += deltaTime;
		if (_time >= moveTime)
		{
			_levelPosition = _movingEnd;
			_moving = false;
		}
		else
		{
			const float t = _time / moveTime;
			_levelPosition = Vector3::Lerp(_movingStart, _movingEnd, t);
		}
	}

	void Entity::Draw(Graphics* graphics, FreeCamera* camera) const
	{
		if (_texture == nullptr || graphics == nullptr)
			return;

		static const float size = LevelCell::Size * 0.6f;
		static const float hsize = size / 2;

// 		static const Vector3 v0(-hsize, 0, 0);
// 		static const Vector3 v1(-hsize, size, 0);
// 		static const Vector3 v2(+hsize, size, 0);
// 		static const Vector3 v3(+hsize, 0, 0);

		graphics->SetMaterial(Graphics::MT_TRANSPARENT);

// 		graphics->DrawQuad(
// 			Vertex(_levelPosition + v0, Vector2::Up),
// 			Vertex(_levelPosition + v1, Vector2::Zero),
// 			Vertex(_levelPosition + v2, Vector2::Right),
// 			Vertex(_levelPosition + v3, Vector2::One),
// 			_texture);

		const auto center = _levelPosition + Vector3(0, LevelCell::HalfSize, 0);
		const auto right = camera->GetRight() / 2;
		const auto up = camera->GetUp() / 2;

		graphics->DrawQuad(
			Vertex(center + size* up - size* right, Vector2::Zero),
			Vertex(center + size* up + size* right, Vector2::Right),
			Vertex(center - size* up + size* right, Vector2::One),
			Vertex(center - size* up - size* right, Vector2::Up),
			_texture);
	}

	Vector3 Entity::CalcPosition(const IntVector2& index)
	{
		return Vector3(
			LevelCell::Size * index.x + LevelCell::HalfSize, 0,
			LevelCell::Size * index.y + LevelCell::HalfSize);
	}
}
