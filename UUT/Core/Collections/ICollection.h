#pragma once
#include "IEnumerable.h"
#include <functional>

namespace uut
{
	template<class T, class DataType>
	class ICollection : public IEnumerable<T, DataType>
	{
	public:
		typedef std::function<bool(const T&)> Predicate;
		typedef std::function<int(const T& a, const T& b)> Comparison;

		int Count() const { return static_cast<int>(_data.size()); }
		bool IsEmpty() const { return Count() == 0; }

		void Add(const T& item)
		{
			_data.push_back(item);
		}

		void Add(int count, const T& item)
		{
			for (int i = 0; i < count; i++)
				Add(item);
		}

		void Clear()
		{
			_data.clear();
		}

		bool Contains(const T& item) const
		{
			for (auto& it : _data)
			{
				if (it == item)
					return true;
			}

			return false;
		}

		bool Remove(const T& item)
		{
			for (auto it = Begin(); it != End(); ++it)
			{
				if (*it != item)
					continue;

				_data.erase(it);
				return true;
			}

			return false;
		}
	};
}