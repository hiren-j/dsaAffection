// Code to find the nth number of the tribonacci sequence ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(3^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n < 3)
            return (n == 0) ? 0 : 1;

        int prevNum1 = solveWithoutMemo(n - 1);
        int prevNum2 = solveWithoutMemo(n - 2);
        int prevNum3 = solveWithoutMemo(n - 3);

        return prevNum1 + prevNum2 + prevNum3;
    }

    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n) {
        if(n < 3)
            return (n == 0) ? 0 : 1;
        
        if(memory[n] != -1)
            return memory[n];

        int prevNum1 = solveWithMemo(memory, n - 1);
        int prevNum2 = solveWithMemo(memory, n - 2);
        int prevNum3 = solveWithMemo(memory, n - 3);

        return memory[n] = (prevNum1 + prevNum2 + prevNum3);
    }

public:
    // Method to find nth tribonacci number, using recursion with memoization - O(N) & O(N)
    int nthTribonacci(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(4*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 1;

        for(int i = 3; i <= n; ++i) {
            int prevNum1 = dp[i - 1];
            int prevNum2 = dp[i - 2];
            int prevNum3 = dp[i - 3];
            dp[i] = (prevNum1 + prevNum2 + prevNum3);
        }

        return dp[n];
    }   

    // O(4*N) & O(1)
    int solveWithoutTable(int n) {
        int dp_i_3 = 0;
        int dp_i_2 = 1;
        int dp_i_1 = 1;
        int dp_i = 1;

        for(int i = 3; i <= n; ++i) {
            int prevNum1 = dp_i_1;
            int prevNum2 = dp_i_2;
            int prevNum3 = dp_i_3;
            dp_i = (prevNum1 + prevNum2 + prevNum3);
            dp_i_3 = dp_i_2;
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
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
