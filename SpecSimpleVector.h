#ifndef SPECSIMPLEVECTOR_H
#define SPECSIMPLEVECTOR_H
#include <iostream> //for input-output operations
#include <string>   //for string manipulation
#include <new>       //for bad_alloc exception handling
#include <cstdlib>   //for exit function
using namespace std; //simplify standard library usage

//pre-condition:T supports default and copy constructors
//post-condition:manages dynamic array with error handling
template <class T>
class SpecSimpleVector
{
protected:
    T* aptr;          //pointer to the allocated array
    int arraySize;    //number of elements in the array
    void memError();  //handles memory allocation errors
    void subError();  //handles subscripts out of range

public:
    SpecSimpleVector() { aptr = nullptr; arraySize = 0; } //default constructor
    SpecSimpleVector(int);                        //constructor with size parameter
    SpecSimpleVector(const SpecSimpleVector&);    //copy constructor
    ~SpecSimpleVector();                          //destructor

    int size() const { return arraySize; }        //returns array size
    T getElementAt(int position);                 //returns element at position
    T& operator[](const int&);                    //overloaded [] operator
};

//pre-condition:class supports string specialization
//post-condition:specialized class for managing string arrays
template <>
class SpecSimpleVector<string>
{
private:
    string* aptr;          //pointer to the allocated array
    int arraySize;         //number of elements in the array
    void memError();       //handles memory allocation errors
    void subError();       //handles subscripts out of range

public:
    SpecSimpleVector() { aptr = nullptr; arraySize = 0; } //default constructor
    SpecSimpleVector(int);                        //constructor with size parameter
    SpecSimpleVector(const SpecSimpleVector<string>&);    //copy constructor
    ~SpecSimpleVector();                          //destructor

    int size() const { return arraySize; }        //returns array size
    string getElementAt(int position);            //returns element at position
    string& operator[](const int&);               //overloaded [] operator
};

//constructor for generic SpecSimpleVector class
//pre-condition:non-negative integer size s
//post-condition:allocates array of size s
template <class T>
SpecSimpleVector<T>::SpecSimpleVector(int s)
{
    arraySize = s;
    try
    {
        aptr = new T[s];
    }
    catch (bad_alloc)
    {
        memError();
    }
    for (int count = 0; count < arraySize; count++)
        aptr[count] = T(); //initialize elements with default values
}

//constructor for SpecSimpleVector<string> specialization
//pre-condition:non-negative integer size s
//post-condition:allocates array of strings of size s
SpecSimpleVector<string>::SpecSimpleVector(int s)
{
    arraySize = s;
    try
    {
        aptr = new string[s];
    }
    catch (bad_alloc)
    {
        memError();
    }
    for (int count = 0; count < arraySize; count++)
        aptr[count] = ""; //initialize elements with empty strings
}

//copy constructor for generic SpecSimpleVector
//pre-condition:valid SpecSimpleVector object passed
//post-condition:creates deep copy of object
template <class T>
SpecSimpleVector<T>::SpecSimpleVector(const SpecSimpleVector& obj)
{
    arraySize = obj.arraySize;
    aptr = new T[arraySize];
    if (aptr == nullptr)
        memError();

    for (int count = 0; count < arraySize; count++)
        aptr[count] = obj.aptr[count]; //copy elements from source
}

//copy constructor for SpecSimpleVector<string> specialization
//pre-condition:valid SpecSimpleVector<string> object passed
//post-condition:creates deep copy of object
SpecSimpleVector<string>::SpecSimpleVector(const SpecSimpleVector<string>& obj)
{
    arraySize = obj.arraySize;
    aptr = new string[arraySize];
    if (aptr == nullptr)
        memError();

    for (int count = 0; count < arraySize; count++)
        aptr[count] = obj.aptr[count]; //copy string elements from source
}

//destructor for generic SpecSimpleVector class
//pre-condition:none
//post-condition:deallocates memory for array
template <class T>
SpecSimpleVector<T>::~SpecSimpleVector()
{
    if (arraySize > 0)
        delete[] aptr; //delete allocated array if size > 0
}

//destructor for SpecSimpleVector<string>
//pre-condition:none
//post-condition:deallocates memory for string array
SpecSimpleVector<string>::~SpecSimpleVector()
{
    if (arraySize > 0)
        delete[] aptr; //delete allocated array if size > 0
}

//memError function for generic SpecSimpleVector class
//pre-condition:none
//post-condition:outputs error and terminates program
template <class T>
void SpecSimpleVector<T>::memError()
{
    cout << "ERROR: Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//memError function for SpecSimpleVector<string>
//pre-condition:none
//post-condition:outputs error and terminates program
void SpecSimpleVector<string>::memError()
{
    cout << "ERROR: Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//subError function for generic SpecSimpleVector class
//pre-condition:none
//post-condition:outputs error and terminates program
template <class T>
void SpecSimpleVector<T>::subError()
{
    cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//subError function for SpecSimpleVector<string>
//pre-condition:none
//post-condition:outputs error and terminates program
void SpecSimpleVector<string>::subError()
{
    cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//getElementAt function for generic SpecSimpleVector
//pre-condition:subscript is within array bounds
//post-condition:returns element at specified subscript
template <class T>
T SpecSimpleVector<T>::getElementAt(int sub)
{
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub]; //return element at index
}

//getElementAt function for SpecSimpleVector<string>
//pre-condition:subscript is within array bounds
//post-condition:returns string element at specified subscript
string SpecSimpleVector<string>::getElementAt(int sub)
{
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub]; //return string element at index
}

//overloaded [] operator for generic SpecSimpleVector
//pre-condition:subscript is within array bounds
//post-condition:returns reference to element at subscript
template <class T>
T& SpecSimpleVector<T>::operator[](const int& sub)
{
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub]; //return reference to element at index
}

//overloaded [] operator for SpecSimpleVector<string>
//pre-condition:subscript is within array bounds
//post-condition:returns reference to string element at subscript
string& SpecSimpleVector<string>::operator[](const int& sub)
{
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub]; //return reference to string element at index
}

#endif
