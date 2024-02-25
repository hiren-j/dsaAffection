// Program to find a list of all unique combinations of "candidates" where the chosen numbers sums to "target" (each number in candidates may only be used once in the combination) ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
using namespace std;

// #1 Backtracking approach:
class Backtracking_V1 {
    vector<vector<int>> combinations;
    int N;

    void getAllUniqueCombinations(vector<int>& candidates, vector<int>& currCombination, int target, int startIdx) {
        if(target == 0) {
            combinations.push_back(currCombination);
            return; // Backtrack
        }

        for(int J = startIdx; (J < N && candidates[J] <= target); J++) {
            // Helps to ignore the duplicate elements
            if(J != startIdx && candidates[J] == candidates[J-1])
                continue;

            currCombination.push_back(candidates[J]); // Include the element
            getAllUniqueCombinations(candidates, currCombination, target-candidates[J], J+1);
            currCombination.pop_back();               // Exclude the element
        }
    }

public:
    // Method to find the list of all unique combinations - O(N^N * K) & O(M * K) : Where N is the size of "candidates", K let be the maximum size of any "currCombination" and M let be the total number of unique combinations
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        N = candidates.size();
        sort(begin(candidates), end(candidates));
        vector<int> currCombination;
        getAllUniqueCombinations(candidates, currCombination, target, 0);
        return combinations;
    }
};

// #2 Backtracking approach:
class Backtracking_V2 {
    vector<vector<int>> combinations;
    set<vector<int>> st; // Requires to ignore the duplicate combinations
    int N;

    void getAllUniqueCombinations(vector<int>& candidates, vector<int>& currCombination, int target, int J) {
        if(target == 0) {
            if(!st.count(currCombination)) {
                combinations.push_back(currCombination);
                st.insert(currCombination);
            }
            return; // Backtrack
        }

        if(J < N && candidates[J] <= target) {
            // Include the element and move on
            currCombination.push_back(candidates[J]);
            getAllUniqueCombinations(candidates, currCombination, target-candidates[J], J+1);
            currCombination.pop_back(); 

            // Exclude the element and move on
            getAllUniqueCombinations(candidates, currCombination, target, J+1);
        }
    }

public:
    // Method to find the list of all unique combinations - O(2^N * (K + LogX)) & O(M * (K + X)) : Where N is the size of "candidates" and K let be the maximum size of any "currCombination", X is the size of the set and M let be the total number of unique combinations
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        N = candidates.size();
        sort(begin(candidates), end(candidates));
        vector<int> currCombination;
        getAllUniqueCombinations(candidates, currCombination, target, 0);
        return combinations;
    }
};
// Note: This solution can lead to the "TLE / Time limit exceed"

// #3 Backtracking approach:
class Backtracking_V3 {
    vector<vector<int>> combinations;
    int N;

    void getAllUniqueCombinations(vector<int>& candidates, vector<int>& currCombination, int target, int J) {
        if(target == 0) {
            combinations.push_back(currCombination);
            return; // Backtrack
        }

        if(J < N && candidates[J] <= target) {
            // Include the element and move on
            currCombination.push_back(candidates[J]);
            getAllUniqueCombinations(candidates, currCombination, target-candidates[J], J+1);
            currCombination.pop_back();              

            // Helps to ignore the duplicate elements
            int I = J+1;
            while(I < N && candidates[I] == candidates[I-1])
                I++;

            // Exclude the element and move on
            getAllUniqueCombinations(candidates, currCombination, target, I);
        }
    }

public:
    // Method to find the list of all unique combinations - O(2^N * K) & O(M * K) : Where N is the size of "candidates" and K let be the maximum size of any "currCombination" and M let be the total number of unique combinations
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        N = candidates.size();
        sort(begin(candidates), end(candidates));
        vector<int> currCombination;
        getAllUniqueCombinations(candidates, currCombination, target, 0);
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

        // Input the array size
        int N;
        cout<<"Enter the size of array: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<int> candidates(N, 0);

        // Input the array values
        cout<<"Enter the array values: ";
        for(int J = 0; J < N; ++J) {
            cin>>candidates[J];
        }

        // Input the target value
        int target;
        cout<<"Enter the target value: ";
        cin>>target;

        // Call to find the list of all unique combinations where the chosen numbers sums to target
        Backtracking_V3 bt;
        vector<vector<int>> combinations = bt.combinationSum2(candidates, target);

        // Print the values of each combination
        cout<<"\nList of all the unique combinations:\n";
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
    Link: https://leetcode.com/problems/combination-sum-ii/description/
*/
