// Code to find the total number of distinct ways from which you can climb to the top ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n <= 1)
            return 1; // Here, We have 1 way to reach point 0 from point n

        int jump1StepDown = solveWithoutMemo(n - 1);
        int jump2StepDown = solveWithoutMemo(n - 2);

        return jump1StepDown + jump2StepDown;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n) {
        if(n <= 1)
            return 1; // Here, We have 1 way to reach point 0 from point n

        if(memory[n] != -1)
            return memory[n];

        int jump1StepDown = solveWithMemo(memory, n - 1);
        int jump2StepDown = solveWithMemo(memory, n - 2);

        return memory[n] = jump1StepDown + jump2StepDown;
    }

public:
    int numWaysToReachTop(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(1*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);
        dp[0] = 1;
        dp[1] = 1;

        for(int i = 2; i <= n; ++i) {
            int jump1StepDown = dp[i - 1];
            int jump2StepDown = dp[i - 2];
            dp[i] = jump1StepDown + jump2StepDown;
        }

        return dp[n];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(int n) {
        int dp_i_2 = 1;
        int dp_i_1 = 1;
        int dp_i = 1; // For when n = 1, because loop won't work for it

        for(int i = 2; i <= n; ++i) {
            int jump1StepDown = dp_i_1;
            int jump2StepDown = dp_i_2;
            dp_i = jump1StepDown + jump2StepDown;
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }

public:
    int numWaysToReachTop(int n) {
        return solveWithoutTable(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Memoization
Link  : https://leetcode.com/problems/climbing-stairs/description/
