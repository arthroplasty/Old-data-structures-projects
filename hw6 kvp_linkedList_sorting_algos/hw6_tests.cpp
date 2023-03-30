// File Name: linked_list_collection.h
// Purpose: tests the implementation of
//	    linked_list_collection.h

#include <iostream>
#include <string>
#include <assert.h>
#include <gtest/gtest.h>
#include <algorithm>
#include "linked_list_collection.h"

using namespace std;

//test 1
TEST(BasicCollectionTest, CorrectSize) {
	LinkedListCollection<string, double> c;
	ASSERT_EQ(c.size(), 0);
	c.insert("a", 10.0);
	ASSERT_EQ(c.size(), 1);
	c.insert("b", 20.0);
	ASSERT_EQ(c.size(), 2);
	
	
	// test compare size between 2 vectors
	LinkedListCollection<int, string> foo;
	foo.insert(0, "zero");
	foo.insert(1, "one");
	foo.insert(2, "two");
	ASSERT_EQ(foo.size(), 3);

	
	LinkedListCollection<char, string> bar;
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
	LinkedListCollection <string, double> c;
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
	LinkedListCollection <string, double> c ;
	c . insert ("a", 10.0);
	c . insert ("b", 20.0);
	c . insert ("c", 30.0);
	double v ;
	c . remove ("a");
	ASSERT_EQ (c.find("a", v ), false );
	c . remove ("b");
	ASSERT_EQ (c.find("b", v ), false );
	c . remove ("c");
	ASSERT_EQ (c.find("c", v ), false );
	ASSERT_EQ (c.size(), 0);
	

	// tests remove on pairs with same keys
	LinkedListCollection <int, string> foo;
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

	// test remove in middle of list, then remove tail, then head
	LinkedListCollection <char, string> z;
	z.insert('w', "whiskey");
	z.insert('x', "xray");
	z.insert('y', "yankee");
	z.insert('z', "zulu");
	string alphabet;

	// removing 'y' from list, testing to make sure nothing else got removed
	z.remove('y');
	ASSERT_EQ(z.find('w', alphabet), true);
	ASSERT_EQ(z.find('x', alphabet), true);
	ASSERT_EQ(z.find('y', alphabet), false);
	ASSERT_EQ(z.find('z', alphabet), true);
	ASSERT_EQ(z.size(), 3);
	
	// removing 'x' from list, testing to make sure nothing else got removed
	z.remove('x');
	ASSERT_EQ(z.find('w', alphabet), true);
	ASSERT_EQ(z.find('x', alphabet), false);
	ASSERT_EQ(z.find('y', alphabet), false);
	ASSERT_EQ(z.find('z', alphabet), true);

	// removing 'z' (tail) from list, testing to make sure nothing else got removed
	z.remove('z');
	ASSERT_EQ(z.find('w', alphabet), true);
	ASSERT_EQ(z.find('x', alphabet), false);
	ASSERT_EQ(z.find('y', alphabet), false);
	ASSERT_EQ(z.find('z', alphabet), false);

	// removing 'w' from list, testing to make sure nothing else got removed
	z.remove('w');
	ASSERT_EQ(z.find('w', alphabet), false);
	ASSERT_EQ(z.find('x', alphabet), false);
	ASSERT_EQ(z.find('y', alphabet), false);
	ASSERT_EQ(z.find('z', alphabet), false);	
	
	// removing from an empty list, nothing should happen
	// since function will return early.
	z.remove('w');
	ASSERT_EQ(z.size(), 0);
	
}

// Test 4
TEST ( BasicCollectionTest , GetKeys ) {
	LinkedListCollection <string ,double > c ;
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
	LinkedListCollection <int, string> foo;
	foo.insert(1, "one");
	vector <int> bar;
	foo.keys(bar);
	vector<int>:: iterator it;
	it = find(bar.begin(), bar.end(), 1);
	ASSERT_EQ(it, bar.begin());
	ASSERT_EQ(foo.size(), 1);
	it = find(bar.begin(), bar.end(), 2);
	ASSERT_EQ(it, bar.end());
}

// Test 5
TEST ( BasicCollectionTest , GetKeyRange ) {
	LinkedListCollection <string, double > c ;
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

	// test range with list size only 2
	LinkedListCollection <int, string> foo;
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

	// test with range where k1 == k2
	LinkedListCollection <char, string> m;
	m.insert('m', "mike");
	m.insert('n', "november");
	m.insert('o', "oscar");
	vector<char> mks;
	m.find('n','n', mks);
	vector<char>:: iterator itt;
	itt = find(mks.begin(), mks.end(), 'n');
	ASSERT_NE(itt, mks.end());
	itt = find(mks.begin(), mks.end(), 'o');
	ASSERT_EQ(itt, mks.end());

	// test with keys not in list, key vector should be
	// empty since function will return early
	LinkedListCollection <int, string> k;
	k.insert(1, "one");
	k.insert(2, "two");
	vector<int> kks;
	// giving bad k2 as argument
	k.find(1, 3, kks);
	ASSERT_EQ(kks.size(), 0);
	// giving bad k1 as argument
	k.find(0, 2, kks);
	ASSERT_EQ(kks.size(), 0);
	// giving bad k1 AND k2 as arguments
	k.find(0, 3, kks);
	ASSERT_EQ(kks.size(), 0);

}

