#ifndef VECTOR_COLLECTION_H
#define VECTOR_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"

template<typename K, typename V>
class VectorCollection : public Collection<K, V>
{
	public:
	
	// insert a key-value pair into the collection
	void insert(const K& key, const V& val) override;
	
	// remove a key value pair from the collection
	void remove(const K& key) override;
	
	// find and return the value associated with the key
	bool find(const K& key, V& val)const override;
	
	// find and return the list of keys >= to k1 and <= to k2
	void find(const K& k1, const K& k2, std::vector<K>& keys)const override;
	
	// return all of the keys in the collection
	void keys(std::vector<K>& keys)const override;
	
	// return all of the keys in ascending (sorted) order
	void sort(std::vector<K>& keys)const override;
	
	// return the number of keys in the collections
	int size() const override;
	
	private:
	std::vector<std::pair<K,V>> kv_list;
	
};

template<typename K, typename V>
void VectorCollection<K,V>::insert(const K& key, const V& val)
{
	std::pair<K,V> p(key, val);
	kv_list.push_back(p);
}

template<typename K, typename V>
void VectorCollection<K,V>::remove(const K& key) 
{
	for(typename std::vector<std::pair<K,V>>::const_iterator it = kv_list.begin(), end = kv_list.end(); it != kv_list.end(); ++it){
		if(it->first == key){
			it = kv_list.erase(it);
			break;
		}
	}
		
				

}

template<typename K, typename V>
bool VectorCollection<K,V>::find(const K& key, V& val) const
{
	for(typename std::vector<std::pair<K,V>>::const_iterator it = kv_list.begin(), end = kv_list.end(); it != kv_list.end(); ++it){
		if(it->first == key && it->second == val)
			return true;
	}
	return false;
}

template<typename K, typename V>
void VectorCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
	int begin = 0;
	for(int i =0; i < kv_list.size(); ++i){
		if(kv_list[i].first == k1){
			begin = i;
			break;
		}
	}
	for(int i = begin; i < kv_list.size(); ++i){
		keys.push_back(kv_list[i].first);
		if(kv_list[i].first == k2){
			break;
		}
	}		
}

template<typename K, typename V>
void VectorCollection<K,V>::keys(std::vector<K>& keys) const	
{
	for(int i = 0; i < kv_list.size(); ++i){
		keys.push_back(kv_list[i].first);
	}
}

template<typename K, typename V>
void VectorCollection<K,V>::sort(std::vector<K>& keys) const
{
	for(int i = 0; i <= kv_list.size(); ++i){
		keys.push_back(kv_list[i].first);
	}
	std::sort(keys.begin(),keys.end());	
}

template<typename K, typename V>
int VectorCollection<K,V>::size() const
{
	return kv_list.size();
}

#endif	
