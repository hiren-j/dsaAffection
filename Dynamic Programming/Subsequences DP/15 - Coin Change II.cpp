// Code to find the total number of combinations that make up the given amount ~ coded by Hiren

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
public:
    // #1 Method to find the number of combinations that make up the given amount, using 2D tabulation - O(N*A) & O(N*A)
    int countWaysToMakeAmount_V1(int amount, vector<int>& coins) {
        int n = coins.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));

        // Initialize the first edge case: If the amount becomes zero then there exists one valid combination
        for(int index = 0; index <= n; ++index)
            dp[index][0] = 1;        

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            for(int currAmount = 1; currAmount <= amount; ++currAmount) {
                int currSkip = dp[index + 1][currAmount]; 
                int currTake = 0;                                                 
                if(coins[index] <= currAmount) {
                    currTake = dp[index][currAmount - coins[index]];
                }
                dp[index][currAmount] = currTake + currSkip;  
            }
        }

        // Return the result value 
        return dp[0][amount];
    }

    // #2 Method to find the number of combinations that make up the given amount, using 1D tabulation - O(N*A) & O(A)
    int countWaysToMakeAmount_V2(int amount, vector<int>& coins) {
        int n = coins.size();

        // 1D DP tables
        vector<int> nextRow(amount + 1, 0), idealRow(amount + 1, 0);
        nextRow[0] = 1;

        // Fill the rest of the table
        for(int index = n-1; index >= 0; --index) {
            idealRow[0] = 1;
            for(int currAmount = 1; currAmount <= amount; ++currAmount) {
                int currSkip = nextRow[currAmount]; 
                int currTake = 0;                                                 
                if(coins[index] <= currAmount) {
                    currTake = idealRow[currAmount - coins[index]];
                }
                idealRow[currAmount] = currTake + currSkip;  
            }
            nextRow = idealRow;
        }

        // Return the result value 
        return nextRow[amount];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/coin-change-ii/description/
        https://cses.fi/problemset/task/1636
