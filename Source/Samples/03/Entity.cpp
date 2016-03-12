#include "Entity.h"
#include <Core/Video/Graphics.h>
#include <Core/Video/Vertex.h>
#include "LevelCell.h"
#include <Core/Video/Texture2D.h>

namespace uut
{
	Entity::Entity()
	{
	}

	void Entity::SetPosition(const IntVector2& pos)
	{
		_position = pos;
	}

	void Entity::Move(Direction dir)
	{
		static const IntVector2 delta[4] =
		{
			+IntVector2::AXIS_Y, +IntVector2::AXIS_X,
			-IntVector2::AXIS_Y, -IntVector2::AXIS_X,
		};

		SetPosition(GetPosition() + delta[static_cast<int>(dir)]);
	}

	void Entity::SetTexture(Texture2D* texture)
	{
		_texture = texture;
	}

	void Entity::Update(float deltaTime)
	{
	}

	void Entity::Draw(Graphics* graphics) const
	{
		if (_texture == nullptr || graphics == nullptr)
			return;

		static const Vector3 v0(-LevelCell::HALF_SIZE, 0, 0);
		static const Vector3 v1(-LevelCell::HALF_SIZE, LevelCell::SIZE, 0);
		static const Vector3 v2(+LevelCell::HALF_SIZE, LevelCell::SIZE, 0);
		static const Vector3 v3(+LevelCell::HALF_SIZE, 0, 0);

		const Vector3 offset(
			LevelCell::SIZE * _position.x + LevelCell::HALF_SIZE, 0,
			LevelCell::SIZE * _position.y + LevelCell::HALF_SIZE);

		graphics->SetMaterial(Graphics::MT_TRANSPARENT);
		graphics->DrawQuad(
			Vertex(v0 + offset, Vector2::AXIS_Y),
			Vertex(v1 + offset, Vector2::ZERO),
			Vertex(v2 + offset, Vector2::AXIS_X),
			Vertex(v3 + offset, Vector2::ONE),
			_texture);
	}
}