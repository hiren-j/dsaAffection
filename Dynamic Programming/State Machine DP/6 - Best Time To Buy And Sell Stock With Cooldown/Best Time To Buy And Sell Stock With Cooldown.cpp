// Code to find the maximum profit you can achieve by completing as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the restriction: After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day) ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& prices, int i, bool canBuy) {
        if(i >= n)
            return 0;

        if(canBuy) {
            int buy  = solveWithoutMemo(prices, i + 1, false) - prices[i];
            int skip = solveWithoutMemo(prices, i + 1, true); 
            return max(buy, skip);
        }
        else {
            int sell = prices[i] + solveWithoutMemo(prices, i + 2, true);
            int skip = solveWithoutMemo(prices, i + 1, false); 
            return max(sell, skip);
        }
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& prices, int i, bool canBuy) {
        if(i >= n)
            return 0;

        if(dp[i][canBuy] != -1)
            return dp[i][canBuy];

        if(canBuy) {
            int buy  = solveWithMemo(dp, prices, i + 1, false) - prices[i];
            int skip = solveWithMemo(dp, prices, i + 1, true); 
            return dp[i][canBuy] = max(buy, skip);
        }
        else {
            int sell = prices[i] + solveWithMemo(dp, prices, i + 2, true);
            int skip = solveWithMemo(dp, prices, i + 1, false); 
            return dp[i][canBuy] = max(sell, skip);
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, prices, 0, true);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveWith2DTable(const vector<int>& prices) {
        vector<vector<int>> dp(n + 2, vector<int>(2, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = dp[i + 1][false] - prices[i];
                    int skip = dp[i + 1][true]; 
                    dp[i][canBuy] = max(buy, skip);
                }
                else {
                    int sell = prices[i] + dp[i + 2][true];
                    int skip = dp[i + 1][false]; 
                    dp[i][canBuy] = max(sell, skip);
                }
            }
        }

        return dp[0][true];
    }

    // O(N) & O(1)
    int solveWith1DTable(const vector<int>& prices) {
        vector<int> firstRow(2, 0), secondRow(2, 0), thirdRow(2, 0);

        for(int i = n - 1; i >= 0; --i) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = secondRow[false] - prices[i];
                    int skip = secondRow[true]; 
                    firstRow[canBuy] = max(buy, skip);
                }
                else {
                    int sell = prices[i] + thirdRow[true];
                    int skip = secondRow[false]; 
                    firstRow[canBuy] = max(sell, skip);
                }
            }
            thirdRow  = secondRow;
            secondRow = firstRow;
        }

        return firstRow[true];
    }

    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& prices) {
        int firstRow_0  = 0, firstRow_1  = 0;
        int secondRow_0 = 0, secondRow_1 = 0;
        int thirdRow_0  = 0, thirdRow_1  = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = secondRow_0 - prices[i];
                    int skip = secondRow_1; 
                    firstRow_1 = max(buy, skip);
                }
                else {
                    int sell = prices[i] + thirdRow_1;
                    int skip = secondRow_0; 
                    firstRow_0 = max(sell, skip);
                }
            }
            thirdRow_0  = secondRow_0;
            thirdRow_1  = secondRow_1;
            secondRow_0 = firstRow_0;
            secondRow_1 = firstRow_1;
        }

        return firstRow_1;
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        return solveWithoutTable(prices);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/
