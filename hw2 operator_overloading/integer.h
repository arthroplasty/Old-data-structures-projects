#ifndef INTEGER_H_INCLUDED
#define INTEGER_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>

typedef std::vector<int> digit_list; // int is really too big ( for 0 to 9)

class Integer
{
public:
    Integer();
	// overloaded constructor , set to given string value (of all digits )
	Integer ( std :: string val );
	bool Integer operator<(const Integer& rhs) const;

private :
	digit_list digits ; // least significant digit first ( little endian )
	bool negative ;


}
#endif // INTEGER_H_INCLUDED