// Test 6
TEST ( BasicCollectionTest , KeySort ) {
	LinkedListCollection < string ,double > c ;
	c.insert ("a", 10.0);
	c.insert ("e", 50.0);
	c.insert ("c", 30.0);
	c.insert ("b", 20.0);
	c.insert ("d", 40.0);
	vector<string> sorted_ks ;
	c.insertion_sort();
	c.keys(sorted_ks);
	// check if sort order
	for (int i = 0; i < int ( sorted_ks.size ()) - 1; ++ i )
	ASSERT_LE ( sorted_ks [ i ] , sorted_ks [ i +1]);
	
	// test sorting list with same keys
	LinkedListCollection <int, string> foo;
	foo.insert(1, "one");
	foo.insert(1, "two");
	foo.insert(1, "john_cena");
	vector<int> bar;
	foo.sort(bar);
	for(int i = 0; i < int (bar.size()) - 1; ++i)
		ASSERT_LE(bar[i], bar[i+1]);
	
}

// Test 7
TEST ( BasicCollectionTest , CopyConstructorAndOperatorAssignment)
{
	LinkedListCollection <int, string> a;
	a.insert(1, "one");
	a.insert(2, "two");
	a.insert(3, "three");
	a.insert(4, "four");
	
	// test copy constructor
	LinkedListCollection <int, string> b(a);
	string v;
	ASSERT_EQ(b.find(1, v), true);
	ASSERT_EQ(v, "one");
	ASSERT_EQ(b.find(2, v), true);
	ASSERT_EQ(v, "two");
	ASSERT_EQ(b.find(3, v), true);
	ASSERT_EQ(v, "three");
	ASSERT_EQ(b.find(4, v), true);
	ASSERT_EQ(v, "four");

	// test operator =
	LinkedListCollection <int, string> c;
	c.insert(1, "JOHN_CENA");
	c.insert(2, "BROCK_LESNAR");
	c = b;

	// previous keys & values in list c should be deleted and
	// is now set to k & vs in list b
	ASSERT_EQ(c.find(1, v), true);
	ASSERT_EQ(v, "one");
	ASSERT_EQ(c.find(2, v), true);
	ASSERT_EQ(v, "two");
	ASSERT_EQ(c.find(3, v), true);
	ASSERT_EQ(v, "three");
	ASSERT_EQ(c.find(4, v), true);
	ASSERT_EQ(v, "four");
}

// Test 8
TEST ( BasicCollectionTest , InsertionSort ) {
	LinkedListCollection <int, string > c ;
	c.insert (7, "seven");
	c.insert (5, "five");
	c.insert (2, "two");
	c.insert (1, "one");
	c.insert (8, "eight");
	c.insert (3, "three");
	c.insert (9, "nine");
	c.insert (4, "four");
	c.insert (6, "six");
	c.insert (1, "ten");	
	vector<int> sorted_ks ;
	c.insertion_sort();
	c.keys(sorted_ks);
	// check if sort order
	for (int i = 0; i < int ( sorted_ks.size ()) - 1; ++ i )
		ASSERT_LE ( sorted_ks [ i ] , sorted_ks [ i +1]);

}

// Test 9
TEST ( BasicCollectionTest , QuickSort ) {
	LinkedListCollection <int, string > c ;
	c.insert (7, "seven");
	c.insert (5, "five");
	c.insert (2, "two");
	c.insert (1, "one");
	c.insert (8, "eight");
	c.insert (3, "three");
	c.insert (9, "nine");
	c.insert (4, "four");
	c.insert (6, "six");
	c.insert (1, "ten");	
	vector<int> sorted_ks ;
	c.quick_sort();
	c.keys(sorted_ks);
	// check if sort order
	for (int i = 0; i < int ( sorted_ks.size ()) - 1; ++ i )
		ASSERT_LE ( sorted_ks [ i ] , sorted_ks [ i +1]);

}

TEST ( BasicCollectionTest , MergeSort ) {
	LinkedListCollection <int, string > c ;
	c.insert (7, "seven");
	c.insert (5, "five");
	c.insert (2, "two");
	c.insert (1, "one");
	c.insert (8, "eight");
	c.insert (3, "three");
	c.insert (9, "nine");
	c.insert (4, "four");
	c.insert (6, "six");
	c.insert (1, "ten");	
	vector<int> sorted_ks ;
	c.merge_sort();
	c.keys(sorted_ks);
	// check if sort order
	for (int i = 0; i < int ( sorted_ks.size ()) - 1; ++ i )
		ASSERT_LE ( sorted_ks [ i ] , sorted_ks [ i +1]);

}




int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}