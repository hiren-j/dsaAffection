// Code to find the maximum possible sum of a non-empty subarray of the given circular array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
    // Method to find the maximum sum of any subarray, using recursion with memoization - O(N) & O(N)
    int maxSubarraySumCircular(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp1(n, vector<int>(2, -1));
        int maxSum = solveWithMemo(dp1, nums, 0, false, true);

        if(maxSum <= 0) // If all the numbers are negative or 0 then return maximum sum you've got
            return maxSum; 

        vector<vector<int>> dp2(n, vector<int>(2, -1)); 
        int minSum   = solveWithMemo(dp2, nums, 0, false, false);
        int totalSum = accumulate(begin(nums), end(nums), 0);
        return max(maxSum, totalSum - minSum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
                    idealRow[prevPick] = (findMaxSum) ? max(startNext, startCurr) : min(startNext, startCurr);
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
    int maxSubarraySumCircular(vector<int>& nums) {
        n = nums.size();
        int maxSum = solveInPlace(nums, true);

        if(maxSum <= 0) // If all the numbers are negative or 0 then return maximum sum you've got
            return maxSum; 

        int minSum   = solveInPlace(nums, false);
        int totalSum = accumulate(begin(nums), end(nums), 0);
        return max(maxSum, totalSum - minSum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class KadaneAlgorithm {
public:
    // O(N) & O(1)
    int maxSubarraySumCircular(vector<int>& nums) {
        int totalSum = 0;
        int maxSum = INT_MIN, maxEnding = 0; // Tracks maximum sum of a subarray among all the subarrays ending at an index
        int minSum = INT_MAX, minEnding = 0; // Tracks minimum sum of a subarray among all the subarrays ending at an index

        // Note: If you're on a index then you've two possibilities on it: 
        // 1. To start a new subarray from it
        // 2. Pick the index element as a part of the "maximum sum subarray or minimum sum subarray" seen till its previous index

        for(int num : nums) {
            totalSum += num;

            // Calculate maximum subarray sum (Kadane's algorithm for maximum sum subarray)
            maxEnding = max(maxEnding + num, num);
            maxSum    = max(maxSum, maxEnding);

            // Calculate minimum subarray sum (Kadane's algorithm for minimum sum subarray)
            minEnding = min(minEnding + num, num);
            minSum    = min(minSum, minEnding);
        }

        if(maxSum <= 0) // If all the numbers are negative or 0 then return maximum sum you've got
            return maxSum;
        return max(maxSum, totalSum - minSum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Divide and Conquer | Dynamic Programming | Queue | Monotonic Queue
Link  : https://leetcode.com/problems/maximum-sum-circular-subarray/description/
