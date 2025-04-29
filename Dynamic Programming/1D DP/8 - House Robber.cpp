// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& houses, int index) {
        if(index >= n)
            return 0;

        int robHouse = houses[index] + solveWithoutMemo(houses, index + 2);
        int skipRob  = solveWithoutMemo(houses, index + 1);

        return max(robHouse, skipRob);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& houses, int index) {
        if(index >= n)
            return 0;

        if(dp[index] != -1)
            return dp[index];

        int robHouse = houses[index] + solveWithMemo(dp, houses, index + 2);
        int skipRob  = solveWithMemo(dp, houses, index + 1);

        return dp[index] = max(robHouse, skipRob);
    }

public:
    int robMaxMoney(vector<int>& houses) {
        n = houses.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, houses, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(1*N) & O(1*N)
    int solveWith1DTable(vector<int>& houses) {
        vector<int> dp(n + 2, -1);
        dp[n] = dp[n + 1] = 0;

        for(int index = n-1; index >= 0; --index) {
            int robHouse = houses[index] + dp[index + 2];
            int skipRob  = dp[index + 1];
            dp[index] = max(robHouse, skipRob);
        }

        return dp[0];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(vector<int>& houses) {
        int dpIndex2 = 0;
        int dpIndex1 = 0; 
        int maxMoney;

        for(int index = n-1; index >= 0; --index) {
            int robHouse = houses[index] + dpIndex2;
            int skipRob  = dpIndex1;
            maxMoney = max(robHouse, skipRob);
            dpIndex2 = dpIndex1;
            dpIndex1 = maxMoney;
        }

        return maxMoney;
    }

public:
    int robMaxMoney(vector<int>& houses) {
        n = houses.size();
        return solveWithoutTable(houses);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/house-robber/description/?envType=daily-question&envId=2024-01-21
        https://www.naukri.com/code360/problems/loot-houses_630510
        https://www.geeksforgeeks.org/problems/stickler-theif-1587115621/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
