// Code to find the maximum profit you can achieve by completing at most two transactions ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown  {
    int dp[100001][2][3];
    int n;

    // O(N) & O(N)
    int solveWithMemo(const vector<int>& prices, int i, bool canBuy, int k) {
        if(i == n || k == 0)
            return 0;

        if(dp[i][canBuy][k] != -1)
            return dp[i][canBuy][k];

        if(canBuy) {
            int buy  = solveWithMemo(prices, i + 1, false, k) - prices[i];
            int skip = solveWithMemo(prices, i + 1, true, k); 
            return dp[i][canBuy][k] = max(buy, skip);
        }
        else {
            int sell = prices[i] + solveWithMemo(prices, i + 1, true, k - 1);
            int skip = solveWithMemo(prices, i + 1, false, k); 
            return dp[i][canBuy][k] = max(sell, skip);
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(prices, 0, true, 2);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveWith3DTable(const vector<int>& prices) {
        int dp[100001][2][3];
        memset(dp, 0, sizeof(dp));

        for(int i = n - 1; i >= 0; --i) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                for(int k = 1; k <= 2; ++k) {
                    if(canBuy) {
                        int buy  = dp[i + 1][false][k] - prices[i];
                        int skip = dp[i + 1][true][k]; 
                        dp[i][canBuy][k] = max(buy, skip);
                    }
                    else {
                        int sell = prices[i] + dp[i + 1][true][k - 1];
                        int skip = dp[i + 1][false][k]; 
                        dp[i][canBuy][k] = max(sell, skip);
                    }
                }
            }
        }

        return dp[0][true][2];
    }

    // O(N) & O(1)
    int solveWith2DTable(const vector<int>& prices) {
        int next[2][3], curr[2][3];
        memset(next, 0, sizeof(next));
        memset(curr, 0, sizeof(curr));

        for(int i = n - 1; i >= 0; --i) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                for(int k = 1; k <= 2; ++k) {
                    if(canBuy) {
                        int buy  = next[false][k] - prices[i];
                        int skip = next[true][k]; 
                        curr[canBuy][k] = max(buy, skip);
                    }
                    else {
                        int sell = prices[i] + next[true][k - 1];
                        int skip = next[false][k]; 
                        curr[canBuy][k] = max(sell, skip);
                    }
                }
            }
            swap(next, curr);
        }

        return next[true][2];
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        return solveWith2DTable(prices);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/
