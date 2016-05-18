#pragma once
#include <Core/Collections/List.h>
#include <Core/Ptr.h>

namespace uut { namespace rpg
{

	class Trait;

	class TraitContainer
	{
	public:
		TraitContainer();

	protected:
		List<SharedPtr<Trait>> _traits;
	};

} }