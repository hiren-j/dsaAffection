// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, const int end) {
        if(i > end)
            return 0;

        int robHouse  = nums[i] + solveWithoutMemo(nums, i + 2, end);
        int skipHouse = solveWithoutMemo(nums, i + 1, end);

        return max(robHouse, skipHouse);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int i, const int end) {
        if(i > end)
            return 0;

        if(dp[i] != -1)
            return dp[i];

        int robHouse  = nums[i] + solveWithMemo(dp, nums, i + 2, end);
        int skipHouse = solveWithMemo(dp, nums, i + 1, end);

        return dp[i] = max(robHouse, skipHouse);
    }

public:
    // Method to find maximum money can rob, using recursion with memoization - O(N) & O(N)
    int robMaxMoney(vector<int>& nums) {
        const int n = nums.size();
        if(n == 1) return nums[0];
        vector<int> dp1(n, -1), dp2(n, -1);
        int startFrom0 = solveWithMemo(dp1, nums, 0, n - 2);
        int startFrom1 = solveWithMemo(dp2, nums, 1, n - 1);
        return max(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(N) & O(N)
    int solveWith1DTable(const vector<int>& nums, const int start, const int end) {
        vector<int> dp(end + 3, -1);
        dp[end + 2] = 0;
        dp[end + 1] = 0;

        for(int i = end; i >= start; --i) {
            int robHouse  = nums[i] + dp[i + 2];
            int skipHouse = dp[i + 1];
            dp[i] = max(robHouse, skipHouse);
        }

        return dp[start];
    }

    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& nums, const int start, const int end) {
        int dp_i_plus_2 = 0; 
        int dp_i_plus_1 = 0; 
        int dp_i = -1;       

        for(int i = end; i >= start; --i) {
            int robHouse  = nums[i] + dp_i_plus_2;
            int skipHouse = dp_i_plus_1;
            dp_i = max(robHouse, skipHouse);
            dp_i_plus_2 = dp_i_plus_1;
            dp_i_plus_1 = dp_i;
        }

        return dp_i;
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
