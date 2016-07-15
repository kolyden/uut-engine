#pragma once
#include <Core/Ptr.h>
#include <Core/Reflection/Type.h>
#include "Entity.h"
#include <array>

namespace uut
{
	class Entity;

	class EntityMatcher
	{
	public:
		EntityMatcher();
		EntityMatcher(const EntityMatcher& matcher);
		EntityMatcher(EntityMatcher&& matcher);

		bool Matches(const SharedPtr<Entity>& entity) const;

		template<typename... Args>
		static EntityMatcher AllOf()
		{
			EntityMatcher matcher;
			matcher._allof = { TypeOf<Args>()... };
			return matcher;
		}

		template<typename... Args>
		static EntityMatcher AnyOf()
		{
			EntityMatcher matcher;
			matcher._anyof = { TypeOf<Args>()... };
			return matcher;
		}

		template<typename... Args>
		static EntityMatcher NoneOf()
		{
			EntityMatcher matcher;
			matcher._noneof = { TypeOf<Args>()... };
			return matcher;
		}

		EntityMatcher& operator|=(const EntityMatcher& matcher);
		EntityMatcher operator|(const EntityMatcher& matcher) const;

	protected:
		List<const Type*> _allof;
		List<const Type*> _anyof;
		List<const Type*> _noneof;
	};
}