// Code to find the subarray having the largest sum ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return prevPick ? 0 : INT_MAX;

        if(prevPick) {
            int pickCurr = nums[i] + solveWithoutMemo(nums, i + 1, true); 
            int stopHere = 0;                                                                    
            return min(pickCurr, stopHere);                
        }
        else {
            int startFromNext = solveWithoutMemo(nums, i + 1, false);              
            int startFromCurr = nums[i] + solveWithoutMemo(nums, i + 1, true);  
            return min(startFromNext, startFromCurr);          
        }
    }

    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return prevPick ? 0 : INT_MAX;

        if(dp[i][prevPick] != INT_MIN)
            return dp[i][prevPick];

        if(prevPick) {
            int pickCurr = nums[i] + solveWithMemo(dp, nums, i + 1, true); 
            int stopHere = 0;                                                                    
            return dp[i][prevPick] = min(pickCurr, stopHere);                
        }
        else {
            int startFromNext = solveWithMemo(dp, nums, i + 1, false);              
            int startFromCurr = nums[i] + solveWithMemo(dp, nums, i + 1, true);  
            return dp[i][prevPick] = min(startFromNext, startFromCurr);          
        }
    }
    
public:
    // Method to find minimum sum of subarray, using recursion with memoization - O(N) & O(N)
    int smallestSumSubarray(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, INT_MIN));
        return solveWithMemo(dp, nums, 0, false);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveWith2DTable(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(2, INT_MAX));
        dp[n][1] = 0;
        dp[n][0] = INT_MIN;

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
        vector<int> nextRow(2, INT_MAX), idealRow(2, INT_MAX); 
        nextRow[1] = 0;
        nextRow[0] = INT_MIN;

        for(int index = n-1; index >= 0; --index) {
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
        int nextRow_1 = 0;
        int nextRow_0 = INT_MIN;

        for(int index = n-1; index >= 0; --index) {
            int idealRow_1 = INT_MAX;
            int idealRow_0 = INT_MAX;
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
