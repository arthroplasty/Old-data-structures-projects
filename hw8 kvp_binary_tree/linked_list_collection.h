// File Name: linked_list_collection.h
// Purpose: defines and implementation the class
//	    linked list with insertion sort,
//	    quicksort, and mergesort


#ifndef LINKED_LIST_COLLECTION_H
#define LINKED_LIST_COLLECTION_H

#include <vector>
#include <algorithm>
#include "collection.h"
#include <iostream>

using namespace std;

template<typename K, typename V>
class LinkedListCollection : public Collection<K, V>
{
	public:
	
	// create an empty linked list
	LinkedListCollection();

	// copy a linked list
	LinkedListCollection(const LinkedListCollection<K,V>& rhs);

	// assign a linked list
	LinkedListCollection<K,V>& operator=(const LinkedListCollection<K,V>& rhs);	
	
	// delete a linked list
	~LinkedListCollection();
		
	// insert a key-value pair into the collection
	void insert(const K& k, const V& val);
	
	// remove a key value pair from the collection
	void remove(const K& k);
	
	// find and return the value associated with the key
	bool find(const K& k, V& val) const;
	
	// find and return the list of keys >= to k1 and <= to k2
	void find(const K& k1, const K& k2, std::vector<K>& keys) const;
	
	// return all of the keys in the collection
	void keys(std::vector<K>& keys) const;
	
	// return all of the keys in ascending (sorted) order
	void sort(std::vector<K>& keys) const;
	
	// return the number of keys in the collections
	int size() const;
	
	// destructor helper function
	void delete_list();
	
	// in place sorting
	void insertion_sort();
	void quick_sort();
	void merge_sort();
	
	private:
	// linked list node structure
	struct Node {
		K key;
		V value;
		Node* next;
	};
	Node* head;
	Node* tail;
	int length;
	void qs_helper(Node* &head);
	void ms_helper(Node* left, int len);
	
};
template<typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection()
{
	head = nullptr;
	tail = nullptr;
	length = 0;
}

template<typename K, typename V>
LinkedListCollection<K,V>& LinkedListCollection<K,V>::operator=(const LinkedListCollection<K,V>& rhs)
{
	
	if(rhs.length > 0){
		delete_list();
		length = rhs.length;
		Node* tmp = rhs.head;
		head = new Node;
		head -> key = tmp -> key;
		head -> value = tmp -> value;
		head -> next = nullptr;
		tail = head;
		Node* current = head;
		tmp = tmp -> next;
		while(tmp != nullptr){
			current -> next = new Node;
			current = current -> next;
			current -> key = tmp -> key;
			current -> value = tmp -> value;
			current -> next = nullptr;
			tail = current;
			tmp = tmp -> next;		
		}
		
	}				
}


template<typename K, typename V>
LinkedListCollection<K,V>::LinkedListCollection(const LinkedListCollection<K,V>& rhs)
{
	head = nullptr;
	tail = nullptr;
	length = 0;
	*this = rhs;
}


