#pragma once
#include <Core/Ptr.h>
#include <Core/Reflection/Type.h>
#include "Entity.h"
#include <array>

namespace uut
{
	class Entity;

	class Matcher
	{
	public:
		Matcher();
		Matcher(const Matcher& matcher);
		Matcher(Matcher&& matcher);

		bool Matches(const SharedPtr<Entity>& entity) const;

		template<typename... Args>
		static Matcher AllOf()
		{
			Matcher matcher;
			matcher._allof = { TypeOf<Args>()... };
			return matcher;
		}

		template<typename... Args>
		static Matcher AnyOf()
		{
			Matcher matcher;
			matcher._anyof = { TypeOf<Args>()... };
			return matcher;
		}

		template<typename... Args>
		static Matcher NoneOf()
		{
			Matcher matcher;
			matcher._noneof = { TypeOf<Args>()... };
			return matcher;
		}

	protected:
		List<const Type*> _allof;
		List<const Type*> _anyof;
		List<const Type*> _noneof;
	};
}