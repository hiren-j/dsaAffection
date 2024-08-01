// Code to break the given n into the sum of K positive integers, where K >= 2, and maximize the product of those integers ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the maximum product you can get, using recursion with memoization - O(N*N) & O(N)
    int integerBreak(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(n, memory);
    }

private:
    // O(N*N) & O(N+N)
    int solveWithMemo(int n, vector<int>& memory) {
        // Edge case: If n is less than or equal to 2 then the maximum product you can get is 1
        if(n <= 2)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[n] != -1)
            return memory[n];

        // Stores the result value
        int maxProduct = INT_MIN;

        // Explore all the possibilities of breaking the n and update the result by the maximum value
        for(int num = 1; num <= n-1; ++num) {
            int nextProduct = max(n - num, solveWithMemo(n - num, memory));
            maxProduct      = max(maxProduct, num * nextProduct);
        }

        // Store the result value to the memoization table and then return it
        return memory[n] = maxProduct;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(int n) {
        // Edge case: If n is less than or equal to 2 then the maximum product you can get is 1
        if(n <= 2)
            return 1;

        // Stores the "maximum product you can get by breaking the n / result value"
        int maxProduct = INT_MIN;

        // Explore all the possibilities of breaking the n and update the result by the maximum value
        for(int num = 1; num <= n-1; ++num) {
            int nextProduct = max(n - num, solveWithoutMemo(n - num));
            maxProduct      = max(maxProduct, num * nextProduct);
        }

        // Return the result value
        return maxProduct;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the maximum product you can get, using 1D tabulation - O(N*N) & O(N)
    int integerBreak(int n) {
        // 1D table: dp[i] represents the maximum product you can get by breaking the Jth index
        vector<int> dp(n + 1, INT_MIN);

        // Set the edge case: If n is equal to 2 then the maximum product you can ge is 1
        dp[2] = 1; 

        // Treat each index 'i' as an individual n and then break it and then look for the maximum product you can get
        for(int i = 3; i <= n; ++i) {
            for(int num = 1; num <= i-1; ++num) {
                int nextProduct = max(i - num, dp[i - num]);
                dp[i] = max(dp[i], num * nextProduct);    
            }
        }
        
        return dp[n];       
    }
};

----------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming
Link  : https://leetcode.com/problems/integer-break/description/
