#include<iostream>              //for standard input-output stream operations
#include"input.h"               //for input validation and handling
#include"MyUnit.h"              //for custom MyUnit class definitions
#include"IntArray.h"            //for IntArray class with bounds checking
#include <vector>               //for using STL vector container
#include <iomanip>              //for output formatting (e.g., setprecision)
#include "TestScores.h"         //for TestScores template class handling test score data
#include "SimpleVector.h"       //for SimpleVector template class (dynamic array)
#include "SpecSimpleVector.h"   //for specialized SimpleVector template class
#include "SearchableVector.h"   //for SearchableVector template class with search capability

using namespace std;            //simplify standard library usage


//function prototypes
int menuOption();
void Challenge3();
void Challenge4();
void Challenge6();
void Challenge7();
void Challenge8();
void Challenge12();

int main()
{
    do
    {
        switch (menuOption())
        {
        case 0: exit(1); break; //exit program if option is 0
        case 3: Challenge3(); break; //run challenge 3 function
        case 4: Challenge4(); break; //run challenge 4 function
        case 6: Challenge6(); break; //run challenge 6 function
        case 7: Challenge7(); break; //run challenge 7 function
        case 8: Challenge8(); break; //run challenge 8 function
        case 12: Challenge12(); break; //run challenge 12 function
        default: cout << "\t\terror - invalid option.please re-enter."; break;
        }
        cout << "\n";
        system("pause"); //pause for user to view output

    } while (true);

    return EXIT_SUCCESS;
}


int menuOption()
{
    cout << "\n\tCMPR121 Chapter 16 - Exceptions and Templates by Francisco Bumanglag";
    cout << "\n\t" << string(60, char(205));
    cout << "\n\t3. Minimum/Maximum Templates";
    cout << "\n\t4. Absolute Value Template";
    cout << "\n\t6. IntArray Class Exception";
    cout << "\n\t7. TestScores Class";
    cout << "\n\t8. SimpleVector Modification";
    cout << "\n\t12. Specialized Templates";
    cout << "\n\t" << string(60, char(196));
    cout << "\n\t0. Exit the Program";
    cout << "\n\t" << string(60, char(205));

    return inputInteger("\n\tOption: ", 0, 12); //get user input within range

}

//pre-condition:a and b must support > operator
//post-condition:returns the larger of a or b 
template<class T>
T maximum(T a, T b)
{
    return (a > b ? a : b); //compare values and return maximum
}

//pre-condition:a and b must support < operator
//post-condition:returns the smaller of a or b 
template<class T>
T minimum(T a, T b)
{
    return (a < b ? a : b); //compare values and return minimum
}

void Challenge3()
{
    int a = inputInteger("\n\tEnter value of a: ");
    int b = inputInteger("\n\tEnter value of b: ");

    //MyUnit a;  //does not have > operator overloaded
    //MyUnit b;

    cout << "\tMaximum: " << maximum(a, b) << "\n";       //call the maximum template function
    cout << "\tMinimum: " << minimum(a, b) << "\n";       //call the minimum template function
}

//pre-condition:n must support < and - operators
//post-condition:returns the absolute value of n
template<class T>
T absolute(T n)
{
    return (n < 0 ? -n : n); //return positive value of n
}

void Challenge4()
{
    int n = inputInteger("\n\tEnter value of n: ");

    cout << "\n\tAbsolute(n): " << absolute(n) << "\n"; //call the absolute template function
}


//this will be used on your 3rd exam
void Challenge6()
{
    IntArray testIA(2); //constructor creates an array of 2 elements
    testIA[0] = 888;    //reassign first element at index 0
    testIA[1] = 777;    //reassign second element at index 1

    //try to process an instruction causing out-of-range exception
    try
    {
        testIA[2] = 666; //attempt to access index out of bounds
    }
    catch (IntArray::OutOfRange e)    //catch out-of-range exception
    {
        cout << "\tERROR: " << e.getIndex() << " is out of range.\n";

        //continue on...but don't exit the program
    }
}

