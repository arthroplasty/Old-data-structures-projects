#include <iostream>
#include <string>
#include <assert.h>
#include <algorithm>
#include "vector_collection.h"

using namespace std;

int main()
{
	VectorCollection<int, string> a;
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
	
	a.remove(0);
	a.remove(10);
	

	
	

	//assert(a.size() == 11);

	int zeroInt = 0;
	string zeroString = "zero";
	bool zeroBool = false;
	zeroBool = a.find(zeroInt, zeroString);
	if (zeroBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int oneInt = 1;
	string oneString = "one";
	bool oneBool = false;
	oneBool = a.find(oneInt, oneString);
	if (oneBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int twoInt = 2;
	string twoString = "two";
	bool twoBool = false;
	twoBool = a.find(twoInt, twoString);
	if (twoBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int threeInt = 3;
	string threeString = "three";
	bool threeBool = false;
	threeBool = a.find(threeInt, threeString);
	if (threeBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int fourInt = 4;
	string fourString = "four";
	bool fourBool = false;
	fourBool = a.find(fourInt, fourString);
	if (fourBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int fiveInt = 5;
	string fiveString = "five";
	bool fiveBool = false;
	fiveBool = a.find(fiveInt, fiveString);
	if (fiveBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int sixInt = 6;
	string sixString = "six";
	bool sixBool = false;
	sixBool = a.find(sixInt, sixString);
	if (sixBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int sevenInt = 7;
	string sevenString = "seven";
	bool sevenBool = false;
	sevenBool = a.find(sevenInt, sevenString);
	if (sevenBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int eightInt = 8;
	string eightString = "eight";
	bool eightBool = false;
	eightBool = a.find(eightInt, eightString);
	if (eightBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;


	int nineInt = 9;
	string nineString = "nine";
	bool nineBool = false;
	nineBool = a.find(nineInt, nineString);
	if (nineBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;

	int tenInt = 10;
	string tenString = "ten";
	bool tenBool = false;
	tenBool = a.find(tenInt, tenString);
	if (tenBool == false)
		cout << "FALSE" << endl;
	else
		cout << "TRUE" << endl;









	
	
}
	
	