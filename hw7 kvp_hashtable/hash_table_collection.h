// File Name: hash_table_collection.h
// Purpose: defines and implementation the class
//	    	hash_table_collection

# ifndef HASH_TABLE_COLLECTION_H
# define HASH_TABLE_COLLECTION_H

# include <vector>
# include <algorithm>
# include <functional>
# include "collection.h"

template <typename K , typename V>
class HashTableCollection : public Collection <K ,V>
{
public :

	// create an empty linked list
	HashTableCollection();

	// copy a linked list
	HashTableCollection(const HashTableCollection <K ,V >& rhs);

	// assign a linked list
	HashTableCollection<K, V>& operator =(const HashTableCollection <K ,V>& rhs);

	// delete a linked list
	~ HashTableCollection();

	// insert a key - value pair into the collection
	void insert(const K & the_key , const V & the_val);

	// remove a key - value pair from the collection
	void remove(const K & the_key);

	// find the value associated with the key
	bool find(const K & the_key, V & the_val) const;

	// find the keys associated with the range
	void find(const K & k1 , const K & k2 , std :: vector <K> & keys) const;

	// return all keys in the collection
	void keys(std :: vector <K> & keys) const;

	// return collection keys in sorted order
	void sort(std :: vector <K> & keys) const;

	// return the number of keys in collection
	int size() const;

private :

	// helper to empty entire hash table
	void make_empty();

	// resize and rehash the hash table
	void resize_and_rehash();

	// linked list node structure
	struct Node {
		K key;
		V value;
		Node * next;
	};

	// number of k-v pairs in the collection
	int collection_size;

	// number of hash table buckets (default is 16)
	int table_capacity;

	// hash table array load factor (set at 75% for resizing)
	const double load_factor_threshold;

	// hash table array
	Node** hash_table;
};

template <typename K, typename V>
HashTableCollection<K, V>::HashTableCollection():
collection_size(0), table_capacity(16), load_factor_threshold(0.75)
{
	// dynamically allocate the hash table array
	hash_table = new Node* [table_capacity];
	// initialize the hash table chains
	for (int i = 0; i < table_capacity ; i++){
		hash_table[i] = nullptr;
	}
}

template <typename K , typename V>
void HashTableCollection <K ,V>::make_empty ()
{
	// make sure hash table exists
	if(hash_table){
	// remove each key
		for(int i = 0; i < table_capacity; i++){
			while(hash_table[i] != nullptr){
				Node* temp = hash_table[i];
				hash_table[i] = temp -> next;
				delete temp;
				collection_size--;
			}
		}	
		if(collection_size > 0) 
		{
			std::cerr << "in make_empty:\ncompleted iteration through all elements in hash_table, collection_size > 0; memory leak implied" << std::endl;
			throw hash_table; //no memory leaks on my watch
		}
	}		
	// remove the hash table
	delete hash_table ;
	
}

template <typename K , typename V>
HashTableCollection <K ,V>::~HashTableCollection()
{
	make_empty();
}


template <typename K , typename V>
HashTableCollection <K ,V >::HashTableCollection(const HashTableCollection <K ,V >& rhs )
: hash_table ( nullptr ), load_factor_threshold(0.75)
{
	*this = rhs;
}

template <typename K , typename V>
HashTableCollection <K ,V >&
HashTableCollection <K ,V >::operator=( const HashTableCollection <K ,V >& rhs )
{
	// check if rhs is current object and return current object
	if ( this == &rhs )
		return *this ;
	// delete current object
	make_empty();
	// initialize current object
	collection_size = rhs.collection_size;
	table_capacity = rhs.table_capacity;
	// create the hash table
	hash_table = new Node* [rhs.table_capacity];
	// do the copy
	Node* temp;
	for(int i = 0; i < table_capacity; i++){
		hash_table[i] = nullptr;
		temp = rhs.hash_table[i];
		while(temp != nullptr){
			Node* to_insert = new Node;
			to_insert -> key = temp -> key;
			to_insert -> value = temp -> value;
			Node* insert_temp = hash_table[i];
			hash_table[i] = to_insert;
			to_insert -> next = insert_temp;
			temp = temp -> next;
		}
	}
	if(collection_size != rhs.collection_size) 
	{
		std::cerr << "in operator=:\nfailed to copy all elements from rhs: " << collection_size << " != " << rhs.collection_size << std::endl;
		throw 1; 
		//something went wrong
		// either we didnt find a key-value pair that is in rhs, or rhs thinks it
		// has more key-value pairs than it does. in either case better to fail fast
	}
	return *this;
}

template <typename K , typename V>
void HashTableCollection <K ,V >::resize_and_rehash()
{
	// setup new table
	int new_capacity = table_capacity * 2;
	// ... similarly with collection size ...
	// dynamically allocate the new table
	Node** new_table = new Node* [ new_capacity ];
	// initialize new table
	for (int i = 0; i < new_capacity; ++i)
		new_table[i] = nullptr;
	// insert key values
	std::vector<K> ks;
	keys(ks);
	V value_to_insert;
	bool find_temp;
	int temp_collection_size = 0;
	
	for ( K key : ks ) {
		// hash the key
		std::hash<K> hash_fun;
		size_t hashkey = hash_fun(key);
		size_t index = hashkey % table_capacity;
		// create a new node in new table
		Node* to_insert = new Node;
		find_temp = find(key, value_to_insert);
		to_insert -> key = key;
		to_insert -> value = value_to_insert;
		Node* temp = new_table[index];
		new_table[index] = to_insert;
		to_insert -> next = temp;
		temp_collection_size++;
	}
	if(temp_collection_size != collection_size)
	{
		std::cerr << "in resize_and_rehash:\nfailed to copy all elements to resized table: " << temp_collection_size << " != " << collection_size << std::endl;
		throw new_table; 
		//something went wrong
		//the k-v count didn't add up
		//so fail fast
	}
	// clear the current data
	make_empty ();
	// update to the new settings
	hash_table = new_table;
	collection_size = temp_collection_size;
	table_capacity = new_capacity;
}

