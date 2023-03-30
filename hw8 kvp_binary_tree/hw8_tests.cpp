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
	c . insert ("b", 20.0);
	ASSERT_EQ (true , c . find ("b", v ));
	ASSERT_EQ (20.0 , v );
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