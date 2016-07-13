#pragma once
#include "Core/Platform.h"
#include "IComparer.h"
#include <functional>
#include <algorithm>
#include <vector>
#include <Core/Assert.h>

namespace uut
{
	template<class T>
	class List
	{
	public:
		typedef std::vector<T> DataType;
		typedef typename DataType::iterator Iterator;
		typedef typename DataType::const_iterator ConstIterator;

		typedef std::function<void(T&)> Iterate;
		typedef std::function<void(const T&)> ConstIterate;
		typedef std::function<bool(const T&)> Predicate;
		typedef std::function<int(const T& a, const T& b)> Comparison;

		List() {}
		List(const List<T>& other) : _data(other._data) {}
		List(List<T>&& other) : _data(std::move(other._data)) {}
		explicit List(const T& data, uint count = 1) : _data(data, count) {}
		List(const T* data, uint count) : _data(data, data + count) {}
		List(std::initializer_list<T> items) : _data(items) {}

		List<T>& operator=(const List<T>& other)
		{
			_data = other._data;
			return *this;
		}

		List<T>& operator=(List<T>&& other)
		{
			if (this != &other)
				_data = std::move(other._data);
			return *this;
		}

		List<T>& operator << (const T& data) { Add(data); return *this; }
		List<T>& operator << (const List<T>& arr) { Append(arr); return *this; }

		T& operator[] (uint index) { return _data[index]; }
		const T& operator[] (uint index) const { return _data[index]; }

		List<T> operator + (const List<T>& list) const { List<T> ret(*this); ret += list; return ret; }
		List<T>& operator += (const List<T>& list) { Append(list); return *this; }

		void SetSize(uint count) { _data.resize(count); }
		void SetSize(uint count, const T& item) { _data.resize(count, item); }
		void SetReserve(uint reserve) { _data.reserve(reserve); }

        uint Count() const { return static_cast<int>(_data.size()); }
		bool IsEmpty() const { return _data.empty(); }

		void Clear() { _data.clear(); }

		void Add(const T& item)
		{
			_data.push_back(item);
		}

		void Add(uint count, const T& item)
		{
			_data.resize(_data.size() + count, item);
		}

		void Append(const List<T>& list) { _data.insert(_data.end(), list._data.begin(), list._data.end()); }

		Iterator Remove(Iterator it) { return _data.erase(it); }

		bool Remove(const T& item)
		{
            int index = IndexOf(item);
            if (index < 0)
				return false;

			RemoveAt(index);
			return true;
		}

        uint RemoveAll(Predicate predicate)
		{
			uint i = 0, total = 0;
			while (i < Count())
			{
				if (predicate(_data[i]))
				{
					RemoveAt(i);
					total++;
				}
				else i++;
			}
			return total;
		}

		virtual void RemoveAt(int index)
		{
			_data.erase(_data.begin() + index);
		}

		void RemoveRange(uint start, uint count)
		{
			const uint total = Count();
			if (start < 0 || start >= total)
				return;

			const uint last = std::min(total, start + count);
			for (uint i = start; i < last; i++)
				RemoveAt(start);
		}

		int CalcCount(Predicate predicate) const
		{
            uint count = 0;
			for (auto& it : _data)
			{
				if (predicate(it))
					count++;
			}
			return count;
		}

		void Sort()
		{
			std::sort(_data.begin(), _data.end());
		}

		void Sort(Comparison comparison)
		{
			std::sort(_data.begin(), _data.end(),
				[&comparison](const T& a, const T& b) -> bool
			{
				return comparison(a, b) < 0;
			});
		}

		void Sort(uint index, Comparison comparison)
		{
			std::sort(_data.begin() + index, _data.end(),
				[&comparison](const T& a, const T& b) -> bool
			{
				return comparison(a, b) < 0;
			});
		}

		void Sort(uint index, uint count, Comparison comparison)
		{
			std::sort(_data.begin() + index, _data.begin() + index + count,
				[&comparison](const T& a, const T& b) -> bool
			{
				return comparison(a, b) < 0;
			});
		}

		void Sort(const IComparer<T>& comparer)
		{
			std::sort(_data.begin(), _data.end(),
				[&comparer](const T& a, const T& b) -> bool
			{
				return comparer.Compare(a, b) < 0;
			});
		}

