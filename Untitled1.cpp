#include <iostream>
#include <vector>

using namespace std;
ABC
CAB
XYZ
AXZ
BCA

filestreamstuff
vector<string> book;
vector<string> groups;
for (int i = 0; i < book.size(); i++) {
    if (findsanewgroup) {
        
    }
}

ABC CAB BCA
XYZ
AXZ


                        ABCC            ABC
bool isAnagram(string current, string cannidate) {
    vector<char> currChar = current.getVector();
    vector<char> cannChar = cannidate.getVector();
    
    for (int i = 0; i < currChar.size(); i++) {
        for (int j = 0; j < cannChar.size(); j++) {
            if (currChar.at(i) == cannChar.at(j)) {
                cannChar.erase(cannChar.begin() + j);
                break;
            }
            if (j == cannChar.size() - 1) {
                return false;
            }
        }
        
        if (cannChar.empty()) {
            return false;
        }
    }
    
    return true;
}

bool isDuplicate(vector<string> current, string cannidate) {
    
    for (int i = 0; i < current.size(); i++) {
        if (current.at(i) == cannidate) {
            return true;
        }
    }
    
    return false;
}

int main() {
    vector<string> book;
    vector<vector<string>> groups;
    
    vector<string> first = book.getFirstString();
    groups.push_back(first);
    
    for (int i = 1; i < book.size(); i++) {
        for (int j = 0; j < groups.size(); j++) {
            if (isAnagram(groups.at(j).getFirstValue(), book.at(i))) {
                if (!isDuplicate(groups, book.at(i))) {
                    groups.at(j).push_back(book.at(i));
                }
            } else {
                vector<string> newGroup = {book.at(i)};
                groups.push_back(newGroup);
            }
        }
    }
    
    
    
    return 0;
}