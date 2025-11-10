// Code to find the minimum cost to reach the top of the floor ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& cost, int idx) {
        if(idx >= n)
            return 0; // If no steps left

        int climb1Step = solveWithoutMemo(cost, idx + 1);
        int climb2Step = solveWithoutMemo(cost, idx + 2);

        return cost[idx] + min(climb1Step, climb2Step);
    }    
    
    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& cost, int idx) {
        if(idx >= n)
            return 0; // If no steps left

        if(dp[idx] != -1)
            return dp[idx];

        int climb1Step = solveWithMemo(dp, cost, idx + 1);
        int climb2Step = solveWithMemo(dp, cost, idx + 2);

        return dp[idx] = cost[idx] + min(climb1Step, climb2Step);
    }    

public:
    // Method to find minimum cost to reach top, using recursion with memoization - O(N) & O(N) 
    int minCostToReachTop(vector<int>& cost) {
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

    // O(1*N) & O(1*N)
    int solveWith1DTable(const vector<int>& cost, int start) {
        vector<int> dp(n + 2, -1);
        dp[n] = 0;
        dp[n + 1] = 0;

        for(int idx = n - 1; idx >= start; --idx) {
            int climb1Step = dp[idx + 1];
            int climb2Step = dp[idx + 2];
            dp[idx] = cost[idx] + min(climb1Step, climb2Step);
        }

        return dp[start];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(const vector<int>& cost, int start) {
        int dp_idx_1 = 0;
        int dp_idx_2 = 0;
        int dp_idx   = 0;

        for(int idx = n - 1; idx >= start; --idx) {
            int climb1Step = dp_idx_1;
            int climb2Step = dp_idx_2;
            dp_idx = cost[idx] + min(climb1Step, climb2Step);
            dp_idx_2 = dp_idx_1;
            dp_idx_1 = dp_idx;
        }

        return dp_idx;
    }

public:
    int minCostToReachTop(vector<int>& cost) {
        n = cost.size();
        int startFrom0 = solveWithoutTable(cost, 0);
        int startFrom1 = solveWithoutTable(cost, 1);
        return min(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/min-cost-climbing-stairs/description/