void Challenge7()
{
    vector<int> testScores;
    int numScores, score;

    //use inputInteger to get validated numScores within range
    numScores = inputInteger("\tEnter the number of test scores: ", 0, 100);

    for (int i = 0; i < numScores; ++i)
    {
        //use inputInteger to validate each score within range
        score = inputInteger("\tEnter score " + to_string(i + 1) + " (0 - 100): ", 0, 100);
        testScores.push_back(score); //add score to vector
    }

    try
    {
        TestScores<int> ts(testScores); //using template with int type

        //display average score with one decimal point
        cout << fixed << setprecision(1);  //set decimal precision
        cout << "\tAverage score: " << static_cast<double>(ts.getAverage()) << endl;
    }
    catch (const invalid_argument& e)
    {
        cout << "\tError: " << e.what() << endl; //display error message
    }
}


void Challenge8()
{
    SimpleVector<int> sv;
    try
    {
        cout << "\tPushing values 10, 20, 30...\n";
        sv.push_back(10); //push first value
        sv.push_back(20); //push second value
        sv.push_back(30); //push third value

        cout << "\tElements in SimpleVector: ";
        for (int i = 0; i < sv.size(); i++)
            cout << sv[i] << " "; //display vector elements
        cout << endl;

        cout << "\tPopping one value...\n";
        sv.pop_back(); //pop last element

        cout << "\tElements in SimpleVector: ";
        for (int i = 0; i < sv.size(); i++)
            cout << sv[i] << " "; //display vector elements
        cout << endl;

        cout << "\tPopping all values...\n";
        sv.pop_back(); //pop next element
        sv.pop_back(); //pop next element
        sv.pop_back();  //this should throw an exception

    }
    catch (const out_of_range& e)
    {
        cout << "\tException: " << e.what() << endl; //handle out of range exception
    }
}

void Challenge12()
{
    //using SpecSimpleVector<int>
    SpecSimpleVector<int> intVector(5); //create int vector of size 5
    for (int i = 0; i < intVector.size(); i++)
        intVector[i] = i * 10; //initialize elements

    cout << "\tSpecSimpleVector<int> contents: ";
    for (int i = 0; i < intVector.size(); i++)
        cout << intVector[i] << " "; //display int vector elements
    cout << endl;

    //using SpecSimpleVector<string> specialized template
    SpecSimpleVector<string> stringVector(3); //create string vector of size 3
    stringVector[0] = "apple"; //initialize first element
    stringVector[1] = "banana"; //initialize second element
    stringVector[2] = "cherry"; //initialize third element

    cout << "\tSpecSimpleVector<string> contents: ";
    for (int i = 0; i < stringVector.size(); i++)
        cout << stringVector[i] << " "; //display string vector elements
    cout << endl;

    //using SearchableVector<int>
    SearchableVector<int> intSearchVector(5); //create searchable int vector of size 5
    for (int i = 0; i < intSearchVector.size(); i++)
        intSearchVector[i] = i * 10; //initialize elements

    int searchInt = 20; //element to search for
    int pos = intSearchVector.findItem(searchInt); //find item position
    cout << "\tSearching for " << searchInt << " in SearchableVector<int>: ";
    cout << (pos != -1 ? "Found at index " + to_string(pos) : "Not found") << endl;

    //using SearchableVector<string> specialized template
    SearchableVector<string> stringSearchVector(3); //create searchable string vector of size 3
    stringSearchVector[0] = "apple"; //initialize first element
    stringSearchVector[1] = "banana"; //initialize second element
    stringSearchVector[2] = "cherry"; //initialize third element

    string searchString = "banana"; //string to search for
    pos = stringSearchVector.findItem(searchString); //find item position
    cout << "\tSearching for \"" << searchString << "\" in SearchableVector<string>: ";
    cout << (pos != -1 ? "Found at index " + to_string(pos) : "Not found") << endl;
}
