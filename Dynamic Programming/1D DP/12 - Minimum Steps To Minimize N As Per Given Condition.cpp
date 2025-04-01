// Code to find the minimum steps required to minimize n to 1 according to the following criteria: If n is divisible by 2 then you may reduce n to n/2. If n is divisible by 3 then you may reduce n to n/3. Otherwise, Decrement n by 1 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the minimum steps required to reduce n to 1, using recursion with memoization - O(N) & O(N)
    int minStepsToMakeOne(int n) {
	vector<int> dp(n + 1, -1);
	return solveWithMemo(dp, n);
    } 
	
private:
    // O(2*N) & O(N+N)
    int solveWithMemo(vector<int>& dp, int n) {
        // Edge case: If n becomes 1 then no more operations are required
        if(n == 1)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(dp[n] != -1)
            return dp[n];
        
        // Count the total steps required to reduce n to 1 using decreament operation
        int minSteps = solveWithMemo(dp, n - 1); 
        
        // If n is divisible by 2 then you may reduce n to n/2. Make sure to update the result by the minimum value
        if(n % 2 == 0) 
            minSteps = min(minSteps, solveWithMemo(dp, n / 2));
            
        // If n is divisible by 3 then you may reduce n to n/3. Make sure to update the result by the minimum value
        if(n % 3 == 0) 
            minSteps = min(minSteps, solveWithMemo(dp, n / 3));
        
        // Store the result value to the memoization table and then return it
        return dp[n] = 1 + minSteps;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        // Edge case: If n becomes 1 then no more operations are required
        if(n == 1)
            return 0;
        
        // Count the total steps required to reduce n to 1 using decreament operation
        int minSteps = solveWithoutMemo(n - 1); 
        
        // If n is divisible by 2 then reduce n to n/2. Make sure to update the result by the minimum value
        if(n % 2 == 0) 
            minSteps = min(minSteps, solveWithoutMemo(n / 2));

        // If n is divisible by 3 then reduce n to n/3. Make sure to update the result by the minimum value
        if(n % 3 == 0) 
            minSteps = min(minSteps, solveWithoutMemo(n / 3));
        
        // Return the result value
        return 1 + minSteps;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum steps required to reduce n to 1, using 1D tabulation - O(N) & O(N)
    int minStepsToMakeOne(int n) {
        // 1D DP table: dp[i] represents the minimum steps required to reduce 'i' to 1
	vector<int> dp(n + 1, -1);

        // Initialize the edge case
	dp[1] = 0;     

        // Fill the rest of the table
	for(int num = 2; num <= n; ++num) {
            int minSteps = dp[num - 1];
                    
            if(num % 2 == 0) 
                minSteps = min(minSteps, dp[num / 2]);

            if(num % 3 == 0) 
                minSteps = min(minSteps, dp[num / 3]);
            
            dp[num] = 1 + minSteps;
	}

        // Return the result value
	return dp[n];
    } 
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/discuss/interview-question/538568/google-onsite-min-operations-to-reduce-number-to-1
        https://www.geeksforgeeks.org/problems/minimum-steps-to-minimize-n-as-per-given-condition0618/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
