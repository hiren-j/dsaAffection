// Code to find the subarray having the largest sum ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return (prevPick == true) ? 0 : INT_MIN;

        if(prevPick) {
            int pickInSubarr = solveWithoutMemo(nums, i + 1, true) + nums[i];
            int stopHere = 0;
            return max(pickInSubarr, stopHere);
        }
        else {
            int startNewFromCurr = solveWithoutMemo(nums, i + 1, true) + nums[i];
            int startNewFromNext = solveWithoutMemo(nums, i + 1, false);
            return max(startNewFromCurr, startNewFromNext);
        }
    }

    // O(4*N) & O(3*N)
    int solveWithMemo(vector<vector<int>>& memory, const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return (prevPick == true) ? 0 : INT_MIN;

        if(memory[i][prevPick] != INT_MIN)
            return memory[i][prevPick];

        if(prevPick) {
            int pickInSubarr = solveWithMemo(memory, nums, i + 1, true) + nums[i];
            int stopHere = 0;
            return memory[i][prevPick] = max(pickInSubarr, stopHere);
        }
        else {
            int startNewFromCurr = solveWithMemo(memory, nums, i + 1, true) + nums[i];
            int startNewFromNext = solveWithMemo(memory, nums, i + 1, false);
            return memory[i][prevPick] = max(startNewFromCurr, startNewFromNext);
        }
    }

public:
    int maxSubArray(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> memory(n, vector<int>(2, INT_MIN));
        return solveWithMemo(memory, nums, 0, false);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveWith2DTable(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(2, INT_MIN));
        dp[n][true]  = 0;
        dp[n][false] = INT_MIN;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickInSubarr = dp[i + 1][true] + nums[i];
                    int stopHere = 0;
                    dp[i][prevPick] = max(pickInSubarr, stopHere);
                }
                else {
                    int startNewFromCurr = dp[i + 1][true] + nums[i];
                    int startNewFromNext = dp[i + 1][false];
                    dp[i][prevPick] = max(startNewFromCurr, startNewFromNext);
                }
            }
        }

        return dp[0][false];
    }
    
    // O(N*2) & O(2*2)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> nextRow(2, INT_MIN); // i + 1th row
        nextRow[true]  = 0;
        nextRow[false] = INT_MIN;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(2, INT_MIN); // ith row

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickInSubarr = nextRow[true] + nums[i];
                    int stopHere = 0;
                    idealRow[prevPick] = max(pickInSubarr, stopHere);
                }
                else {
                    int startNewFromCurr = nextRow[true] + nums[i];
                    int startNewFromNext = nextRow[false];
                    idealRow[prevPick] = max(startNewFromCurr, startNewFromNext);
                }
            }

            swap(nextRow, idealRow);
        }

        return nextRow[false];
    }
    
    // O(N*2) & O(1)
    int solveWithoutTable(const vector<int>& nums) {
        int nextRow_1 = 0;
        int nextRow_0 = INT_MIN;

        for(int i = n - 1; i >= 0; --i) {
            int idealRow_1 = INT_MIN;
            int idealRow_0 = INT_MIN;

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickInSubarr = nextRow_1 + nums[i];
                    int stopHere = 0;
                    idealRow_1 = max(pickInSubarr, stopHere);
                }
                else {
                    int startNewFromCurr = nextRow_1 + nums[i];
                    int startNewFromNext = nextRow_0;
                    idealRow_0 = max(startNewFromCurr, startNewFromNext);
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