template <typename K , typename V>
void HashTableCollection <K ,V >::insert(const K& the_key , const V & the_val )
{
	// check current load factor versus load factor threshold ,
	// and resize and copy if necessary by calling resize_and_rehash ()
	double current_load_factor = (double) (collection_size + 1) / table_capacity;
	if(current_load_factor > load_factor_threshold){
		resize_and_rehash();
	}
	
	// hash the key
	std::hash<K> hash_fun;
	size_t hashkey = hash_fun(the_key);
	size_t index = hashkey % table_capacity;
	
	// create the new node
	Node* pair = new Node;
	pair -> key = the_key;
	pair -> value = the_val;
	
	Node* temp = hash_table[index];
	hash_table[index] = pair;
	pair -> next = temp;
	
	// update the size
	collection_size++;	
}

template <typename K , typename V>
void HashTableCollection<K,V>::remove(const K & the_key)
{
	Node* temp;
	Node* prev;
	for(int i = 0; i < table_capacity; i++){
		temp = hash_table[i];
		prev = hash_table[i];
		while(temp != nullptr){
			if(temp -> key == the_key){
				if(prev == temp){
					hash_table[i] = temp -> next;
					delete temp;
					collection_size--;
					return;
				} else {
					prev -> next = temp -> next;
					delete temp;
					collection_size--;
					return;
				}				
			} else {
				if(prev == temp){
					temp = temp -> next;
					
				} else {
					prev = prev -> next;
					temp = temp -> next;
				}
			}
		}
	}
}

template <typename K , typename V>
bool HashTableCollection<K,V>::find(const K & the_key , V & the_val) const
{
	Node* temp;
	for(int i = 0; i < table_capacity; ++i){
		temp =  hash_table[i];
		while(temp != nullptr){
			if(temp -> key == the_key){
				the_val = temp -> value;
				return true;
			} else {
				temp = temp -> next;
			}
		}
	}
	return false;
}

template <typename K , typename V>
void HashTableCollection<K,V>::find(const K & k1 , const K & k2 , std :: vector <K >& keys) const
{
	Node* temp;
	keys.clear();
	for(int i = 0; i < table_capacity; i++){
		temp = hash_table[i];
		while(temp != nullptr){
			if(temp -> key >= k1 && temp -> key <= k2)
				keys.push_back(temp -> key);
			temp = temp -> next;
		}
	}
}

template <typename K , typename V>
void HashTableCollection<K ,V >::keys(std::vector<K> & keys) const
{
	keys.clear();
	Node* temp;
	for(int i = 0; i < table_capacity; i++){
		temp = hash_table[i];
		while(temp != nullptr){
			keys.push_back(temp -> key);
			temp = temp -> next;
		}
	}
}

template <typename K , typename V>
void HashTableCollection<K ,V >::sort(std::vector<K> & ks) const
{
	keys(ks);
	std::sort(ks.begin(), ks.end());
}

template <typename K , typename V>
int HashTableCollection <K ,V >::size() const
{
	return collection_size;
}

# endif




































template<typename K, typename V>
void LinkedListCollection<K,V>::ms_helper(Node* left, int len)
{
	if(left == nullptr || left -> next == nullptr){
		return;
	}

	int lhs_len = 1;
	int rhs_len = 1;
	int mid = length / 2;

	Node* lhs_head = head;
	Node* lhs_tail = head;
	Node* rhs_head = head;
	Node* rhs_tail = head;

	for(int i = 1; i < mid; i++){
		lhs_tail = lhs_tail -> next;
		lhs_len++;
	}

	rhs_head = lhs_tail -> next;
	rhs_tail = lhs_tail -> next;
	lhs_tail -> next = nullptr;
	while(rhs_tail -> next != nullptr){
		rhs_tail = rhs_tail -> next;
	}
	ms_helper(lhs_head, lhs_len);
	ms_helper(rhs_head, rhs_len);

	//Node* temp;
	Node* temp_head = nullptr;
	Node* curr;

	if(lhs_head != nullptr && rhs_head != nullptr){
		if(lhs_head -> key < rhs_head -> key){
			if(temp_head == nullptr){
			temp_head = lhs_head;
			curr = temp_head;
			lhs_head = lhs_head -> next;
			} else {
				curr -> next = lhs_head;
				curr = curr -> next;
				lhs_head = lhs_head -> next;
			}
		} else {
			
			if(temp_head == nullptr){
				temp_head = rhs_head;
				curr = temp_head;
				rhs_head = rhs_head -> next;	
			} else {
				curr -> next = rhs_head;
				curr = curr -> next;
				rhs_head = rhs_head -> next;
		}
	}
	head = temp_head;
	
}
}
