// Code to find the total number of distinct ways from which you can climb to the top ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n <= 0)
            return (n == 0);

        int climb1Step = solveWithMemo(n - 1);
        int climb2Step = solveWithMemo(n - 2);

        return climb1Step + climb2Step;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n) {
        if(n <= 0)
            return (n == 0);

        if(memory[n] != -1)
            return memory[n];

        int climb1Step = solveWithMemo(memory, n - 1);
        int climb2Step = solveWithMemo(memory, n - 2);

        return memory[n] = (climb1Step + climb2Step);
    }

public:
    int numWaysToReachTop(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithoutTable(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(1*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);
        dp[0] = 1;

        for(int i = 1; i <= n; ++i) {
            int climb1Step = dp[i - 1];
            int climb2Step = (i - 2 >= 0) ? dp[i - 2] : 0;
            dp[i] = climb1Step + climb2Step;
        }
        
        return dp[n];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(int n) {
        int climb1Step = 1;
        int climb2Step = 0;
        int numWays    = 0;

        for(int i = 1; i <= n; ++i) {
            numWays    = climb1Step + climb2Step;
            climb2Step = climb1Step;
            climb1Step = numWays;
        }
        
        return numWays;
    }

public:
    int numWaysToReachTop(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithoutTable(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Memoization
Link  : https://leetcode.com/problems/climbing-stairs/description/
