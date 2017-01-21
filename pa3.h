//  pa3.h
//Header that contains the method initializations needed to utilize the stack and vector class

#ifndef pa3_h
#define pa3_h

#include <iostream>
#include <fstream> //to read/write over files
#include <vector>
#include <stdlib.h>
#include <algorithm> //for remove and find functions
#include <string> //for getline function
using namespace std;


//Stack class
class Stack{
public:
    //**VARIABLE
    vector <string> word;
    

    //**CONSTRUCTOR
    Stack(){
        //The stack class contains this vector in order for the methods below to be properly used
        vector <string> word;
    }
    
    
    //**METHODS
    //Returns whatever is on the top of the stack
    string top(){
        return word.back();
    }
    
    //Checks whether the stack is empty
    bool empty(){
        return word.empty();
    }
    
    //Adds new words to the stack
    void push(string s){
        word.push_back(s);
    }
    
    //Removes the item from the stack
    void pop(){
        word.pop_back();
    }
    
    //Gets the size of the stack
    size_t size() {
        return word.size();
    }
};




//A print metho to print out any vector, such as the evaluations below.
//Evaluations: Keywords, identifiers, constants, operators, delimiters, syntax errors, depth of nested loops
void printAnalysis( vector<string> evaluate);


//This method goes through each line within the file and checks for keywords, identifiers, constants, operators, delimiters, syntax errors, and the depth of the nested loops.
//It uses the printAnalysis method to print out the final results
void checkFileLines(vector<string> filelines);




//Method to remove duplicates and sort the vectors before it actually gets printed onto the screen
template <typename T>
void sortAndRemove(vector<T> &s);




#endif /* pa3_h */