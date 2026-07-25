// Code to partition the array into (contiguous) subarrays of length at most K. After partitioning, each subarray has their values changed to become the maximum value of that subarray. The aim is to find the largest sum of the given array after partitioning ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, k;

    // O(N^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i) {
        if(i == n)
            return 0;
        
        int maxSum = 0;
        int maxElement = 0;

        for(int j = i; j < min(i + k, n); ++j) {
            maxElement  = max(maxElement, nums[j]);
            int nextSum = solveWithoutMemo(nums, j + 1);
            int currSum = maxElement * (j - i + 1);
            maxSum = max(maxSum, currSum + nextSum);
        }

        return maxSum;
    }

    // O(N^2) & O(N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int i) {
        if(i == n)
            return 0;

        if(dp[i] != -1)
            return dp[i];
        
        int maxSum = 0;
        int maxElement = 0;

        for(int j = i; j < min(i + k, n); ++j) {
            maxElement  = max(maxElement, nums[j]);
            int nextSum = solveWithMemo(dp, nums, j + 1);
            int currSum = maxElement * (j - i + 1);
            maxSum = max(maxSum, currSum + nextSum);
        }

        return dp[i] = maxSum;
    }

public:
    int maxSumAfterPartitioning(vector<int>& nums, int K) {
        n = nums.size(), k = K;
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N^2) & O(N)
    int maxSumAfterPartitioning(vector<int>& nums, int k) {
        const int n = nums.size();

        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int i = n - 1; i >= 0; --i) {
            int maxSum = 0;
            int maxElement = 0;
    
            for(int j = i; j < min(i + k, n); ++j) {
                maxElement  = max(maxElement, nums[j]);
                int nextSum = dp[j + 1];
                int currSum = maxElement * (j - i + 1);
                maxSum = max(maxSum, currSum + nextSum);
            }
    
            dp[i] = maxSum;
        }

        return dp[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/partition-array-for-maximum-sum/description/
