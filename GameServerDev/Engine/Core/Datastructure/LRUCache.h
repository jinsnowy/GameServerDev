#pragma once

template <typename TKey, typename TVal>
class LRUCache
{
private:
	using Cache = std::pair<TKey, TVal>;
	size_t _cache_size;
	std::list<Cache> _lru_caches;
	std::unordered_map<TKey, typename std::list<Cache>::iterator> _cache_map;

public:
	LRUCache(size_t cache_size)
		:
		_cache_size(cache_size)
	{}

	size_t Size() const {
		return _lru_caches.size();
	}

	bool Empty() const {
		return _lru_caches.empty();
	}

	bool Top(TVal& value) {
		if (Empty()) {
			return false;
		}
		value = _lru_caches.front().second;
		return true;
	}

	void Put(const TKey& key, TVal&& value) {
		if (auto iter = _cache_map.find(key); iter != _cache_map.end()) {
			_lru_caches.splice(_lru_caches.begin(), _lru_caches, iter->second);
			iter->second->second = std::forward<TVal>(value);
			return;
		}
		if (_lru_caches.size() == _cache_size) {
			_cache_map.erase(_lru_caches.back().first);
			_lru_caches.pop_back();
		}
		_lru_caches.emplace_front(key, std::forward<TVal>(value));
		_cache_map[key] = _lru_caches.begin();
	}

	void Put(const TKey& key, const TVal& value) {
		if (auto iter = _cache_map.find(key); iter != _cache_map.end()) {
			_lru_caches.splice(_lru_caches.begin(), _lru_caches, iter);
			iter->second->second = std::forward<TVal>(value);
			return;
		}
		if (_lru_caches.size() == _cache_size) {
			_cache_map.erase(_lru_caches.back().first);
			_lru_caches.pop_back();
		}
		_lru_caches.emplace_front(key, value);
		_cache_map[key] = _lru_caches.begin();
	}

	bool Get(const TKey& key, TVal& value) {
		auto iter = _cache_map.find(key);
		if (iter == _cache_map.end()) {
			return false;
		}
		_lru_caches.splice(_lru_caches.begin(), _lru_caches, iter->second);
		value = iter->second->second;
		return true;
	}

	TVal Get(const TKey& key) {
		auto iter = _cache_map.find(key);
		if (iter == _cache_map.end()) {
			return false;
		}
		_lru_caches.splice(_lru_caches.begin(), _lru_caches, iter->second);
		return iter->second->second;
	}
};
