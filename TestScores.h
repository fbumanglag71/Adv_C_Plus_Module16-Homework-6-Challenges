#pragma once
#include <vector>       //for vector container
#include <stdexcept>    //for standard exception handling
#include <type_traits>  //for type trait checks
using namespace std;    //simplify standard library usage

//pre-condition:T must be a numeric type
//post-condition:manages scores and calculates average
template <class T>
class TestScores
{
private:
    vector<T> scores; //stores test scores

public:
    //constructor accepting a vector of scores
    //pre-condition:scores must be between 0 and 100
    //post-condition:initializes scores vector or throws exception
    TestScores(const vector<T>& testScores)
    {
        static_assert(is_arithmetic<T>::value, "Template parameter must be a numeric type."); //ensure T is numeric

        for (T score : testScores) //iterate through provided scores
        {
            if (score < 0 || score > 100) //validate score range
                throw invalid_argument("Score out of range (must be between 0 and 100).");

            scores.push_back(score); //add valid score to vector
        }
    }

    //calculates and returns average score
    //pre-condition:vector contains valid scores
    //post-condition:returns average of scores or 0 if empty
    T getAverage() const
    {
        T total = 0;
        for (T score : scores) //sum all scores in vector
            total += score;

        return scores.empty() ? static_cast<T>(0) : total / scores.size(); //return 0 if empty
    }
};
