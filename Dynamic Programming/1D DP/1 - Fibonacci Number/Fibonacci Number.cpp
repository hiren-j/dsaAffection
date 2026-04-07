// Code to find the nth number of the fibonacci sequence ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// NOTE: The problem link and topic tags are provided at the end of the page.   
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n == 0)
            return 0;

        if(n == 1)
            return 1;

        int res1 = solveWithoutMemo(n - 1);
        int res2 = solveWithoutMemo(n - 2);

        return res1 + res2;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n == 0)
            return 0;

        if(n == 1)
            return 1;

        if(dp[n] != -1)
            return dp[n];

        int res1 = solveWithMemo(dp, n - 1);
        int res2 = solveWithMemo(dp, n - 2);

        return dp[n] = res1 + res2;
    }

public:
    int nthFibonacci(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    // O(3*GN) & O(1*GN) : Where GN = given_n
    int solveWith1DTable(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 0; 
        dp[1] = 1;

        for(int n = 2; n <= given_n; ++n) {
            int res1 = dp[n - 1];
            int res2 = dp[n - 2];
            dp[n] = res1 + res2;
        }

        return dp[given_n];
    }

    // O(3*GN) & O(1) : Where GN = given_n
    int solveWithoutTable(int given_n) {
        int dp_n_2 = 0; 
        int dp_n_1 = 1; 
        int dp_n   = 1; 

        for(int n = 2; n <= given_n; ++n) {
            int res1 = dp_n_1;
            int res2 = dp_n_2;
            dp_n   = res1 + res2;     
            dp_n_2 = dp_n_1;
            dp_n_1 = dp_n;
        }

        return dp_n;
    }

public:
    int nthFibonacci(int n) {
        if(n == 0)
            return 0;
        return solveWithoutTable(n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Maths | Dynamic Programming | Recursion | Memoization
Link  : https://leetcode.com/problems/fibonacci-number/
