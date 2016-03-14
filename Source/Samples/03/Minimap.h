#pragma once
#include <Core/Object.h>
#include "LevelCell.h"

namespace uut
{
	class Level;
	class Tileset;
	class Texture2D;

	enum class ToolType
	{
		Clear,
		Floor,
		Wall,
	};

	class Minimap : public Object
	{
	public:
		explicit Minimap(Level* level);

		void Update();

		ToolType GetToolType() const { return _toolType; }
		Direction GetDirection() const { return _direction; }

	protected:
		SharedPtr<Level> _level;
		SharedPtr<Tileset> _tileset;
		int _wallTile;

		ToolType _toolType;
		Direction _direction;
	};
}