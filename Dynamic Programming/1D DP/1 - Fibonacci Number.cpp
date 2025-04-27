// Code to find the nth number of the fibonacci sequence ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: In the first 9 problems of this 1D Dynamic Programming pattern, the focus is on developing intuitive bottom-up solutions, not just straightforward conversions from memoized code.
                            This approach is designed to help you grasp the principles of Dynamic Programming from the ground up.
                            Although this process might be time-consuming and sometimes frustrating, it is essential for building a strong foundation.
                            Don't hesitate to use a pen and paper as you work through these problems.
                            Even if the bottom-up solutions look like direct conversions, they are made with intuitive thinking to help you learn better.
                            Reminder: After these 9 problems, all remaining bottom-up solutions of the series will be direct conversions.
*/
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*   
    DON'T IGNORE MUST READ: For the Top-Down DP problems in the series, each problem will feature two solutions: `solveWithoutMemo` and `solveWithMemo`. 
                            You must start with `solveWithoutMemo`, which demonstrates the recursive solution without memoization (without DP) and which is expected to run into TLE (Time Limit Exceeded). 
                            After understanding the non-optimized approach, move to `solveWithMemo` for the memoized solution. Follow this order for all Top-Down DP solutions in the DP series.
*/
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n < 2)
            return n;

        int prevNum1 = solveWithoutMemo(n - 1);
        int prevNum2 = solveWithoutMemo(n - 2);

        return prevNum1 + prevNum2;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n < 2)
            return n;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[n] != -1) 
            return dp[n];

        int prevNum1 = solveWithMemo(dp, n - 1);
        int prevNum2 = solveWithMemo(dp, n - 2);

        // Store the result value to the memoization table and then return it
        return dp[n] = (prevNum1 + prevNum2); 
    }

public:
    int fib(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(N) & O(N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);

        // Initiailze the edge case
        dp[0] = 0;
        dp[1] = 1;

        for(int i = 2; i <= n; ++i) { 
            int prevNum1 = dp[i - 1];
            int prevNum2 = dp[i - 2];
            dp[i] = prevNum1 + prevNum2;
        }

        return dp[n]; 
    }

    // O(N) & O(1)
    int solveWithoutTable(int n) {
        int prevNum1 = 1, prevNum2 = 0;
        int currNum  = 0;

        for(int i = 2; i <= n; ++i) {
            currNum  = prevNum1 + prevNum2;
            prevNum2 = prevNum1;
            prevNum1 = currNum;
        }

        return currNum;
    }

public:
    int fib(int n) {
        if(n < 2)
            return n;
        return solveWith1DTable(n);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Maths | Dynamic Programming | Recursion | Memoization
Link  : https://leetcode.com/problems/fibonacci-number/
