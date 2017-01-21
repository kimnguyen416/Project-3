//pa3.cpp

#include "pa3.h"

//****METHODS THAT ARE NEEDED TO GIVE A COMPLETE ANALYSIS OF THE TEXT FILE ARE ALL BELOW

//Sorts and removes all of the duplicates from each vector
template <typename T>
void sortAndRemove(vector<T> &s){
    sort(s.begin(), s.end());
    s.erase(unique(s.begin(), s.end()), s.end());
}


//Basic print method to help print out the analysis results
void printAnalysis( std::vector<std::string> evaluate){
    //Needs the size of whatever is being evaluated in order to print out the total result. For example: keywords, identifiers, constants, operators, and delimiters.
    size_t size = evaluate.size();
    
    
    for (int i = 0; i < size; i++){
        //It will print out all of the elements that are valid within each section that needs to be evaluated.
        std::cout << evaluate.at(i) << " ";
    }
    std::cout << "\n";
}



//Method to search for keywords, identifiers, constants, operators, delimiters, and syntax errors found within the file.
void checkFileLines(vector<string> filelines){
    size_t fileline = filelines.size();
    
    //These are the variables that are used to search through the text file to see if the text file has any of these variables for the final analysis output.
    //If the text does have keywords or any of these other variables, add these to their vector list.
    vector<string> keywords;
    vector<string> identifiers;
    vector<string> constants;
    vector<string> operators;
    vector<string> delimiters;
    vector<string> syntaxerrors;
    
    //Creation of vector lists for keywords, operators and delimiters, since these are the only known evaluations that you know for sure.
    //Initialization
    vector<string> allkeywords;
    vector<string> alloperators;
    vector<string> alldelimiters;
    //Declaration, push_back allows you to add them to the vector list
    //For Keywords, there are only 3 and they are all uppercased.
    allkeywords.push_back("FOR");
    allkeywords.push_back("BEGIN");
    allkeywords.push_back("END");
    //For Operators, there are 6 of them.
    alloperators.push_back("+");
    alloperators.push_back("-");
    alloperators.push_back("*");
    alloperators.push_back("/");
    alloperators.push_back("++");
    alloperators.push_back("=");
    //For Delimiters
    alldelimiters.push_back(",");
    alldelimiters.push_back(";");
    
    
    //**Searches for keywords
    //Searches through the entire allkeywords list to see if the filelines has any of these words.
    for(int i = 0; i < allkeywords.size();i++){
        //set the key string to index i of the allkeywords list
        string key = allkeywords.at(i);
        //The part below keeps running until it reaches the end of the file
        for(int line = 0; line < fileline; ){
            //As the name states, the currentline that is being checked for the specific keyword at index i.
            string currentline = filelines[line];
            //Looks entirely through the current line until its end, if the word is found, push it to the keywords vector
            if(currentline.find(key) != string::npos){
                keywords.push_back(key); //keyword found and being added to the keywords vector
                
            }
            
            line++; //increment to move the current line to the next line of the filelines vector
        }
        
    }
    
    
    
    
    //**Sections below checks for nested loops
    //Variables to keep track of the amount of keywords that are found within the file to help figure out the depth of the nested loops
    int forcount = 0; //a counter for the FORS
    Stack mystack; //stack variable needed to push/pop a BEGIN whenever it is found within the file
    int maxdepth = 0; //keeps track of the maximum number of nested FOR loops found in the file
    int tempdepth = 0; //temporary maximum variable before figuring out the actual maxdepth. Serves like the temp in a regular max function
    int loop = 0; //serves as a template to reset the temploop to 0
    int temploop = 0; //use this to update the loop
    
    
    
    
    //This for loop goes through every line within the filelines vector itself
    for(int line = 0; line < fileline; ){
        string currentline = filelines[line];//reads in whatever line that is being examined at the moment
        
        
        //This for loop goes through every character within the string currentline
        for(int i = 0;  i < currentline.size(); i++){
            string temp; //put this string here so that it can reset every time to find a new keyword within the file
            
            
            
            //if at the current index the first letter is a letter & uppercase, do the following
            if(isalpha(currentline[i]) && isupper(currentline[i])){
                
                //if the following character is still a letter, you want to add it to add that word to the temp string
                while(isalpha(currentline[i])){
                    temp += currentline[i];
                    
                    //increment i to look at every character afterwards, but once it finds a character that does not satisfy this condition, it exits out of this while loop
                    i++;
                }
                
                
                //**if statements below checks if this temp string is actually one of our KEYWORDS
                //if FOR was found:
                if(temp.compare("FOR") == 0){
                    //increment the forcount
                    forcount++;
                }
                
                
                
                
                //if BEGIN was found:
                if(temp.compare("BEGIN") == 0){
                    //In the case if there was no FOR before the BEGIN, print out this error message to let the user know
                    if(forcount == 0){
                        //This BEGIN did not have a FOR before it
                        //syntaxerrors.push_back("BEGIN");
                    }
                    
                    
                    //if there was a FOR before the BEGIN, do the following
                    if(forcount > 0){
                        //Pushes the BEGIN keyword to the stack
                        mystack.push(temp);
                        
                        
                        //decrement forcount by one to indicate that it had at least a BEGIN after it
                        forcount--;
                    }
                }//end of if statement for BEGIN
                
                
                
                
                
                //if END was found
                if(temp.compare("END") == 0){
                    //In the case when the stack isn't empty and the top of the stack is BEGIN. Therefore, the FOR loop was correct and the FOR loop has both an END & BEGIN after it.
                    if((!mystack.empty()) && (mystack.top().compare("BEGIN") == 0)){
                        //removes BEGIN from the top of the function to show that its accounted for
                        mystack.pop();
                        temploop++;//increment the loop variable
                        
                        
                        
                        
                        //if the stack is empty completely after the pop or if your at the very last line of the file, do the following
                        //The only possibility of maxdepth changing will be the case when the stack is empty.
                        if(mystack.empty() || (line == fileline - 1) ){
                            //Now the stack is completely empty and you will now want to know the maximum depth of the file
                            
                            //You want to make this the temporary depth for each nested/single loop to be equal to the loop counter
                            tempdepth = temploop;
                            
                            //If the maxdepth is < than the tempdepth, set maxdepth = to tempdepth to indicate that this is the maximum depth of the file at the moment
                            if(maxdepth < tempdepth){
                                maxdepth = tempdepth;
                            }
                            
                            
                            //to reset the temploop back to 0
                            temploop = loop;
                        }
                        //Otherwise, your FOR loop was incorrect.
                        else{
                            //There was not a FOR before this END
                            //syntaxerrors.push_back("END");
                        }
                        
                    }//end of the giant if statement of when the stack is not empty and the top of the stack is BEGIN
                    
                }//end of giant if statement for when END was found
                
            }//end of giant if statement for the case where the word is a keyword
            
        }//end of for loop that goes through every character within the currentline string
        
        
        
        //move onto the next line within the file
        line++;
        
    }//end of huge for loop to look at every line within the document to search for KEYWORDS to be pushed/popped and analysis of the depth of the for loops
    
    
    
    //This line prints out the final results
    cout << endl << "\nThe depth of nested loop(s) is " << maxdepth << ".\n\n";
    
    
    
    
    
 
    
    
    //**Searches for operators
    //Searches through the entire alloperators list to see if the filelines has any of these.
    for(int i = 0; i < alloperators.size();i++){
        //set the key string to index i of the alloperators list
        string key = alloperators.at(i);
        //The part below keeps running until it reaches the end of the file
        for(int line = 0; line < fileline; ){
            string currentline = filelines[line];
            //Looking entirely through the current line until its end, if the word is found, push it to the operators vector
            if(currentline.find(key) != string::npos){
                operators.push_back(key);//operators found and being added to the operators vector
            }
            
            line++;//increment to move the current line to the next line
        }
    }
  
    
    
    //**Searches for delimiters
    //Searches through the entire alldelimiters list to see if the filelines has any of these.
    for(int i = 0; i < alldelimiters.size();i++){
        //set the key string to index i of the alldelimiters list
        string key = alldelimiters.at(i);
        //The part below keeps running until it reaches the end of the file
        for(int line = 0; line < fileline; ){
            string currentline = filelines[line];
            //Looking entirely through the current line until its end, if the word is found, push it to the delimiters vector
            if(currentline.find(key) != string::npos){
                delimiters.push_back(key);//delimiter found and being added to the delimiters vector
                
            }
            
            line++;//increment to move the current line to the next line
        }
    }
    
  
    
    
    //line is to keep track of which line we are on in the file lines, while i is to keep track of what specific character index we are on within the currentline variable whenever it switches to a different line from the filelines vector.
    for(int line = 0; line < fileline; ){
        //we set the currentline to the very first index of the filelines vector for comparison
        string currentline = filelines[line];
        
        
        
        //**Searches for identifiers
        for(int i = 0; i < currentline.size(); i++){
            string temp; //put this here so that it can restart whenever it tries to find a new identifier
            
            //if the index of the currentline that is currently being examined is alphanumeric and lowercase, it's an identifier.
            if(isalpha(currentline[i]) && islower(currentline[i])){
                //while the current idex is a lowercased letter, add that same word together
                while(isalpha(currentline[i])){
                    //temp is the identifier string and is piecing it together.
                    temp += currentline[i];
                    
                    //increment i so that this while loop can keep checking if its still a lowercase letter
                    i++;
                }
                //add the final product to the identifiers list
                identifiers.push_back(temp);
            }
        }
        
        
        
        //**Searches for constants/numbers
        for(int i = 0; i < currentline.size(); i++){
            string temp; //put this here so that it can restart whenever it tries to find a new identifier
            
            //if the index being examined is a digit, do the following
            if(isdigit(currentline[i])){
                //while the following digits afterwards are still a digit, concatenate it to the temp string
                while(isdigit(currentline[i])){
                    temp += currentline[i];
                    
                    //increment i so that this while loop can keep checking if its still a constant # after it
                    i++;
                }
                
                //add the final product to the constants list
                constants.push_back(temp);
            }
            
        }
        
        
        
        
        //**Searches for Syntax Errors
        for(int i = 0; i < currentline.size(); i++){
            string temp;//put this here so that it can restart whenever it tries to find a new identifier
            
            //if at the current index of the currentline string is uppercase and a letter, do the following
            if(isalpha(currentline[i]) && isupper(currentline[i])){
                //while the following word is a letter, add it to the temp string
                while(isalpha(currentline[i])){
                    temp += currentline[i];
                    
                    //increment i so that this while loop can keep checking if its still an uppercase letter after it
                    i++;
                }
                
                
                //If the temp string is all uppercase and is a keyword, it is not considered as a syntax error.
                if(temp.compare("BEGIN") == 0){
                    //do nothing
                }
                else if(temp.compare("END") == 0){
                    //do nothing
                }
                else if(temp.compare("FOR") == 0){
                    //do nothing
                }
                //if the word is all uppercase and is not a keyword, it is a syntax error.
                else{
                    //add it to the syntax errors list
                    syntaxerrors.push_back(temp);
                }
            }
        }
        
        
        
        //move onto the next line if none of the if statements above are satisfied
        line++;
        
    }//end of for loop for search for constants, identifiers, and syntax errors
    
    
    
    //Sorts the vector list first and then removes all of the duplicates from each vector list before printing them out
    sortAndRemove(keywords);
    sortAndRemove(identifiers);
    sortAndRemove(constants);
    sortAndRemove(operators);
    sortAndRemove(delimiters);
    sortAndRemove(syntaxerrors);
    
    
    
    //This section gives the output of the final analsysis results
    cout << "\nKeywords: ";
    printAnalysis(keywords); //prints out the keywords
    cout << "Identifier: ";
    printAnalysis(identifiers);//prints out the identifiers
    cout << "Constant: ";
    printAnalysis(constants);//prints out the constants
    cout << "Operators: ";
    printAnalysis(operators);//prints out the operators
    cout << "Delimiter: ";
    printAnalysis(delimiters);//prints out the delimiters
    cout << "\nSyntax Error(s): ";
    printAnalysis(syntaxerrors);//prints out the syntax errors
    cout << endl;
    
}





//******Main Method
int main(int argc, char * argv[]) {
    
    //***Portion below is for opening the file then performing the needed analysis of the file that is being read
    
    ifstream inputfile; //variable needed to take in the file that the reader wants to be read
    
    string filename;
    
    //Asks for user's file
    cout << "Please enter the name of the input file: ";
    cin >> filename;
    
    string line; //variable to take in each line of the file
    vector<string> filelines; //stores all of the read lines within this string, the deque allows you to add each lines being read to the filelines
    
    
    //*This performs the action of opening the file, but it doesn't necessarily mean that the file exists
    inputfile.open(filename.c_str());
    
    
    //If the file does exist, then read through each of lines within the file
    if(inputfile.is_open()){
        //Go through every line in the file until it reaches the end of the file
        while(getline(inputfile, line)){
            //reads each of the lines and add them in filelines vector
            filelines.push_back(line);
            
        }
        
        inputfile.close(); //after the file is done being read, close the file.
    }
    //This is the case if the file does not exist, so this line of text prints out to let the user know that.
    else{
        cout << "Unknown file, please try again." << endl;
        return 1;
    }
    
    
    //***After the file has been read, the method below will analyze each line and then print out the final results.
    checkFileLines(filelines);
    
    
    return 0;
}

