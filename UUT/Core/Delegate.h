#pragma once
#include "Collections/List.h"
#include <functional>

namespace uut
{
	template<typename... Args>
	class Delegate
	{
	public:
		typedef std::function<void(Args...)> FuncHandle;

		void Connect(FuncHandle func)
		{
			_handles << func;
		}

		void Invoke(Args... args)
		{
			for (auto& func : _handles)
				func(args...);
		}

		void operator() (Args... args)
		{
			Invoke(args...);
		}

		Delegate& operator += (FuncHandle func)
		{
			Connect(func);
			return *this;
		}

	protected:
		List<FuncHandle> _handles;
	};
}
