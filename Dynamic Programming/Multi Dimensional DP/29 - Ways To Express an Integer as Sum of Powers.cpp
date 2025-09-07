// Code to find the number of ways n can be expressed as the sum of the xth power of unique positive integers ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T FORGET, REGARDING INTUITION BEHIND THE PRECOMPUTATION OF POWERS:
        : xthPower[i] represents pow(i, x) where i <= n.
        : Brute forcely we could use pow(i, x) but this will lead to TLE, due to log(x) more increament in time.
        : So It would be beneficial to precomute the xth power of every possible number (i <= n).
*/
    
-----------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    vector<int> xthPower;

    void precomputeXthPower(int n, int x) {
        xthPower.resize(n + 1);

        for(int i = 1; i <= n; ++i) {
            xthPower[i] = (long long)pow(i, x);
        }
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(int n, int start, int x) {
        if(n == 0)
            return 1;

        int count = 0;

        for(int i = start; (i <= n && xthPower[i] <= n); ++i) {
            count = (count + solveWithoutMemo(n - xthPower[i], i + 1, x)) % MOD;
        }

        return count;
    }

    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, int n, int start, int x) {
        if(n == 0)
            return 1;

        if(dp[n][start] != -1)
            return dp[n][start];

        int count = 0;

        for(int i = start; (i <= n && xthPower[i] <= n); ++i) {
            count = (count + solveWithMemo(dp, n - xthPower[i], i + 1, x)) % MOD;
        }

        return dp[n][start] = count;
    }

public:
    // Method to find number of ways, using recursion with memoization - O(N^3) & O(N^2)
    int numberOfWays(int n, int x) {
        precomputeXthPower(n, x);
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
        return solveWithMemo(dp, n, 1, x);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    vector<int> xthPower;

    void precomputeXthPower(int n, int x) {
        xthPower.resize(n + 1);

        for(int i = 1; i <= n; ++i) {
            xthPower[i] = (long long)pow(i, x);
        }
    }

    // O(N^3) & O(N^2)
    int solveWith2DTable(int n, int x) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 2, 0));

        for(int start = 0; start <= n + 1; ++start)
            dp[0][start] = 1;

        for(int num = 1; num <= n; ++num) {
            for(int start = n; start >= 1; --start) {
                int count = 0;

                for(int i = start; (i <= num && xthPower[i] <= num); ++i) {
                    int idx = num - xthPower[i];
                    if(idx >= 0 && idx <= n) {
                        count = (count + dp[idx][i + 1]) % MOD;
                    }
                }

                dp[num][start] = count;
            }
        }

        return dp[n][1];
    }

public:
    int numberOfWays(int n, int x) {
        precomputeXthPower(n, x);
        return solveWith2DTable(n, x);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Biweekly Contest 109
Link  : https://leetcode.com/problems/ways-to-express-an-integer-as-sum-of-powers/description/
