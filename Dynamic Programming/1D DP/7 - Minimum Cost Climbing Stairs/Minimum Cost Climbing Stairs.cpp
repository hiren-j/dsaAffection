// Code to find the minimum cost to reach the top of the floor ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& cost, int i) {
        if(i >= n)
            return 0;

        int climb1Step = solveWithoutMemo(cost, i + 1) + cost[i];
        int climb2Step = solveWithoutMemo(cost, i + 2) + cost[i];

        return min(climb1Step, climb2Step);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& cost, int i) {
        if(i >= n)
            return 0;

        if(dp[i] != -1)
            return dp[i];

        int climb1Step = solveWithMemo(dp, cost, i + 1) + cost[i];
        int climb2Step = solveWithMemo(dp, cost, i + 2) + cost[i];

        return dp[i] = min(climb1Step, climb2Step);
    }

public:
    // Method to find minimum cost to reach top, using recursion with memoziation - O(N) & O(N)
    int minCostClimbingStairs(vector<int>& cost) {
        n = cost.size();
        vector<int> dp1(n, -1), dp2(n, -1);
        int startFrom0 = solveWithMemo(dp1, cost, 0);
        int startFrom1 = solveWithMemo(dp2, cost, 1);
        return min(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveWith1DTable(const vector<int>& cost, int start) {
        vector<int> dp(n + 2, -1);
        dp[n + 1] = 0;
        dp[n] = 0;

        for(int i = n - 1; i >= start; --i) {
            int climb1Step = dp[i + 1] + cost[i];
            int climb2Step = dp[i + 2] + cost[i];
            dp[i] = min(climb1Step, climb2Step);
        }

        return dp[start];
    }

    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& cost, int start) {
        int dp_i_plus_2 = 0; // dp[i + 2] = dp[n - 1 + 2] = dp[n + 1]
        int dp_i_plus_1 = 0; // dp[i + 1] = dp[n - 1 + 1] = dp[n]
        int dp_i = -1;       // dp[i]

        for(int i = n - 1; i >= start; --i) {
            int climb1Step = dp_i_plus_1 + cost[i];
            int climb2Step = dp_i_plus_2 + cost[i];
            dp_i = min(climb1Step, climb2Step);
            dp_i_plus_2 = dp_i_plus_1;
            dp_i_plus_1 = dp_i;
        }

        return dp_i;
    }

public:
    int minCostClimbingStairs(vector<int>& cost) {
        n = cost.size();
        int startFrom0 = solveWithoutTable(cost, 0);
        int startFrom1 = solveWithoutTable(cost, 1);
        return min(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpOnePass {
public:
    // O(N) & O(N)
    int minCostClimbingStairs(vector<int>& cost) {
        const int n = cost.size();

        vector<int> dp(n + 2, -1);
        dp[n + 1] = 0;
        dp[n] = 0;

        for(int i = n - 1; i >= 0; --i) {
            int climb1Step = dp[i + 1] + cost[i];
            int climb2Step = dp[i + 2] + cost[i];
            dp[i] = min(climb1Step, climb2Step);
        }

        int startFrom0 = dp[0];
        int startFrom1 = dp[1];
        return min(startFrom0, startFrom1);
    }
};
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/min-cost-climbing-stairs/description/
