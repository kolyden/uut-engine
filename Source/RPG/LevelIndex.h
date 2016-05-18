#pragma once
#include <Core/Ptr.h>

namespace uut { namespace rpg {

	class Level;

	class LevelIndex
	{
	public:
		LevelIndex();
		LevelIndex(Level* level, intptr_t data);

		Level* GetLevel() const;
		intptr_t GetData() const;
		bool IsValid() const;

		static const LevelIndex Empty;

	protected:
		WeakPtr<Level> _level;
		intptr_t _data;
	};

} }