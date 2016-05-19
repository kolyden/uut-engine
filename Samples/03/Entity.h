#pragma once
#include <Core/Object.h>
#include <Core/Math/IntVector2.h>
#include <Core/Math/Vector3.h>

namespace uut
{
	class FreeCamera;
	enum class Direction;
	class Graphics;
	class Texture2D;
	class Level;

	class Entity : public Object
	{
	public:
		Entity();

		void SetPosition(const IntVector2& pos);
		const IntVector2& GetPosition() const { return _position; }

		bool Move(Direction dir);

		void SetTexture(Texture2D* texture);
		Texture2D* GetTexture() const { return _texture; }

		void Update(float deltaTime);
		void Draw(Graphics* graphics, FreeCamera* camera) const;

		Level* GetLevel() const { return _level; }

		static Vector3 CalcPosition(const IntVector2& index);

	protected:
		IntVector2 _position;
		SharedPtr<Texture2D> _texture;
		WeakPtr<Level> _level;
		Vector3 _levelPosition;
		float _time;
		bool _moving;
		Vector3 _movingStart;
		Vector3 _movingEnd;

		friend class Level;
	};
}