// Code to break the given n into the sum of k positive integers, where k >= 2, and maximize the product of those integers ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(N^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n <= 2)
            return 1;
        
        int maxProduct = 1;

        for(int num = 1; num < n; ++num) {
            int nextProduct = max(n - num, solveWithoutMemo(n - num));
            maxProduct = max(maxProduct, nextProduct * num);
        }

        return maxProduct;
    }

    // O(N*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n <= 2)
            return 1;

        if(dp[n] != -1)
            return dp[n];
        
        int maxProduct = 1;

        for(int num = 1; num < n; ++num) {
            int nextProduct = max(n - num, solveWithMemo(dp, n - num));
            maxProduct = max(maxProduct, nextProduct * num);
        }

        return dp[n] = maxProduct;
    }

public:
    int integerBreak(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(1*N) : Where N = given_n
    int integerBreak(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 1;

        for(int n = 3; n <= given_n; ++n) {
            int maxProduct = 1;

            for(int num = 1; num < n; ++num) {
                int nextProduct = max(n - num, dp[n - num]);
                maxProduct = max(maxProduct, nextProduct * num);
            }

            dp[n] = maxProduct;
        }

        return dp[given_n];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://leetcode.com/problems/integer-break/description/
