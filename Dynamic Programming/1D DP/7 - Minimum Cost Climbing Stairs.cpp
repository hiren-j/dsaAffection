// Code to find the minimum cost to reach the top of the floor ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int n;

    int solveWithoutMemo(vector<int>& cost, int step) {
        if(step >= n)
            return 0;
        
        int climb1Step = solveWithoutMemo(cost, step + 1);
        int climb2Step = solveWithoutMemo(cost, step + 2);

        return min(climb1Step, climb2Step) + cost[step];
    }

    int solveWithMemo(vector<int>& memory, vector<int>& cost, int step) {
        if(step >= n)
            return 0;

        if(memory[step] != -1)
            return memory[step];
        
        int climb1Step = solveWithMemo(memory, cost, step + 1);
        int climb2Step = solveWithMemo(memory, cost, step + 2);

        return memory[step] = min(climb1Step, climb2Step) + cost[step];
    }

public:
    int minCostClimbingStairs(vector<int>& cost) {
        n = cost.size();

        vector<int> memory1(n, -1), memory2(n, -1);
        
        int startFrom0 = solveWithMemo(memory1, cost, 0);
        int startFrom1 = solveWithMemo(memory2, cost, 1);

        return min(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int n;

    int solveWith1DTable(vector<int>& cost, int startPoint) {
        vector<int> dp(n + 2, -1);
        dp[n] = 0;
        dp[n + 1] = 0;

        for(int step = n-1; step >= startPoint; --step) {
            int climb1Step = dp[step + 1];
            int climb2Step = dp[step + 2];
            dp[step] = min(climb1Step, climb2Step) + cost[step];
        }

        return dp[startPoint];
    }

    int solveWithoutTable(vector<int>& cost, int startPoint) {
        int climb1Step = 0;
        int climb2Step = 0;
        int minCost;

        for(int step = n-1; step >= startPoint; --step) {
            minCost    = min(climb1Step, climb2Step) + cost[step];
            climb2Step = climb1Step;
            climb1Step = minCost;
        }

        return minCost;
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

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/min-cost-climbing-stairs/description/
