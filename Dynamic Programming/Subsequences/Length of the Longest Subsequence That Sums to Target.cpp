// Program to find the length of the longest subsequence of the array that sums up to target. If no such subsequence exists then return -1 ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the length of the longest subsequence which sums to target, using recursion with memoization - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int N = nums.size();
        vector<vector<int>> memory(N, vector<int>(target + 1, -1));
        int maxLength = solveWithMemo(memory, nums, N, 0, target);
        return (maxLength == INT_MIN) ? -1 : maxLength;
    }

private:
    // O(N*T) & O(N*T)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int index, int target) {
        // Edge case: If the target becomes 0, then return 0 as a valid indication of the existence of a subsequence that sums to the target
        if(target == 0)
            return 0;
            
        // Edge case: If all the elements are exhausted, then you can't take any more element
        if(index == N)
            return (target == 0) ? 0 : INT_MIN;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[index][target] != -1)
            return memory[index][target];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, nums, N, index + 1, target); // Is to skip the index value and move on
        int currTake = INT_MIN;                                           // Is to take the index value and move on                                            

        // If possible then take the index value
        if(nums[index] <= target) {
            currTake = solveWithMemo(memory, nums, N, index + 1, target - nums[index]);
            currTake = (currTake != INT_MIN) ? 1 + currTake : currTake;
        }

        // Store the maximum length value to the memoization table and then return it
        return memory[index][target] = max(currTake, currSkip);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int index, int target) {
        // Edge case: If all the elements are exhausted, then you can't take any more element
        if(index == N)
            return (target == 0) ? 0 : INT_MIN;

        // Edge case: If the target becomes 0, then return 0 as a valid indication of the existence of a subsequence that sums to the target
        if(target == 0)
            return 0;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(nums, N, index + 1, target); // Is to skip the index value and move on
        int currTake = INT_MIN;                                      // Is to take the index value and move on

        // If possible then take the index value
        if(nums[index] <= target) {
            currTake = solveWithoutMemo(nums, N, index + 1, target - nums[index]);
            currTake = (currTake != INT_MIN) ? 1 + currTake : currTake;
        }

        // Return the maximum length value
        return max(currTake, currSkip);
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the length of the longest subsequence which sums to target, using recursion with memoization - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        int N = nums.size();
        vector<vector<int>> memory(N, vector<int>(target + 1, -1));
        int maxLength = solveWithMemo(memory, nums, N, 0, target);
        return (maxLength == INT_MIN) ? -1 : maxLength;
    }

