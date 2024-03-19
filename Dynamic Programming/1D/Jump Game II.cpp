// Program to find the minimum number of jumps required to reach the last index ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the minimum number of jumps you can make to reach the last index, using recursion with memoization - O(N*N) & O(N) : Where N let be the size of array
    int minimumJumps(vector<int>& nums) {
        int N = nums.size();
        vector<int> memory(N, -1);
        return solveWithMemo(memory, nums, N, 0);
    }

private:
    // O(N*N) & O(N)
    int solveWithMemo(vector<int>& memory, vector<int>& nums, int N, int index) {
        // Edge case: If you reached the last index, then return 0 as a valid indication of it
        if(index == N - 1)
            return 0;

        // Edge case: If all the index are exhausted, then you can't reach the last index
        if(index >= N)
            return INT_MAX;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index] != -1)
            return memory[index];

        // Stores the "result value / minimum number of jumps required to reach the last index from the current index"
        int minJumps = INT_MAX;

        // Iterate and if possible, then make the jump and update the result value by the minimum value
        for(int jump = 1; jump <= nums[index]; ++jump) {
            int currJumps = solveWithMemo(memory, nums, N, index + jump);
            if(currJumps != INT_MAX) {
                minJumps = min(minJumps, 1 + currJumps);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[index] = minJumps;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int index) {
        // Edge case: If you reached the last index, then return 0 as a valid indication of it
        if(index == N - 1)
            return 0;

        // Edge case: If all the index are exhausted, then you can't reach the last index
        if(index >= N)
            return INT_MAX;

        // Stores the "result value / minimum number of jumps required to reach the last index from the current index"
        int minJumps = INT_MAX;

        // Iterate and if possible, then make the jump and update the result value by the minimum value
        for(int jump = 1; jump <= nums[index]; ++jump) {
            int currJumps = solveWithoutMemo(nums, N, index + jump);
            if(currJumps != INT_MAX) {
                minJumps = min(minJumps, 1 + currJumps);
            }
        }

        // Return the result value
        return minJumps;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the minimum number of jumps you can make to reach the last index, using 1D buffer for tabulation - O(N*N) & O(N) : Where N let be the size of array
    int minimumJumps(vector<int>& nums) {
        int N = nums.size();

        // Tabulation buffer: dp[index] represents the minimum number of jumps required to reach the "index"
        vector<int> dp(N, INT_MAX);

        // Edge case: If there is only a single element, then 0 jumps are required to reach the last index   
        dp[0] = 0;

        // Iterate and find the minimum number of jumps required to reach the "index"
        for(int index = 0; index < N; ++index) {
            // Iterate and if possible, then make the jump and update the result value by the minimum value
            for(int jump = 1; (jump <= nums[index] && index + jump < N); ++jump) {
                dp[index + jump] = min(dp[index + jump], 1 + dp[index]);
            }
        }

        // Return the minimum number of jumps required to reach the last index
        return dp[N - 1];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the array size
        int N;
        cout<<"Enter the size of array: ";
        cin>>N;

        // Check the given size is lying within the problem constraints or not
        if(N <= 0 || N >= 10001) {
            cout<<"You must enter a size which lies between 1 and 10^4!";
        }
        else {
            // Stores the values of the array
            vector<int> nums(N, 0);

            // Input the values of the array
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= -1 || nums[index] >= 1001)
                    cout<<"You must enter a value which lies between 0 and 10^3!\n";
                else 
                    index++;
            }

            // Call to find the minimum number of jumps required to reach the last index
            BottomUp bottomUp;
            int minJumps = bottomUp.minimumJumps(nums);
            cout<<"\nThe minimum number of jumps required to reach the last index is: "<<minJumps;
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
    Link: https://leetcode.com/problems/jump-game-ii/description/
*/
