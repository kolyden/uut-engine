#include "EntityGroup.h"
#include "Matcher.h"

namespace uut
{
	EntityGroup::EntityGroup(const Matcher& matcher)
		: _pool(nullptr)
		, _matcher(matcher)
	{
	}

	void EntityGroup::EntityChanged(const SharedPtr<Entity>& entity)
	{
		auto it = _entities.Find(entity);
		if (it == _entities.End())
		{
			if (_matcher.Matches(entity))
			{
				_entities.Add(entity);
				onAdd(entity);
			}
		}
		else
		{
			if (!_matcher.Matches(entity))
			{
				onRemove(entity);
				_entities.Remove(it);
			}
		}
	}
}