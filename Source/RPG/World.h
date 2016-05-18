#pragma once
#include <Core/Module.h>

namespace uut { namespace rpg
{

	class Level;

	class World : public Module
	{
		UUT_MODULE(World, Module)
	public:
		World();

	protected:
		List<SharedPtr<Level>> _levels;
	};

} }