// Code to find the maximum profit you can achieve by completing as many transactions as you like, but you need to pay the transaction fee for each transaction ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, fee;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& prices, int i, bool canBuy) {
        if(i == n)
            return 0;

        if(canBuy) {
            int buy  = solveWithoutMemo(prices, i + 1, false) - prices[i] - fee;
            int skip = solveWithoutMemo(prices, i + 1, true); 
            return max(buy, skip);
        }
        else {
            int sell = prices[i] + solveWithoutMemo(prices, i + 1, true);
            int skip = solveWithoutMemo(prices, i + 1, false); 
            return max(sell, skip);
        }
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& prices, int i, bool canBuy) {
        if(i == n)
            return 0;

        if(dp[i][canBuy] != -1)
            return dp[i][canBuy];

        if(canBuy) {
            int buy  = solveWithMemo(dp, prices, i + 1, false) - prices[i] - fee;
            int skip = solveWithMemo(dp, prices, i + 1, true); 
            return dp[i][canBuy] = max(buy, skip);
        }
        else {
            int sell = prices[i] + solveWithMemo(dp, prices, i + 1, true);
            int skip = solveWithMemo(dp, prices, i + 1, false); 
            return dp[i][canBuy] = max(sell, skip);
        }
    }

public:
    int maxProfit(vector<int>& prices, int FEE) {
        n = prices.size(), fee = FEE;
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, prices, 0, true);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int n, fee;

    // O(N) & O(N)
    int solveWith2DTable(const vector<int>& prices) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][0] = 0;
        dp[n][1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = dp[i + 1][false] - prices[i] - fee;
                    int skip = dp[i + 1][true]; 
                    dp[i][canBuy] = max(buy, skip);
                }
                else {
                    int sell = prices[i] + dp[i + 1][true];
                    int skip = dp[i + 1][false]; 
                    dp[i][canBuy] = max(sell, skip);
                }
            }
        }

        return dp[0][true];
    }

    // O(N) & O(1)
    int solveWith1DTable(const vector<int>& prices) {
        vector<int> nextRow(2, -1); 
        nextRow[0] = 0;
        nextRow[1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(2, -1); 
            
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = nextRow[false] - prices[i] - fee;
                    int skip = nextRow[true]; 
                    idealRow[canBuy] = max(buy, skip);
                }
                else {
                    int sell = prices[i] + nextRow[true];
                    int skip = nextRow[false]; 
                    idealRow[canBuy] = max(sell, skip);
                }
            }

            swap(nextRow, idealRow);
        }

        return nextRow[true];
    }

    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& prices) {
        int nextRow_0 = 0;
        int nextRow_1 = 0;

        for(int i = n - 1; i >= 0; --i) {
            int idealRow_0 = -1;
            int idealRow_1 = -1;
            
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = nextRow_0 - prices[i] - fee;
                    int skip = nextRow_1; 
                    idealRow_1 = max(buy, skip);
                }
                else {
                    int sell = prices[i] + nextRow_1;
                    int skip = nextRow_0; 
                    idealRow_0 = max(sell, skip);
                }
            }

            swap(nextRow_0, idealRow_0);
            swap(nextRow_1, idealRow_1);
        }

        return nextRow_1;
    }

public:
    int maxProfit(vector<int>& prices, int FEE) {
        n = prices.size(), fee = FEE;
        return solveWithoutTable(prices);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/description/
