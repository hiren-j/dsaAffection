// Code to find the total number of combinations that make up the given amount ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^(N+A)) & O(N+A) : Where A = amount
    int solveWithoutMemo(const vector<int>& coins, int i, int amount) {
        if(amount == 0)
            return 1;

        if(i == n)
            return 0;

        int currSkip = solveWithoutMemo(coins, i + 1, amount);
        int currTake = coins[i] <= amount 
                        ? solveWithoutMemo(coins, i, amount - coins[i])
                        : 0;

        return (currSkip + currTake);
    }

    // O(N*A) & O(N*A) : Where A = amount
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& coins, int i, int amount) {
        if(amount == 0)
            return 1;

        if(i == n)
            return 0;

        if(dp[i][amount] != -1)
            return dp[i][amount];

        int currSkip = solveWithMemo(dp, coins, i + 1, amount);
        int currTake = coins[i] <= amount 
                        ? solveWithMemo(dp, coins, i, amount - coins[i])
                        : 0;

        return dp[i][amount] = (currSkip + currTake);
    }

    // O(N*N*A) & O(N*A) : Where A = amount
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& coins, int start, int amount) {
        if(amount == 0)
            return 1;

        if(start == n)
            return 0;

        if(dp[start][amount] != -1)
            return dp[start][amount];

        int count = 0;

        for(int i = start; i < n; ++i) {
            int currTake = coins[i] <= amount 
                            ? solveWithMemoLoop(dp, coins, i, amount - coins[i])
                            : 0;
            count += currTake;
        }

        return dp[start][amount] = count;
    }


public:
    int countWaysToMakeAmount(int amount, vector<int>& coins) {
        n = coins.size();
        vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
        return solveWithMemoLoop(dp, coins, 0, amount);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*AG) & O(N*AG) : Where A = amountGiven
    int solveBy2DTable(const vector<int>& coins, int amountGiven) {
        vector<vector<int>> dp(n + 1, vector<int>(amountGiven + 1, -1));

        for(int amount = 0; amount <= amountGiven; ++amount) 
            dp[n][amount] = 0;

        for(int i = 0; i <= n; ++i)
            dp[i][0] = 1;

        for(int i = n - 1; i >= 0; --i) {
            for(int amount = 0; amount <= amountGiven; ++amount) {
                unsigned int currSkip = dp[i + 1][amount];
                unsigned int currTake = coins[i] <= amount 
                                ? dp[i][amount - coins[i]]
                                : 0;
                dp[i][amount] = (currSkip + currTake);   
            }
        }

        return dp[0][amountGiven];
    }

    // O(N*AG) & O(N*AG) : Where A = amountGiven
    int solveBy2DEnhanced(const vector<int>& coins, int amountGiven) {
        vector<vector<int>> dp(n + 1, vector<int>(amountGiven + 1, 0));

        for(int i = 0; i <= n; ++i)
            dp[i][0] = 1;

        for(int i = n - 1; i >= 0; --i) {
            for(int amount = 0; amount <= amountGiven; ++amount) {
                unsigned int currSkip = dp[i + 1][amount];
                unsigned int currTake = coins[i] <= amount 
                                ? dp[i][amount - coins[i]]
                                : 0;
                dp[i][amount] = (currSkip + currTake);   
            }
        }

        return dp[0][amountGiven];
    }

    // O(N*AG) & O(AG) : Where A = amountGiven
    int solveBy1DTable(const vector<int>& coins, int amountGiven) {
        vector<int> nextRow(amountGiven + 1, 0); // i + 1th row
        nextRow[0] = 1;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(amountGiven + 1, 0); // ith row
            idealRow[0] = 1;
            
            for(int amount = 0; amount <= amountGiven; ++amount) {
                unsigned int currSkip = nextRow[amount];
                unsigned int currTake = coins[i] <= amount 
                                ? idealRow[amount - coins[i]]
                                : 0;
                idealRow[amount] = (currSkip + currTake);   
            }

            swap(nextRow, idealRow);
        }

        return nextRow[amountGiven];
    }   

public:
    int countWaysToMakeAmount(int amount, vector<int>& coins) {
        n = coins.size();
        return solveBy1DTable(coins, amount);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/coin-change-ii/description/
        https://cses.fi/problemset/task/1636
