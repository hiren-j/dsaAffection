// Code to find the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 109 + 7 ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ (REGARDING INTUITION BEHIND THE PROBLEM / MY PATTERN OBSERVATION BEHING THE SOLUTION):
    
    How I approached: To be honest, I haven't read the problem description, I just read the main task, It was to find number of ways and after that I saw the constraints, I got that its combinatorics + dp, then I wrote the first 10 values with their output, and observed the pattern.
    Here it is, as you could see the results of any bigger value of `n`, is always greater than results of lesser values of `n`. So I thought its possible that results of smaller values may help to create results for bigger values, and you could also figure it out from the increasing order of the results. 
    Any next result seems `some value add + double` of previous result, but still I've to figure out what value to add, I tried to add delta of results of (n-2 and n-1) but this was making the results wrong, then I tried to add the results of smaller `n`, 
    for that tried adding results of the `n` from beginning (n = 1, 2, 3, etc) one by one and got that adding the result of 3rd value by stepping back is helping creating the result for current `n`, hence I tried this to each `n` and its working out. 
    So more clearly, `adding result of n-3 to double of previous result is giving the result for current n`, so just coded it, and then did our memoization, bottom-up within 6-7 minutes, that's it! I've solved a lot of problems like this way before, Now If you liked this way of approaching then keep up with my DP series.
    n = 2 | 2
    n = 3 | 5
    n = 4 | 11
    n = 5 | 24
    n = 6 | 53
    n = 7 | 117
    n = 8 | 258
    n = 9 | 569
    n = 10 | 1255, 
    result of n = double of n-1th result + result of n-3 
    let the result is represented by dp array, so: 
    dp[n] = 2 * dp[n-1] + dp[n-3] 
*/

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class TopDown {
    const int MOD = 1e9+7;

    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n < 3)
            return (n < 2) ? 1 : 2;

        return (solveWithoutMemo(n-1) * 2 % MOD + solveWithoutMemo(n-3)) % MOD;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n < 3)
            return (n < 2) ? 1 : 2;

        if(dp[n] != -1)
            return dp[n];

        return dp[n] = (solveWithMemo(dp, n-1) * 2 % MOD + solveWithMemo(dp, n-3)) % MOD;
    }

public:
    int numTilings(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

    // O(1*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;

        for(int i = 4; i <= n; ++i) 
            dp[i] = (dp[i-1] * 2 % MOD + dp[i-3]) % MOD;

        return dp[n];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(int n) {
        int dp_i_3  = 1;
        int dp_i_2  = 2;
        int dp_i_1  = 5;
        int numWays = 5; // Storing result for n = 3, as the loop is not going to work for it

        for(int i = 4; i <= n; ++i) {
            numWays = (dp_i_1 * 2 % MOD + dp_i_3) % MOD;
            dp_i_3 = dp_i_2;
            dp_i_2 = dp_i_1;
            dp_i_1 = numWays;
        }

        return numWays;
    }

public:
    int numTilings(int n) {
        if(n < 3)
            return n;
        return solveWithoutTable(n);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Combinatorics | Dynamic Programming
Link  : https://leetcode.com/problems/domino-and-tromino-tiling/description/
