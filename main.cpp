#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

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
            int highestIndex = currentLine.size() - 1;
            
            // multiple branches in case you wish to refactor "int" but not variables such as "int1", or if you are
            // going to refactor "in" and do not want "int" to be modifed at all.
            
            if (currentLine.find(original, index) != 0 && currentLine.find(original, index) + original.size() < highestIndex) {
                // goes into this loop if NOT the front or back of the line
                
                char peekFront = currentLine.at(currentLine.find(original, index) - 1);
                char peekBack = currentLine.at(currentLine.find(original, index) + original.length());
                
                if ((peekFront > 47 && peekFront < 58) || (peekFront > 64 && peekFront < 91) || 
                (peekFront > 96 && peekFront < 123) || (peekBack > 47 && peekBack < 58) ||
                (peekBack > 64 && peekBack < 91) || (peekBack > 96 && peekBack < 123)) {
                    index = currentLine.find(original, index) + 1;
                } else {
                    firstHalf = currentLine.substr(0, currentLine.find(original, index));
                    secondHalf = currentLine.substr(currentLine.find(original, index) + original.length(), original.length() - (currentLine.find(original, index) + original.length()));
                    currentLine = firstHalf + refactor + secondHalf;
                } 
            } else if (currentLine.find(original, index) != 0) {
                
                // goes into this loop if NOT the front
                char peekFront = currentLine.at(currentLine.find(original, index) - 1);
                
                if ((peekFront > 47 && peekFront < 58) || (peekFront > 64 && peekFront < 91) || 
                (peekFront > 96 && peekFront < 123)) {
                    index = currentLine.find(original, index) + 1;
                } else {
                    firstHalf = currentLine.substr(0, currentLine.find(original, index));
                    currentLine = firstHalf + refactor + secondHalf;
                }
            } else if (currentLine.find(original, index) + original.size() < highestIndex) {
                
                // goes into this loop if NOT the back
                char peekBack = currentLine.at(currentLine.find(original, index) + original.length());
                if ((peekBack > 47 && peekBack < 58) || (peekBack > 64 && peekBack < 91) || 
                (peekBack > 96 && peekBack < 123)) {
                    index = currentLine.find(original, index) + 1;
                } else {
                    secondHalf = currentLine.substr(currentLine.find(original, index) + original.length(), original.length() - (currentLine.find(original, index) + original.length()));
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