#pragma once
#include <map>
#include "List.h"

namespace uut
{
	template<class TKey, class TValue>
	class Dictionary
	{
	public:
		typedef TKey KeyType;
		typedef TValue ValueType;

		typedef std::map<TKey, TValue> DataMap;
		typedef typename DataMap::iterator Iterator;
		typedef typename DataMap::const_iterator ConstIterator;

		typedef std::function<bool(const TKey& key, const TValue& val)> Predicate;

		Dictionary() {}
		Dictionary(const DataMap& data) : _dataMap(data) {}
		Dictionary(DataMap&& data) { _dataMap = std::move(data); }
// 		Dictionary(const Dictionary<TKey, TValue>& other) : _dataMap(other._dataMap) {}
		Dictionary(Dictionary<TKey,TValue>&& other) { _dataMap = std::move(other._dataMap); }
		Dictionary(std::initializer_list<std::pair<TKey,TValue>> items)
			: _dataMap(items) {}

		void Add(const TKey& key, TValue val)
		{
			_dataMap[key] = val;
		}

		TValue& Get(const TKey& key)
		{
			return _dataMap[key];
		}

		const TValue& Get(const TKey& key) const
		{
			return _dataMap[key];
		}

		bool Remove(const TKey& key)
		{
			auto it = _dataMap.find(key);
			if (it == _dataMap.end())
				return false;

			_dataMap.erase(it);
			return true;
		}

		Iterator Remove(Iterator it)
		{
			return _dataMap.erase(it);
		}

		int RemoveAll(Predicate predicate)
		{
			int count = 0;
			for (auto it = Begin(); it != End();)
			{
				if (predicate(it->first, it->second))
					_dataMap.erase(it++);
				else ++it;
			}

			return count;
		}

		int Count() const
		{
			return (int)_dataMap.size();
		}

		bool IsEmpty() const
		{
			return _dataMap.empty();
		}

		void Clear()
		{
			_dataMap.clear();
		}

		bool Contains(const TKey& key) const
		{
			auto it = _dataMap.find(key);
			return (it != _dataMap.end());
		}

		List<TKey> GetKeys() const
		{
			List<TKey> keys;
			for (auto& it : _dataMap)
				keys << it.first;

			return keys;
		}

		List<TValue> GetValues() const
		{
			List<TValue> keys;
			for (auto& it : _dataMap)
				keys << it.second;

			return keys;
		}

		Iterator Find(const TKey& key)
		{
			return _dataMap.find(key);
		}

		ConstIterator Find(const TKey& key) const
		{
			return _dataMap.find(key);
		}

		bool TryGetValue(const TKey& key, TValue& val) const
		{
			auto it = _dataMap.find(key);
			if (it == _dataMap.end())
				return false;

			val = it->second;
			return true;
		}

		TValue& operator[] (const TKey& key)
		{
			return _dataMap[key];
		}

		Dictionary<TKey, TValue>& operator=(Dictionary<TKey, TValue>&& other)
		{
			if (this != other)
				_dataMap = std::move(other._dataMap);
			return *this;
		}

		Iterator Begin() { return _dataMap.begin(); }
		Iterator End() { return _dataMap.end(); }
		ConstIterator Begin() const { return _dataMap.begin(); }
		ConstIterator End() const { return _dataMap.end(); }

		DataMap& GetMap() { return _dataMap; }
		const DataMap& GetMap() const { return _dataMap; }

		template<typename TSource>
		static Dictionary<TKey, TSource> FromList(const List<TSource>& list, std::function<TKey(const TSource&)> keySelector)
		{
			Dictionary<TKey, TSource> dict;
			for (auto& it : list)
				dict.Add(keySelector(it), it);

			return dict;
		}

		static const Dictionary EMPTY;

	protected:
		DataMap _dataMap;
	};

	template<class TKey, class TValue>
	const Dictionary<TKey, TValue> Dictionary<TKey, TValue>::EMPTY;

	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::Iterator begin(Dictionary<TKey, TValue>& list) { return list.Begin(); }
	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::Iterator end(Dictionary<TKey, TValue>& list) { return list.End(); }

	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::ConstIterator begin(const Dictionary<TKey, TValue>& list) { return list.Begin(); }
	template<class TKey, class TValue> typename Dictionary<TKey, TValue>::ConstIterator end(const Dictionary<TKey, TValue>& list) { return list.End(); }
}