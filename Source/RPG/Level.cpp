#include "Level.h"
#include "LevelIndex.h"

namespace uut { namespace rpg {

	UUT_OBJECT_IMPLEMENT(Level)
	{}

	Level::Level()
	{
	}

	bool Level::IsIndexValid(const LevelIndex& index) const
	{
		return  (index.GetLevel() == this);
	}

	////////////////////////////////////////////////////////////////////
	LevelIndex Level::CreateIndex(uintptr_t data)
	{
		return LevelIndex(this, data);
	}

	LevelIndex Level::CreateIndex(void* data)
	{
		return LevelIndex(this, reinterpret_cast<intptr_t>(data));
	}

} }