template<typename K, typename V>
void LinkedListCollection<K,V>::insert(const K& k, const V& val)
{
	Node* ptr = new Node;
	ptr -> key = k;
	ptr -> value = val;
	ptr -> next = nullptr;
	if(head==nullptr){
		head = ptr;
		tail = ptr;
	} else {
		tail -> next = ptr;
		tail = ptr;
	}
	length++;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::remove(const K& k)
{	
	if(head==nullptr){
		return;
	} else if(head==tail){
		if(head -> key == k){
			delete head;
			length--;
		}
	} else if(head -> key == k){	
		Node* tmp = head -> next;
		delete head;
		head = tmp;
		length--;
	} else {
		Node* previous = new Node;
		Node* current = new Node;
		current = head->next;
		previous = head;
		while(current != nullptr){
			if(current -> key == k){
				previous -> next = current -> next;
				if(current == tail){
					previous = tail;
				}
				delete current;
				length--;
				return;
			} else {					
				previous = current;
				current = current -> next;
			}
		}
	}
}

template<typename K, typename V>
bool LinkedListCollection<K,V>::find(const K& k, V& val) const
{
	Node* ptr = new Node;
	ptr = head;
	while(ptr != nullptr){
		if(ptr-> key == k){
			val = ptr -> value;
			ptr = nullptr;
			delete ptr;	
			return true;
		} else {
			ptr = ptr->next;
		}
	}
	return false;
		
}

template<typename K, typename V>
void LinkedListCollection<K,V>::find(const K& k1, const K& k2, std::vector<K>& keys) const
{
	bool is_Real_Key_One = false;
	bool is_Real_Key_Two = false;
	Node* ptr = head;
	Node* keyptr;
	while(ptr != nullptr){
		if(ptr->key == k1) {
			is_Real_Key_One = true;
			keyptr = ptr;
			break;
		} else {
			ptr = ptr->next;
		}
	}
	if(!(is_Real_Key_One)){
		return;
	}
	while(ptr != nullptr){
		if(ptr->key == k2) {
			is_Real_Key_Two = true;
			break;
		} else {
			ptr = ptr->next;
		}
	}
	if(!(is_Real_Key_Two)){
		return;
	}
	if(k1 == k2){
		keys.push_back(ptr -> key);
	} else { 
		while(keyptr != ptr->next){
			keys.push_back(keyptr->key);
			keyptr = keyptr->next;
		}
	}
}

template<typename K, typename V>
void LinkedListCollection<K,V>::keys(std::vector<K>& keys) const
{
	keys.clear();
	Node* temp = head;
	while(temp){
		keys.push_back(temp -> key);
		temp = temp -> next;
	}	
}

template<typename K, typename V>
void LinkedListCollection<K,V>::sort(std::vector<K>& keys) const
{
	Node* ptr = head;
	while (ptr != nullptr) {
		keys.push_back(ptr->key);
		ptr = ptr->next;
	}
	std::sort(keys.begin(), keys.end());
}

template<typename K, typename V>
int LinkedListCollection<K,V>::size() const
{
	return length;
}

template<typename K, typename V>
void LinkedListCollection<K,V>::delete_list()
{
	Node* tmp;
	tmp = head;
	while(tmp != nullptr){
		head = head -> next;
		delete tmp;
		tmp = head;
	}
}

template<typename K, typename V>
LinkedListCollection<K,V>::~LinkedListCollection()
{
	delete_list();
}

template<typename K, typename V>
void LinkedListCollection<K,V>::insertion_sort()
{
	if(head == nullptr || head -> next == nullptr)
		return;
	Node* current = head;
	Node* temp;
	while(current -> next != nullptr){
		if(current -> key <= current -> next -> key)
			current = current -> next;
		else{
			temp = current -> next;
			current -> next = current -> next -> next;
			Node* ptr = head -> next;
			Node* previous_ptr = head;
			while(ptr != nullptr){
				if(temp -> key < previous_ptr -> key){
					temp -> next = previous_ptr;
					head = temp;
					break;
				} else if(temp -> key < ptr -> key) {
					temp -> next = ptr;
					previous_ptr -> next = temp;
					break;
				} else {
					previous_ptr = ptr;
					ptr = ptr -> next;
				}
			}
		}
	}
}

template<typename K, typename V>
void LinkedListCollection<K,V>::quick_sort()
{			
	qs_helper(head);
}

template<typename K, typename V>
void LinkedListCollection<K,V>::qs_helper(Node* &head)
{
	if(head == nullptr || head -> next == nullptr){
		return;
	}
	Node* pivot = head;
	head = head -> next;
	pivot -> next = nullptr;
	
	Node* lhs = nullptr;	
	Node** pplhs = &lhs;
	Node* rhs = nullptr;	
	Node** pprhs = &rhs;

	while(head != nullptr){
		if(head -> key < pivot -> key){
			*pplhs = head;
			pplhs = &(*pplhs) -> next;
		} else {
			*pprhs = head;
			pprhs = &(*pprhs) -> next;
		}
		head = head -> next;
	}
	*pplhs = *pprhs = nullptr;
	qs_helper(lhs);
	qs_helper(rhs);

	while(*pplhs){
		pplhs = &(*pplhs) -> next;
	}
	*pplhs = pivot;
	pivot -> next = rhs;
	head = lhs;
}


template<typename K, typename V>
void LinkedListCollection<K,V>::merge_sort()
{			
	ms_helper(head, length);
}


template<typename K, typename V>
void LinkedListCollection<K,V>::ms_helper(Node* left, int len)
{
	if(len == 0 || len == 1){
		return;
	}

	int lhs_len = 1;
	int rhs_len = 1;
	int mid = len / 2;

	Node* lhs_head = left;
	Node* lhs_tail = left;
	Node* rhs_head = left;
	Node* rhs_tail = left;
	
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
	
	if(lhs_head > rhs_head){
		head = rhs_head;
		rhs_head = rhs_head -> next;
	} else {
		head = lhs_head;
		lhs_head = lhs_head -> next;
	}
	Node* curr;
	Node* tmp;
	curr = head;
	
	while(lhs_head != nullptr && rhs_head != nullptr){
		if(lhs_head -> key < rhs_head -> key){
			tmp = lhs_head;
			curr -> next = tmp;
			curr = tmp;
			lhs_head = lhs_head -> next;
		} else {
			tmp = rhs_head;
			curr -> next = tmp;
			curr = tmp;
			rhs_head = rhs_head -> next;
		}
		
	}


	while(lhs_head != nullptr){
		curr -> next = lhs_head;
		curr = lhs_head;
		lhs_head = lhs_head -> next;
	}
	while(rhs_head != nullptr){
		curr -> next = rhs_head;
		curr = rhs_head;
		rhs_head = rhs_head -> next;
	}
}

#endif	
