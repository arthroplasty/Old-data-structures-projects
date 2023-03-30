#include <iostream>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include "bst_collection.h"

using namespace std;


// Test 1
TEST ( TreeCollectionTest , CorrectSize ) {
	BSTCollection < string , double > c ;
	ASSERT_EQ (0 , c . size ());
	c . insert ("a", 10.0);
	ASSERT_EQ (1 , c . size ());
	c . insert ("b", 20.0);
	ASSERT_EQ (2 , c . size ());
}

// Test 2
TEST ( TreeCollectionTest , InsertAndFind ) {
	BSTCollection < string , double > c ;
	double v ;
	ASSERT_EQ (false , c . find ("a", v ));
	c . insert ("a", 10.0);
	ASSERT_EQ (true , c . find ("a", v ));
	ASSERT_EQ (v , 10.0);
	ASSERT_EQ (false , c . find ("b", v ));
	c . insert ("g", 320.0);
	c . insert ("h", 100.0);
	c . insert ("i", 80.0);
	c . insert ("z", 50.0);
	c . insert ("l", 40.0);
	c . insert ("m", 30.0);
	c.insert("b", 20.00);
	ASSERT_EQ (true , c . find ("b", v ));
	ASSERT_EQ (20.0 , v );
	ASSERT_EQ (true , c . find ("g", v ));
	ASSERT_EQ (320.0 , v );
	ASSERT_EQ (true , c . find ("h", v ));
	ASSERT_EQ (100.0 , v );
	ASSERT_EQ (true , c . find ("i", v ));
	ASSERT_EQ (80.0 , v );
	ASSERT_EQ (true , c . find ("z", v ));
	ASSERT_EQ (50.0 , v );
	ASSERT_EQ (true , c . find ("l", v ));
	ASSERT_EQ (40.0 , v );
	ASSERT_EQ (true , c . find ("m", v ));
	ASSERT_EQ (30.0 , v );

}

TEST ( TreeCollectionTest, InsertAndFindAndRemoveThiccTest)
{
	BSTCollection<int, char> z;
	char x;
	ASSERT_EQ(false, z.find(1, x));
	z.insert(8, 'h');
	z.insert(5, 'e');
	z.insert(10, 'j');
	z.insert(4, 'd');
	z.insert(7, 'g');
	z.insert(6, 'f');
	z.insert(1, 'a');
	z.insert(3, 'c');
	z.insert(2, 'b');
	z.insert(9, 'i');
	z.insert(11, 'k');
	ASSERT_EQ(true, z.find(11, x));
	ASSERT_EQ('k', x);
	ASSERT_EQ(true, z.find(9, x));
	ASSERT_EQ('i', x);
	ASSERT_EQ(true, z.find(2, x));
	ASSERT_EQ('b', x);
	ASSERT_EQ(true, z.find(3, x));
	ASSERT_EQ('c', x);
	ASSERT_EQ(true, z.find(1, x));
	ASSERT_EQ('a', x);
	ASSERT_EQ(true, z.find(6, x));
	ASSERT_EQ('f', x);
	ASSERT_EQ(true, z.find(7, x));
	ASSERT_EQ('g', x);
	ASSERT_EQ(true, z.find(4, x));
	ASSERT_EQ('d', x);
	ASSERT_EQ(true, z.find(10, x));
	ASSERT_EQ('j', x);
	ASSERT_EQ(true, z.find(5, x));
	ASSERT_EQ('e', x);
	ASSERT_EQ(true, z.find(8, x));
	ASSERT_EQ('h', x);
	ASSERT_EQ(11, z.size());
	z.remove(8);
	ASSERT_EQ(false, z.find(8, x));
	ASSERT_EQ(10, z.size());
	z.remove(10);
	ASSERT_EQ(false, z.find(8, x));
	ASSERT_EQ(9, z.size());
	z.remove(3);
	ASSERT_EQ(false, z.find(3, x));
	ASSERT_EQ(8, z.size());
	z.remove(9);
	ASSERT_EQ(false, z.find(9, x));
	ASSERT_EQ(7, z.size());
	z.remove(6);
	ASSERT_EQ(false, z.find(6, x));
	ASSERT_EQ(6, z.size());
	z.remove(2);
	ASSERT_EQ(false, z.find(2, x));
	ASSERT_EQ(5, z.size());
	z.remove(1);
	ASSERT_EQ(false, z.find(1, x));
	ASSERT_EQ(4, z.size());
	z.remove(4);
	ASSERT_EQ(false, z.find(4, x));
	ASSERT_EQ(3, z.size());
	z.remove(11);
	ASSERT_EQ(false, z.find(11, x));
	ASSERT_EQ(2, z.size());
	z.remove(5);
	ASSERT_EQ(false, z.find(5, x));
	ASSERT_EQ(1, z.size());
	z.remove(7);
	ASSERT_EQ(false, z.find(7, x));
	ASSERT_EQ(0, z.size());
}



