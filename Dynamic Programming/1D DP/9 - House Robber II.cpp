// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& houses, int start, int end) {
        if(start > end)
            return 0;
        
        int robHouse = houses[start] + solveWithoutMemo(houses, start + 2, end);
        int skipRob  = solveWithoutMemo(houses, start + 1, end);

        return max(robHouse, skipRob);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& houses, int start, int end) {
        if(start > end)
            return 0;
        
        if(dp[start] != -1)
            return dp[start];

        int robHouse = houses[start] + solveWithMemo(dp, houses, start + 2, end);
        int skipRob  = solveWithMemo(dp, houses, start + 1, end);

        return dp[start] = max(robHouse, skipRob);
    }

public:
    int robMaxMoney(vector<int>& houses) {
        int n = houses.size();

        if(n == 1) 
            return houses[0];

        vector<int> dp1(n, -1), dp2(n, -1);

        int startFrom0 = solveWithMemo(dp1, houses, 0, n-2);
        int startFrom1 = solveWithMemo(dp2, houses, 1, n-1);

        return max(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(1*N) & O(1*N)
    int solveWith1DTable(vector<int>& houses, int start, int end) {
        vector<int> dp(n + 2, -1);
        dp[end + 1] = 0;
        dp[end + 2] = 0;

        for(int index = end; index >= start; --index) {
            int robHouse = houses[index] + dp[index + 2];
            int skipRob  = dp[index + 1];
            dp[index] = max(robHouse, skipRob);
        } 

        return dp[start];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(vector<int>& houses, int start, int end) {
        int dpIndex2 = 0;
        int dpIndex1 = 0;
        int maxMoney;

        for(int index = end; index >= start; --index) {
            int robHouse = houses[index] + dpIndex2;
            int skipRob  = dpIndex1;
            maxMoney = max(robHouse, skipRob);
            dpIndex2 = dpIndex1;
            dpIndex1 = maxMoney;
        } 

        return maxMoney;
    }

public:
    int robMaxMoney(vector<int>& houses) {
        n = houses.size();

        if(n == 1) 
            return houses[0];

        vector<int> dp1(n, -1), dp2(n, -1);

        int startFrom0 = solveWithoutTable(houses, 0, n-2);
        int startFrom1 = solveWithoutTable(houses, 1, n-1);

        return max(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/house-robber-ii/
