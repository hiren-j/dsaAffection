// Code to find the minimum steps required to minimize n to 1 according to the following criteria: If n is divisible by 2 then you may reduce n to n/2. If n is divisible by 3 then you may reduce n to n/3. Otherwise, Decrement n by 1 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int solveWithMemo(vector<int>& dp, int n) {
        if(n == 1)
            return 0;
            
        if(dp[n] != -1)
            return dp[n];
            
        int minSteps = solveWithMemo(dp, n - 1);
        
        for(int divisor = 2; divisor <= 3; ++divisor)
            if(n % divisor == 0)
                minSteps = minSteps = min(minSteps, solveWithMemo(dp, n / divisor));

        return dp[n] = minSteps + 1;
    }
    
public:
    int minSteps(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};
// Note: In the previous approach, we're writing the same logic through redundant conditions so instead of doing that here I just generalized them into the loop

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    int minSteps(int given_n) {
        vector<int> dp(given_n + 1, -1);
        dp[1] = 0;
        
        for(int n = 2; n <= given_n; ++n) {
            int minSteps = dp[n - 1];
            
            for(int divisor = 2; divisor <= 3; ++divisor) {
                if(n % divisor == 0) {
                    minSteps = minSteps = min(minSteps, dp[n / divisor]);
                }
            }
    
            dp[n] = minSteps + 1;   
        }
        
        return dp[given_n];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/discuss/interview-question/538568/google-onsite-min-operations-to-reduce-number-to-1
        https://www.geeksforgeeks.org/problems/minimum-steps-to-minimize-n-as-per-given-condition0618/0
