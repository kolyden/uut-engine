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
		virtual ~Matcher()
		{
		}

		virtual bool Matches(const SharedPtr<Entity>& entity) const = 0;
	};

	template<typename... Args>
	class MatcherAllOf : public Matcher
	{
	public:
		typedef std::array<const Type*, sizeof...(Args)> DataType;
		static const DataType Data;

		bool Matches(const SharedPtr<Entity>& entity) const override
		{
			return _internalRecurseMatches<0>(entity);
		}

	protected:
		template<size_t index,
			std::enable_if_t<(index < sizeof...(Args)), void>* = nullptr>
		static bool _internalRecurseMatches(const SharedPtr<Entity>& entity)
		{
			if (!entity->HasComponent(Data[index]))
				return false;

			return _internalRecurseMatches<index + 1>(entity);
		}

		template<size_t index,
			std::enable_if_t<(index >= sizeof...(Args)), void>* = nullptr>
		static bool _internalRecurseMatches(const SharedPtr<Entity>& entity)
		{
			return true;
		}
	};

	template<typename... Args> const typename MatcherAllOf<Args...>::DataType MatcherAllOf<Args...>::Data = { TypeOf<Args>()... };
}
