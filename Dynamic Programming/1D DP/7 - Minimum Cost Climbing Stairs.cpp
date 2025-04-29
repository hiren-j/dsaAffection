// Code to find the minimum cost to reach the top of the floor ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N) : Where N = total steps
    int solveWithoutMemo(vector<int>& cost, int step) {
        if(step >= n)
            return 0;
        
        int climb1Step = solveWithoutMemo(cost, step + 1);
        int climb2Step = solveWithoutMemo(cost, step + 2);

        return cost[step] + min(climb1Step, climb2Step);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, vector<int>& cost, int step) {
        if(step >= n)
            return 0;

        if(memory[step] != -1)
            return memory[step];
        
        int climb1Step = solveWithMemo(memory, cost, step + 1);
        int climb2Step = solveWithMemo(memory, cost, step + 2);

        return memory[step] = cost[step] + min(climb1Step, climb2Step);
    }

public:
    int minCostToReachTop(vector<int>& cost) {
        n = cost.size();

        vector<int> memory1(n, -1), memory2(n, -1);
        
        int startFrom0 = solveWithMemo(memory1, cost, 0);
        int startFrom1 = solveWithMemo(memory2, cost, 1);

        return min(startFrom0, startFrom1);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(1*N) & O(1*N)
    int solveWith1DTable(vector<int>& cost, int startPoint) {
        vector<int> dp(n + 2, -1);
        dp[n] = dp[n + 1] = 0;

        for(int step = n-1; step >= startPoint; --step) {
            int climb1Step = dp[step + 1];
            int climb2Step = dp[step + 2];
            dp[step] = cost[step] + min(climb1Step, climb2Step);
        }

        return dp[startPoint];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(vector<int>& cost, int startPoint) {
        int climb1Step = 0;
        int climb2Step = 0;
        int minCost;

        for(int step = n-1; step >= startPoint; --step) {
            minCost    = cost[step] + min(climb1Step, climb2Step);
            climb2Step = climb1Step;
            climb1Step = minCost;
        }

        return minCost;
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
