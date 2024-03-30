// Program to determine if you can reach the last index or not (each element in the array represents your maximum jump length at that position) ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to determine if you can reach the last index or not, using recursion with memoization - O(N*N) & O(N) : Where N let be the size of array
    bool canReachLastIndex(vector<int>& nums) {
        int N = nums.size();
        vector<int> memory(N, -1);
        return solveWithMemo(memory, nums, N, 0);
    }

private:
    // O(N*N) & O(N)
    bool solveWithMemo(vector<int>& memory, vector<int>& nums, int N, int index) {
        // Edge case: If you reached the last index, then return true
        if(index == N - 1)
            return true;

        // Edge case: If all the index are exhausted, then you can't reach the last index
        if(index >= N)
            return false;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index] != -1)
            return memory[index];

        // Tracks the "result value / reach to the last index is possible from the current index or not"
        bool flag = false;

        // If you didn't reached the last index, then iterate and make each possible jump from the current index
        for(int jump = 1; (!flag && jump <= nums[index]); ++jump)
            flag |= solveWithMemo(memory, nums, N, index + jump);

        // Store the result value to the memoization table and then return it
        return memory[index] = flag;
    }

    // O(N^N) & O(N)
    bool solveWithouMemo(vector<int>& nums, int N, int index) {
        // Edge case: If you reached the last index, then return true
        if(index == N - 1)
            return true;

        // Edge case: If all the index are exhausted, then you can't reach the last index
        if(index >= N)
            return false;

        // Tracks the "result value / reach to the last index is possible from the current index or not"
        bool flag = false;

        // If you didn't reached the last index, then iterate and make each possible jump from the current index
        for(int jump = 1; (!flag && jump <= nums[index]); ++jump)
            flag |= solveWithouMemo(nums, N, index + jump);

        // Return the result value
        return flag;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to determine if you can reach the last index or not, using 1D buffer for tabulation - O(N*N) & O(N) : Where N let be the size of array
    bool canReachLastIndex(vector<int>& nums) {
        int N = nums.size();

        // Tabulation buffer: dp[index] represents the information of you can reach the "index" or not
        vector<bool> dp(N, false);

        // Edge case: If there is only a single element, then you're already on the last index
        dp[0] = true;

        // If the "index" is reachable, then iterate and mark the indeces you can the reach from the "index"
        for(int index = 0; (dp[index] && index < N); ++index) {
            // If you didn't reached the last index, then iterate and make each possible jump from the "index"
            for(int jump = 1; (!dp[N - 1] && jump <= nums[index] && index + jump < N); ++jump) {
                dp[index + jump] = true;
            }
        }

        // Return the information of you can reach the last index or not
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

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

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
                if(nums[index] <= -1 || nums[index] >= 100001)
                    cout<<"You must enter a value which lies between 0 and 10^5!\n";
                else 
                    index++;
            }

            // Call to determine if you can reach the last index or not
            BottomUp bottomUp;
            if(bottomUp.canReachLastIndex(nums)) 
                cout<<"\nYou can reach the last index!";
            else
                cout<<"\nYou can't reach the last index!";
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
    Link: https://leetcode.com/problems/jump-game/description/
*/
