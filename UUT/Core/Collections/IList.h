#pragma once
#include "ICollection.h"

namespace uut
{
	template<class T, class DataType>
	class IList : public ICollection<T, DataType>
	{
	public:
		static const int NPOS = -1;

		typedef std::function<bool(const T&)> Predicate;
		typedef std::function<int(const T& a, const T& b)> Comparison;

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		T& GetAt(int index) { return _data[index]; }
		const T& GetAt(int index) const { return _data[index]; }

		int IndexOf(const T& item) const
		{
			for (int i = 0; i < Count(); i++)
			{
				if (GetAt(i) == item)
					return i;
			}

			return NPOS;
		}

		void Insert(int index, const T& item)
		{
			_data.insert(index, item);
		}

		void RemoveAt(int index)
		{
			_data.erase(_data.begin() + index);
		}
	};
}