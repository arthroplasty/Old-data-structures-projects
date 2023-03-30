// File Name: hw5_tests.cpp
// Professor Bowers
// Purpose: tests the implementation for class
//	    binsearch_collection

#include <iostream>
#include <string>
#include <assert.h>
#include <gtest/gtest.h>
#include <algorithm>
#include "binsearch_collection.h"

using namespace std;

//test 1
TEST(BasicCollectionTest, CorrectSize) {
	BinsearchCollection<string, double> c;
	ASSERT_EQ(c.size(), 0);
	c.insert("a", 10.0);
	ASSERT_EQ(c.size(), 1);
	c.insert("b", 20.0);
	ASSERT_EQ(c.size(), 2);

	// test compare size between 2 vectors
	BinsearchCollection<int, string> foo;
	foo.insert(0, "zero");
	foo.insert(1, "one");
	foo.insert(2, "two");
	ASSERT_EQ(foo.size(), 3);

	BinsearchCollection<char, string> bar;
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
	BinsearchCollection<string, double> c;
	double v;
	ASSERT_EQ(c.find("a" , v), false);
	c.insert("a", 10.0);
	ASSERT_EQ(c.find("a", v), true);
	ASSERT_EQ(v, 10.0);
	ASSERT_EQ(c.find("b", v), false);
	c.insert("b", 20.0);
	ASSERT_EQ(c.find("b", v), true);
	ASSERT_EQ(v, 20.0);

	// test insert and find on a longer vector
	// with values inserted out of order
	BinsearchCollection<int, string> a;
	string testval;
	a.insert(10, "ten");
	a.insert(1, "one");
	a.insert(6, "six");
	a.insert(8, "eight");
	a.insert(4, "four");
	a.insert(9, "nine");
	a.insert(3, "three");
	a.insert(0, "zero");
	a.insert(7, "seven");
	a.insert(5, "five");
	a.insert(2, "two");
	for(int i = 1; i <= 10; i++){
		ASSERT_EQ(a.find(i, testval), true);
	}

}




// Test 3
TEST ( BasicCollectionTest , RemoveElems ) {
	BinsearchCollection< string ,double > c ;
	c.insert ("a", 10.0);
	c.insert ("b", 20.0);
	c.insert ("c", 30.0);
	double v ;
	c.remove ("a");
	ASSERT_EQ (c.find("a", v ), false );
	c.remove ("b");
	ASSERT_EQ (c.find("b", v ), false );
	c.remove ("c");
	ASSERT_EQ (c.find("c", v ), false );
	ASSERT_EQ (c.size() , 0);

	// tests pairs with same keys
	BinsearchCollection<int, string> foo;
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

	// try to remove from empty vector
	BinsearchCollection<int, string> test;
	test.remove(1);
}

// Test 4
TEST ( BasicCollectionTest , GetKeys ) {
	BinsearchCollection <string ,double > c ;
	c.insert ("a", 10.0);
	c.insert ("b", 20.0);
	c.insert ("c", 30.0);
	vector <string> ks ;
	c.keys( ks );
	vector <string>:: iterator iter ;
	iter = find (ks.begin(), ks.end (), "a");
	ASSERT_NE (iter, ks.end ());
	iter = find (ks.begin(), ks.end(), "b");
	ASSERT_NE (iter ,ks.end());
	iter = find (ks.begin(), ks.end(), "c");
	ASSERT_NE (iter ,ks.end ());
	iter = find (ks.begin(), ks.end(), "d");
	ASSERT_EQ (iter, ks.end ());

	// test vector with length of 1
	BinsearchCollection<int, string> foo;
	foo.insert(1, "one");
	vector <int> bar;
	foo.keys(bar);
	vector<int>:: iterator it;
	it = find(bar.begin(), bar.end(), 1);
	ASSERT_EQ(it, bar.begin());
	it = find(bar.begin(), bar.end(), 2);
	ASSERT_EQ(it, bar.end());
}

// Test 5
TEST ( BasicCollectionTest , GetKeyRange ) {
	BinsearchCollection <string, double > c ;
	c.insert ("a", 10.0);
	c.insert ("b", 20.0);
	c.insert ("c", 30.0);
	c.insert ("d", 40.0);
	c.insert ("e", 50.0);
	vector <string> ks ;
	c.find ("b", "d", ks );
	vector < string >:: iterator iter ;
	iter = find (ks.begin(), ks.end(), "b");
	ASSERT_NE (iter, ks.end());
	iter = find (ks.begin(), ks.end(), "c");
	ASSERT_NE (iter, ks.end());
	iter = find (ks.begin(), ks.end(), "d");
	ASSERT_NE (iter, ks.end());
	iter = find (ks.begin(), ks.end() , "a");
	ASSERT_EQ (iter, ks.end());
	iter = find (ks.begin(), ks.end() , "e");
	ASSERT_EQ (iter, ks.end());

	// test range with vector of size only 2
	BinsearchCollection<int, string> foo;
	foo.insert(1, "one");
	foo.insert(2, "two");
	vector<int> bar;
	foo.find(1, 2, bar);
	vector<int>:: iterator it;
	it = find(bar.begin(), bar.end(), 1);
	ASSERT_EQ(it, bar.begin());
	it = find(bar.begin(), bar.end(), 2);
	ASSERT_NE(it, bar.end());
	it = find(bar.begin(), bar.end(), 3);
	ASSERT_EQ(it, bar.end());
	
	// test range with vector of out-of-order inserted
	// keys, this will also test insert as well since it
	// checks the to see the vector of keys is sorted.
	BinsearchCollection<int, string> john;
	john.insert(3, "three");
	john.insert(8, "eight");
	john.insert(5, "five");
	john.insert(2, "two");
	john.insert(10, "ten");
	john.insert(4, "four");
	john.insert(1, "one");
	john.insert(7, "seven");
	john.insert(6, "six");
	john.insert(9, "nine");
	
	vector<int> intvec;
	john.find(2,8, intvec);
	for(int i = 2; i<=8; i++){
		ASSERT_EQ(i, intvec[i-2]);
	}

	// passes the same vector as above, to
	// ensure the function clears vector before
	// pushing keys into it
	john.find(0,11, intvec);
	for(int i = 1; i<=10; i++){
		ASSERT_EQ(i, intvec[i-1]);
	}

}

// Test 6
TEST ( BasicCollectionTest , SortedInsertion ) {
	BinsearchCollection< string ,double > c ;
	c.insert("a", 10.0);
	c.insert("e", 50.0);
	c.insert("c", 30.0);
	c.insert("b", 20.0);
	c.insert("d", 40.0);
	vector<string> sorted_ks ;
	
	// check if sort order
	for(int i = 0; i < int (sorted_ks.size()) - 1; ++ i )
	ASSERT_LE(sorted_ks[i], sorted_ks[i +1]);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
