// Code to count the number of ways to construct sum n by throwing a dice one or more times. Each throw produces an outcome between 1 and 6 ~ coded by Hiren 

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(6^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n == 0)
            return 1;
        
        int count = 0;
 
        for(int outcome = 1; (outcome <= 6 && n - outcome >= 0); ++outcome) 
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
 
        for(int outcome = 1; (outcome <= 6 && n - outcome >= 0); ++outcome) 
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
    const int MOD = 1e9 + 7;
 
    // O(N*6) & O(1*N) : Where N = given_n
    int solveWith1DTable(int n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 1;
 
        for(int n = 1; n <= given_n; ++n) {
            int count = 0;

            for(int outcome = 1; (outcome <= 6 && n - outcome >= 0); ++outcome) {
                count = (count + dp[n - outcome]) % MOD;
            }
 
            dp[n] = count;
        }
 
        return dp[given_n];
    }
    
    // O(N*6) & O(1) : Where N = given_n
    int solveWithoutTable(int given_n) {
        int dp_n_1 = 1; // dp[n - 1]
        int dp_n_2 = 0; // dp[n - 2]
        int dp_n_3 = 0; // dp[n - 3]
        int dp_n_4 = 0; // dp[n - 4]
        int dp_n_5 = 0; // dp[n - 5]
        int dp_n_6 = 0; // dp[n - 6]
        int dp_n   = 1; // dp[n]

        for(int n = 1; n <= given_n; ++n) {
            int count = 0;
            count = (count + dp_n_1) % MOD;
            count = (count + dp_n_2) % MOD;
            count = (count + dp_n_3) % MOD;
            count = (count + dp_n_4) % MOD;
            count = (count + dp_n_5) % MOD;
            count = (count + dp_n_6) % MOD;
            dp_n  = count;

            dp_n_6 = dp_n_5;
            dp_n_5 = dp_n_4;
            dp_n_4 = dp_n_3;
            dp_n_3 = dp_n_2;
            dp_n_2 = dp_n_1;
            dp_n_1 = dp_n;
        }

        return dp_n;
    }

public:
    int numWays(int n) {
        return solveWith1DTable(n);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Combinatorics
Link  : https://cses.fi/problemset/task/1633