private:
    // O(N*T) & O(N*T)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& nums, int N, int startIndex, int target) {
        // Edge case: If all the elements are exhausted, then you can't take any more element
        if(startIndex == N)
            return (target == 0) ? 0 : INT_MIN;

        // Edge case: If the target becomes 0, then return the value 0 as a valid indication of the existence of a subsequence that sums to the target
        if(target == 0)
            return 0;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[startIndex][target] != -1)
            return memory[startIndex][target];
        
        // Stores the "length of the longest subsequence which sums to target / result value"
        int maxLength = INT_MIN;

        // Iterate and if possible, then take the index value
        for(int index = startIndex; index < N; ++index) {
            if(nums[index] <= target) {
                int currLength = solveWithMemo(memory, nums, N, index + 1, target - nums[index]);
                if(currLength != INT_MIN) {
                    maxLength = max(maxLength, 1 + currLength);
                }
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[startIndex][target] = maxLength;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int N, int startIndex, int target) {
        // Edge case: If all the elements are exhausted, then you can't take any more element
        if(startIndex == N)
            return (target == 0) ? 0 : INT_MIN;

        // Edge case: If the target becomes 0, then return the value 0 as a valid indication of the existence of a subsequence that sums to the target
        if(target == 0)
            return 0;

        // Stores the "length of the longest subsequence which sums to target / result value"
        int maxLength = INT_MIN;

        // Iterate and if possible, then take the index value
        for(int index = startIndex; index < N; ++index) {
            if(nums[index] <= target) {
                int currLength = solveWithoutMemo(nums, N, index + 1, target - nums[index]);
                if(currLength != INT_MIN) {
                    maxLength = max(maxLength, 1 + currLength);
                }
            }
        }

        // Return the result value
        return maxLength;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the length of the longest subsequence which sums to target, using 2D buffer for tabulation - O(N*T) & O(N*T) : Where N let be the array size and T let be the target
    int lengthOfLongestSubsequence_V1(vector<int>& nums, int target) {
        int N = nums.size();
        
        // Tabulation buffer: dp[index][currTarget] represents the length of the longest subsequence lying within the "index" elements from the start of the array, such that their sum is equal to the "currTarget"
        vector<vector<int>> dp(N + 1, vector<int>(target + 1, INT_MIN));

        // Edge case: If the array is empty and then target is 0, then no elements are required to sum to 0
        dp[0][0] = 0;

        // Treat each index as the "number of elements can take from the start of the array" and find the length of the longest subsequence lying within the "index" elements, such that their sum is equal to the "currTarget"
        for(int index = 1; index <= N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = dp[index - 1][currTarget];
                int currTake = INT_MIN;
                if(nums[index - 1] <= currTarget) {
                    currTake = dp[index - 1][currTarget - nums[index - 1]];
                    currTake = (currTake != INT_MIN) ? 1 + currTake : currTake;
                }
                dp[index][currTarget] = max(currTake, currSkip);
            }
        }

        // Return the length of the longest subsequence which sums to the given target, return -1 if not found
        return (dp[N][target] == INT_MIN) ? -1 : dp[N][target];
    }

    // #2 Method to find the length of the longest subsequence which sums to target, using 1D buffer for tabulation - O(N*T) & O(T) : Where N let be the array size and T let be the target
    int lengthOfLongestSubsequence_V2(vector<int>& nums, int target) {
        int N = nums.size();

        // Tabulation buffer: "prevRow[currTarget] / currRow[currTarget]" represents the length of the longest subsequence lying within the "index" elements from the start of the array, such that their sum is equal to the "currTarget"
        vector<int> prevRow(target + 1, INT_MIN), currRow(target + 1, INT_MIN);

        // Edge case: If the array is empty and then target is 0, then no elements are required to sum to 0
        prevRow[0] = 0;

        // Treat each index as the "number of elements can take from the start of the array" and find the length of the longest subsequence lying within the "index" elements, such that their sum is equal to the "currTarget"
        for(int index = 1; index <= N; ++index) {
            for(int currTarget = 0; currTarget <= target; ++currTarget) {
                int currSkip = prevRow[currTarget];
                int currTake = INT_MIN;
                if(nums[index - 1] <= currTarget) {
                    currTake = prevRow[currTarget - nums[index - 1]];
                    currTake = (currTake != INT_MIN) ? 1 + currTake : currTake;
                }
                currRow[currTarget] = max(currTake, currSkip);
            }
            prevRow = currRow;
        }

        // Return the length of the longest subsequence which sums to the given target, return -1 if not found
        return (prevRow[target] == INT_MIN) ? -1 : prevRow[target];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
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

        // Check the given values are valid or not
        if(N <= 0 || N >= 1001 || target <= 0 || target >= 1001) {
            cout<<"You must enter the size and target which lies between 1 and 10^3!";
        }
        else {
            // Stores the array values
            vector<int> nums(N, 0);

            // Input the array values
            for(int index = 0; index < N;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                if(nums[index] <= 0 || nums[index] >= 1001) {
                    cout<<"You must enter a value which lies between 1 and 10^3!\n";
                    continue;
                }
                index++;
            }

            // Call to find the length of the longest subsequence that sums up to target
            BottomUp bottomUp;
            int maxLength = bottomUp.lengthOfLongestSubsequence_V2(nums, target);
            cout<<"\nThe length of the longest subsequence of that sums up to target "<<target<<" is: "<<maxLength;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/description/
*/
