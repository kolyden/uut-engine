#pragma once
#include <Core/Object.h>

namespace uut { namespace rpg {

	class LevelIndex;

	class Level : public Object
	{
		UUT_OBJECT(Level, Object)
	public:
		Level();

		bool IsIndexValid(const LevelIndex& index) const;

	protected:
		LevelIndex CreateIndex(uintptr_t data);
		LevelIndex CreateIndex(void* data);
	};

} }