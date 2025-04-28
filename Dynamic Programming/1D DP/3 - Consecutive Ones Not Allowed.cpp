// Code to count all the possible distinct binary strings of length n such that there are no consecutive 1’s ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    NOTE: The solution of this problem is totally same as the first one (Fibonacci Number). The edge case in the only change.
*/
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n < 3)
            return n;

        int prevNum1 = solveWithoutMemo(n - 1);
        int prevNum2 = solveWithoutMemo(n - 2);

        return prevNum1 + prevNum2;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n < 3)
            return n;

        if(dp[n] != -1) 
            return dp[n];

        int prevNum1 = solveWithMemo(dp, n - 1);
        int prevNum2 = solveWithMemo(dp, n - 2);

        return dp[n] = (prevNum1 + prevNum2); 
    }

public:
    int numDistinctBinaryStrs(int n) {
        vector<int> dp(n + 2, -1);
        return solveWithMemo(dp, n + 1); // The main task is to find the n + 1th number of the fibonacci sequence
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(1*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 2, -1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        
        for(int i = 3; i <= n+1; ++i) {
            int prevNum1 = dp[i - 1];
            int prevNum2 = dp[i - 2];
            dp[i] = (prevNum1 + prevNum2); 
        }
        
        return dp[n + 1];
    }
    
    // O(1*N) & O(1)
    int solveWithoutTable(int n) {
        int prevNum1 = 2;
        int prevNum2 = 1;
        int currNum  = (n == 1) ? 2 : 3; // Handle when n = 1 and n = 2, as the loop is not going to work for them

        for(int i = 3; i <= n+1; ++i) {
            currNum  = prevNum1 + prevNum2;
            prevNum2 = prevNum1;
            prevNum1 = currNum;
        }

        return currNum;
    }
    
public:
    int numDistinctBinaryStrs(int n) {
        return solveWithoutTable(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1
