// Program to find all the possible subsequences of the string "s" in lexicographically-sorted order ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Backtracking approach:
class Backtracking_V1 {
    vector<string> allSubsequences;
    
    void getAllUniqueSubsequences(const string& s, string& currSubsequence, int n, int i) {
        if(i >= n) {
            if(currSubsequence != "") {
                allSubsequences.push_back(currSubsequence);
            }
            return;
        }

        // Include the element and move one
        currSubsequence.push_back(s[i]);
        getAllUniqueSubsequences(s, currSubsequence, n, i+1);
        currSubsequence.pop_back();
        
        // Exclude the element and move one
        getAllUniqueSubsequences(s, currSubsequence, n, i+1);
    }
    
public:
    // Method to find all the possible subsequences of the string "s" in lexicographically-sorted order - O(2^N * N) & O(2^N * N)
    vector<string> AllPossibleStrings(const string& s) {
	string currSubsequence;
	getAllUniqueSubsequences(s, currSubsequence, s.size(), 0);
	sort(begin(allSubsequences), end(allSubsequences));
	return allSubsequences;
    }
};

// #2 Backtracking approach:
class Backtracking_V2 {
    vector<string> allSubsequences;
    
    void getAllUniqueSubsequences(const string& s, string& currSubsequence, int n, int startIdx) {
        if(currSubsequence != "")
            allSubsequences.push_back(currSubsequence);
            
        for(int i=startIdx; i<n; i++) {
            currSubsequence.push_back(s[i]); // Include the element (perform the action)
            getAllUniqueSubsequences(s, currSubsequence, n, i+1);
            currSubsequence.pop_back();      // Exclude the element (revert the action)
        }
    }
    
public:
    // Method to find all the possible subsequences of the string "s" in lexicographically-sorted order - O(2^N * N) & O(2^N * N)
    vector<string> AllPossibleStrings(const string& s) {
	string currSubsequence;
	getAllUniqueSubsequences(s, currSubsequence, s.size(), 0);
	sort(begin(allSubsequences), end(allSubsequences));
	return allSubsequences;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input a string
        string s;
        cout<<"Enter a string: ";
        cin>>s;

        // Call to get the list containing all the possible subsequences of the string "s"
        Backtracking_V2 bt;
        vector<string> allSubsequences = bt.AllPossibleStrings(s);

        // Print each subsequence of the string "s"
        cout<<"\nList of all the possible subsequences in lexicographically-sorted order:\n";
        for(auto& currSubsequence: allSubsequences) {
            int size = currSubsequence.size();
            cout<<"[";
            for(int i=0; i<size; ++i) {
                (i < size-1) ? cout<<currSubsequence[i]<<", " : cout<<currSubsequence[i];
            }
            cout<<"]\n";
        }
        
        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: String | Backtracking
    Link: https://www.geeksforgeeks.org/problems/power-set4302/1
*/
