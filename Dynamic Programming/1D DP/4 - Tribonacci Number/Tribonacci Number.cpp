// Code to find the nth number of the tribonacci sequence ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(3^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n < 3)
            return (n == 0) ? 0 : 1;

        int res1 = solveWithoutMemo(n - 1);
        int res2 = solveWithoutMemo(n - 2);
        int res3 = solveWithoutMemo(n - 3);

        return res1 + res2 + res3;
    }

    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n) {
        if(n < 3)
            return (n == 0) ? 0 : 1;

        if(memory[n] != -1)
            return memory[n];

        int res1 = solveWithMemo(memory, n - 1);
        int res2 = solveWithMemo(memory, n - 2);
        int res3 = solveWithMemo(memory, n - 3);

        return memory[n] = res1 + res2 + res3;
    }

public:
    int nthTribonacci(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(4*GN) & O(GN) : Where GN = given_n
    int solveWith1DTable(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for(int n = 3; n <= given_n; ++n) {
            int res1 = dp[n - 1];
            int res2 = dp[n - 2];
            int res3 = dp[n - 3];
            dp[n] = res1 + res2 + res3;
        }

        return dp[given_n];
    }

    // O(4*GN) & O(1) : Where GN = given_n
    int solveWithoutTable(int given_n) {
        int dp_n_3 = 0; 
        int dp_n_2 = 1; 
        int dp_n_1 = 1; 
        int dp_n   = 1; 

        for(int n = 3; n <= given_n; ++n) {
            int res1 = dp_n_1;
            int res2 = dp_n_2;
            int res3 = dp_n_3;
            dp_n   = res1 + res2 + res3;
            dp_n_3 = dp_n_2;            
            dp_n_2 = dp_n_1;            
            dp_n_1 = dp_n;            
        }

        return dp_n;
    }

public:
    int nthTribonacci(int n) {
        if(n < 3)
            return (n == 0) ? 0 : 1;
        return solveWithoutTable(n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Math | Memoization
Link  : https://leetcode.com/problems/N-th-tribonacci-number/description/
