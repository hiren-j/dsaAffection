// Code to count the number of ways to construct sum n by throwing a dice one or more times. Each throw produces an outcome between 1 and 6 ~ coded by Hiren 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;

    // O(6^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n == 0)
            return 1;
        
        int count = 0;
 
        for(int outcome = 1; (outcome <= 6 && outcome <= n); ++outcome) 
            count = (count + solveWithoutMemo(n - outcome)) % MOD;
 
        return count;
    }
 
    // O(6*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n == 0)
            return 1;
 
        if(dp[n] != -1)
            return dp[n];    
    
        int count = 0;
 
        for(int outcome = 1; (outcome <= 6 && outcome <= n); ++outcome) 
            count = (count + solveWithMemo(dp, n - outcome)) % MOD;
 
        return dp[n] = count;
    }
 
public:
    int numWays(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
 
public:
    // O(N*6) & O(1*N) : Where N = given_n
    int numWays(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 1;
 
        for(int n = 1; n <= given_n; ++n) {
            int count = 0;

            for(int outcome = 1; (outcome <= 6 && outcome <= n); ++outcome) {
                count = (count + dp[n - outcome]) % MOD;
            }
 
            dp[n] = count;
        }
 
        return dp[given_n];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Combinatorics
Link  : https://cses.fi/problemset/task/1633
