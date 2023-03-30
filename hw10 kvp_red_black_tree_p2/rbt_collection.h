#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include "collection.h"


template < typename K , typename V >
class RBTCollection : public Collection <K ,V >
{
	public :

	// create an empty linked list
	RBTCollection ();

	// copy a linked list
	RBTCollection ( const RBTCollection <K ,V >& rhs );

	// assign a linked list
	RBTCollection <K ,V >& operator =( const RBTCollection <K ,V >& rhs );

	// delete a linked list
	~RBTCollection ();

	// insert a key - value pair into the collection
	void insert (const K & the_key , const V & the_val);

	// remove a key - value pair from the collection
	void remove ( const K & the_key );

	// find the value associated with the key
	bool find ( const K & the_key , V & the_val ) const ;

	// find the keys associated with the range
	void find ( const K & k1 , const K & k2 , std :: vector <K >& keys ) const ;

	// return all keys in the collection
	void keys ( std :: vector <K >& keys ) const ;

	// return collection keys in sorted order
	void sort ( std :: vector <K >& keys ) const ;

	// return the number of keys in collection
	int size () const ;

	// return the height of the tree
	int height () const ;

	private :

	// binary search tree node structure
	struct Node {
		K key ;
		V value ;
		Node * left ;
		Node * right ;
		bool is_black;
	};

	// root node of the search tree
	Node * root ;

	// number of k-v pairs in the collection
	int collection_size ;

	// helper to recursively empty search tree
	void make_empty ( Node * subtree_root );
	
	// helper functions to perform a single right rotation
	Node* rotate_right (Node* k2);

	// helper functions to perform a single left rotation
	Node* rotate_left (Node* k2);
	
	Node * insert_helper (const K & the_key , const V & the_val , Node * subtree_root);
	
	// helper to recursively build sorted list of keys
	void inorder ( const Node * subtree , std :: vector <K >& keys ) const;

	// helper to recursively build sorted list of keys
	void preorder ( const Node * subtree , std :: vector <K >& keys ) const;
	
	//void preorder_copy (Node * lhs_subtree, const Node * rhs_subtree);

	// helper to recursively find range of keys
	void range_search ( const Node * subtree , const K & k1 , const K & k2 ,
	std :: vector <K >& keys ) const ;

	// return the height of the tree rooted at subtree_root
	int height ( const Node * subtree_root ) const ;

	Node* remove_helper(const K & the_key, Node* subtree_root);

};


template < typename K , typename V >
RBTCollection <K ,V >:: RBTCollection () :
collection_size (0) , root ( nullptr )
{
}

template < typename K , typename V >
void RBTCollection <K ,V >:: make_empty ( Node * subtree_root )
{
	if(subtree_root != nullptr){
		make_empty(subtree_root -> left);
		make_empty(subtree_root -> right);
		delete subtree_root;
	}
	collection_size = 0;
}


template < typename K , typename V >
RBTCollection <K ,V >::~ RBTCollection ()
{
	make_empty(root);
}

template < typename K , typename V >
RBTCollection <K ,V >:: RBTCollection ( const RBTCollection <K ,V >& rhs )
: collection_size (0) , root ( nullptr )
{
	*this = rhs ;
}

template < typename K , typename V >
RBTCollection <K ,V >& RBTCollection <K ,V >:: operator =( const RBTCollection <K ,V >& rhs )
{
	if(this == &rhs)
		return *this ;
	// delete current
	make_empty(root);
	// build tree
	std::vector<K> ks ;
	preorder (rhs.root, ks );
	V val;
	bool temp;
	for(K it_key : ks){
		temp = find(it_key, val);
		insert(it_key, val);
	}
	return *this ;
}

template < typename K , typename V >
void RBTCollection <K ,V >:: insert (const K & the_key , const V & the_val)
{
	root = insert_helper(the_key, the_val, root);
}


template < typename K , typename V >
void RBTCollection <K ,V >:: remove ( const K & the_key )
{
	//todo
}

template < typename K , typename V >
bool RBTCollection <K ,V >:: find ( const K & the_key , V & the_val ) const
{
	Node* temp = root;
	while(temp != nullptr){
		if(the_key == temp -> key){
			the_val = temp -> value;
			return true;
		} else if(the_key < temp -> key){
			temp = temp -> left;
		} else {
			temp = temp -> right;
		}
	}
	return false;
}

template < typename K , typename V >
void RBTCollection <K ,V >::
range_search ( const Node * subtree , const K & k1 , const K & k2 , std :: vector <K >& ks ) const
{
	if(subtree){
		if(subtree -> key > k1)
			range_search(subtree -> left, k1, k2, ks);
		
		if(subtree -> key >= k1 && subtree -> key <= k2)
			ks.push_back(subtree -> key);
		
		if(subtree -> key < k2)
			range_search(subtree -> right, k1, k2, ks);
	}	
}

template < typename K , typename V > void
RBTCollection <K ,V >:: find ( const K & k1 , const K & k2 , std :: vector <K >& ks ) const
{
	// defer to the range search ( recursive ) helper function
	range_search ( root , k1 , k2 , ks );
}


