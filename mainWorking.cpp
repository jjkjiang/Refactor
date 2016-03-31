#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

int main(int argc, char* argv[] ) {
    
    if (argc != 2) {
        cout << "Invalid input - this program is run by ./refactor.exe nameoffilehere" << endl;
        return 0;
    }
    
    ifstream inFS;
    ofstream outFS;
    inFS.open(argv[1]);
    string fileName = argv[1];
    fileName += "_refactored";
    outFS.open(fileName.c_str());
    
    if (!inFS.is_open()) {
        cout << "There was an error loading your file or it does not exist." << endl;
        return 0;
    }
    
    string original, refactor;
    char warningResponse = 'n';
    int iterations = 0;
    
    cout << "Enter text you wish to replace: ";
    getline(cin, original);
    cout << endl;
    
    if (original == "") {
        cout << "No input detected.";
        return 0;
    }
    
    if (original.length() < 4) {
        cout << "Refactoring something with such a low length could be dangerous, continue? (y/n)";
        cin >> warningResponse;
        cout << endl;
        cin.ignore();
        if (warningResponse != 'y') {
            return 0;
        }
    }
    
    cout << "Enter text you wish to replace " << original << " with: ";
    getline(cin, refactor);
    cout << endl;
    
    string currentLine;
    
    while (getline(inFS, currentLine)) {
        while (currentLine.find(original) != string::npos) {
            // string firstHalf;
            // string secondHalf;
            // if (currentLine.find(original) != 0) {
            //     char peekFront = currentLine.at(currentLine.find(original) - 1);
            //     char peekBack = currentLine.at(currentLine.find(original) + original.length() - 1);
            //     if (!(peekFront > 47 && peekFront < 58) && !(peekFront > 64 && peekFront < 91) && 
            //     !(peekFront > 96 && peekFront < 123) && !(peekBack > 47 && peekBack < 58) &&
            //     !(peekBack > 64 && peekBack < 91) && !(peekBack > 96 && peekBack < 123)) {
            //         firstHalf = currentLine.substr(0, currentLine.find(original));
            //         secondHalf = currentLine.substr(currentLine.find(original) + original.length(), original.length() - (currentLine.find(original) + original.length()));
            //         currentLine = firstHalf + refactor + secondHalf;
            //     }
            // } else {
            //     char peekBack = currentLine.at(currentLine.find(original) + original.length() - 1);
            //     if (!(peekBack > 47 && peekBack < 58) && !(peekBack > 64 && peekBack < 91) && 
            //     !(peekBack > 96 && peekBack < 123)) {
            //         secondHalf = currentLine.substr(currentLine.find(original) + original.length(), original.length() - (currentLine.find(original) + original.length()));
            //         currentLine = firstHalf + refactor + secondHalf;
                    string firstHalf = currentLine.substr(0, currentLine.find(original));
                    string secondHalf = currentLine.substr(currentLine.find(original) + original.length(), currentLine.length() - (currentLine.find(original) + original.length()));
                    currentLine = firstHalf + refactor + secondHalf;
            //    }
            //}
        }
        
        outFS << currentLine << endl;
    }
}