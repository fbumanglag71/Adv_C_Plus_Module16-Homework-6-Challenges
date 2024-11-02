#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H
#include <iostream> //for input-output operations
#include <new>       //for bad_alloc exception handling
#include <cstdlib>   //for exit function
using namespace std; //simplify standard library usage

//pre-condition:T supports default and copy constructors
//post-condition:manages dynamic array with resizing
template <class T>
class SimpleVector
{
private:
    T* aptr;          //pointer to allocated array
    int arraySize;    //number of elements in array
    int capacity;     //capacity of the array
    void memError();  //handles memory allocation errors
    void subError();  //handles subscripts out of range
    void resize(int newSize); //resizes the array if needed

public:
    //default constructor initializes empty vector
    SimpleVector()
    {
        aptr = nullptr;
        arraySize = 0;
        capacity = 0;
    }

    //constructor with size parameter
    SimpleVector(int);

    //copy constructor
    SimpleVector(const SimpleVector&);

    //destructor
    ~SimpleVector();

    //returns the current size of the array
    int size() const { return arraySize; }

    //returns value at specific position
    T getElementAt(int position);

    //overloaded [] operator for array access
    T& operator[](const int&);

    //adds value to array's end
    void push_back(T value);

    //removes last element in array
    void pop_back();
};

//constructor for SimpleVector class
//pre-condition:parameter s must be non-negative
//post-condition:allocates array of size s
template <class T>
SimpleVector<T>::SimpleVector(int s) : arraySize(s), capacity(s)
{
    try
    {
        aptr = new T[s];
    }
    catch (bad_alloc)
    {
        memError();
    }

    for (int count = 0; count < arraySize; count++)
        *(aptr + count) = 0; //initialize elements to zero
}

//copy constructor for SimpleVector class
//pre-condition:valid SimpleVector object passed
//post-condition:creates deep copy of object
template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector& obj)
{
    arraySize = obj.arraySize;
    capacity = obj.capacity;
    aptr = new T[capacity];
    if (aptr == 0)
        memError();

    for (int count = 0; count < arraySize; count++)
        *(aptr + count) = *(obj.aptr + count); //copy elements
}

//destructor for SimpleVector class
//pre-condition:none
//post-condition:deallocates dynamic array memory
template <class T>
SimpleVector<T>::~SimpleVector()
{
    if (capacity > 0)
        delete[] aptr; //delete array if allocated
}

//handles memory allocation errors
//pre-condition:none
//post-condition:outputs error and exits program
template <class T>
void SimpleVector<T>::memError()
{
    cout << "ERROR: Cannot allocate memory.\n";
    exit(EXIT_FAILURE);
}

//handles subscript out-of-range errors
//pre-condition:none
//post-condition:outputs error and exits program
template <class T>
void SimpleVector<T>::subError()
{
    cout << "ERROR: Subscript out of range.\n";
    exit(EXIT_FAILURE);
}

//returns value at given subscript
//pre-condition:sub must be within array bounds
//post-condition:returns array element at sub
template <class T>
T SimpleVector<T>::getElementAt(int sub)
{
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub];
}

//overloaded [] operator for array access
//pre-condition:sub must be within array bounds
//post-condition:returns reference to element at sub
template <class T>
T& SimpleVector<T>::operator[](const int& sub)
{
    if (sub < 0 || sub >= arraySize)
        subError();
    return aptr[sub];
}

//resizes the array if capacity reached
//pre-condition:newSize > current capacity
//post-condition:allocates new array, copies data
template <class T>
void SimpleVector<T>::resize(int newSize)
{
    try
    {
        T* temp = new T[newSize]; //create new larger array
        for (int i = 0; i < arraySize; i++)
            temp[i] = aptr[i]; //copy elements to new array

        delete[] aptr; //delete old array
        aptr = temp;   //reassign to new array
        capacity = newSize; //update capacity
    }
    catch (bad_alloc)
    {
        memError();
    }
}

//adds an element at array's end
//pre-condition:valid T type value
//post-condition:resizes if needed, appends value
template <class T>
void SimpleVector<T>::push_back(T value)
{
    if (arraySize >= capacity)
        resize(capacity == 0 ? 1 : capacity * 2); //double capacity if needed

    aptr[arraySize++] = value; //append new element
}

//removes the last element from array
//pre-condition:array has elements to pop
//post-condition:decreases array size by one
template <class T>
void SimpleVector<T>::pop_back()
{
    if (arraySize > 0)
        arraySize--; //decrement size if non-zero
    else
        throw out_of_range("No elements to pop."); //throw exception if empty
}

#endif
