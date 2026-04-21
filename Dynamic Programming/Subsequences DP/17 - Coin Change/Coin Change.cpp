// Code to find the minimum number of coins to make the change for given cents. Suppose you've infinite supply of each type of coin ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^(N+A)) & O(N+A) : Where A = amount
    int solveWithoutMemo(const vector<int>& coins, int i, int amount) {
        if(amount == 0)
            return 0;

        if(i == n)
            return INT_MAX;

        int currSkip = solveWithoutMemo(coins, i + 1, amount);
        int currTake = coins[i] <= amount 
                        ? solveWithoutMemo(coins, i, amount - coins[i])
                        : INT_MAX;

        if(currTake != INT_MAX)
            currTake += 1;

        return min(currSkip, currTake);
    }

    // O(N*A) & O(N*A) : Where A = amount
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& coins, int i, int amount) {
        if(amount == 0)
            return 0;

        if(i == n)
            return INT_MAX;

        if(dp[i][amount] != -1)
            return dp[i][amount];

        int currSkip = solveWithMemo(dp, coins, i + 1, amount);
        int currTake = coins[i] <= amount 
                        ? solveWithMemo(dp, coins, i, amount - coins[i])
                        : INT_MAX;

        if(currTake != INT_MAX)
            currTake += 1;

        return dp[i][amount] = min(currSkip, currTake);
    }

    // O(N*N*A) & O(N*A) : Where A = amount
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& coins, int start, int amount) {
        if(amount == 0)
            return 0;

        if(start == n)
            return INT_MAX;

        if(dp[start][amount] != -1)
            return dp[start][amount];

        int minCoins = INT_MAX;

        for(int i = start; i < n; ++i) {
            int currTake = coins[i] <= amount 
                            ? solveWithMemoLoop(dp, coins, i, amount - coins[i])
                            : INT_MAX;
            if(currTake != INT_MAX) currTake += 1;
            minCoins = min(minCoins, currTake);
        }

        return dp[start][amount] = minCoins;
    }

public:
    int minCoinsToMakeChange(vector<int>& coins, int amount) {
        n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        int minCoins = solveWithMemo(dp, coins, 0, amount);
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*AG) & O(N*AG) : Where AG = amountGiven
    int solveBy2DTable(const vector<int>& coins, int amountGiven) {
        vector<vector<int>> dp(n + 1, vector<int>(amountGiven + 1, -1));

        for(int amount = 0; amount <= amountGiven; ++amount) 
            dp[n][amount] = INT_MAX;

        for(int i = 0; i <= n; ++i)
            dp[i][0] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int amount = 0; amount <= amountGiven; ++amount) {
                int currSkip = dp[i + 1][amount];
                int currTake = coins[i] <= amount 
                                ? dp[i][amount - coins[i]]
                                : INT_MAX;
                if(currTake != INT_MAX) 
                    currTake += 1;
                dp[i][amount] = min(currSkip, currTake);
            }
        }

        int minCoins = dp[0][amountGiven];
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }

    // O(N*AG) & O(N*AG) : Where AG = amountGiven
    int solveBy2DEnhanced(const vector<int>& coins, int amountGiven) {
        vector<vector<int>> dp(n + 1, vector<int>(amountGiven + 1, INT_MAX));
            
        for(int i = 0; i <= n; ++i)
            dp[i][0] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int amount = 0; amount <= amountGiven; ++amount) {
                int currSkip = dp[i + 1][amount];
                int currTake = coins[i] <= amount 
                                ? dp[i][amount - coins[i]]
                                : INT_MAX;
                if(currTake != INT_MAX) 
                    currTake += 1;
                dp[i][amount] = min(currSkip, currTake);
            }
        }

        int minCoins = dp[0][amountGiven];
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }

    // O(N*AG) & O(AG) : Where AG = amountGiven
    int solveBy1DTable(const vector<int>& coins, int amountGiven) {
        vector<int> nextRow(amountGiven + 1, INT_MAX); // i + 1th row
        nextRow[0] = 0;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(amountGiven + 1, INT_MAX); // ith row
            idealRow[0] = 0;
            
            for(int amount = 0; amount <= amountGiven; ++amount) {
                int currSkip = nextRow[amount];
                int currTake = coins[i] <= amount 
                                ? idealRow[amount - coins[i]]
                                : INT_MAX;
                if(currTake != INT_MAX) 
                    currTake += 1;
                idealRow[amount] = min(currSkip, currTake);   
            }

            swap(nextRow, idealRow);
        }

        int minCoins = nextRow[amountGiven];
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }   

public:
    int minCoinsToMakeChange(vector<int>& coins, int amount) {
        n = coins.size();
        return solveBy1DTable(coins, amount);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/number-of-coins1824/1
        https://leetcode.com/problems/coin-change/description/
        https://cses.fi/problemset/task/1634
