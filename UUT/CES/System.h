#pragma once
#include <Core/Platform.h>
#include <limits>

namespace uut
{
	class EntityPool;

	class System
	{
	public:
		System() : _pool(nullptr) {}
		virtual ~System() {}

	protected:
		EntityPool* _pool;

		virtual void Init() {}
		virtual void Execute() = 0;

		friend class EntityPool;
	};
}