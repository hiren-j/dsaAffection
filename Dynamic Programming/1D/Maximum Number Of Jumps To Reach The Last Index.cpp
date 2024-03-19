// Program to find the maximum number of jumps you can make to reach the last index ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the maximum number of jumps you can make to reach the last index, using recursion with memoization - O(N*N) & O(N) : Where N let be the size of array
    int maximumJumps(vector<int>& nums, int target) {
        int N = nums.size();
        vector<int> memory(N, -1);
        int maxJumps = solveWithMemo(memory, nums, N, target, 0);
        return (maxJumps == INT_MIN) ? -1 : maxJumps;
    }

private:
    // O(N*N) & O(N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int N, int target, int I) {
        // Edge case: If you reached the last index, then return 0 as a valid indication of it
        if(I == N - 1)
            return 0;
            
        // Edge case: If all the index are exhausted, then you can't reach the last index
        if(I == N)
            return INT_MIN;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[I] != -1)
            return memory[I];

        // Stores the "result value / maximum number of jumps required to reach the last index from the Ith index"
        int maxJumps = INT_MIN;

        // Iterate and if possible, then make the jump and update the result value by the maximum value
        for(int J = I + 1; J < N; ++J) {
            if((-target <= nums[J] - nums[I]) && (nums[J] - nums[I] <= target)) {
                int currJumps = solveWithMemo(memory, nums, N, target, J);
                if(currJumps != INT_MIN) {
                    maxJumps = max(maxJumps, 1 + currJumps);
                } 
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[I] = maxJumps;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int target, int I) {
        // Edge case: If you reached the last index, then return 0 as a valid indication of it
        if(I == N - 1)
            return 0;
            
        // Edge case: If all the index are exhausted, then you can't reach the last index
        if(I == N)
            return INT_MIN;

        // Stores the "result value / maximum number of jumps required to reach the last index from the Ith index"
        int maxJumps = INT_MIN;

        // Iterate and if possible, then make the jump and update the result value by the maximum value
        for(int J = I + 1; J < N; ++J) {
            if((-target <= nums[J] - nums[I]) && (nums[J] - nums[I] <= target)) {
                int currJumps = solveWithoutMemo(nums, N, target, J);
                if(currJumps != INT_MIN) {
                    maxJumps = max(maxJumps, 1 + currJumps);
                } 
            }
        }

        // Return the result value
        return maxJumps;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the maximum number of jumps you can make to reach the last index, using 1D buffer for tabulation - O(N*N) & O(N) : Where N let be the size of array
    int maximumJumps(vector<int>& nums, int target) {
        int N = nums.size();
        
        // Tabulation buffer: dp[I] represents the maximum number of jumps required to reach the Ith index
        vector<int> dp(N, INT_MIN);

        // Edge case: If there is only a single element, then 0 jumps are required to reach the last index
        dp[0] = 0;

        // Iterate and find the maximum number of jumps required to reach the Ith index
        for(int I = 0; I < N; ++I) {   
            // Iterate and if possible, then make the jump and update the result value by the maximum value
            for(int J = I + 1; J < N; ++J) {
                if((-target <= nums[J] - nums[I]) && (nums[J] - nums[I] <= target)) {
                    dp[J] = max(dp[J], 1 + dp[I]);
                }
            }
        }

        // Return the maximum number of jumps required to reach the last index
        return (dp[N - 1] < 0) ? -1 : dp[N - 1];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int N;
        cout<<"Enter the size of array: ";
        cin>>N;

        // Input the target value
        int target;
        cout<<"Enter the target value: ";
        cin>>target;

        // Check the given values are lying within the problem constraints or not
        if(N <= 1 || N >= 1001) {
            cout<<"You must enter a size which lies between 2 and 10^3!";
        }
        else if(target <= -1 || target >= 2 * 1e9 + 1) {
            cout<<"You must enter a target which lies between 0 and 2 * 1e9!";
        }
        else {
            // Stores the values of the array
            vector<int> nums(N, 0);

            // Input the values of the array
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1e9 - 1 || nums[index] >= 1e9 + 1)
                    cout<<"You must enter a value which lies between -10^9 and 10^9!\n";
                else 
                    index++;
            }

            // Call to find the maximum number of jumps required to reach the last index
            BottomUp bottomUp;
            int maxJumps = bottomUp.maximumJumps(nums, target);
            cout<<"\nThe maximum number of jumps required to reach the last index is: "<<maxJumps;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/maximum-number-of-jumps-to-reach-the-last-index/description/
*/
