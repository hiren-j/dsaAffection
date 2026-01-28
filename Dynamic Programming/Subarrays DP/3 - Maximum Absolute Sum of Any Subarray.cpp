// Code to find the maximum absolute sum of any subarray of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, bool findMaxSum) {
        if(i == n)
            return (prevPick == true) ? 0 : (findMaxSum ? INT_MIN : INT_MAX);

        if(prevPick) {
            int pickInSubarr = solveWithoutMemo(nums, i + 1, true, findMaxSum) + nums[i];
            int stopHere = 0;
            return findMaxSum ? max(pickInSubarr, stopHere) : min(pickInSubarr, stopHere);
        }
        else {
            int startCurr = solveWithoutMemo(nums, i + 1, true, findMaxSum) + nums[i];
            int startNext = solveWithoutMemo(nums, i + 1, false, findMaxSum);
            return findMaxSum ? max(startCurr, startNext) : min(startCurr, startNext);
        }
    }

    // O(4*N) & O(3*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, bool prevPick, bool findMaxSum) {
        if(i == n)
            return (prevPick == true) ? 0 : (findMaxSum ? INT_MIN : INT_MAX);

        if(dp[i][prevPick] != (findMaxSum ? INT_MIN : INT_MAX))
            return dp[i][prevPick];

        if(prevPick) {
            int pickInSubarr = solveWithMemo(dp, nums, i + 1, true, findMaxSum) + nums[i];
            int stopHere = 0;
            return dp[i][prevPick] = findMaxSum ? max(pickInSubarr, stopHere) : min(pickInSubarr, stopHere);
        }
        else {
            int startCurr = solveWithMemo(dp, nums, i + 1, true, findMaxSum) + nums[i];
            int startNext = solveWithMemo(dp, nums, i + 1, false, findMaxSum);
            return dp[i][prevPick] = findMaxSum ? max(startCurr, startNext) : min(startCurr, startNext);
        }
    }

public:
    int maxAbsoluteSum(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp1(n, vector<int>(2, INT_MIN)), dp2(n, vector<int>(2, INT_MAX));
        int maxSum = solveWithMemo(dp1, nums, 0, false, true);
        int minSum = solveWithMemo(dp2, nums, 0, false, false);
        return max(maxSum, abs(minSum));
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveWith2DTable(const vector<int>& nums, bool findMaxSum) {
        vector<vector<int>> dp(n + 1, vector<int>(2, (findMaxSum ? INT_MIN : INT_MAX)));
        dp[n][true]  = 0;
        dp[n][false] = (findMaxSum ? INT_MIN : INT_MAX); 

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickInSubarr = dp[i + 1][true] + nums[i];
                    int stopHere = 0;
                    dp[i][prevPick] = findMaxSum ? max(pickInSubarr, stopHere) : min(pickInSubarr, stopHere);
                }
                else {
                    int startCurr = dp[i + 1][true] + nums[i];
                    int startNext = dp[i + 1][false];
                    dp[i][prevPick] = findMaxSum ? max(startCurr, startNext) : min(startCurr, startNext);
                }
            }
        } 

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveWith1DTable(const vector<int>& nums, bool findMaxSum) {
        vector<int> nextRow(2, (findMaxSum ? INT_MIN : INT_MAX)); // i + 1th row
        nextRow[true]  = 0;
        nextRow[false] = (findMaxSum ? INT_MIN : INT_MAX); 

        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(2, (findMaxSum ? INT_MIN : INT_MAX)); // ith row

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickInSubarr = nextRow[true] + nums[i];
                    int stopHere = 0;
                    currRow[prevPick] = findMaxSum ? max(pickInSubarr, stopHere) : min(pickInSubarr, stopHere);
                }
                else {
                    int startCurr = nextRow[true] + nums[i];
                    int startNext = nextRow[false];
                    currRow[prevPick] = findMaxSum ? max(startCurr, startNext) : min(startCurr, startNext);
                }
            }

            swap(nextRow, currRow);
        } 

        return nextRow[false];
    }
    
    // O(N*2) & O(1)
    int solveWithoutTable(const vector<int>& nums, bool findMaxSum) {
        int nextRow_1  = 0;
        int nextRow_0 = (findMaxSum ? INT_MIN : INT_MAX); 

        for(int i = n - 1; i >= 0; --i) {
            int currRow_1 = (findMaxSum ? INT_MIN : INT_MAX);
            int currRow_0 = (findMaxSum ? INT_MIN : INT_MAX); 

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickInSubarr = nextRow_1 + nums[i];
                    int stopHere = 0;
                    currRow_1 = findMaxSum ? max(pickInSubarr, stopHere) : min(pickInSubarr, stopHere);
                }
                else {
                    int startCurr = nextRow_1 + nums[i];
                    int startNext = nextRow_0;
                    currRow_0 = findMaxSum ? max(startCurr, startNext) : min(startCurr, startNext);
                }
            }

            swap(nextRow_1, currRow_1);
            swap(nextRow_0, currRow_0);
        } 

        return nextRow_0;
    }

public:
    int maxAbsoluteSum(vector<int>& nums) {
        n = nums.size();
        int maxSum = solveWithoutTable(nums, true);
        int minSum = solveWithoutTable(nums, false);
        return max(maxSum, abs(minSum));
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class KadaneAlgorithm {
public:
    // O(N) & O(1)
    int maxAbsoluteSum(vector<int>& nums) {
        int maxTillNow = 0;
        int minTillNow = 0;
        int maxSum = INT_MIN;
        int minSum = INT_MAX;

        for(int num : nums)
            maxTillNow = max(maxTillNow + num, num),
            minTillNow = min(minTillNow + num, num),
            maxSum = max(maxSum, maxTillNow),
            minSum = min(minSum, minTillNow);

        return max(maxSum, abs(minSum));
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/ 
