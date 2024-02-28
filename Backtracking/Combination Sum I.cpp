// Program to find a list of all unique combinations of "candidates" where the chosen numbers sums to "target" ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Backtracking approach:
class BackTracking_V1 {
    vector<vector<int>> combinations;
    int N;

    void getAllUniqueCombinations(vector<int>& candidates, vector<int>& currCombination, int target, int startIdx) {
        if(target == 0) {
            combinations.push_back(currCombination);
            return;
        }

        for(int J = startIdx; J < N; ++J) {
            if(candidates[J] <= target) {
                currCombination.push_back(candidates[J]);
                getAllUniqueCombinations(candidates, currCombination, target-candidates[J], J);
                currCombination.pop_back();
            }
        }
    }

public:
    // Method to find the list of all unique combinations where the chosen numbers sums to target - O(2^T * K) & O(M * K) : Where N is the size of "candidates", T is the "target", K let be the maximum size of any "currCombination" and M let be the total number of unique combinations.
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        N = candidates.size();
        vector<int> currCombination;
        getAllUniqueCombinations(candidates, currCombination, target, 0);
        return combinations;
    }
};

// #2 Backtracking approach:
class BackTracking_V2 {
    vector<vector<int>> combinations;
    int N;

    void getAllUniqueCombinations(vector<int>& candidates, vector<int>& currCombination, int target, int startIdx) {
        if(target == 0) {
            combinations.push_back(currCombination);
            return;
        }

        for(int J = startIdx; (J < N && candidates[J] <= target); J++) {
            currCombination.push_back(candidates[J]);
            getAllUniqueCombinations(candidates, currCombination, target-candidates[J], J);
            currCombination.pop_back();
        }
    }

public:
    // Method to find the list of all unique combinations where the chosen numbers sums to target - O(2^T * K) & O(M * K) : Where N is the size of "candidates", T is the "target", K let be the maximum size of any "currCombination" and M let be the total number of unique combinations.
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        N = candidates.size();
        sort(begin(candidates), end(candidates));
        vector<int> currCombination;
        getAllUniqueCombinations(candidates, currCombination, target, 0);
        return combinations;
    }
};

// #3 Backtracking approach:
class BackTracking_V3 {
    vector<vector<int>> combinations;
    int N;

    void getAllUniqueCombinations(vector<int>& candidates, vector<int>& currCombination, int target, int J) {
        if(target == 0) {
            combinations.push_back(currCombination);
            return;
        }

        if(J < N && candidates[J] <= target) {
            currCombination.push_back(candidates[J]);
            getAllUniqueCombinations(candidates, currCombination, target-candidates[J], J);
            currCombination.pop_back();

            getAllUniqueCombinations(candidates, currCombination, target, J+1);
        }
    }

public:
    // Method to find the list of all unique combinations where the chosen numbers sums to target - O(2^T * K) & O(M * K) : Where T is the "target", K let be the maximum size of any "currCombination" and M let be the total number of unique combinations.
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
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
        cout<<"Enter unique values for the array: ";
        for(int J = 0; J < N; ++J) {
            cin>>candidates[J];
        }

        // Input the target value
        int target;
        cout<<"Enter the target value: ";
        cin>>target;

        // Call to find the list of all unique combinations where the chosen numbers sums to target
        BackTracking_V3 bt;
        vector<vector<int>> combinations = bt.combinationSum(candidates, target);

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
    Link: https://leetcode.com/problems/combination-sum/description/
*/
