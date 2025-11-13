// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int idx) {
        if(idx >= n)
            return 0; // If no houses then can rob no money

        int robHouse  = nums[idx] + solveWithoutMemo(nums, idx + 2); 
        int skipHouse = solveWithoutMemo(nums, idx + 1);          

        return max(robHouse, skipHouse);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int idx) {
        if(idx >= n)
            return 0; // If no houses then can rob no money

        if(dp[idx] != -1)
            return dp[idx];

        int robHouse  = nums[idx] + solveWithMemo(dp, nums, idx + 2); 
        int skipHouse = solveWithMemo(dp, nums, idx + 1);

        return dp[idx] = max(robHouse, skipHouse);
    }

public:
    // Methot to find maximum money can rob, using recursion with memoization - O(N) & O(N)
    int robMaxMoney(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(1*N) & O(1*N)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> dp(n + 2, -1);
        dp[n] = 0;
        dp[n + 1] = 0;

        for(int idx = n-1; idx >= 0; --idx) {
            int robHouse  = nums[idx] + dp[idx + 2]; 
            int skipHouse = dp[idx + 1];
            dp[idx] = max(robHouse, skipHouse);
        }

        return dp[0];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(const vector<int>& nums) {
        int dp_idx_1 = 0;
        int dp_idx_2 = 0;
        int dp_idx   = 0;

        for(int idx = n-1; idx >= 0; --idx) {
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
        n = nums.size();
        return solveWithoutTable(nums);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/house-robber/description/?envType=daily-question&envId=2024-01-21
        https://www.naukri.com/code360/problems/loot-houses_630510
        https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
