// File Name: binsearch_collection.h
// Purpose: defines and implements functions for 
//	    class binsearch_collection, which
//	    uses binary search to insert keys 
//	    in order


#ifndef BINSEARCH_COLLECTION_H
#define BINSEARCH_COLLECTION_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "collection.h"
using namespace std;
template<typename K, typename V>
class BinsearchCollection : public Collection<K, V>
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
	
	// return the number of keys in the collections
	int size() const override;

	// return all of the keys in ascending (sorted) order
	void sort(std::vector<K>& keys)const override;
	
	private:
	std::vector<std::pair<K,V>> kv_list;
	
	bool binsearch(const K& key, int& index) const;
	
};

template<typename K, typename V>
void BinsearchCollection<K,V>::insert(const K& key, const V& val)
{
	std::pair<K,V> p(key, val);
	int index = 0;
	bool isInserted = binsearch(key, index);
	kv_list.insert(kv_list.begin() + index, p);
}

template<typename K, typename V>
void BinsearchCollection<K,V>::remove(const K& key) 
{
	bool isFound = false;
	int index = 0;
	isFound = binsearch(key, index);
	if(isFound == true){
		kv_list.erase(kv_list.begin() + index);
	}		
}

template<typename K, typename V>
bool BinsearchCollection<K,V>::find(const K& key, V& val) const
{
	bool isFound = false;
	int index = 0;
	isFound = binsearch(key, index);
	if(isFound == true){
		val = kv_list[index].second;
		return true;
	}
	return false;	
}

template<typename K, typename V>
void BinsearchCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
	bool isFoundOne = false;
	bool isFoundTwo = false;
	int indexOne = 0;
	int indexTwo = 0;
	isFoundOne = binsearch(k1, indexOne);
	isFoundTwo = binsearch(k2, indexTwo);
	keys.clear();
	if(indexOne <= indexTwo){
		while(indexOne <= indexTwo && indexOne != kv_list.size()){ 
			keys.push_back(kv_list[indexOne].first);
			indexOne++;
		}
	}
	
}

template<typename K, typename V>
void BinsearchCollection<K,V>::keys(std::vector<K>& keys) const	
{
	for(int i = 0; i < kv_list.size(); ++i){
		keys.push_back(kv_list[i].first);
	}
}

template<typename K, typename V>
bool BinsearchCollection<K,V>::binsearch(const K& key, int& index) const
{		
	if(kv_list.size() == 0){
		index = 0;
		return false;
	}	
	
	int lower = 0;
	int upper = (int)(kv_list.size() - 1);
	int middle = lower + (upper - lower) / 2;
	int closest_Index = -1;
	while(lower <= upper)
	{
		// exits loop if mid index is less than zero or 
		// greater than last index of the vector
		if((middle < 0) or (middle > kv_list.size()-1))
			break;
		
		if(key == kv_list[middle].first){
			index = middle;
			return true;
		}

		// checks left side of vector, then checks if there
		// is stil a value to the left of middle (i.e. not less than first index)
		// then comapres that value with key, if it's less, then set
		// closest_index to middle	
		if(key < (kv_list[middle].first)){
			if(middle - 1 >= 0){
				if(kv_list[middle-1].first < key){
					closest_Index = middle;
					
				}
			}
			upper = middle - 1;
		}

		// same concept as above, except this checks right side of vector
		// instead of setting closest_index to middle, it sets it to
		// middle + 1 instead of just middle 
		else if(key > (kv_list[middle].first)){
			if(middle + 1 <= kv_list.size()-1){
				if(kv_list[middle+1].first > key){
					closest_Index = middle + 1;
					
					
				}
			}
			lower = middle + 1;
		}
		middle = lower + (upper - lower) / 2;
	}

	// if closest_Index was not changed (still at -1), one of two options
	// one: middle is at 0, means key is smaller than anything else in vector
	// two: middle exceeds last index, means key is higher than anything else in vector
	if(closest_Index == -1){
		if(middle <= 0)
			closest_Index = 0;
		else if(middle >= kv_list.size())
			closest_Index = kv_list.size();
	}
	index = closest_Index;
	return false;
}

template<typename K, typename V>
void BinsearchCollection<K,V>::sort(std::vector<K>& keys) const
{
	for(int i = 0; i <= kv_list.size(); ++i){
		keys.push_back(kv_list[i].first);
	}	
}

template<typename K, typename V>
int BinsearchCollection<K,V>::size() const
{
	return kv_list.size();
}

#endif	
