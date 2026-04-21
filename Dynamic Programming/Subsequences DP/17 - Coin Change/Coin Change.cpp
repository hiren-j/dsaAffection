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
public:
    // #1 Method to find the minimum number of coins to make the change for given cents, using 2D tabulation - O(N*C) & O(N*C)
    int minCoinsToMakeChange_V1(vector<int>& coins, int n, int cents) { 
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(cents + 1, INT_MAX));

        // Initialize the first edge case: If the cents becomes zero then you've make the change hence return 0 as a valid indication of it
        for(int index = 0; index <= n; ++index)
            dp[index][0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int cent = 1; cent <= cents; ++cent) {
                int currSkip = dp[index + 1][cent];
                int currTake = INT_MAX;        
                if(cent - coins[index] >= 0) {
                    int nextCoins = dp[index][cent - coins[index]];
                    currTake = (nextCoins != INT_MAX) ? nextCoins + 1 : INT_MAX;
                }
                dp[index][cent] = min(currTake, currSkip);
            }
        }

        int minCoins = dp[0][cents];

        // Return the result value
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }

    // #2 Method to find the minimum number of coins to make the change for given cents, using 1D tabulation - O(N*C) & O(C)
    int minCoinsToMakeChange_V2(vector<int>& coins, int n, int cents) { 
        // 1D DP tables
        vector<int> nextRow(cents + 1, INT_MAX), idealRow(cents + 1, INT_MAX);
        nextRow[0] = 0;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0] = 0;
            for(int cent = 1; cent <= cents; ++cent) {
                int currSkip = nextRow[cent];
                int currTake = INT_MAX;        
                if(cent - coins[index] >= 0) {
                    int nextCoins = idealRow[cent - coins[index]];
                    currTake = (nextCoins != INT_MAX) ? nextCoins + 1 : INT_MAX;
                }
                idealRow[cent] = min(currTake, currSkip);
            }
            nextRow = idealRow;
        }

        int minCoins = nextRow[cents];

        // Return the result value
        return (minCoins == INT_MAX) ? -1 : minCoins;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/number-of-coins1824/1
        https://leetcode.com/problems/coin-change/description/
        https://cses.fi/problemset/task/1634