template < typename K , typename V >
void RBTCollection <K ,V >:: inorder ( const Node * subtree , std :: vector <K >& ks ) const
{
	if(subtree != nullptr){
		inorder(subtree -> left, ks);
		ks.push_back(subtree -> key);
		inorder(subtree -> right, ks);
	}
}


template < typename K , typename V >
void RBTCollection <K ,V >:: preorder ( const Node * subtree , std :: vector <K >& ks ) const
{
	if(subtree != nullptr){
		ks.push_back(subtree -> key);
		preorder(subtree -> left, ks);
		preorder(subtree -> right, ks);
	}
}

template < typename K , typename V >
void RBTCollection <K ,V >:: keys ( std :: vector <K >& ks ) const
{
	// defer to the inorder ( recursive ) helper function
	inorder(root , ks );
}

template < typename K , typename V >
void RBTCollection <K ,V >:: sort ( std :: vector <K >& ks ) const
{
	// defer to the inorder ( recursive ) helper function
	inorder(root, ks );
}

template < typename K , typename V >
int RBTCollection <K ,V >:: size () const
{
	return collection_size ;
}


template < typename K , typename V >
int RBTCollection <K ,V >:: height ( const Node * subtree_root ) const
{
	if(subtree_root == nullptr)
		return 0;
	int left = height(subtree_root -> left);
	int right = height(subtree_root -> right);
	if(left > right)
		return left + 1;
	return right + 1;
}

template < typename K , typename V >
int RBTCollection <K ,V >:: height () const
{
	// defer to the height ( recursive ) helper function
	return height ( root );
}

template < typename K , typename V >
typename RBTCollection <K ,V >::Node* RBTCollection <K ,V >::remove_helper(const K& the_key, Node* subtree_root)
{
	//todo
}


template < typename K , typename V >
typename RBTCollection <K ,V >:: Node * RBTCollection <K ,V >:: rotate_right ( Node * k2 )
{
	Node* a = k2 -> left;
	Node* b = a -> right;
	a -> right = k2;
	k2 -> left = b;
	return a;
}

template < typename K , typename V >
typename RBTCollection <K ,V >:: Node * RBTCollection <K ,V >:: rotate_left ( Node * k2 )
{
	Node* a = k2 -> right;
	Node* b = a -> left;
	a -> left = k2;
	k2 -> right = b;
	return a;
}
template < typename K , typename V >
typename RBTCollection <K ,V >::Node * RBTCollection <K ,V >:: insert_helper (const K & the_key , const V & the_val , Node * subtree_root)
{
	if(subtree_root == nullptr){
		Node* temp = new Node;
		temp -> key = the_key;
		temp -> value = the_val;
		temp -> left = nullptr;
		temp -> right = nullptr;
		temp -> is_black = false;
		subtree_root = temp;
		collection_size++;
	} 
	
	else if (the_key < subtree_root -> key)
	{
		subtree_root -> left = insert_helper(the_key, the_val, subtree_root -> left);
	}
	 
	else 
	{
		subtree_root -> right = insert_helper(the_key, the_val, subtree_root -> right);
	}

	
	//if this is root of the tree being inserted, paint it black
	if(subtree_root == root){
		subtree_root -> is_black = true;
	}
	
	
	if(subtree_root)
	{
		if(subtree_root -> is_black) //grandparent is black
		{
			{
				if((subtree_root -> left && !subtree_root -> left -> is_black) && (subtree_root -> right && !subtree_root -> right -> is_black)) //both parent & uncle red
				{
					if(subtree_root != root)
						subtree_root -> is_black = false;
					subtree_root -> left -> is_black = true;
					subtree_root -> right -> is_black = true;
				}
				else
				{
					if((subtree_root -> left && !subtree_root -> left -> is_black) && (subtree_root -> left -> left && !subtree_root -> left -> left -> is_black)) //LL case
					{
						subtree_root = rotate_right(subtree_root);
						subtree_root -> is_black = true;
						subtree_root -> right -> is_black = false;
					}
					else if((subtree_root -> left && !subtree_root -> left -> is_black) && (subtree_root -> left -> right && !subtree_root -> left -> right -> is_black))//LR case
					{
						subtree_root -> left = rotate_left(subtree_root -> left);
						subtree_root = rotate_right(subtree_root);
						subtree_root -> is_black = true;
						subtree_root -> right -> is_black = false;
						
					}
					else if((subtree_root -> right && !subtree_root -> right -> is_black) && (subtree_root -> right -> right && !subtree_root -> right -> right -> is_black)) //RR case
					{
						subtree_root = rotate_left(subtree_root);
						subtree_root -> is_black = true;
						subtree_root -> left -> is_black = false;
					}
					else if((subtree_root -> right && !subtree_root -> right -> is_black) && (subtree_root -> right -> left && !subtree_root -> right -> left -> is_black)) //RL case
					{
						subtree_root -> right = rotate_right(subtree_root -> right);
						subtree_root = rotate_left(subtree_root);
						subtree_root -> is_black = true;
						subtree_root -> left -> is_black = false;
					}
				}	
			}
		}
	}
	return subtree_root;
	
	
}
# endif