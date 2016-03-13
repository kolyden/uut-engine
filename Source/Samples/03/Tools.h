#pragma once
#include <Core/Object.h>
#include "LevelCell.h"

namespace uut
{
	class Tileset;

	enum class ToolType
	{
		Clear,
		Floor,
		Wall,
	};

	class Tools : public Object
	{
	public:
		Tools(Tileset* tilest);

		void Update();

		ToolType GetType() const { return _type; }
		Direction GetDirection() const { return _direction; }

	protected:
		SharedPtr<Tileset> _tileset;
		ToolType _type;
		Direction _direction;
	};
}
