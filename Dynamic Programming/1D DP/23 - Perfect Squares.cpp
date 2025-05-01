// Code to find the least number of perfect square numbers that sums to N ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(sqrt(N) ^ N) & O(N)
    int solveWithoutMemo(int n) {
        if(n == 0)
            return 0;

        int minSquares = INT_MAX;

        for(int i = 1; i*i <= n; ++i) {
            int nextSquares = solveWithoutMemo(n - i*i);
            minSquares = min(minSquares, nextSquares + 1);
        }

        return minSquares;
    }

    // O(sqrt(N) * N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n == 0)
            return 0;

        if(dp[n] != -1)
            return dp[n];

        int minSquares = INT_MAX;

        for(int i = 1; i*i <= n; ++i) {
            int nextSquares = solveWithMemo(dp, n - i*i);
            minSquares = min(minSquares, nextSquares + 1);
        }

        return dp[n] = minSquares;
    }

public:
    int numSquares(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);  
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(sqrt(N) * N) & O(1*N) : Where N = given_n
    int numSquares(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 0;

        for(int n = 1; n <= given_n; ++n) {
            int minSquares = INT_MAX;

            for(int i = 1; i*i <= n; ++i) {
                int nextSquares = dp[n - i*i];
                minSquares = min(minSquares, nextSquares + 1);
            }

            dp[n] = minSquares;
        }
            
        return dp[given_n];      
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://leetcode.com/problems/perfect-squares/description/
