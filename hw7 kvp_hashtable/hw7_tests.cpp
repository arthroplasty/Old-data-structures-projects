// File Name: hw7_tests.cpp
// Purpose: tests the implementation for class
//	    hash_table_collection

#include <iostream>
#include <string>
#include <assert.h>
#include <gtest/gtest.h>
#include <algorithm>
#include "hash_table_collection.h"

using namespace std;

//test 1
TEST(BasicCollectionTest, CorrectSize) {
	HashTableCollection<string, double> c;
	ASSERT_EQ(c.size(), 0);
	c.insert("a", 10.0);
	ASSERT_EQ(c.size(), 1);
	c.insert("b", 20.0);
	ASSERT_EQ(c.size(), 2);
	
	// test compare size between 2 vectors
	HashTableCollection<int, string> foo;
	foo.insert(0, "zero");
	foo.insert(1, "one");
	foo.insert(2, "two");
	ASSERT_EQ(foo.size(), 3);

	HashTableCollection<char, string> bar;
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
TEST(BasicCollectionTest, InsertAndFindAndResizeRehash) {
	HashTableCollection<string, double> c;
	double v;
	ASSERT_EQ(c.find("a" , v), false);
	c.insert("a", 10.0);
	ASSERT_EQ(c.find("a", v), true);
	ASSERT_EQ(v, 10.0);
	ASSERT_EQ(c.find("b", v), false);
	c.insert("b", 20.0);
	ASSERT_EQ(c.find("b", v), true);
	ASSERT_EQ(v, 20.0);

	// test insert and find 
	// with values inserted out of order
	// this also tests resize_and_rehash
	// since load factor will be > 75%
	HashTableCollection<int, string> a;
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
	a.insert(12, "twelve");
	a.insert(11, "eleven");
	a.insert(14, "fourteen");
	a.insert(13, "thirteen");
	a.insert(16, "sixteen");
	a.insert(15, "fifteen");
	a.insert(18, "eighteen");
	a.insert(17, "seventeen");
	a.insert(19, "nineteen");
	a.insert(20, "twenty");
	a.insert(21, "twenty-one");
	a.insert(22, "twenty-two");
	a.insert(24, "twenty-four");
	a.insert(23, "twenty-three");
	a.insert(26, "twenty-six");
	a.insert(25, "twenty-five");
	a.insert(27, "twenty-seven");

	for(int i = 1; i <= 10; i++){
		ASSERT_EQ(a.find(i, testval), true);
	}

}




// Test 3
TEST ( BasicCollectionTest , RemoveElems ) {
	HashTableCollection< string ,double > c ;
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
	HashTableCollection<int, string> foo;
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

	// try to remove from empty table
	HashTableCollection<int, string> test;
	test.remove(1);
}

// Test 4
TEST ( BasicCollectionTest , GetKeys ) {
	HashTableCollection <string ,double > c ;
	c.insert ("a", 10.0);
	c.insert ("b", 20.0);
	c.insert ("c", 30.0);
	vector <string> ks ;
	c.keys( ks );
	vector <string>:: iterator iter ;
	iter = find (ks.begin(), ks.end (), "a");
	/*ASSERT_NE (iter, ks.end ());
	iter = find (ks.begin(), ks.end(), "b");
	ASSERT_NE (iter ,ks.end());
	iter = find (ks.begin(), ks.end(), "c");
	ASSERT_NE (iter ,ks.end ());
	iter = find (ks.begin(), ks.end(), "d");
	ASSERT_EQ (iter, ks.end ());

	// test table with length of 1
	HashTableCollection<int, string> foo;
	foo.insert(1, "one");
	vector <int> bar;
	foo.keys(bar);
	vector<int>:: iterator it;
	it = find(bar.begin(), bar.end(), 1);
	ASSERT_EQ(it, bar.begin());
	it = find(bar.begin(), bar.end(), 2);
	ASSERT_EQ(it, bar.end());*/
}

// Test 5
TEST ( BasicCollectionTest , GetKeyRange) {
	HashTableCollection <string, double > c ;
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

	// test range with table of size only 2
	HashTableCollection<int, string> foo;
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
	
	// test range with table of out-of-order inserted keys
	HashTableCollection<int, string> john;
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
TEST ( BasicCollectionTest , CopyConstructor) {
	HashTableCollection< string ,double > c ;
	c.insert("a", 10.0);
	c.insert("e", 50.0);
	c.insert("c", 30.0);
	c.insert("b", 20.0);
	c.insert("d", 40.0);
	HashTableCollection<string, double> g(c);
	
	vector<string> keys1;
	c.keys(keys1);
	std::sort(keys1.begin(), keys1.end());
	vector<string> keys2;
	g.keys(keys2);
	std::sort(keys2.begin(), keys2.end());
	for(int i = 0; i < keys1.size(); ++i){
		ASSERT_EQ(keys1.at(i), keys2.at(i));
	}
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
