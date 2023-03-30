#include <string>
#include <vector>
#include <iostream>

#include "integer.h"

using namespace std;

Integer::Integer()
{
	digits.push_back(0);
	return;
}

Integer::Integer(string val)
{
	negative = false;
	int n = int(val.size());

	if(n == 0){
		digits.push_back(0);
		return;
	}

	if(val[0] == '0' && n > 1) {
		digits.push_back(0);
		return;
	}
	for(int i = n-1; i>=0; --i) {
		char c = val[i];
		if(isdigit(c))
			digits.push_back(c - '0');
		else {
			digits.clear();
			digits.push_back(0);
			return;
		}
	}
}

bool Integer::operator<(const Integer& rhs) const
{
	if((negative == false) && (rhs.negative == false)){
		if(this->digits.size() < rhs.digits.size())
			return true;
		else if(this->digits.size() > rhs.digits.size())
			return false;
		else {
			for(int i = (this->digits.size()-1); i>=0; --i){
				if(this->digits[i] < rhs.digits[i])
					return true;
				else if(this->digits[i] > rhs.digits[i])
					return false;
			}
			return false;
		}
	}
	
	else if((negative == false) && (rhs.negative == true)){
		return false;
	}
	else if((negative == true) && (rhs.negative == false)){
		return true;
	}
	
	else {
		if(this->digits.size() < rhs.digits.size())
			return false;
		else if(this->digits.size() > rhs.digits.size())
			return true;
		else {
			for(int i = (this->digits.size()-1); i>=0; --i){
				if(this->digits[i] < rhs.digits[i])
					return false;
				else if(this->digits[i] > rhs.digits[i])
					return true;
			}
			return false;
		}
	}
		
}

bool Integer::operator>(const Integer& rhs) const
{
	return rhs < *this;
}

bool Integer::operator==(const Integer& rhs) const
{
	return !(rhs < *this) and !(*this < rhs);
}

bool Integer::operator<=(const Integer& rhs) const
{
	return !(rhs < *this);
}

bool Integer::operator>=(const Integer& rhs) const
{
	return !(*this < rhs);
}

bool Integer::operator!=(const Integer& rhs) const
{
	return !(*this == rhs);
}


std::ostream& operator <<(std::ostream& out, const Integer& rhs)
{
	if(rhs.negative == true)
		cout<< "-";	

	for(int i =(rhs.digits.size()-1); i>=0; --i){
		out << rhs.digits[i];
	}
	return out;
}

Integer Integer::operator+(const Integer& rhs) const
{
	Integer tmp;
	tmp.negative = false;
	
	if((negative == false) && (rhs.negative == false)){
		tmp.digits = add(this->digits, rhs.digits);
		tmp.negative = false;
		return tmp;
	}
	else if((negative == true) xor (rhs.negative == true)){
		if(*this == rhs){
			tmp.digits[0] = 0;
			tmp.negative = false;
			return tmp;
		}
		else if((*this > rhs && (negative == true)) || (rhs > *this && (rhs.negative == true))){
			tmp.digits = sub(this->digits, rhs.digits);
			tmp.negative = true;
			return tmp;
		}
		else {
			tmp.digits = sub(this->digits, rhs.digits);
			tmp.negative = false;
			return tmp;
		}
	}
	else {
		tmp.digits = add(this->digits, rhs.digits);
		tmp.negative = true;
		return tmp;
	}
	
	//end here
	return tmp;
}

Integer Integer::operator-(const Integer& rhs) const{
	Integer tmp;
	tmp.negative = false;
	
	if((negative == false) && (rhs.negative ==false)){
		if(*this > rhs){
			tmp.digits = sub(this->digits, rhs.digits);
			tmp.negative = false;
			return tmp;
		}
		else if(*this < rhs){
			tmp.digits = sub(rhs.digits, this->digits);
			tmp.negative = true;
			return tmp;
		}
		else {
			tmp.digits[0] = 0;
			tmp.negative = false;
			return tmp;
		}
	}
	
	if((negative == true) xor (rhs.negative == true)){
		if((negative == true) && (rhs.negative ==false)){
			tmp.digits = sub(this->digits, rhs.digits);
			tmp.negative = true;
			return tmp;
		}
		else if((negative == false) && (rhs.negative ==true)){
			tmp.digits = add(this->digits, rhs.digits);
			tmp.negative = false;
			return tmp;
		}
	}
	
	if ((negative == true) && (rhs.negative == true)){
		if(*this < rhs){
			tmp.digits = sub(this->digits, rhs.digits);
			tmp.negative = true;
			return tmp;
		}
		else if(*this > rhs){
			tmp.digits = sub(rhs.digits, this->digits);
			tmp.negative = false;
			return tmp;
		}
		else {
			tmp.digits[0] = 0;
			tmp.negative = false;
			return tmp;
		}
	}
	return tmp;
}
		
	


