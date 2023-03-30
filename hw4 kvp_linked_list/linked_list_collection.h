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
	void insertion_sort ();
	
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
	if(head == nullptr){
		return;
	} else if(head==tail) {
		keys.push_back(head -> key);
	} else { 	
		Node* tmp = head;
		while(tmp != nullptr) {
			keys.push_back(tmp -> key);
			tmp = tmp -> next;
		}
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
	while(current != nullptr){
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
				
}
#endif	
