// Program to find all the possible subsets (the solution set must not contain duplicate subsets) ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Backtracking approach:
class Backtracking_V1 {
    vector<vector<int>> allSubsets;
    int N;

    void getAllUniqueSubsets(vector<int>& nums, vector<int>& currSubset, int startIdx) {
        allSubsets.push_back(currSubset);

        for(int J = startIdx; J < N; ++J) {
            currSubset.push_back(nums[J]); // Include the element (perform the action)
            getAllUniqueSubsets(nums, currSubset, J+1);
            currSubset.pop_back();         // Exclude the element (revert the action)
        }    
    }

public: 
    // Method to find all the possible subsets - O(N^N * N) & O(2^N * N) : Where N is the size of "nums" (there could be 2^N possible subsets)
    vector<vector<int>> subsets(vector<int>& nums) {
        N = nums.size();
        vector<int> currSubset;
        getAllUniqueSubsets(nums, currSubset, 0);
        return allSubsets;
    }
};

// #2 Backtracking approach:
class Backtracking_V2 {
    vector<vector<int>> allSubsets;
    int N;

    void getAllUniqueSubsets(vector<int>& nums, vector<int>& currSubset, int J) {
        // Edge case: When all the elements are exhausted
        if(J >= N) {
            allSubsets.push_back(currSubset);
            return;
        }       

        // Include the element and move one
        currSubset.push_back(nums[J]); 
        getAllUniqueSubsets(nums, currSubset, J+1);
        currSubset.pop_back();

        // Exclude the element and move on
        getAllUniqueSubsets(nums, currSubset, J+1);
    }

public: 
    // Method to find all the possible subsets - O(2^N * N) & O(2^N * N) : Where N is the size of "nums" (there could be 2^N possible subsets)
    vector<vector<int>> subsets(vector<int>& nums) {
        N = nums.size();
        vector<int> currSubset;
        getAllUniqueSubsets(nums, currSubset, 0);
        return allSubsets;
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
        vector<int> nums(N, 0);

        // Input the array values
        cout<<"Enter unique values for the array: ";
        for(int J = 0; J < N; ++J) {
            cin>>nums[J];
        }

        // Call to get the list of all the possible subsets
        Backtracking_V2 bt;
        vector<vector<int>> allSubsets = bt.subsets(nums);

        // Print the values of each subset
        cout<<"\nList of all the possible subsets:\n";
        for(auto& currSubset : allSubsets) {
            int size = currSubset.size();
            cout<<"[";
            for(int J = 0; J < size; ++J) {
                cout<<currSubset[J];
                if(J < size-1) cout<<", ";
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
    Link: https://leetcode.com/problems/subsets/description/
*/
