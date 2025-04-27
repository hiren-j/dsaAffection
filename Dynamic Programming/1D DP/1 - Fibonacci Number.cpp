// Code to find the nth number of the fibonacci sequence ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


/*   
    DON'T IGNORE MUST READ: Hey! Welcome to my series. I am assuming you know the basic theory of DP, like there are two ways to do DP (TopDown and BottomUp), meaning of memoization, meaning of tabulation, why DP is required? I know you want this so I'll be adding this theory soon. 
                            Now, For the Top-Down DP approach in the series, each problem will feature two solutions: `solveWithoutMemo` and `solveWithMemo`. 
                            You must start with `solveWithoutMemo`, which demonstrates the recursive solution without memoization (without DP) and which is expected to run into TLE (Time Limit Exceeded, but its not necessary its because acceptance is dependent on the constraints, haven't got it? its okay). 
                            After understanding the non-optimized approach, move to `solveWithMemo` for the memoized solution (DP in recursion), and after understanding the Top-Down DP (memoization approach), 
                            now you could move to the Bottom-Up DP (tabulation approach) and in this always follow this order, Start from the space consuming tabulation then move to the optimized one as ordered. 
                            So, Follow this order of solving problems for all the questions of the DP series.
*/
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
/*
    DON'T IGNORE MUST READ: The bottom-up solution is the direct conversions of the memoized solution (recursive DP). 
                            This conversion technique helps to create Bottom-up solution very easily and fast, this helps to reduce time and avoid the need for pen and paper as it takes in intuitive bottom-up, This makes the process more efficient, as we will be avoiding the recursive stack space in bottom-up, and also bottom-up is more time optimized compared to the time of memoized solution.
                            Sometimes you'll see that memoization is giving TLE, but the bottom-up is getting accepted, so you see bottom-up is totally efficient than memoized solution, so that's how it is!
                            As you work through the bottom-up solutions, switch tabs to view the memoized solution side-by-side, now give your time and try to observe that what's happening, how things are relating in the memoized and bottom-up solution. 
                            This will help you see how the values passed as parameters in the memoized solution correspond to what we calculate and store in the bottom-up approach. 
                            With practice, you’ll be able to create bottom-up solutions within minutes or even seconds, as I have developed the habit of doing. 
                            This conversion technique will be applied to the all the Bottom-up solutions of the remaining problems across all DP patterns.
*/   
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n < 2)
            return n;

        int prevNum1 = solveWithoutMemo(n - 1);
        int prevNum2 = solveWithoutMemo(n - 2);

        return prevNum1 + prevNum2;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, int n) {
        if(n < 2)
            return n;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[n] != -1) 
            return dp[n];

        int prevNum1 = solveWithMemo(dp, n - 1);
        int prevNum2 = solveWithMemo(dp, n - 2);

        // Store the sum to the memoization table and then return it
        return dp[n] = (prevNum1 + prevNum2); 
    }

public:
    int fib(int n) {
        vector<int> dp(n + 1, -1);
        return solveWithMemo(dp, n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    // O(1*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);

        // Initiailze the edge case of (n < 2) 
        dp[0] = 0; // n == 0 then return 0
        dp[1] = 1; // n == 1 then return 1

        for(int i = 2; i <= n; ++i) { // In recursion we are moving from n to edge case, in Bottom-up just move the reverse way, move from edge case to n
            int prevNum1 = dp[i - 1];
            int prevNum2 = dp[i - 2];
            dp[i] = prevNum1 + prevNum2;
        }

        return dp[n]; // Its the conversion of the first call that we made in recursive DP, [return solveWithMemo(dp, n)], simply remove the function name (dp, n) remains, now do this, dp[n]
    }
    // Note: For calculating the result of any ith number we are dependent on the previous two values, which is constant, so we could simply maintain two variables instead of using the dp array  

    // O(N) & O(1)
    int solveWithoutTable(int n) {
        int prevNum1 = 1, prevNum2 = 0;
        int currNum  = 0;

        for(int i = 2; i <= n; ++i) {
            currNum  = prevNum1 + prevNum2;
            prevNum2 = prevNum1;
            prevNum1 = currNum;
        }

        return currNum;
    }

public:
    int fib(int n) {
        if(n < 2)
            return n;
        return solveWithoutTable(n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Maths | Dynamic Programming | Recursion | Memoization
Link  : https://leetcode.com/problems/fibonacci-number/
