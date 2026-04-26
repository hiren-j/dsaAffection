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
    
    // O(N*GS) & O(N*GS) : Where GS = givenSum
    int solveBy2DTable(int n, int givenSum) {
        vector<vector<int>> dp(n + 1, vector<int>(givenSum + 1, -1));
        
        for(int sum = 0; sum <= givenSum; ++sum)
            dp[n][sum] = (sum == 0);
        
        for(int len = n - 1; len >= 0; --len) {
            for(int sum = 0; sum <= givenSum; ++sum) {
                int count = 0;
                
                for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && digit <= sum); ++digit) {
                    count = (count + dp[len + 1][sum - digit]) % MOD;
                }
                 
                dp[len][sum] = count;
            }
        }
        

        int count = dp[0][givenSum]; 
        return (count == 0) ? -1 : count;
    }
    
    // O(N*GS) & O(GS) : Where GS = givenSum
    int solveBy1DTable(int n, int givenSum) {
        vector<int> nextRow(givenSum + 1, -1); 
        
        for(int sum = 0; sum <= givenSum; ++sum)
            nextRow[sum] = (sum == 0);
        
        for(int len = n - 1; len >= 0; --len) {
            vector<int> currRow(givenSum + 1, -1); 
            
            for(int sum = 0; sum <= givenSum; ++sum) {
                int count = 0;
                
                for(int digit = (len == 0 ? 1 : 0); (digit <= 9 && digit <= sum); ++digit) {
                    count = (count + nextRow[sum - digit]) % MOD;
                }
                 
                currRow[sum] = count;
            }
            
            swap(nextRow, currRow);
        }
        

        int count = nextRow[givenSum]; 
        return (count == 0) ? -1 : count;
    }
    
public:
    int countWays(int n, int sum) {
        return solveBy1DTable(n, sum);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/count-of-n-digit-numbers-whose-sum-of-digits-equals-to-given-sum0733/1
