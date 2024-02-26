// Program to find all possible valid combinations of "k" numbers that sum up to "n" such that the specified conditions are true (the list must not contain the same combination twice) ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Backtracking approach:
class Backtracking_V1 {
    vector<vector<int>> combinations;

    void getAllValidCombinations(vector<int>& currCombination, int k, int n, int startNum) {
        if(k == 0) {
            if(n == 0) {
                combinations.push_back(currCombination);
            }
            return; // Backtrack
        }

        for(int num = startNum; (num <= 9 && num <= n); num++) {
            currCombination.push_back(num); // Include the element (peform the action)
            getAllValidCombinations(currCombination, k-1, n-num, num+1);
            currCombination.pop_back();     // Exclude the element (revert the action)
        }
    }

public:
    // Method to find all possible valid combinations of "k" numbers that sums to "n" - O(9^9 * K) & O(M * K) : Where K let be the maximum size of any "currCombination" and M is the total number of all possible valid combinations
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> currCombination;
        getAllValidCombinations(currCombination, k, n, 1);
        return combinations;
    }
};

// #2 Backtracking approach:
class Backtracking_V2 {
    vector<vector<int>> combinations;

    void getAllValidCombinations(vector<int>& currCombination, int k, int n, int currNum) {
        if(k == 0) {
            if(n == 0) {
                combinations.push_back(currCombination);
            }
            return; // Backtrack
        }

        if(currNum <= 9 && currNum <= n) {
            // Include the element and move on
            currCombination.push_back(currNum);
            getAllValidCombinations(currCombination, k-1, n-currNum, currNum+1);
            currCombination.pop_back();

            // Exclude the element and move on
            getAllValidCombinations(currCombination, k, n, currNum+1);    
        }
    }

public:
    // Method to find all possible valid combinations of "k" numbers that sums to "n" - O(2^9 * K) & O(M * K) : Where K let be the maximum size of any "currCombination" and M is the total number of all possible valid combinations
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> currCombination;
        getAllValidCombinations(currCombination, k, n, 1);
        return combinations;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        // Input section for "k" and "n"
        int k, n;
        cout<<"Enter the value of k: "; cin>>k;
        cout<<"Enter the value of n: "; cin>>n;

        // Check the given value is valid or not
        if(k <= 0 || n <= 0) {
            cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }

        // Call to get the list of all possible valid combinations
        Backtracking_V2 bt;
        vector<vector<int>> combinations = bt.combinationSum3(k, n);

        // Print the values of each combination
        cout<<"\nList of all the possible valid combinations:\n";
        for(auto& currCombination : combinations) {
            int K = currCombination.size();
            cout<<"[";
            for(int J = 0; J < K; ++J) {
                cout<<currCombination[J];
                if(J < K-1) cout<<", ";
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
    Topics: Array | Backtracking
    Link: https://leetcode.com/problems/combination-sum-iii/
*/
