#pragma once
#include <Core/Object.h>
#include <Core/Math/Vector3.h>
#include <Core/Video/Color32.h>
#include "LevelCell.h"

namespace uut
{
	class Texture2D;
	class Graphics;

	class BaseTile : public Object
	{
	public:
		virtual void Update(float deltaTime) {}
		virtual Texture2D* GetTexture() const = 0;
		virtual bool IsTransparent() const { return false; }
	};

	class FloorTile : public BaseTile
	{
	public:
		virtual void DrawFloor(Graphics* graphics, const Vector3& center, const Color32& color) const = 0;
	};

	class WallTile : public BaseTile
	{
	public:
		virtual void DrawWall(Graphics* graphics, const Vector3& center, Direction dir, const Color32& color) const = 0;
	};

	//////////////////////////////////////////////////////////////////////////////
	class SimpleFloorTile : public FloorTile
	{
	public:
		explicit SimpleFloorTile(Texture2D* texture);

		virtual Texture2D* GetTexture() const override { return _texture; }
		virtual void DrawFloor(Graphics* graphics, const Vector3& center, const Color32& color) const override;

	protected:
		SharedPtr<Texture2D> _texture;
	};

	class SimpleWallTile : public WallTile
	{
	public:
		explicit SimpleWallTile(Texture2D* texture, bool transparent = false);

		virtual Texture2D* GetTexture() const override { return _texture; }
		virtual bool IsTransparent() const override { return _transparent; }
		virtual void DrawWall(Graphics* graphics, const Vector3& center, Direction dir, const Color32& color) const override;

	protected:
		SharedPtr<Texture2D> _texture;
		bool _transparent;
	};
}