// Code to find the subarray having the smallest sum ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    using LL = long long;
    int n;
    
    // O(2^N) & O(N)
    LL solveWithoutMemo(const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return (prevPick == true) ? 0 : LLONG_MAX;

        if(prevPick) {
            LL pickInSubarr = solveWithoutMemo(nums, i + 1, true) + nums[i];
            LL stopHere = 0;
            return min(pickInSubarr, stopHere);
        }
        else {
            LL startFromCurr = solveWithoutMemo(nums, i + 1, true) + nums[i];
            LL startFromNext = solveWithoutMemo(nums, i + 1, false);
            return min(startFromCurr, startFromNext);
        }
    }
    
    // O(4*N) & O(3*N)
    LL solveWithMemo(vector<vector<LL>>& memory, const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return (prevPick == true) ? 0 : LLONG_MAX;

        if(memory[i][prevPick] != LLONG_MAX)
            return memory[i][prevPick]; 

        if(prevPick) {
            LL pickInSubarr = solveWithMemo(memory, nums, i + 1, true) + nums[i];
            LL stopHere = 0;
            return memory[i][prevPick] = min(pickInSubarr, stopHere);
        }
        else {
            LL startFromCurr = solveWithMemo(memory, nums, i + 1, true) + nums[i];
            LL startFromNext = solveWithMemo(memory, nums, i + 1, false);
            return memory[i][prevPick] = min(startFromCurr, startFromNext);
        }
    }

public:
    // Method to find minimum sum of a subarray, using recursion with memoization - O(N) & O(N)
    int smallestSumSubarray(vector<int>& nums) {
        n = nums.size();
        vector<vector<LL>> memory(n, vector<LL>(2, LLONG_MAX));
        return solveWithMemo(memory, nums, 0, false);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
	using LL = long long;
	int n;

    // O(N*2) & O(N*2)
    LL solveBy2DTable(const vector<int>& nums) {
        vector<vector<LL>> dp(n + 1, vector<LL>(2, LLONG_MAX));
        dp[n][true]  = 0;
        dp[n][false] = LLONG_MAX;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    LL pickInSubarr = dp[i + 1][true] + nums[i];
                    LL stopHere = 0;
                    dp[i][prevPick] = min(pickInSubarr, stopHere);
                }
                else {
                    LL startFromCurr = dp[i + 1][true] + nums[i];
                    LL startFromNext = dp[i + 1][false];
                    dp[i][prevPick]  = min(startFromCurr, startFromNext);
                }   
            }
        }
        
        return dp[0][false];
    }
    
    // O(N*2) & O(2*2)
    LL solveBy1DTable(const vector<int>& nums) {
        vector<LL> nextRow(2, LLONG_MAX); // i + 1th row
        nextRow[true]  = 0;
        nextRow[false] = LLONG_MAX;
        
        for(int i = n - 1; i >= 0; --i) {
            vector<LL> currRow(2, LLONG_MAX); // ith row
            
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    LL pickInSubarr = nextRow[true] + nums[i];
                    LL stopHere = 0;
                    currRow[prevPick] = min(pickInSubarr, stopHere);
                }
                else {
                    LL startFromCurr  = nextRow[true] + nums[i];
                    LL startFromNext  = nextRow[false];
                    currRow[prevPick] = min(startFromCurr, startFromNext);
                }   
            }
            
            swap(nextRow, currRow);
        }
        
        return nextRow[false];
    }
    
    // O(N*2) & O(1)
    LL solveWithoutTable(const vector<int>& nums) {
        LL nextRow_1 = 0;
        LL nextRow_0 = LLONG_MAX;
        
        for(int i = n - 1; i >= 0; --i) {
            LL currRow_1 = LLONG_MAX;
            LL currRow_0 = LLONG_MAX;
            
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    LL pickInSubarr = nextRow_1 + nums[i];
                    LL stopHere = 0;
                    currRow_1 = min(pickInSubarr, stopHere);
                }
                else {
                    LL startFromCurr = nextRow_1 + nums[i];
                    LL startFromNext = nextRow_0;
                    currRow_0 = min(startFromCurr, startFromNext);
                }   
            }
            
            swap(nextRow_1, currRow_1);
            swap(nextRow_0, currRow_0);
        }
        
        return nextRow_0;
    }

public:
    int smallestSumSubarray(vector<int>& nums) {
        n = nums.size();
        return solveWithoutTable(nums);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class KadaneAlgorithm {
public: 
    // O(N) & O(1)
    int minSumSubArray(vector<int>& nums) {
        int minEnding = 0; // Represents the minimum sum of a subarray among all the subarrays ending at an index
        int result = INT_MAX;

        // Note: If you're on a index then you've two possibilities on it: 
        // 1. To start a new subarray from it
        // 2. Pick the index element as a part of the minimum sum subarray seen till its previous index

        for(int num : nums) {
            minEnding = min(minEnding + num, num);
            result    = min(result, minEnding);     
        }

        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Divide and Conquer | Dynamic Programming 
Link  : https://www.geeksforgeeks.org/problems/smallest-sum-contiguous-subarray/1
