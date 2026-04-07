// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i) {
        if(i >= n)
            return 0;

        int robHouse  = nums[i] + solveWithoutMemo(nums, i + 2);
        int skipHouse = solveWithoutMemo(nums, i + 1);

        return max(robHouse, skipHouse);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int i) {
        if(i >= n)
            return 0;

        if(dp[i] != -1)
            return dp[i];

        int robHouse  = nums[i] + solveWithMemo(dp, nums, i + 2);
        int skipHouse = solveWithMemo(dp, nums, i + 1);

        return dp[i] = max(robHouse, skipHouse);
    }

public:
    int robMaxMoney(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> dp(n + 2, -1);
        dp[n + 1] = 0;
        dp[n] = 0;

        for(int i = n - 1; i >= 0; --i) {
            int robHouse  = nums[i] + dp[i + 2];
            int skipHouse = dp[i + 1];
            dp[i] = max(robHouse, skipHouse);
        }

        return dp[0];
    }

    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& nums) {
        int dp_i_plus_2 = 0; 
        int dp_i_plus_1 = 0; 
        int dp_i = -1; 

        for(int i = n - 1; i >= 0; --i) {
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
        n = nums.size();
        return solveWithoutTable(nums);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/house-robber/description/?envType=daily-question&envId=2024-01-21
        https://www.naukri.com/code360/problems/loot-houses_630510
        https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
