#ifndef SEARCHABLEVECTOR_H
#define SEARCHABLEVECTOR_H
#include "SpecSimpleVector.h"

//pre-condition:T must support equality operator
//post-condition:enables search within vector
template <class T>
class SearchableVector : public SpecSimpleVector<T>
{
public:
    //constructor initializes base class with size
    SearchableVector(int size) : SpecSimpleVector<T>(size) {}

    int findItem(const T); //finds index of specified item
};

//pre-condition:supports string search functionality
//post-condition:enables string search specialization
template <>
class SearchableVector<string> : public SpecSimpleVector<string>
{
public:
    //constructor for string specialization with size
    SearchableVector(int size) : SpecSimpleVector<string>(size) {}

    int findItem(const string); //finds index of specified string
};

//findItem implementation for generic types
//pre-condition:template parameter supports equality operator
//post-condition:returns index of item or -1 if not found
template <class T>
int SearchableVector<T>::findItem(const T item)
{
    for (int count = 0; count < this->size(); count++) //loop through all elements
    {
        if (this->getElementAt(count) == item) //check if element matches item
            return count; //return index if found
    }
    return -1; //return -1 if item not found
}

//specialized findItem implementation for string
//pre-condition:template type is string
//post-condition:returns index of string or -1 if not found
int SearchableVector<string>::findItem(const string item)
{
    for (int count = 0; count < this->size(); count++) //loop through string elements
    {
        if (this->getElementAt(count) == item) //check if element matches item
            return count; //return index if found
    }
    return -1; //return -1 if string not found
}

#endif