// Test 3 -- THIS TEST SHOULD FAIL FOR HW8
TEST ( TreeCollectionTest , RemoveElems ) {
	BSTCollection < string , double > c ;
	c . insert ("a", 10.0);
	c . insert ("b", 20.0);
	c . insert ("c", 30.0);
	double v ;
	c . remove ("a");
	ASSERT_EQ (false , c . find ("a", v ));
	ASSERT_EQ (true , c . find ("b", v ));
	ASSERT_EQ (true , c . find ("c", v ));
	c . remove ("b");
	ASSERT_EQ (false , c . find ("b", v ));
	ASSERT_EQ (true , c . find ("c", v ));
	c . remove ("c");
	ASSERT_EQ (false , c . find ("c", v ));
	ASSERT_EQ (0 , c . size ());
}

// Test 4
TEST (TreeCollectionTest , GetKeys ) {
	BSTCollection < string , double > c ;
	c.insert ("a", 10.0);
	c.insert ("b", 20.0);
	c.insert ("c", 30.0);
	vector<string> ks ;
	c.keys(ks);
	vector <string>:: iterator iter ;
	iter = find(ks.begin(), ks.end(), "a");
	ASSERT_NE ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "b");
	ASSERT_NE ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "c");
	ASSERT_NE ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "d");
	ASSERT_EQ ( ks . end () , iter );
}

// Test 5
TEST ( TreeCollectionTest , GetKeyRange ) {
	BSTCollection < string , double > c ;
	c . insert ("a", 10.0);
	c . insert ("b", 20.0);
	c . insert ("c", 30.0);
	c . insert ("d", 40.0);
	c . insert ("e", 50.0);
	vector < string > ks ;
	c . find ("b", "d", ks );
	vector < string >:: iterator iter ;
	iter = find ( ks . begin () , ks . end () , "b");
	ASSERT_NE ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "c");
	ASSERT_NE ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "d");
	ASSERT_NE ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "a");
	ASSERT_EQ ( ks . end () , iter );
	iter = find ( ks . begin () , ks . end () , "e");
	ASSERT_EQ ( ks . end () , iter );
}

// Test 6
TEST ( TreeCollectionTest , KeySort ) {
	BSTCollection < string , double > c ;
	c . insert ("a", 10.0);
	c . insert ("e", 50.0);
	c . insert ("c", 30.0);
	c . insert ("b", 20.0);
	c . insert ("d", 40.0);
	vector < string > sorted_ks ;
	c . sort ( sorted_ks );
	ASSERT_EQ ( c . size () , sorted_ks . size ());
	for (int i = 0; i < int ( sorted_ks . size ()) - 1; ++ i ) {
		ASSERT_LE ( sorted_ks [ i ] , sorted_ks [ i +1]);
	}
}

// Test 7
TEST ( TreeCollectionTest , AssignOpTest ) {
	BSTCollection < string ,int > c1 ;
	c1 . insert ("c", 10);
	c1 . insert ("b", 15);
	c1 . insert ("d", 20);
	c1 . insert ("a", 20);
	BSTCollection < string ,int > c2 ;
	c2 = c1 ;
	ASSERT_EQ ( c1 . size () , c2 . size ());
	ASSERT_EQ ( c1 . height () , c2 . height ());
}

// Test 8
TEST ( TreeCollectionTest , GetHeightTest ) {
	BSTCollection <int, string> a;
	a.insert(8, "eight");
	a.insert(4, "four");
	a.insert(5, "five");
	a.insert(10, "ten");
	a.insert(13, "thirteen");
	a.insert(2, "two");
	a.insert(3, "three");
	a.insert(6, "six");
	ASSERT_EQ(a.height(), 4);

	BSTCollection <int, string> b;
	b.insert(0, "zero");
	b.insert(1, "one");
	b.insert(2, "two");
	b.insert(3, "three");
	b.insert(4, "four");
	b.insert(5, "five");
	b.insert(6, "six");
	b.insert(7, "seven");
	ASSERT_EQ(b.height(), 8);

	BSTCollection <int, string> c;
	ASSERT_EQ(c.height(), 0);
}


int main (int argc , char ** argv )
{
	testing :: InitGoogleTest (& argc , argv );
	return RUN_ALL_TESTS ();
}