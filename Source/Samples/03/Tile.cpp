#include "Tile.h"
#include <Core/Video/Graphics.h>
#include <Core/Math/Vector2.h>
#include <Core/Video/Vertex.h>
#include <Core/Math/Degree.h>
#include <Core/Video/Texture2D.h>

namespace uut
{
	SimpleFloorTile::SimpleFloorTile(Texture2D* texture)
		: _texture(texture)
	{
	}

	void SimpleFloorTile::DrawFloor(Graphics* graphics, const Vector3& center) const
	{
		static const Color32 color = Color32::White;

		graphics->SetMaterial(Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + Vector3(-LevelCell::HalfSize, 0, -LevelCell::HalfSize), color, Vector2::Up),
			Vertex(center + Vector3(-LevelCell::HalfSize, 0, +LevelCell::HalfSize), color, Vector2::Zero),
			Vertex(center + Vector3(+LevelCell::HalfSize, 0, +LevelCell::HalfSize), color, Vector2::Right),
			Vertex(center + Vector3(+LevelCell::HalfSize, 0, -LevelCell::HalfSize), color, Vector2::One),
			_texture);
	}

	//////////////////////////////////////////////////////////////////////////////
	SimpleWallTile::SimpleWallTile(Texture2D* texture, bool transparent /* = false */)
		: _texture(texture)
		, _transparent(transparent)
	{
	}

	void SimpleWallTile::DrawWall(Graphics* graphics, const Vector3& center, uint8_t bitmask, Direction dir) const
	{
		static const Color32 color = Color32::White;
		static const Matrix4 rotMat[4] =
		{
			Matrix4::Identity,
			Matrix4::RotationY(Degree(90)),
			Matrix4::RotationY(Degree(180)),
			Matrix4::RotationY(Degree(270)),
		};

		static const Vector3 v0(-LevelCell::HalfSize, LevelCell::Size, LevelCell::HalfSize - LevelCell::WallSize);
		static const Vector3 v1(+LevelCell::HalfSize, LevelCell::Size, LevelCell::HalfSize - LevelCell::WallSize);
		static const Vector3 v2(+LevelCell::HalfSize, 0, LevelCell::HalfSize - LevelCell::WallSize);
		static const Vector3 v3(-LevelCell::HalfSize, 0, LevelCell::HalfSize - LevelCell::WallSize);

		static const Vector3 v4(-LevelCell::HalfSize, LevelCell::Size, LevelCell::HalfSize);
		static const Vector3 v5(+LevelCell::HalfSize, LevelCell::Size, LevelCell::HalfSize);

		const int i = static_cast<int>(dir);
		graphics->SetMaterial(_transparent ? Graphics::MT_TRANSPARENT : Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + rotMat[i].VectorTransform(v0), color, Vector2::Zero),
			Vertex(center + rotMat[i].VectorTransform(v1), color, Vector2::Right),
			Vertex(center + rotMat[i].VectorTransform(v2), color, Vector2::One),
			Vertex(center + rotMat[i].VectorTransform(v3), color, Vector2::Up),
			_texture);

		graphics->SetMaterial(Graphics::MT_OPAQUE);
		graphics->DrawQuad(
			Vertex(center + rotMat[i].VectorTransform(v4), Color32::Black),
			Vertex(center + rotMat[i].VectorTransform(v5), Color32::Black),
			Vertex(center + rotMat[i].VectorTransform(v1), Color32::Black),
			Vertex(center + rotMat[i].VectorTransform(v0), Color32::Black),
			nullptr);
	}
}