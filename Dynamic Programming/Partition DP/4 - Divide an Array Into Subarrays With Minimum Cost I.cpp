// Code to find the minimum sum of the cost of splitted array. You are given an array of integers nums of length n. The cost of an array is the value of its first element. For example, the cost of [1,2,3] is 1 while the cost of [3,4,1] is 3. You need to divide nums into 3 disjoint contiguous subarrays ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int start_i, int k) {
        // Edge case: If you've divided the array into 3 subarrays then return 0
        if(start_i == n) 
            return (k == 0) ? 0 : INT_MAX; 

        // Edge case: If array needs more than 3 splits then don't do the partition
        if(k < 0) 
            return INT_MAX;

        int subArrayCost, minCost = INT_MAX;

        for(int i = start_i; i < n; ++i) {
            if(i == start_i) subArrayCost = nums[i];
            int nextCost = solveWithoutMemo(nums, i + 1, k - 1);
            if(nextCost != INT_MAX) minCost = min(minCost, subArrayCost + nextCost);
        }

        return minCost;
    }

    // O(N*N*4) & O(N*4 + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int start_i, int k) {
        // Edge case: If you've divided the array into 3 subarrays then return 0
        if(start_i == n) 
            return (k == 0) ? 0 : INT_MAX; 

        // Edge case: If array needs more than 3 splits then don't do the partition
        if(k < 0) 
            return INT_MAX;

        if(dp[start_i][k] != -1)
            return dp[start_i][k];

        int subArrayCost, minCost = INT_MAX;

        for(int i = start_i; i < n; ++i) {
            if(i == start_i) subArrayCost = nums[i];
            int nextCost = solveWithMemo(dp, nums, i + 1, k - 1);
            if(nextCost != INT_MAX) minCost = min(minCost, subArrayCost + nextCost);
        }

        return dp[start_i][k] = minCost;
    }

public:
    // Method to find the minimum sum of the cost of splitted array, using recursion with memoization - O(N^2) & O(N)
    int minimumCost(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solveWithMemo(dp, nums, 0, 3);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum sum of the cost of splitted array, using 2D tabulation - O(N^2) & O(N)
    int minimumCost(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> dp(n + 1, vector<int>(4, INT_MAX));
        dp[n][0] = 0; // Initialize the first edge case

        for(int start_i = n-1; start_i >= 0; --start_i) {
            for(int k = 1; k <= 3; ++k) {
                int subArrayCost, minCost = INT_MAX;

                for(int i = start_i; i < n; ++i) {
                    if(i == start_i) subArrayCost = nums[i];
                    int nextCost = dp[i + 1][k - 1];
                    if(nextCost != INT_MAX) minCost = min(minCost, subArrayCost + nextCost);
                }

                dp[start_i][k] = minCost;
            }
        }

        return dp[0][3];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/divide-an-array-into-subarrays-with-minimum-cost-i/description/ 
