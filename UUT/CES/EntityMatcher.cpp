#include "EntityMatcher.h"
#include "Entity.h"

namespace uut
{
	EntityMatcher::EntityMatcher()
	{
	}

	EntityMatcher::EntityMatcher(const EntityMatcher& matcher)
		: _allof(matcher._allof)
		, _anyof(matcher._anyof)
		, _noneof(matcher._noneof)
	{
	}

	EntityMatcher::EntityMatcher(EntityMatcher&& matcher)
		: _allof(std::move(matcher._allof))
		, _anyof(std::move(matcher._anyof))
		, _noneof(std::move(matcher._noneof))
	{
	}

	bool EntityMatcher::Matches(const SharedPtr<Entity>& entity) const
	{
		const bool matchAllOf = _allof.IsEmpty() || entity->HasComponents(_allof);
		const bool matchAnyOf = _anyof.IsEmpty() || entity->HasAnyComponents(_anyof);
		const bool matchNoneOf = _noneof.IsEmpty() || !entity->HasAnyComponents(_noneof);

		return matchAllOf && matchAnyOf && matchNoneOf;
	}

	EntityMatcher& EntityMatcher::operator|=(const EntityMatcher& matcher)
	{
		_allof += matcher._allof;
		_anyof += matcher._anyof;
		_noneof += matcher._noneof;
		return *this;
	}

	EntityMatcher EntityMatcher::operator|(const EntityMatcher& matcher) const
	{
		EntityMatcher ret(*this);
		ret |= matcher;
		return ret;
	}
}