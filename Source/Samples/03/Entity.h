#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector2.h>

namespace uut
{
	enum class Direction;
	class Graphics;
	class Texture2D;

	class Entity : public Object
	{
	public:
		Entity();

		void SetPosition(const IntVector2& pos);
		const IntVector2& GetPosition() const { return _position; }

		void Move(Direction dir);

		void SetTexture(Texture2D* texture);
		Texture2D* GetTexture() const { return _texture; }

		void Update(float deltaTime);
		void Draw(Graphics* graphics) const;

	protected:
		IntVector2 _position;
		SharedPtr<Texture2D> _texture;
	};
}