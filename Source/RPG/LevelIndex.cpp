#include "LevelIndex.h"
#include "Level.h"

namespace uut { namespace rpg {

	const LevelIndex LevelIndex::Empty;

	LevelIndex::LevelIndex()
		: _data(0)
	{
	}

	LevelIndex::LevelIndex(Level* level, intptr_t data)
		: _level(level)
		, _data(data)
	{
	}

	Level* LevelIndex::GetLevel() const
	{
		return _level;
	}

	intptr_t LevelIndex::GetData() const
	{
		return _data;
	}

	bool LevelIndex::IsValid() const
	{
		return _level != nullptr && _level->IsIndexValid(*this);
	}

}
}