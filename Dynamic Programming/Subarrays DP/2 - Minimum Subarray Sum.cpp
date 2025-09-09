// Code to find the subarray having the smallest sum ~ coded by Hiren

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

        if(dp[i][prevPick] != -1)
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
    // Method to find minimum sum of a subarray, using recursion with memoization - O(N) & O(N)
    int minSumSubarray(vector<int>& nums) {
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
        dp[n][1] = 0;
        dp[n][0] = INT_MAX;

        for(int i = n-1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurr = nums[i] + dp[i + 1][true];
                    int stopHere = 0;
                    dp[i][prevPick] = min(pickCurr, stopHere);
                }
                else {
                    int startFromNext = dp[i + 1][false];
                    int startFromCurr = nums[i] + dp[i + 1][true];
                    dp[i][prevPick] = min(startFromNext, startFromCurr);
                }
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> nextRow(2, -1);
        nextRow[1] = 0;
        nextRow[0] = INT_MAX;

        for(int i = n-1; i >= 0; --i) {
            vector<int> idealRow(2, -1);
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurr = nums[i] + nextRow[true];
                    int stopHere = 0;
                    idealRow[prevPick] = min(pickCurr, stopHere);
                }
                else {
                    int startFromNext = nextRow[false];
                    int startFromCurr = nums[i] + nextRow[true];
                    idealRow[prevPick] = min(startFromNext, startFromCurr);
                }
            }
            swap(nextRow, idealRow);
        }

        return nextRow[false];
    }

    // O(N*2) & O(1)
    int solveWithoutTable(vector<int>& nums) {
        int nextRow_1 = 0;
        int nextRow_0 = INT_MAX;

        for(int i = n-1; i >= 0; --i) {
            int idealRow_1 = -1;
            int idealRow_0 = -1;
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurr = nums[i] + nextRow_1;
                    int stopHere = 0;
                    idealRow_1 = min(pickCurr, stopHere);
                }
                else {
                    int startFromNext = nextRow_0;
                    int startFromCurr = nums[i] + nextRow_1;
                    idealRow_0 = min(startFromNext, startFromCurr);
                }
            }
            swap(nextRow_1, idealRow_1);
            swap(nextRow_0, idealRow_0);
        }
        
        return nextRow_0;
    }

public:
    int minSumSubarray(vector<int>& nums) {
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
