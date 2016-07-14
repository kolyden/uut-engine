#include "Matcher.h"
#include "Entity.h"

namespace uut
{
	Matcher::Matcher()
	{
	}

	Matcher::Matcher(const Matcher& matcher)
		: _allof(matcher._allof)
		, _anyof(matcher._anyof)
		, _noneof(matcher._noneof)
	{
	}

	Matcher::Matcher(Matcher&& matcher)
		: _allof(std::move(matcher._allof))
		, _anyof(std::move(matcher._anyof))
		, _noneof(std::move(matcher._noneof))
	{
	}

	bool Matcher::Matches(const SharedPtr<Entity>& entity) const
	{
		const bool matchAllOf = _allof.IsEmpty() || entity->HasComponents(_allof);
		const bool matchAnyOf = _anyof.IsEmpty() || entity->HasAnyComponents(_anyof);
		const bool matchNoneOf = _noneof.IsEmpty() || !entity->HasAnyComponents(_noneof);

		return matchAllOf && matchAnyOf && matchNoneOf;
	}
}