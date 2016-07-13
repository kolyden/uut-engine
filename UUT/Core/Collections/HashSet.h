#pragma once
#include <Core/Platform.h>
#include <set>

namespace uut
{
	template<typename T>
	class HashSet
	{
	public:
		typedef std::set<T> DataType;
		typedef typename DataType::iterator Iterator;
		typedef typename DataType::const_iterator CIterator;

		HashSet() {}

		void Add(const T& item) { _data.insert(item); }

		void Clear() { _data.clear(); }

		bool Contains(const T& item) const
		{
			return std::find(_data.begin(), _data.end(), item) != _data.end();
		}

		uint Count() const { return _data.size(); }

		bool Remove(const T& item)
		{
			auto it = std::find(_data.begin(), _data.end(), item);
			if (it == _data.end())
				return false;

			_data.erase(it);
			return true;
		}

		Iterator Remove(Iterator iterator)
		{
			return _data.erase(iterator);
		}

		Iterator Find(const T& item) { return _data.find(item); }
		CIterator Find(const T& item) const { return _data.find(item); }

		Iterator Begin() { return _data.begin(); }
		Iterator End() { return _data.end(); }
		CIterator Begin() const { return _data.begin(); }
		CIterator End() const { return _data.end(); }

		static const HashSet<T> Empty;

	protected:
		DataType _data;
	};

	template<class T> const HashSet<T> HashSet<T>::Empty;

	template<class T> typename HashSet<T>::Iterator begin(HashSet<T>& container) { return container.Begin(); }
	template<class T> typename HashSet<T>::Iterator end(HashSet<T>& container) { return container.End(); }

	template<class T> typename HashSet<T>::CIterator begin(const HashSet<T>& container) { return container.Begin(); }
	template<class T> typename HashSet<T>::CIterator end(const HashSet<T>& container) { return container.End(); }

// 	template<typename T> constexpr static const HashSet<T>& GetDefault<HashSet<T>>()
// 	{
// 		return HashSet<T>::Empty;
// 	}
}