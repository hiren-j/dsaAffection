// Code to find the maximum amount of money that you can rob tonight without alerting the police ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int solveWithoutMemo(const vector<int>& houses, int start, const int end) {
        if(start > end)
            return 0;

        int robHouse  = houses[start] + solveWithoutMemo(houses, start + 2, end);
        int skipHouse = solveWithoutMemo(houses, start + 1, end);
        
        return max(robHouse, skipHouse);
    }

    int solveWithMemo(vector<int>& dp, const vector<int>& houses, int start, const int end) {
        if(start > end)
            return 0;

        if(dp[start] != -1)
            return dp[start];

        int robHouse  = houses[start] + solveWithMemo(dp, houses, start + 2, end);
        int skipHouse = solveWithMemo(dp, houses, start + 1, end);
        
        return dp[start] = max(robHouse, skipHouse);
    }

    int solveWith1DTable(const vector<int>& houses, int start, const int end) {
        vector<int> dp(end + 3, -1);
        dp[end + 1] = 0;
        dp[end + 2] = 0;

        for(int idx = end; idx >= start; --idx) {
            int robHouse  = houses[idx] + dp[idx + 2];
            int skipHouse = dp[idx + 1];
            dp[idx] = max(robHouse, skipHouse);
        }

        return dp[start];
    }

    int solveWithoutTable(const vector<int>& houses, int start, const int end) {
        int dp_idx_2 = 0;
        int dp_idx_1 = 0;
        int dp_idx   = 0;

        for(int idx = end; idx >= start; --idx) {
            int robHouse  = houses[idx] + dp_idx_2;
            int skipHouse = dp_idx_1;
            dp_idx   = max(robHouse, skipHouse);
            dp_idx_2 = dp_idx_1;
            dp_idx_1 = dp_idx;
        }

        return dp_idx;
    }

public:
    int robMaxMoney(vector<int>& houses) {
        const int n = houses.size();
        if(n == 1) return houses[0];
        int startFrom0 = solveWith1DTable(houses, 0, n - 2);
        int startFrom1 = solveWith1DTable(houses, 1, n - 1);
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
        int dpIndex1 = 0;
        int dpIndex2 = 0;
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
