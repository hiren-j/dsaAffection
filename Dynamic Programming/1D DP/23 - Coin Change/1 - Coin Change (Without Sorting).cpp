// Code to find the fewest number of coins that you need to make up the amount. If that amount of money cannot be made up by any combination of the coins then return -1. You may assume that you have an infinite number of each kind of coin ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N^A) & O(A) : Where A = amount
    int solveWithoutMemo(const vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;
            
        int minCoins = INT_MAX;

        for(int i = 0; i < n; ++i) {
            if(coins[i] > amount) 
                continue;
            int nextCoins = solveWithoutMemo(coins, amount - coins[i]);
            if(nextCoins != INT_MAX) minCoins = min(minCoins, nextCoins + 1);
        }

        return minCoins;
    }

    // O(N*A) & O(2*A) : Where A = amount
    int solveWithMemo(vector<int>& dp, const vector<int>& coins, int amount) {
        if(amount == 0)
            return 0;

        if(dp[amount] != -1)
            return dp[amount];

        int minCoins = INT_MAX;

        for(int i = 0; i < n; ++i) {
            if(coins[i] > amount) 
                continue;
            int nextCoins = solveWithMemo(dp, coins, amount - coins[i]);
            if(nextCoins != INT_MAX) minCoins = min(minCoins, nextCoins + 1);
        }

        return dp[amount] = minCoins;
    }

public:
    int minCoinsToMakeAmount(vector<int>& coins, int amount) {
        n = coins.size();
        vector<int> dp(amount + 1, -1);
        int minCoins = solveWithMemo(dp, coins, amount);
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:    
    // O(A*N) & O(1*A) : Where A = givenAmount
    int minCoinsToMakeAmount(const vector<int>& coins, int givenAmount) {
        int n = coins.size();
        
        vector<int> dp(givenAmount + 1, -1);
        dp[0] = 0;

        for(int amount = 1; amount <= givenAmount; ++amount) {
            int minCoins = INT_MAX;

            for(int i = 0; i < n; ++i) {
                if(coins[i] > amount) 
                    continue;
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