//private helpers for adding and subtracting digit lists
digit_list Integer::add ( const digit_list & lhs , const digit_list & rhs ) const
{
	Integer tmp;
	tmp.negative = false;
	int lhs_size = lhs.size();
	int rhs_size = rhs.size();
	int tmp_int = 0;
	int carry = 0;
	int smaller_one = 0;
	int bigger_one = 0;

	
	if(lhs_size == rhs_size){
		for(int i=0; i<lhs_size; i++){
			if(carry !=0)
				tmp_int += 1;
			carry = 0;
			tmp_int += lhs[i] + rhs[i];
			if(tmp_int >= 10){
				tmp_int -= 10;
				carry = 1;
			}
			if(i == 0)
				tmp.digits[i] = tmp_int;
			else
				tmp.digits.push_back(tmp_int);				
			tmp_int = 0;
		}
		if(carry !=0){
			tmp.digits.push_back(1);
		}
		return tmp.digits;
	}			 
	

	else {
		for(int k=0; k<smaller_one; k++){
			if(carry !=0)
				tmp_int += 1;
			carry = 0;
			tmp_int += lhs[k] + rhs[k];
			if(tmp_int >= 10){
				tmp_int -= 10;
				carry = 1;
			}
			if(k == 0)
				tmp.digits[k] = tmp_int;
			else
				tmp.digits.push_back(tmp_int);				
			tmp_int = 0;
		}
		
		for(int j=smaller_one; j<bigger_one; j++){
			if (carry !=0)
				tmp_int +=1;
			carry = 0;
			
			if(lhs_size > rhs_size)
				tmp_int += lhs[j];
			else
				tmp_int += rhs[j];
			
			if(tmp_int >= 10){
				tmp_int -= 10;
				carry = 1;
			}
			tmp.digits.push_back(tmp_int);
			tmp_int = 0;
		}
		if(carry !=0)
			tmp.digits.push_back(1);
		return tmp.digits;
	}
}
	
digit_list Integer::sub ( const digit_list & lhs , const digit_list & rhs ) const
{
	Integer tmp;
	int tmp_int = 0;
	int carry = 0;
	int small_size = rhs.size();
	int smaller_one = 0;
	int bigger_one = 0;
	
	if(lhs_size == rhs_size){
		for(int i=0; i<lhs_size; i++){
			if(carry !=0)
				tmp_int -= 1;
			carry = 0;
			tmp_int += (lhs[i] - rhs[i]);
			if(tmp_int < 0){
				tmp_int += 10;
				carry = 1;
			}
			tmp.digits.push_back(tmp_int);				
			tmp_int = 0;
		}
		return tmp.digits;
	}
		
			 	

	else {
		for(int k=0; k<smaller_one; k++){
			if(carry !=0)
				tmp_int -= 1;
			carry = 0;
			tmp_int += (lhs[k] - rhs[k]);
			if(tmp_int < 0){
				tmp_int += 10;
				carry = 1;
			}
			tmp.digits.push_back(tmp_int);				
			tmp_int = 0;
		}
		
		for(int j=smaller_one; j<bigger_one; j++){
			if (carry !=0)
				tmp_int -=1;
			carry = 0;
			
			if(lhs_size > rhs_size)
				tmp_int += lhs[j];
			else
				tmp_int += rhs[j];
			
			if(tmp_int < 0){
				tmp_int += 10;
				carry = 1;
			}
			tmp.digits.push_back(tmp_int);
			tmp_int = 0;
		}
		
		for(int i = 0; i<tmp.digits.size(); i++){
			tmp.digits.erase(digits.begin())
		}
		return tmp.digits;
	}
	
	return tmp.digits;
}