		bool Contains(const T& data) const
		{
			if (_data.empty())
				return false;

			for (auto& it : _data)
			{
				if (it == data)
					return true;
			}

			return false;
		}

		template<class U> List<U> ConvertAll(std::function<U(T&)> convert)
		{
			List<U> list;
			for (auto& it : _data)
				list.Add(convert(it));
			return list;
		}

		template<class U> List<U> ConvertAll(std::function<U(const T&)> convert) const
		{
			List<U> list;
			for (auto& it : _data)
				list.Add(convert(it));
			return list;
		}

		const T& GetRepeat(uint index) const
		{
			const uint count = Count();
            UUT_ASSERT(count > 0);
            return _data[index % count];
		}

		T* GetData() { return _data.data(); }
		const T* GetData() const { return _data.data(); }

		void Swap(List<T>& list) { std::swap(_data, list._data); }
		void Swap(uint index1, uint index2) { std::swap(_data[index1], _data[index2]); }

		List<T> GetRange(uint index, uint count) const
		{
			if (count <= 0)
				return Empty;

			UUT_ASSERT(index >= 0 && index < Count());
			UUT_ASSERT(index + count <= Count());

			List<T> ret;
			ret.SetReserve(count);
			for (uint i = 0; i < count; i++)
				ret << _data[index + i];

			return ret;
		}

		bool Exist(Predicate predict) const
		{
			for (auto& it : _data)
			{
				if (predict(it))
					return true;
			}

			return false;
		}

		const T& Find(const T& defval, Predicate predicate) const
		{
			const uint count = Count();
			for (uint i = 0; i < count; i++)
			{
				if (predicate(_data[i]))
					return _data[i];
			}

			return defval;
		}

		List<T> FindAll(Predicate predicate) const
		{
			List<T> list;
			const uint count = Count();
			for (uint i = 0; i < count; i++)
			{
				if (predicate(_data[i]))
					list << _data[i];
			}
			return list;
		}

		int FindIndex(Predicate predicate) const
		{
			return FindIndex(0, Count(), predicate);
		}

		int FindIndex(uint start, Predicate predicate) const
		{
			const int count = Count();
			return FindIndex(start, count - start, predicate);
		}

		int FindIndex(uint start, uint count, Predicate predicate) const
		{
			const uint total = Count();
			if (start < 0 || start >= total)
				return -1;

			const uint last = std::min(start + count, total);
			for (uint i = start; i < last; i++)
			{
				if (predicate(_data[i]))
					return i;
			}

			return -1;
		}

		int IndexOf(const T& item) const
		{
			return IndexOf(item, 0, Count());
		}

		int IndexOf(const T& item, uint start) const
		{
			const uint count = Count();
			return IndexOf(item, start, count - start);
		}

		int IndexOf(const T& item, uint start, uint count) const
		{
			const uint total = Count();
			if (start < 0 || start >= total)
				return -1;

			const uint last = std::min(start + count, total);
			for (uint i = start; i < last; i++)
			{
				if (_data[i] == item)
					return i;
			}

			return -1;
		}

		void Insert(uint index, const T& item)
		{
			_data.insert(index, item);
		}

		bool TrueForAll(Predicate match) const
		{
			for (auto& it : _data)
			{
				if (!match(it))
					return false;
			}

			return true;
		}

		T Sum(const T& startValue, std::function<void(T&, const T&)> func) const
		{
			T ret = startValue;
			for (auto& it : _data)
				func(ret, it);
			return ret;
		}

		static const List<T> Empty;

		template<typename ... Args>
		static List<T> Make(Args... args)
		{
			return List<T>(args...);
		};

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }
		ConstIterator Begin() const { return _data.begin(); }
		ConstIterator End() const { return _data.end(); }

	protected:
		DataType _data;
	};

	template<class T> const List<T> List<T>::Empty;

	template<class T> typename List<T>::Iterator begin(List<T>& list) { return list.Begin(); }
	template<class T> typename List<T>::Iterator end(List<T>& list) { return list.End(); }

	template<class T> typename List<T>::ConstIterator begin(const List<T>& list) { return list.Begin(); }
	template<class T> typename List<T>::ConstIterator end(const List<T>& list) { return list.End(); }
}