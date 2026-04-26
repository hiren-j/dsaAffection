// Code to find the count of all `n` digit numbers whose sum of digits is `sum`. Leading 0’s are not counted as digits ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(10^N) & O(N)
    int solveWithoutMemo(int n, int len, int sum) {
        if(len == n)
            return (sum == 0); 
                    
        int count = 0;
        
        for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && digit <= sum); ++digit)
            count = (count + solveWithoutMemo(n, len + 1, sum - digit)) % MOD;
         
        return count;
    }
    
    // O(N*S) & O(N*S) : Where S = sum
    int solveWithMemo(vector<vector<int>>& dp, int n, int len, int sum) {
        if(len == n)
            return (sum == 0); 
            
        if(dp[len][sum] != -1)
            return dp[len][sum];
            
        int count = 0;
        
        for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && digit <= sum); ++digit)
            count = (count + solveWithMemo(dp, n, len + 1, sum - digit)) % MOD;
         
        return dp[len][sum] = count;
    }
    
public:
    int countWays(int n, int sum) {
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        int count = solveWithMemo(dp, n, 0, sum); 
        return (count == 0) ? -1 : count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
public:
    // #1 Method to count all n length numbers whose sum of digits equals to sum, using 2D tabulation - O(N*S) & O(N*S)
    long countWays_V1(int n, int sum) {
        vector<vector<long>> dp(n + 1, vector<long>(sum + 1, 0));
        dp[n][0] = 1; // Initialize the edge case
        
        for(int len = n-1; len >= 0; --len) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                long count = 0;
                for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && currSum - digit >= 0); ++digit) {
                    count = (count + dp[len + 1][currSum - digit]) % MOD;
                }
                dp[len][currSum] = count;
            }
        }

        long count = dp[0][sum]; 
        return (count == 0) ? -1 : count;
    }

    // #2 Method to count all n length numbers whose sum of digits equals to sum, using 1D tabulation - O(N*S) & O(S)
    long countWays_V2(int n, int sum) {
        vector<long> nextRow(sum + 1, 0), idealRow(sum + 1, 0);
        nextRow[0] = 1; // Initialize the edge case
        
        for(int len = n-1; len >= 0; --len) {
            for(int currSum = 0; currSum <= sum; ++currSum) {
                long count = 0;
                for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && currSum - digit >= 0); ++digit) {
                    count = (count + nextRow[currSum - digit]) % MOD;
                }
                idealRow[currSum] = count;
            }
            nextRow = idealRow;
        }
        
        long count = nextRow[sum]; 
        return (count == 0) ? -1 : count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/count-of-n-digit-numbers-whose-sum-of-digits-equals-to-given-sum0733/1
