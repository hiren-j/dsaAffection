// Code to find the fewest number of coins that you need to make up the amount. If that amount of money cannot be made up by any combination of the coins then return -1. You may assume that you have an infinite number of each kind of coin ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    NOTE: If the given array is always sorted then the solutions of 22.2 are slower comparted to 22.1   
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int solveWithoutMemo(vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;
            
        int minCoins = INT_MAX;

        for(int i = 0; (i < n && coins[i] <= amount); ++i) {
            int nextCoins = solveWithoutMemo(coins, amount - coins[i]);
            if(nextCoins != INT_MAX) minCoins = min(minCoins, nextCoins + 1);
        }

        return minCoins;
    }

    int solveWithMemo(vector<int>& dp, vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;

        if(dp[amount] != -1)
            return dp[amount];

        int minCoins = INT_MAX;

        for(int i = 0; (i < n && coins[i] <= amount); ++i) {
            int nextCoins = solveWithMemo(dp, coins, amount - coins[i]);
            if(nextCoins != INT_MAX) minCoins = min(minCoins, nextCoins + 1);
        }

        return dp[amount] = minCoins;
    }

public:
    int minCoinsToMakeAmount(vector<int>& coins, int amount) {
        n = coins.size();
        sort(begin(coins), end(coins));
        vector<int> dp(amount + 1, -1);
        int minCoins = solveWithMemo(dp, coins, amount);
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    int minCoinsToMakeAmount(vector<int>& coins, int givenAmount) {
        int n = coins.size();
        sort(begin(coins), end(coins));

        vector<int> dp(givenAmount + 1, -1);
        dp[0] = 0;

        for(int amount = 1; amount <= givenAmount; ++amount) {
            int minCoins = INT_MAX;

            for(int i = 0; (i < n && coins[i] <= amount); ++i) {
                int nextCoins = dp[amount - coins[i]];
                if(nextCoins != INT_MAX) minCoins = min(minCoins, nextCoins + 1);
            }

            dp[amount] = minCoins;
        }

        int minCoins = dp[givenAmount];
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/coin-change/description/
        https://cses.fi/problemset/task/1634
