// Code to find the minimum number of coins needed to acquire all the fruits. The fruit market has the following reward for each fruit: If you purchase the ith fruit at prices[i] coins, you can get any number of the next (i + 1) fruits for free. Note that even if you can take fruit j for free, you can still purchase it for prices[j] coins to receive its reward ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int solveWithoutMemo(vector<int>& prices, int index) {
        if(index >= n)
            return 0;

        int jumpLimit = index + 1;
        int minCoins  = solveWithoutMemo(prices, index + jumpLimit + 1);

        for(int jump = 1; (jump <= jumpLimit && index + jump <= n); ++jump) {
            int nextBuy = solveWithoutMemo(prices, index + jump);
            minCoins = min(minCoins, nextBuy);
        }
    
        return minCoins + prices[index];
    }

    int solveWithMemo(vector<int>& dp, vector<int>& prices, int index) {
        if(index >= n)
            return 0;

        if(dp[index] != -1)
            return dp[index];

        int jumpLimit = index + 1;
        int minCoins  = solveWithMemo(dp, prices, index + jumpLimit + 1);

        for(int jump = 1; (jump <= jumpLimit && index + jump <= n); ++jump) {
            int nextBuy = solveWithMemo(dp, prices, index + jump);
            minCoins = min(minCoins, nextBuy);
        }
    
        return dp[index] = minCoins + prices[index];
    }

public:
    int minimumCoins(vector<int>& prices) {
        n = prices.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, prices, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();

        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int index = n-1; index >= 0; --index) {
            int jumpLimit = index + 1;
            int nextIndex = index + jumpLimit + 1;
            int minCoins  = (nextIndex <= n) ? dp[nextIndex] : 0;

            for(int jump = 1; (jump <= jumpLimit && index + jump <= n); ++jump) {
                int nextBuy = dp[index + jump];
                minCoins = min(minCoins, nextBuy);
            }

            dp[index] = minCoins + prices[index];
        }

        return dp[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Queue | Heap (Priority Queue) | Monotonic Queue
Link  : https://leetcode.com/problems/minimum-number-of-coins-for-fruits/description/
