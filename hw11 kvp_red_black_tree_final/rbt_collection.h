// Filename: rbt_collection.h
// Purpose: Defines and implements the functions for red black tree collection

#ifndef RBT_COLLECTION_H
#define RBT_COLLECTION_H

#include <vector>
#include "collection.h"
#include <cmath>

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

	void print() const;
	
	private :

	// binary search tree node structure
	struct Node {
		K key ;
		V value ;
		Node * left ;
		Node * right ;
		bool is_black;
		bool is_dbl_black_left ; // for remove rotations
		bool is_dbl_black_right ; // for remove rotations

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

	// recursive helper to remove node with given key
	Node * remove ( const K & the_key , Node * parent , Node * subtree_root , bool & found );

	// helper to perform a single rebalance step on a red - black tree on remove
	Node * remove_color_adjust ( Node * parent );

	void print(Node* subtree, std::vector<std::pair<K,bool>>& ks) const;

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

template < typename K , typename V >
void RBTCollection <K ,V >:: remove ( const K & the_key )
{
	// check if anything to remove
	if ( root == nullptr )
		return ;
	// create a " fake " root to pass in as parent of root
	Node * root_parent = new Node ;
	root_parent -> key = root -> key ;
	root_parent -> left = nullptr ;
	root_parent -> right = root ;
	root_parent -> is_black = true ;
	root_parent -> is_dbl_black_left = false ;
	root_parent -> is_dbl_black_right = false ;
	// call remove
	bool found = false ;
	root_parent = remove ( the_key , root_parent , root , found );
	// update results
	if (found) {
		collection_size--;
		root = root_parent -> right ;
		if (root) {
			root -> is_black = true ;
			root -> is_dbl_black_right = false ;
			root -> is_dbl_black_left = false ;
		}
	}
	delete root_parent ;
}

template < typename K , typename V >
typename RBTCollection <K ,V >:: Node *
RBTCollection <K ,V >:: remove ( const K & the_key , Node * parent , Node * subtree_root , bool & found )
{
	
	if ( subtree_root && the_key < subtree_root -> key ){
		std::cout << "go left..." << std::endl;
		subtree_root -> left = remove ( the_key , subtree_root , subtree_root -> left , found );}
	else if ( subtree_root && the_key > subtree_root -> key ){
		subtree_root -> right = remove ( the_key , subtree_root , subtree_root -> right , found );
		std::cout << "go right..." << std::endl;}
	else if ( subtree_root && the_key == subtree_root -> key ) {
		std::cout << "found..." << std::endl;
		found = true ;
		// leaf node
		if (! subtree_root -> left && ! subtree_root -> right ) {
			// if node is black then set double -black , adjust parent ,
			// and delete subtree root ...
			

			if(subtree_root -> is_black){
				if(parent -> left == subtree_root)
					parent -> is_dbl_black_left;
				else
					parent -> is_dbl_black_right;
			}
			delete subtree_root;
		}
		// left non - empty but right empty
		else if ( subtree_root -> left && ! subtree_root -> right ) {
			// similar to above
			

			if(parent -> left == subtree_root){
				parent -> left = subtree_root -> left;
				if(subtree_root -> is_black)
					parent -> is_dbl_black_left;
			}
			else {
                  		parent -> right = subtree_root -> left;
                  		if(subtree_root -> is_black)
                    			parent -> is_dbl_black_right;                
            		}
			delete subtree_root;
		}
		// left empty but right non - empty
		else if (! subtree_root -> left && subtree_root -> right ) {
			
			if(parent -> left == subtree_root){
				parent -> left = subtree_root -> right;
				if(subtree_root -> is_black)
					parent -> is_dbl_black_left;
			}
			else {
                 		parent -> right = subtree_root -> right;
                  		if(subtree_root -> is_black)
                    			parent -> is_dbl_black_right;                
            		}
			delete subtree_root;
		}
		// left and right non empty
		else {
			
			// find inorder successor (right , then iterate left )
			// then call remove again on inorder successor key and subtree root ’s
			// right child once the key and value copy is complete
			Node* i_o_successor = subtree_root -> right;
			while(i_o_successor && i_o_successor -> left){
				i_o_successor = i_o_successor -> left;	
			}
			subtree_root -> key = i_o_successor -> key;
			subtree_root -> value = i_o_successor -> value;
			bool is_found;
			subtree_root -> right = remove(i_o_successor -> key, parent, subtree_root -> right, is_found);
		}
	}

	if (!found)
		return parent;

	// backtracking , adjust color at parent
	return remove_color_adjust ( parent );
}


template < typename K , typename V >
typename RBTCollection <K ,V >:: Node *
RBTCollection <K ,V >:: remove_color_adjust ( Node * subtree_root )
{
	// subtree root is " grandparent " g, with left child gl and right child gr
	Node* g = subtree_root;
	Node* gl = g -> left;
	Node* gr = g -> right;
	// parent p is either gl or gr
	Node* p = nullptr;
	bool left_parent = false;
	if (gl && (gl -> is_dbl_black_left || gl -> is_dbl_black_right)) {
		p = gl;
		left_parent = true;
	}
	else if ( gr && ( gr -> is_dbl_black_left || gr -> is_dbl_black_right ))
		p = gr;
	else
		return subtree_root;

	// parent ’s left child is a double black node
	if (p -> is_dbl_black_left ) {
	// do the following cases
	// case 1: red sibling
	if ((p-> right and !(p-> right-> is_black) and ((p->right->left and p->right->left->is_black) or (p->right->left==nullptr))
             and ((p-> right-> right and p-> right-> right-> is_black) or (p->right->right==nullptr)))){
            
            p -> is_black = false;
			p -> right -> is_black = true;
			p = rotate_left(p);
            if (left_parent)
                g-> left = p;
            else
                g-> right = p;
			p -> is_dbl_black_left = false;
           
        }
	// case 2: black sibling with red child ( outside )
	else if ((p-> right and p-> right-> is_black)
             and p-> right-> right  and !(p-> right-> right-> is_black)) {
           
            p = rotate_left(p);
            if (left_parent)
                g-> left = p;
            else
                g-> right = p;
            bool temp = p -> is_black;
			p -> is_black = p -> right -> is_black;
			p -> right -> is_black = temp;
			p-> is_dbl_black_left = false;
            
           
        }
	// case 2: black sibling with red child ( inside )
	else if ((p-> right and p-> right-> is_black)
             and p-> right-> left and !(p-> right-> left-> is_black)) {
            
			p -> right = rotate_right(p -> right);
			p = rotate_left(p);
			p -> is_black = p -> left -> is_black;
            if (left_parent)
                g-> left = p;
            else
                g-> right = p;
            p-> is_dbl_black_left = false;
            
        }
	// case 3: black sibling with black children , red parent
	else if ((p-> right and p-> right-> is_black) and ((p->right->right and p->right->right->is_black) or (p->right->right == nullptr))
             and ((p-> right-> left and p-> right-> left-> is_black) or (p->left->left == nullptr)) and !(p -> is_black)) {
          
			p -> is_black = true;
			p -> right -> is_black = false;
			if (left_parent){
				g -> left = p;
				g -> is_dbl_black_left = true;
			}
			else {
				g -> right = p;
				g -> is_dbl_black_right = true;
			}
			p -> is_dbl_black_left = false;
           
        }
	
	// case 3: black sibling with black children , black parent
	else if ((p-> right and p-> right-> is_black) and ((p->right->right and p->right->right->is_black) or (p->right->right == nullptr))
             and ((p-> right-> left and p-> right-> left-> is_black) or (p->left->left == nullptr)) and (p -> is_black)) {
           
			p -> right -> is_black = false;
			if (left_parent){
				g -> left = p;
				g -> is_dbl_black_left = true;
			}
			else {
				g -> right = p;
				g -> is_dbl_black_right = true;
			}
			p -> is_dbl_black_left = false;
           
        }
	}

	// parent ’s right child is a double black node
	if (p -> is_dbl_black_right) {
	// do the following cases
	// case 1: red sibling
	if ((p-> left and !(p-> left-> is_black) and ((p->left->left and p->left->left->is_black) or (p->left->left==nullptr))
             and ((p-> left-> right and p-> left-> right-> is_black) or (p->left->right==nullptr)))) {
            
            p -> is_black = false;
			p -> left -> is_black = true;
			p = rotate_right(p);
            if (left_parent)
                g-> left = p;
            else
                g-> right = p;
			p -> is_dbl_black_right = false;
	
            
    }
	// case 2: black sibling with red child ( outside )
	else if ((p-> left and p-> left-> is_black)
             and p-> left-> left and !(p-> left-> left-> is_black)) {
            
		p -> left = rotate_left(p -> left);
		p = rotate_right(p);
		p -> is_black = p -> right -> is_black;
            if (left_parent)
                g-> left = p;
            else
                g-> right = p;
            p-> is_dbl_black_right = false;
            
    }
	// case 2: black sibling with red child ( inside )
	else if ((p-> right and p-> right-> is_black)
             and p-> right-> left and !(p-> right-> left-> is_black)) {
            
			p -> right = rotate_right(p -> right);
			p = rotate_left(p);
			p -> is_black = p -> left -> is_black;
            if (left_parent)
                g-> left = p;
            else
                g-> right = p;
            p-> is_dbl_black_right = false;
            
    }
	// case 3: black sibling with black children , red parent
	else if ((p-> left and p-> left-> is_black) and ((p->left->left and p->left->left->is_black) or (p->left->left == nullptr))
             and ((p-> left-> right and p-> left-> right-> is_black) or (p->left->right == nullptr)) and !(p -> is_black)) {
            
			p -> is_black = true;
			p -> left -> is_black = false;
			if (left_parent){
				g -> left = p;
				g -> is_dbl_black_left = true;
			}
			else {
				g -> right = p;
				g -> is_dbl_black_right = true;
			}
			p -> is_dbl_black_right = false;
            
     }
	// case 3: black sibling with black children , black parent
	else if ((p-> left and p-> left-> is_black) and ((p->left->right and p->left->right->is_black) or (p->left->right == nullptr))
             and ((p-> left-> left and p-> left-> left-> is_black) or (p->left->left == nullptr)) and (p -> is_black)) {
           		p -> left -> is_black = false;
			if (left_parent){
				g -> left = p;
				g -> is_dbl_black_left = true;
			}
			else {
				g -> right = p;
				g -> is_dbl_black_right = true;
			}
			p -> is_dbl_black_right = false;
            
        }
	}

	// connect up the subtree_root to the parent
	if (left_parent)
		subtree_root -> left = p;
	else
		subtree_root -> right = p;

	return subtree_root;
}

template<typename K,typename V>
void RBTCollection<K,V>::print() const
{
	std::vector<std::pair<K,bool>> ks;
	print(root, ks);
	std::cout << std::endl;
	for(int i = 0; i < ks.size(); i++)
	{
		for(int j = 0; j <= std::floor(std::log2(ks.size())) - std::floor(std::log2(i+1)); j++)
		{
			std::cout << " ";
		}
		std::cout << ks[i].first << " " << ks[i].second << std::endl;
	}
	std::cout << std::endl;
}


template<typename K,typename V>
void RBTCollection<K,V>::print(Node* subtree, std::vector<std::pair<K,bool>>& ks) const
{
	if(subtree)
	{
		std::vector<std::pair<K,bool>> left_ks, right_ks;
		print(subtree->left, left_ks);
		print(subtree->right, right_ks);
		int size = std::max(left_ks.size(), right_ks.size());
		for(int i = left_ks.size(); i < size; i++)
		{
			left_ks.push_back(std::pair<K,bool>(K(), 1));
		}
		for(int i = right_ks.size(); i < size; i++)
		{
			right_ks.push_back(std::pair<K,bool>(K(), 1));
		}
		ks.push_back(std::pair<K,bool>(subtree->key, subtree->is_black));
		for(int i = 0,k = 0; i < size; k++)
		{
			for(int j = 0; j < std::pow(2,k); j++)
			{
				ks.push_back(std::pair<K,bool>(left_ks[0].first, left_ks[0].second));
				i++;
				left_ks.erase(left_ks.begin());
			}
			for(int j = 0; j < std::pow(2,k); j++)
			{
				ks.push_back(std::pair<K,bool>(right_ks[0].first, right_ks[0].second));
				i++;
				right_ks.erase(right_ks.begin());
			}
		}
	}
}
# endif