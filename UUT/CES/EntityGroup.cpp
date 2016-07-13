#include "EntityGroup.h"
#include "Matcher.h"

namespace uut
{
	EntityGroup::EntityGroup(const SharedPtr<Matcher>& matcher)
		: _matcher(matcher)
	{
	}

	const SharedPtr<Matcher>& EntityGroup::GetMatcher() const
	{
		return _matcher;
	}

	void EntityGroup::EntityChanged(const SharedPtr<Entity>& entity)
	{
		auto it = _entities.Find(entity);
		if (it == _entities.End())
		{
			if (_matcher->Matches(entity))
			{
				_entities.Add(entity);
				onAdd(entity);
			}
		}
		else
		{
			if (!_matcher->Matches(entity))
			{
				onRemove(entity);
				_entities.Remove(it);
			}
		}
	}
}