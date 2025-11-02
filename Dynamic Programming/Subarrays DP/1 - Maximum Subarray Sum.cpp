// Code to find the subarray having the largest sum ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int index, bool prevPick) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return 0 else INT_MIN 
        if(index == n)
            return prevPick ? 0 : INT_MIN;

        // Previously if you've picked any subarray then you've two possibilities on the index 
        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithoutMemo(nums, index + 1, true); // Pick the index element or current subarray as a part of the previous subarray
            int stopHere = 0;                                                           // Consider the index as an end point for the previous subarray    
            return max(pickCurrSubarr, stopHere);                                       // As we're striving for the maximum sum hence return the maximum value
        }
        // If you haven't picked any subarray till now then you've two possibilities on the index
        else {
            int startNewFromNext = solveWithoutMemo(nums, index + 1, false);              // Start a new subarray from the next index
            int startNewFromCurr = nums[index] + solveWithoutMemo(nums, index + 1, true); // Start a new subarray from the current index
            return max(startNewFromNext, startNewFromCurr);                               // As we're striving for the maximum sum hence return the maximum value
        }
    }

    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& memory, const vector<int>& nums, int index, bool prevPick) {
        // Edge case: If elements are exhausted and previously if you've picked any subarray then return 0 else INT_MIN 
        if(index == n)
            return prevPick ? 0 : INT_MIN;

        if(memory[index][prevPick] != -1)
            return memory[index][prevPick];

        // Previously if you've picked any subarray then you've two possibilities on the index 
        if(prevPick) {
            int pickCurrSubarr = nums[index] + solveWithMemo(memory, nums, index + 1, true); // Pick the index element or current subarray as a part of the previous subarray
            int stopHere = 0;                                                                // Consider the index as an end point for the previous subarray    
            return memory[index][prevPick] = max(pickCurrSubarr, stopHere);                
        }
        // If you haven't picked any subarray till now then you've two possibilities on the index
        else {
            int startNewFromNext = solveWithMemo(memory, nums, index + 1, false);              // Start a new subarray from the next index
            int startNewFromCurr = nums[index] + solveWithMemo(memory, nums, index + 1, true); // Start a new subarray from the current index
            return memory[index][prevPick] = max(startNewFromNext, startNewFromCurr);          
        }
    }

public:  
    // Method to find maximum sum of a subarray, using recursion with memoization - O(N) & O(N)
    int maxSubArray(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, nums, 0, false);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveWith2DTable(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][1] = 0;       // Init edge case: if(index == n) prevPick ? 0
        dp[n][0] = INT_MIN; // Init edge case: if(index == n) prevPick : INT_MIN

        for(int index = n-1; index >= 0; --index) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + dp[index + 1][true];
                    int stopHere = 0;
                    dp[index][prevPick] = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = dp[index + 1][false];
                    int startNewFromCurr = nums[index] + dp[index + 1][true];
                    dp[index][prevPick] = max(startNewFromNext, startNewFromCurr);
                }
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> nextRow(2, -1);
        nextRow[1] = 0;       // Init edge case: if(index == n) prevPick ? 0
        nextRow[0] = INT_MIN; // Init edge case: if(index == n) prevPick : INT_MIN

        for(int index = n-1; index >= 0; --index) {
            vector<int> idealRow(2, -1);
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + nextRow[true];
                    int stopHere = 0;
                    idealRow[prevPick] = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextRow[false];
                    int startNewFromCurr = nums[index] + nextRow[true];
                    idealRow[prevPick] = max(startNewFromNext, startNewFromCurr);
                }
            }
            swap(nextRow, idealRow);
        }

        return nextRow[false];
    }

    // O(N*2) & O(1)
    int solveWithoutTable(vector<int>& nums) {
        int nextRow_1 = 0;       // Init edge case: if(index == n) prevPick ? 0
        int nextRow_0 = INT_MIN; // Init edge case: if(index == n) prevPick ? INT_MIN

        for(int index = n-1; index >= 0; --index) {
            int idealRow_1 = -1;
            int idealRow_0 = -1;
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[index] + nextRow_1;
                    int stopHere = 0;
                    idealRow_1 = max(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextRow_0;
                    int startNewFromCurr = nums[index] + nextRow_1;
                    idealRow_0 = max(startNewFromNext, startNewFromCurr);
                }
            }
            swap(nextRow_1, idealRow_1);
            swap(nextRow_0, idealRow_0);
        }
        
        return nextRow_0;
    }

public:
    int maxSubArray(vector<int>& nums) {
        n = nums.size();
        return solveWithoutTable(nums);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class KadaneAlgorithm {
public: 
    // O(N) & O(1)
    int maxSubArray(vector<int>& nums) {
        int maxEnding = 0; // Represents the maximum sum of a subarray among all the subarrays ending at an index
        int result = INT_MIN;

        // Note: If you're on a index then you've two possibilities on it: 
        // 1. To start a new subarray from it
        // 2. Pick the index element as a part of the maximum sum subarray seen till its previous index

        for(int num : nums) {
            maxEnding = max(maxEnding + num, num);
            result    = max(result, maxEnding);     
        }

        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Divide and Conquer | Dynamic Programming 
Link  : https://leetcode.com/problems/maximum-subarray/description/
