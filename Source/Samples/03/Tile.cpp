#include "Tile.h"
#include <Core/Video/Graphics.h>
#include <Core/Math/Vector2.h>
#include <Core/Video/Vertex.h>
#include <Core/Math/Radian.h>
#include <Core/Math/Degree.h>
#include <Core/Video/Texture2D.h>

namespace uut
{
	SimpleFloorTile::SimpleFloorTile(Texture2D* texture)
		: _texture(texture)
	{
	}

	void SimpleFloorTile::DrawFloor(Graphics* graphics, const Vector3& center, const Color32& color) const
	{
		graphics->SetMaterial(Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::Up),
			Vertex(center + Vector3(-LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Zero),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, +LevelCell::HALF_SIZE), color, Vector2::Right),
			Vertex(center + Vector3(+LevelCell::HALF_SIZE, 0, -LevelCell::HALF_SIZE), color, Vector2::One),
			_texture);
	}

	//////////////////////////////////////////////////////////////////////////////
	SimpleWallTile::SimpleWallTile(Texture2D* texture, bool transparent /* = false */)
		: _texture(texture)
		, _transparent(transparent)
	{
	}

	void SimpleWallTile::DrawWall(Graphics* graphics, const Vector3& center, Direction dir, const Color32& color) const
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
		graphics->SetMaterial(_transparent ? Graphics::MT_TRANSPARENT : Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + rotMat[i].VectorTransform(v0), color, Vector2::Zero),
			Vertex(center + rotMat[i].VectorTransform(v1), color, Vector2::Right),
			Vertex(center + rotMat[i].VectorTransform(v2), color, Vector2::One),
			Vertex(center + rotMat[i].VectorTransform(v3), color, Vector2::Up),
			_texture);
	}
}