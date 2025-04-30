// Code to find the minimum number of coins needed to acquire all the fruits. The fruit market has the following reward for each fruit: If you purchase the ith fruit at prices[i] coins, you can get any number of the next (i + 1) fruits for free. Note that even if you can take fruit j for free, you can still purchase it for prices[j] coins to receive its reward ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2 * N^N) & O(N)
    int solveWithoutMemo(vector<int>& prices, int index) {
        if(index >= n)
            return 0;

        int minCoins  = INT_MAX;
        int jumpLimit = index + 1;

        for(int jump = 1; (jump <= jumpLimit && index + jump <= n); ++jump) {
            int nextBuy   = solveWithoutMemo(prices, index + jump);     // Consider purchasing the next fruit, hence move to that start point
            int nextFree  = solveWithoutMemo(prices, index + jump + 1); // Consider the next fruit as free, hence skip that start point
            int currCoins = prices[index] + min(nextBuy, nextFree);
            minCoins = min(minCoins, currCoins);
        }
    
        return minCoins;
    }

    // O(2*N*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& prices, int index) {
        if(index >= n)
            return 0;

        if(dp[index] != -1)
            return dp[index];

        int minCoins  = INT_MAX;
        int jumpLimit = index + 1;

        for(int jump = 1; (jump <= jumpLimit && index + jump <= n); ++jump) {
            int nextBuy   = solveWithMemo(dp, prices, index + jump);     // Consider purchasing the next fruit, hence move to that start point
            int nextFree  = solveWithMemo(dp, prices, index + jump + 1); // Consider the next fruit as free, hence skip that start point
            int currCoins = prices[index] + min(nextBuy, nextFree);
            minCoins = min(minCoins, currCoins);
        }
    
        return dp[index] = minCoins;
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
    // O(N*N) & O(1*N)
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();

        vector<int> dp(n + 2, -1);
        dp[n] = 0;
        dp[n + 1] = 0;

        for(int index = n-1; index >= 0; --index) {
            int minCoins  = INT_MAX;
            int jumpLimit = index + 1;

            for(int jump = 1; (jump <= jumpLimit && index + jump <= n); ++jump) {
                int nextBuy   = dp[index + jump];
                int nextFree  = dp[index + jump + 1];
                int currCoins = prices[index] + min(nextBuy, nextFree);
                minCoins = min(minCoins, currCoins);
            }

            dp[index] = minCoins;
        }
        
        return dp[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Queue | Heap (Priority Queue) | Monotonic Queue
Link  : https://leetcode.com/problems/minimum-number-of-coins-for-fruits/description/
