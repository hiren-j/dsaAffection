// Program to find the sums of all the subsets ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Backtracking approach:
class Backtracking_V1 {
    vector<int> sums;
    
    void getAllSubestsSum(vector<int>& nums, int N, int currSum, int J) {
        // Edge case: If all the array elements are taken
        if(J >= N) {
            sums.push_back(currSum);
            return; // Backtrack
        }
        
        getAllSubestsSum(nums, N, currSum+nums[J], J+1); // Include the element and move on
        getAllSubestsSum(nums, N, currSum, J+1);         // Exclude the element and move on
    }
    
public:
    // Method to find the sums of all the subsets - O(2^N) & O(2^N)
    vector<int> subsetSums(vector<int>& nums, int N) {
        getAllSubestsSum(nums, N, 0, 0);
        return sums;
    }
};

// #2 Backtracking approach:
class Backtracking_V2 {
    vector<int> sums;
    
    void getAllSubestsSum(vector<int>& nums, int N, int currSum, int startIdx) {
        sums.push_back(currSum);
        for(int J=startIdx; J<N; J++) {
            getAllSubestsSum(nums, N, currSum+nums[J], J+1);
        }
    }
    
public:
    // Method to find the sums of all the subsets - O(2^N) & O(2^N)
    vector<int> subsetSums(vector<int>& nums, int N) {
        getAllSubestsSum(nums, N, 0, 0);
        return sums;
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
        cout<<"Enter values of the array: ";
        for(int J = 0; J < N; ++J) {
            cin>>nums[J];
        }

        // Call to get the list of sums
        Backtracking_V2 bt;
        vector<int> sums = bt.subsetSums(nums, N);

        // Print values
        cout<<"List of all the subsets: ";
        for(int sum : sums)
            cout<<sum<<' ';

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Backtracking
    Link: https://www.geeksforgeeks.org/problems/subset-sums2234/1
*/
