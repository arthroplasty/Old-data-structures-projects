// Filename: hw11test.cpp
// Purpose: Tests the implements for red black tree collection

#include <iostream>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>
#include "rbt_collection.h"

using namespace std;


// Test 1
TEST ( TreeCollectionTest , CorrectSize ) {
	RBTCollection < string , double > c ;
	ASSERT_EQ (0 , c . size ());
	c . insert ("a", 10.0);
	ASSERT_EQ (1 , c . size ());
	c . insert ("b", 20.0);
	ASSERT_EQ (2 , c . size ());
}

// Test 2
TEST ( TreeCollectionTest , InsertAndFind ) {
	RBTCollection < string , double > c ;
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

// Test 3
TEST (TreeCollectionTest, DetailedInsertTest)
{
	RBTCollection<int,int> f;
	f.insert(30, 0);
	f.insert(20, 0);
	f.insert(10, 0); 
	f.insert(40, 0); 
	f.insert(50, 0); 
	f.insert(8, 0); 
	f.insert(9, 0); 
	f.insert(35, 0);
	ASSERT_EQ(8, f.size());
	ASSERT_EQ(4, f.height());
}




// Test 4
TEST (TreeCollectionTest , GetKeys ) {
	RBTCollection < string , double > c ;
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
	RBTCollection < string , double > c ;
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
	RBTCollection < string , double > c ;
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
	RBTCollection < string ,int > c1 ;
	c1 . insert ("c", 10);
	c1 . insert ("b", 15);
	c1 . insert ("d", 20);
	c1 . insert ("a", 20);
	RBTCollection < string ,int > c2 ;
	c2 = c1 ;
	ASSERT_EQ ( c1 . size () , c2 . size ());
	ASSERT_EQ ( c1 . height () , c2 . height ());
}

// Test 8
TEST ( TreeCollectionTest , SecondHeightTest ) {
	RBTCollection <int, string> a;
	a.insert(8, "eight");
	a.insert(4, "four");
	a.insert(5, "five");
	a.insert(10, "ten");
	a.insert(13, "thirteen");
	a.insert(2, "two");
	a.insert(3, "three");
	a.insert(6, "six");
	ASSERT_EQ(a.height(), 4);
	RBTCollection <int, string> b;
	b.insert(0, "zero");
	b.insert(1, "one");
	b.insert(2, "two");
	b.insert(3, "three");
	b.insert(4, "four");
	b.insert(5, "five");
	b.insert(6, "six");
	b.insert(7, "seven");
	ASSERT_EQ(b.height(), 4);
	RBTCollection <int, string> c;
	ASSERT_EQ(c.height(), 0);
}

// test 10
TEST(TreeCollectionTest, SecondInsertTest) {
	RBTCollection<int,double> c;
	for(int i = 1; i < 61; i++)
	{
		c.insert(i, (10.0 * i));
	}
	ASSERT_EQ(60, c.size());
	double v;
	ASSERT_EQ(true, c.find(10, v));
	ASSERT_EQ(100.0 , v);
	ASSERT_EQ(true, c.find(30, v));
	ASSERT_EQ(300.0 , v);
	ASSERT_EQ(true, c.find(20, v));
	ASSERT_EQ(200.0 , v);
	ASSERT_EQ(true, c.find(16, v));
	ASSERT_EQ(160.0 , v);
	ASSERT_EQ(true, c.find(5, v));
	ASSERT_EQ(50.0 , v);
	ASSERT_EQ(true, c.find(42, v));
	ASSERT_EQ(420.0 , v);
	ASSERT_NE(true, c.find(50000, v));
	ASSERT_NE(true, c.find(61, v));
	ASSERT_NE(true, c.find(-30, v));
	ASSERT_NE(true, c.find(121, v));
	ASSERT_NE(false, c.find(41, v));
	ASSERT_EQ(410.0 , v);
	ASSERT_NE(false, c.find(50, v));
	ASSERT_EQ(500.0 , v);
	ASSERT_EQ(60, c.size());
}


// Test 9
TEST(TreeCollectionTest, SecondRemoveTest) {
	RBTCollection<string,double> c;
	vector<string> ks;
	c.insert("a", 10.0);
	c.insert("b", 20.0);
	c.insert("c", 30.0);
	c.insert("d", 40.0);
	c.insert("e", 50.0);
	ASSERT_EQ(5, c.size());
	double v;
	ASSERT_EQ(false, c.find("q", v));
	ASSERT_EQ(true, c.find("b", v));
	ASSERT_EQ(20.0, v);
	c.remove("b");
	ASSERT_EQ(false, c.find("q", v));
	ASSERT_EQ(true, c.find("d", v));
	ASSERT_EQ(false, c.find("b", v));
	ASSERT_NE(20.0, v);
	ASSERT_EQ(40.0, v);
	c.insert("b", 20.0);
	ASSERT_EQ(false, c.find("q", v));
	ASSERT_EQ(true, c.find("b", v));
	ASSERT_EQ(20.0, v);
	ASSERT_NE(40.0, v);
	c.remove("b");
	ASSERT_EQ(false, c.find("q", v));
	ASSERT_EQ(true, c.find("d", v));
	ASSERT_EQ(false, c.find("b", v));
	ASSERT_NE(20.0, v);
	ASSERT_EQ(40.0, v);
	c.insert("b", 384.0);
	ASSERT_EQ(5, c.size());
	ASSERT_EQ(false, c.find("q", v));
	ASSERT_EQ(true, c.find("d", v));
	ASSERT_EQ(true, c.find("b", v));
	ASSERT_NE(20.0, v);
	ASSERT_EQ(384.0, v);
	c.remove("b");
	ASSERT_EQ(false, c.find("q", v));
	ASSERT_EQ(true, c.find("d", v));
	ASSERT_EQ(false, c.find("b", v));
	ASSERT_NE(20.0, v);
	ASSERT_NE(384.0, v);
	ASSERT_EQ(40.0, v);
}



int main (int argc , char ** argv )
{
	testing :: InitGoogleTest (& argc , argv );
	return RUN_ALL_TESTS ();
}