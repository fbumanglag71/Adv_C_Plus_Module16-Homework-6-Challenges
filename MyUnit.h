#pragma once
#include<cstring> //for string manipulation functions
#include<iostream> //for standard input-output stream operations
using namespace std; //simplify standard library usage

class MyUnit
{
private:
	unsigned short value; //stores the unit value
	char description[100]; //stores description text
public:
	MyUnit()                //default constructor
	{
		value = 0;          //initialize value to zero
		strncpy_s(description, "unknown", 99); //copy default text
	}
	void setValue(int n)    //set value to given integer
	{
		value = n;          //assign n to value
	}

	int getValue() const    //returns stored value
	{
		return value;
	}

	void setDescription(string d) //set description from string
	{
		strncpy_s(description, d.c_str(), 99); //copy string to char array
	}

	string getDescription() const //returns description as string
	{
		return description;
	}

	friend ostream& operator<<(ostream&, const MyUnit&); //overload << operator

};

ostream& operator<<(ostream& out, const MyUnit& obj)
{
	out << "\nvalue: " << obj.getValue(); //output value
	out << "\ndescription: " << obj.getDescription(); //output description

	return out;               //return output stream
}
