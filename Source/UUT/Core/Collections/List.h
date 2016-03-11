#pragma once
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
		typedef typename DataType::const_iterator CIterator;

		typedef std::function<void(T&)> Iterate;
		typedef std::function<void(const T&)> ConstIterate;
		typedef std::function<bool(const T&)> Predicate;
		typedef std::function<int(const T& a, const T& b)> Comparison;

		List() {}
		List(const List<T>& other) : _data(other._data) {}
		List(List<T>&& other) { _data = std::move(other._data); }
		explicit List(const T& data, int count = 1) : _data(data, count) {}
		List(const T* data, unsigned int count) : _data(data, data + count) {}
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

		T& operator[] (int index) { return _data[index]; }
		const T& operator[] (int index) const { return _data[index]; }

		List<T> operator + (const List<T>& list) const { List<T> ret(*this); ret += list; return ret; }
		List<T>& operator += (const List<T>& list) { Append(list); return *this; }

		void SetSize(int count) { _data.resize(count); }
		void SetSize(int count, const T& item) { _data.resize(count, item); }
		void SetReserve(int reserve) { _data.reserve(reserve); }

		int Count() const { return static_cast<int>(_data.size()); }
		bool IsEmpty() const { return _data.empty(); }

		void Clear() { _data.clear(); }

		void Add(const T& item)
		{
			_data.push_back(item);
		}

		void Add(int count, const T& item)
		{
			_data.resize(_data.size() + count, item);
		}

		void Append(const List<T>& list) { _data.insert(_data.end(), list._data.begin(), list._data.end()); }

		Iterator Remove(Iterator it) { return _data.erase(it); }

		bool Remove(const T& item)
		{
			auto it = std::find(Begin(), End(), item);
			if (it == End())
				return false;

			Remove(it);
			return true;
		}


		int RemoveAll(Predicate predicate)
		{
			int i = 0, total = 0;
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

		void RemoveRange(int start, int count)
		{
			const int total = Count();
			if (start < 0 || start >= total)
				return;

			const int last = std::min(total, start + count);
			for (int i = start; i < last; i++)
				RemoveAt(start);
		}

		int CalcCount(Predicate predicate) const
		{
			int count = 0;
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

		void Sort(int index, Comparison comparison)
		{
			std::sort(_data.begin() + index, _data.end(),
				[&comparison](const T& a, const T& b) -> bool
			{
				return comparison(a, b) < 0;
			});
		}

		void Sort(int index, int count, Comparison comparison)
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

		const T& GetRepeat(int index) const
		{
			const int count = Count();
			UUT_ASSERT(count > 0);
			index %= count;
			if (index < 0)
				index += count;
			return _data[index];
		}

		T* GetData() { return _data.data(); }
		const T* GetData() const { return _data.data(); }

		void Swap(List<T>& list) { std::swap(_data, list._data); }
		void Swap(int index1, int index2) { std::swap(_data[index1], _data[index2]); }

		List<T> GetRange(int index, int count) const
		{
			if (count <= 0)
				return EMPTY;

			UUT_ASSERT(index >= 0 && index < Count());
			UUT_ASSERT(index + count <= Count());

			List<T> ret;
			ret.SetReserve(count);
			for (int i = 0; i < count; i++)
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
			const int count = Count();
			for (int i = 0; i < count; i++)
			{
				if (predicate(_data[i]))
					return _data[i];
			}

			return defval;
		}

		List<T> FindAll(Predicate predicate) const
		{
			List<T> list;
			const int count = Count();
			for (int i = 0; i < count; i++)
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

		int FindIndex(int start, Predicate predicate) const
		{
			const int count = Count();
			return FindIndex(start, count - start, predicate);
		}

		int FindIndex(int start, int count, Predicate predicate) const
		{
			const int total = Count();
			if (start < 0 || start >= total)
				return -1;

			const int last = std::min(start + count, total);
			for (int i = start; i < last; i++)
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

		int IndexOf(const T& item, int start) const
		{
			const int count = Count();
			return IndexOf(item, start, count - start);
		}

		int IndexOf(const T& item, int start, int count) const
		{
			const int total = Count();
			if (start < 0 || start >= total)
				return -1;

			const int last = std::min(start + count, total);
			for (int i = start; i < last; i++)
			{
				if (_data[i] == item)
					return i;
			}

			return -1;
		}

		void Insert(int index, const T& item)
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

		static const List<T> EMPTY;

		template<typename ... Args>
		static List<T> Make(Args... args)
		{
			return List<T>(args...);
		};

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }
		CIterator Begin() const { return _data.begin(); }
		CIterator End() const { return _data.end(); }

	protected:
		DataType _data;
	};

	template<class T> const List<T> List<T>::EMPTY;

	template<class T> typename List<T>::Iterator begin(List<T>& list) { return list.Begin(); }
	template<class T> typename List<T>::Iterator end(List<T>& list) { return list.End(); }

	template<class T> typename List<T>::ConstIterator begin(const List<T>& list) { return list.Begin(); }
	template<class T> typename List<T>::ConstIterator end(const List<T>& list) { return list.End(); }
}
