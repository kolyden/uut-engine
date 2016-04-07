#pragma once
#include <Core/Object.h>
#include "LevelCell.h"

namespace uut
{
	class EditorLevel;
	class Tileset;
	class Texture2D;

	enum class ToolType
	{
		Clear,
		Solid,
		Floor,
		Wall,
	};

	class Minimap : public Object
	{
	public:
		explicit Minimap(EditorLevel* level);

		void Update();

		ToolType GetToolType() const { return _toolType; }
		Direction GetDirection() const { return _direction; }

	protected:
		SharedPtr<EditorLevel> _level;
		SharedPtr<Tileset> _tileset;
		int _wallTile;

		ToolType _toolType;
		Direction _direction;
	};
}