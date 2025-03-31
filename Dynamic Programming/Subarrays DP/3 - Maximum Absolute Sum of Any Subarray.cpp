// Code to find the maximum absolute sum of any subarray of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int solveWithoutMemo(vector<int>& nums, int i, bool prevPick, bool toFindMax) {
        if(i == n)
            return (prevPick ? 0 : (toFindMax ? INT_MIN : INT_MAX));

        if(dp[i][prevPick] != -1)
            return dp[i][prevPick];

        if(prevPick) {
            int pickCurrSubarr = nums[i] + solveWithoutMemo(nums, i + 1, true, toFindMax);
            int stopHere = 0;
            return (toFindMax) ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere);
        }
        else {
            int startNewFromNext = solveWithoutMemo(nums, i + 1, false, toFindMax);
            int startNewFromCurr = nums[i] + solveWithoutMemo(nums, i + 1, true, toFindMax);
            return (toFindMax) ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr);
        }
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int i, bool prevPick, bool toFindMax) {
        if(i == n)
            return (prevPick ? 0 : (toFindMax ? INT_MIN : INT_MAX));

        if(dp[i][prevPick] != -1)
            return dp[i][prevPick];

        if(prevPick) {
            int pickCurrSubarr = nums[i] + solveWithMemo(dp, nums, i + 1, true, toFindMax);
            int stopHere = 0;
            return dp[i][prevPick] = (toFindMax) ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere);
        }
        else {
            int startNewFromNext = solveWithMemo(dp, nums, i + 1, false, toFindMax);
            int startNewFromCurr = nums[i] + solveWithMemo(dp, nums, i + 1, true, toFindMax);
            return dp[i][prevPick] = (toFindMax) ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr);
        }
    }

public:
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

    int solveBy2DTable(vector<int>& nums, bool toFindMax) {
        vector<vector<int>> dp(n + 1, vector<int>(2, (toFindMax ? INT_MIN : INT_MAX)));
        dp[n][1] = 0;
        dp[n][0] = (toFindMax) ? INT_MIN : INT_MAX;

        for(int i = n-1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[i] + dp[i + 1][true];
                    int stopHere = 0; 
                    dp[i][prevPick] = (toFindMax) ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = dp[i + 1][false];
                    int startNewFromCurr = nums[i] + dp[i + 1][true];
                    dp[i][prevPick] = (toFindMax) ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr);
                }
            }
        }

        return dp[0][false];
    }

    int solveBy1DTable(vector<int>& nums, bool toFindMax) {
        vector<int> nextRow(2, (toFindMax ? INT_MIN : INT_MAX));
        nextRow[1] = 0;
        nextRow[0] = (toFindMax) ? INT_MIN : INT_MAX;

        for(int i = n-1; i >= 0; --i) {
            vector<int> idealRow(2, (toFindMax ? INT_MIN : INT_MAX));
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[i] + nextRow[true];
                    int stopHere = 0; 
                    idealRow[prevPick] = (toFindMax) ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextRow[false];
                    int startNewFromCurr = nums[i] + nextRow[true];
                    idealRow[prevPick]   = (toFindMax) ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr);
                }
            }
            nextRow = idealRow;
        }

        return nextRow[false];
    }

    int solveInPlace(vector<int>& nums, bool toFindMax) {
        int nextRow_1 = 0;
        int nextRow_0 = (toFindMax) ? INT_MIN : INT_MAX;

        for(int i = n-1; i >= 0; --i) {
            int idealRow_1 = (toFindMax ? INT_MIN : INT_MAX);
            int idealRow_0 = (toFindMax ? INT_MIN : INT_MAX);
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nums[i] + nextRow_1;
                    int stopHere = 0; 
                    idealRow_1 = (toFindMax) ? max(pickCurrSubarr, stopHere) : min(pickCurrSubarr, stopHere);
                }
                else {
                    int startNewFromNext = nextRow_0;
                    int startNewFromCurr = nums[i] + nextRow_1;
                    idealRow_0 = (toFindMax) ? max(startNewFromNext, startNewFromCurr) : min(startNewFromNext, startNewFromCurr);
                }
            }
            nextRow_1 = idealRow_1;
            nextRow_0 = idealRow_0;
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
