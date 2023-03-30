#include <iostream>
#include <string>
#include <assert.h>
#include <gtest/gtest.h>
#include <algorithm>
#include "vector_collection.h"

using namespace std;

//test 1
TEST(BasicCollectionTest, CorrectSize) {
	VectorCollection<string, double> c;
	ASSERT_EQ(c.size(), 0);
	c.insert("a", 10.0);
	ASSERT_EQ(c.size(), 1);
	c.insert("b", 20.0);
	ASSERT_EQ(c.size(), 2);

	// test compare size between 2 vectors
	VectorCollection<int, string> foo;
	foo.insert(0, "zero");
	foo.insert(1, "one");
	foo.insert(2, "two");
	ASSERT_EQ(foo.size(), 3);

	VectorCollection<char, string> bar;
	bar.insert('a', "alpha");
	bar.insert('b', "bravo");
	assert(foo.size() > bar.size());
	bar.insert('c', "charlie");
	assert(foo.size() == bar.size());
	bar.insert('d', "delta");
	assert(foo.size() < bar.size());
	ASSERT_EQ(bar.size(), 4);
}

// test 2
	TEST(BasicCollectionTest, InsertAndFind) {
	VectorCollection<string, double> c;
	double v;
	ASSERT_EQ(c.find("a" , v), false);
	c.insert("a", 10.0);
	ASSERT_EQ(c.find("a", v), true);
	ASSERT_EQ(v, 10.0);
	ASSERT_EQ(c.find("b", v), false);
	c.insert("b", 20.0);
	ASSERT_EQ(c.find("b", v), true);
	ASSERT_EQ(v, 20.0);
}




// Test 3
TEST ( BasicCollectionTest , RemoveElems ) {
	VectorCollection < string ,double > c ;
	c . insert ("a", 10.0);
	c . insert ("b", 20.0);
	c . insert ("c", 30.0);
	double v ;
	c . remove ("a");
	ASSERT_EQ ( c . find ("a", v ) , false );
	c . remove ("b");
	ASSERT_EQ ( c . find ("b", v ) , false );
	c . remove ("c");
	ASSERT_EQ ( c . find ("c", v ) , false );
	ASSERT_EQ ( c . size () , 0);

	// tests pairs with same keys
	VectorCollection<int, string> foo;
	foo.insert(1, "one");
	foo.insert(1, "another_one");
	foo.insert(1, "yet_another_one");
	string bar;
	foo.remove(1);
	ASSERT_EQ(foo.find(1, bar), true);
	foo.remove(1);
	ASSERT_EQ(foo.find(1, bar), true);
	foo.remove(1);
	ASSERT_EQ(foo.find(1, bar), false);
}

// Test 4
TEST ( BasicCollectionTest , GetKeys ) {
	VectorCollection < string ,double > c ;
	c . insert ("a", 10.0);
	c . insert ("b", 20.0);
	c . insert ("c", 30.0);
	vector < string > ks ;
	c . keys ( ks );
	vector < string >:: iterator iter ;
	iter = find ( ks . begin () , ks . end () , "a");
	ASSERT_NE ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "b");
	ASSERT_NE ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "c");
	ASSERT_NE ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "d");
	ASSERT_EQ ( iter , ks . end ());

	// test vector with length of 1
	VectorCollection<int, string> foo;
	foo.insert(1, "one");
	vector <int> bar;
	foo.keys(bar);
	vector<int>:: iterator it;
	it = find(bar.begin(), bar.end(), 1);
	ASSERT_EQ(it, bar.begin());
	ASSERT_EQ(it, bar.end());
}

// Test 5
TEST ( BasicCollectionTest , GetKeyRange ) {
	VectorCollection < string ,double > c ;
	c . insert ("a", 10.0);
	c . insert ("b", 20.0);
	c . insert ("c", 30.0);
	c . insert ("d", 40.0);
	c . insert ("e", 50.0);
	vector < string > ks ;
	c . find ("b", "d", ks );
	vector < string >:: iterator iter ;
	iter = find ( ks . begin () , ks . end () , "b");
	ASSERT_NE ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "c");
	ASSERT_NE ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "d");
	ASSERT_NE ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "a");
	ASSERT_EQ ( iter , ks . end ());
	iter = find ( ks . begin () , ks . end () , "e");
	ASSERT_EQ ( iter , ks . end ());

	// test range with vector of size only 2
	VectorCollection<int, string> foo;
	foo.insert(1, "one");
	foo.insert(2, "two");
	vector<int> bar;
	foo.find(1, 2, bar);
	vector<int>:: iterator it;
	it = find(bar.begin(), bar.end(), 1);
	ASSERT_EQ(it, bar.begin());
	it = find(bar.begin(), bar.end(), 2);
	ASSERT_EQ(it, bar.end());
}

// Test 6
TEST ( BasicCollectionTest , KeySort ) {
	VectorCollection < string ,double > c ;
	c . insert ("a", 10.0);
	c . insert ("e", 50.0);
	c . insert ("c", 30.0);
	c . insert ("b", 20.0);
	c . insert ("d", 40.0);
	vector < string > sorted_ks ;
	c . sort ( sorted_ks );
	// check if sort order
	for (int i = 0; i < int ( sorted_ks . size ()) - 1; ++ i )
	ASSERT_LE ( sorted_ks [ i ] , sorted_ks [ i +1]);
	
	// test sorting list with same keys
	VectorCollection<int, string> foo;
	foo.insert(1, "one");
	foo.insert(1, "two");
	foo.insert(1, "john_cena");
	vector<int> bar;
	foo.sort(bar);
	for(int i = 0; i < int (bar.size()) - 1; ++i)
		ASSERT_LE(bar[i], bar[i+1]);
	
}





int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
