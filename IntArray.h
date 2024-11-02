//specification file for the IntArray class
#ifndef INTARRAY_H
#define INTARRAY_H

class IntArray
{
private:
    int* aptr;                         //pointer to the array
    int arraySize;                     //holds the array size
    void subscriptError();             //handles invalid subscripts
public:
    //exception error handling
    class OutOfRange
    {
    private:
        int index;                    //stores invalid index value
    public:
        OutOfRange(int i)             //constructor sets error index
        {
            index = i;                //initialize index with parameter
        }
        int getIndex() const          //returns the stored index
        {
            return index;
        }

    };

    IntArray(int);                     //constructor
    IntArray(const IntArray&);        //copy constructor
    ~IntArray();                       //destructor

    int size() const                   //returns the array size
    {
        return arraySize;
    }

    const IntArray operator=(const IntArray&);  //overloaded = operator
    int& operator[](const int&);      //overloaded [] operator
};
#endif
