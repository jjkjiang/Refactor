#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

// // this is dumb
// struct lineInfo() {
//     lineInfo();
//     lineInfo(string, string, int);
    
//     string currentLine;
//     string userString;
//     int currentIndex;
// }

// lineInfo() {
//     currentLine = "";
//     userString = "";
//     currentIndex = 0;
// }

// lineInfo(string currentLine, string userString, int currentIndex) {
//     this->currentLine = currentLine;
//     this->userString = userString;
//     this->currentIndex = currentIndex;
// }

bool isANumberOrLetter(char candidate) {
    if ((candidate >= '0' && candidate <= '9') ||
    (candidate >= 'a' && candidate <= 'z') ||
    (candidate >= 'A' && candidate <= 'Z')) {
        return true;
    }
    return false;
}

bool isNotFrontOfString(string currentLine, string userString, int currentIndex) {
    if (currentLine.find(userString, currentIndex) != 0) {
        return true;
    }
    return false;
}

bool isNotBackOfString(string currentLine, string userString, int currentIndex) {
    int highestIndex = currentLine.size() - 1;
    if (currentLine.find(userString, currentIndex) + userString.size() < highestIndex) {
        return true;
    }
    return false;
}

string getFrontOfIndexedWord(string currentLine, string userString, int currentIndex) {
    return currentLine.substr(0, currentLine.find(userString, currentIndex));
}

string getBackOfIndexedWord(string currentLine, string userString, int currentIndex) {
    return currentLine.substr(currentLine.find(userString, currentIndex) + userString.length(), 
    currentLine.length() - (currentLine.find(userString, currentIndex) + userString.length()));
}

int main(int argc, char* argv[] ) {
    
    // checks if the program is run with the correct input.
    if (argc != 2) {
        cout << "Invalid input - this program is run by ./refactor.exe nameoffilehere" << endl;
        return 0;
    }
    
    // initalize streams
    ifstream inFS;
    ofstream outFS;
    inFS.open(argv[1]);
    
    // error message for opening
    if (!inFS.is_open()) {
        cout << "There was an error loading your file or it does not exist." << endl;
        return 0;
    }
    
    // creates a target file to
    string fileName = argv[1];
    fileName += "_refactored";
    outFS.open(fileName.c_str());
    
    string original, refactor;
    char warningResponse = 'n';
    int iterations = 0;
    
    cout << "Enter text you wish to replace: ";
    getline(cin, original);
    cout << endl;
    
    // dissallows replacing nothing
    if (original == "") {
        cout << "No input detected.";
        return 0;
    }
    
    // warning
    if (original.length() < 4) {
        cout << "Refactoring something with such a low length could be dangerous, continue? (y/n) ";
        cin >> warningResponse;
        cout << endl;
        cin.ignore();
        if (warningResponse != 'y' && warningResponse != 'Y') {
            return 0;
        }
    }
    
    cout << "Enter text you wish to replace " << original << " with: ";
    getline(cin, refactor);
    cout << endl;
    
    string currentLine;
    
    while (getline(inFS, currentLine)) {
        // initalize index of current in case skipping is needed
        int index = 0;
        // continues getting from the file until eof
        while (currentLine.find(original, index) != string::npos) {
            string firstHalf = "";
            string secondHalf = "";
            
            // multiple branches in case you wish to refactor "int" but not variables such as "int1", or if you are
            // going to refactor "in" and do not want "int" to be modifed at all.
            
            if (isNotFrontOfString(currentLine, original, index) && isNotBackOfString(currentLine, original, index)) {
                // goes into this loop if NOT the front or back of the line
                char peekFront = currentLine.at(currentLine.find(original, index) - 1);
                char peekBack = currentLine.at(currentLine.find(original, index) + original.length());
                
                if (isANumberOrLetter(peekFront) || isANumberOrLetter(peekBack)) {
                    index = currentLine.find(original, index) + 1;
                } else {
                    firstHalf = getFrontOfIndexedWord(currentLine, original, index);
                    secondHalf = getBackOfIndexedWord(currentLine, original, index);
                    currentLine = firstHalf + refactor + secondHalf;
                } 
            } else if (isNotFrontOfString(currentLine, original, index)) {
                // goes into this loop if NOT the front
                char peekFront = currentLine.at(currentLine.find(original, index) - 1);
                
                if (isANumberOrLetter(peekFront)) {
                    index = currentLine.find(original, index) + 1;
                } else {
                    firstHalf = getFrontOfIndexedWord(currentLine, original, index);
                    currentLine = firstHalf + refactor + secondHalf;
                }
            } else if (isNotBackOfString(currentLine, original, index)) {
                // goes into this loop if NOT the back
                char peekBack = currentLine.at(currentLine.find(original, index) + original.length());
                if (isANumberOrLetter(peekBack)) {
                    index = currentLine.find(original, index) + 1;
                } else {
                    secondHalf = getBackOfIndexedWord(currentLine, original, index);
                    currentLine = firstHalf + refactor + secondHalf;
                }
            } else {
                // goes into this loop if NOT any
                currentLine = firstHalf + refactor + secondHalf;
            }
        }
        
        outFS << currentLine << endl;
    }
    
    cout << "Successfully refactored file to " << fileName << endl;
    return 0;
}
