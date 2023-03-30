#include <iostream>
#include "hash_table_collection.h"
#include "test_driver.h"

using namespace std;

int main(int argc, char** argv)
{
	// cehck command-line arguments
	if (argc != 2) {
				cout << "usage: " << argv[0] << " filename" << endl;
				return 1;
	}
	
	// run basic performance tests
	HashTableCollection<string,double> test_collection;
	TestDriver<string,double> driver(argv[1], &test_collection);
	driver.run_tests();
	driver.print_results();
}