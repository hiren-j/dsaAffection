// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int start, const int end) {
        if(start > end)
            return 0;

        int robHouse  = nums[start] + solveWithoutMemo(nums, start + 2, end);
        int skipHouse = solveWithoutMemo(nums, start + 1, end);
        
        return max(robHouse, skipHouse);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int start, const int end) {
        if(start > end)
            return 0;

        if(dp[start] != -1)
            return dp[start];

        int robHouse  = nums[start] + solveWithMemo(dp, nums, start + 2, end);
        int skipHouse = solveWithMemo(dp, nums, start + 1, end);
        
        return dp[start] = max(robHouse, skipHouse);
    }

public:
    // Methot to find maximum money can rob, using recursion with memoization - O(N) & O(N)
    int robMaxMoney(vector<int>& nums) {
        const int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> dp1(n - 1, -1), dp2(n, -1);
        int startFrom0 = solveWithMemo(dp1, nums, 0, n - 2);
        int startFrom1 = solveWithMemo(dp2, nums, 1, n - 1);
        return max(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(1*N) & O(1*N)
    int solveWith1DTable(const vector<int>& nums, int start, const int end) {
        vector<int> dp(end + 3, -1);
        dp[end + 2] = 0;
        dp[end + 1] = 0;

        for(int idx = end; idx >= start; --idx) {
            int robHouse  = nums[idx] + dp[idx + 2];
            int skipHouse = dp[idx + 1];
            dp[idx] = max(robHouse, skipHouse);
        }

        return dp[start];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(const vector<int>& nums, int start, const int end) {
        int dp_idx_2 = 0;
        int dp_idx_1 = 0;
        int dp_idx   = 0;

        for(int idx = end; idx >= start; --idx) {
            int robHouse  = nums[idx] + dp_idx_2;
            int skipHouse = dp_idx_1;
            dp_idx   = max(robHouse, skipHouse);
            dp_idx_2 = dp_idx_1;
            dp_idx_1 = dp_idx;
        }

        return dp_idx;
    }

public:
    int robMaxMoney(vector<int>& nums) {
        const int n = nums.size();
        if(n == 1) return nums[0];
        int startFrom0 = solveWithoutTable(nums, 0, n - 2);
        int startFrom1 = solveWithoutTable(nums, 1, n - 1);
        return max(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/house-robber-ii/
