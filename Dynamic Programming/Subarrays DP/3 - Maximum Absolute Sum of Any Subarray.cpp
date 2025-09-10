// Code to find the maximum absolute sum of any subarray of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, bool findMaxSum) {
        if(i == n)
            return prevPick ? 0 : (findMaxSum ? INT_MIN : INT_MAX);

        if(prevPick) {
            int pickCurr = nums[i] + solveWithoutMemo(nums, i + 1, true, findMaxSum);
            int stopHere = 0;
            return (findMaxSum) ? max(pickCurr, stopHere) : min(pickCurr, stopHere);
        }
        else {
            int startNext = solveWithoutMemo(nums, i + 1, false, findMaxSum);
            int startCurr = nums[i] + solveWithoutMemo(nums, i + 1, true, findMaxSum);
            return (findMaxSum) ? max(startNext, startCurr) : min(startNext, startCurr);
        }
    }

    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, bool prevPick, bool findMaxSum) {
        if(i == n)
            return (prevPick ? 0 : (findMaxSum ? INT_MIN : INT_MAX));

        if(dp[i][prevPick] != -1)
            return dp[i][prevPick];

        if(prevPick) {
            int pickCurr = nums[i] + solveWithMemo(dp, nums, i + 1, true, findMaxSum);
            int stopHere = 0;
            return dp[i][prevPick] = (findMaxSum) ? max(pickCurr, stopHere) : min(pickCurr, stopHere);
        }
        else {
            int startNext = solveWithMemo(dp, nums, i + 1, false, findMaxSum);
            int startCurr = nums[i] + solveWithMemo(dp, nums, i + 1, true, findMaxSum);
            return dp[i][prevPick] = (findMaxSum) ? max(startNext, startCurr) : min(startNext, startCurr);
        }
    }

public:
    // Method to find maximum absolute sum of subarray, using recursion with memoization - O(N) & O(N)
    int maxAbsoluteSum(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp1(n, vector<int>(2, -1)), dp2(n, vector<int>(2, -1));
        int maxSum = solveWithMemo(dp1, nums, 0, false, true);
        int minSum = solveWithMemo(dp2, nums, 0, false, false);
        return max(maxSum, abs(minSum));
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveBy2DTable(const vector<int>& nums, bool findMaxSum) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][1] = 0;
        dp[n][0] = (findMaxSum ? INT_MIN : INT_MAX);

        for(int i = n-1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurr = nums[i] + dp[i + 1][true];
                    int stopHere = 0; 
                    dp[i][prevPick] = (findMaxSum) ? max(pickCurr, stopHere) : min(pickCurr, stopHere);
                }
                else {
                    int startNext = dp[i + 1][false];
                    int startCurr = nums[i] + dp[i + 1][true];
                    dp[i][prevPick] = (findMaxSum) ? max(startNext, startCurr) : min(startNext, startCurr);
                }
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveBy1DTable(const vector<int>& nums, bool findMaxSum) {
        vector<int> nextRow(2, -1);
        nextRow[1] = 0;
        nextRow[0] = (findMaxSum ? INT_MIN : INT_MAX);

        for(int i = n-1; i >= 0; --i) {
            vector<int> idealRow(2, -1);
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurr = nums[i] + nextRow[true];
                    int stopHere = 0; 
                    idealRow[prevPick] = (findMaxSum) ? max(pickCurr, stopHere) : min(pickCurr, stopHere);
                }
                else {
                    int startNext = nextRow[false];
                    int startCurr = nums[i] + nextRow[true];
                    idealRow[prevPick]   = (findMaxSum) ? max(startNext, startCurr) : min(startNext, startCurr);
                }
            }
            swap(nextRow, idealRow);
        }

        return nextRow[false];
    }

    // O(N*2) & O(1)
    int solveInPlace(const vector<int>& nums, bool findMaxSum) {
        int nextRow_1 = 0;
        int nextRow_0 = (findMaxSum ? INT_MIN : INT_MAX);

        for(int i = n-1; i >= 0; --i) {
            int idealRow_1 = -1;
            int idealRow_0 = -1;
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurr = nums[i] + nextRow_1;
                    int stopHere = 0; 
                    idealRow_1 = (findMaxSum) ? max(pickCurr, stopHere) : min(pickCurr, stopHere);
                }
                else {
                    int startNext = nextRow_0;
                    int startCurr = nums[i] + nextRow_1;
                    idealRow_0 = (findMaxSum) ? max(startNext, startCurr) : min(startNext, startCurr);
                }
            }
            swap(nextRow_1, idealRow_1);
            swap(nextRow_0, idealRow_0);
        }

        return nextRow_0;
    }

public:
    int maxAbsoluteSum(vector<int>& nums) {
        n = nums.size();
        int maxSum = solveInPlace(nums, true);
        int minSum = solveInPlace(nums, false);
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
