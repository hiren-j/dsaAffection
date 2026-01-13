// Code to find the number of ways n can be expressed as the sum of the xth power of unique positive integers ~ coded by vHiren
    
-----------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    vector<long long> myPower;

    // O(NLogX) Time
    void precomputePowerExponentX(int n, int x) {
        myPower.resize(n + 1);

        for(int v = 1; v <= n; ++v) {
            myPower[v] = pow(v, x);
        }
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(int n, int x, int start) {
        if(n == 0)
            return 1;
        
        int count = 0;

        for(int v = start; (v <= n && myPower[v] <= n); ++v) {
            int next_n    = n - myPower[v];
            int nextCount = solveWithoutMemo(next_n, x, v + 1);
            count = (count + nextCount) % MOD;
        }

        return count;
    }

    // O(N^3) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, int n, int x, int start) {
        if(n == 0)
            return 1;

        if(dp[n][start] != -1)
            return dp[n][start];
        
        int count = 0;

        for(int v = start; (v <= n && myPower[v] <= n); ++v) {
            int next_n    = n - myPower[v];
            int nextCount = solveWithMemo(dp, next_n, x, v + 1);
            count = (count + nextCount) % MOD;
        }

        return dp[n][start] = count;
    }

public:
    int numberOfWays(int n, int x) {
        precomputePowerExponentX(n, x);
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return solveWithMemo(dp, n, x, 1);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    vector<long long> myPower;

    // O(NLogX) Time
    void precomputePowerExponentX(int n, int x) {
        myPower.resize(n + 1);

        for(int v = 1; v <= n; ++v) {
            myPower[v] = pow(v, x);
        }
    }

    // O(N^3) & O(N^2) : Where N = given_n
    int solveBy2DTable(int given_n, int x) {
        vector<vector<int>> dp(given_n + 1, vector<int>(given_n + 2, -1));

        for(int start = 0; start <= given_n + 1; ++start)
            dp[0][start] = 1;

        for(int n = 1; n <= given_n; ++n) {
            for(int start = given_n; start >= 1; --start) {
                int count = 0;

                for(int v = start; (v <= n && myPower[v] <= n); ++v) {
                    int next_n    = n - myPower[v];
                    int nextCount = dp[next_n][v + 1];
                    count = (count + nextCount) % MOD;
                }

                dp[n][start] = count;
            }
        } 

        return dp[given_n][1];
    }

public:
    int numberOfWays(int n, int x) {
        precomputePowerExponentX(n, x);
        return solveBy2DTable(n, x);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Biweekly Contest 109
Link  : https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/description/
