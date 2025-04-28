// Code to find the total number of ways the frog can take to reach the top of the nth step, a frog can jump either 1, 2, or 3 steps to go to the top ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    // O(3^N) & O(N)
    int solveWithoutMemo(int n) {
        if(n <= 0) 
            return (n == 0); // Edge case: If n becomes 0 then you've 1 way

        // There are three possibilities to reach this nth step
        int jump1Step = solveWithoutMemo(n - 1); // To make 1 jump from any step below it
        int jump2Step = solveWithoutMemo(n - 2); // To make 2 jump from any step below it
        int jump3Step = solveWithoutMemo(n - 3); // To make 3 jump from any step below it

        // Return total number of ways exists to reach this nth step
        return jump1Step + jump2Step + jump3Step;
    }
    
    // O(3*N) & O(2*N)
    int solveWithMemo(vector<int>& memory, int n) {
        if(n <= 0)
            return (n == 0); // Edge case: If n becomes 0 then you've 1 way
        
        if(memory[n] != -1)
            return memory[n];
        
        // There are three possibilities to reach this nth step
        int jump1Step = solveWithMemo(memory, n - 1); // To make 1 jump from any step below it
        int jump2Step = solveWithMemo(memory, n - 2); // To make 2 jump from any step below it
        int jump3Step = solveWithMemo(memory, n - 3); // To make 3 jump from any step below it
        
        // Store the result to memoization table and then return it
        return memory[n] = (jump1Step + jump2Step + jump3Step);
    }
    
public:
    int numWaysToReachTop(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(1*N) & O(1*N)
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);
        dp[0] = 1; // Init the edge case
        
        for(int i = 1; i <= n; ++i) {
            int jump1Step = dp[i - 1];
            int jump2Step = (i - 2 >= 0) ? dp[i - 2] : 0;
            int jump3Step = (i - 3 >= 0) ? dp[i - 3] : 0;
            dp[i] = jump1Step + jump2Step + jump3Step;
        }
        
        return dp[n];
    }
    
    // O(1*N) & O(1)
    int solveWithoutTable(int n) {
        int jump1Step = 1;
        int jump2Step = 0;
        int jump3Step = 0;
        int numWays   = 0;

        for(int i = 1; i <= n; ++i) {
            numWays   = jump1Step + jump2Step + jump3Step;
            jump3Step = jump2Step;
            jump2Step = jump1Step;
            jump1Step = numWays;
        }
        
        return numWays;
    }
    
public:
    int numWaysToReachTop(int n) {
        return solveWithoutTable(n);
    }
};
5
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/count-number-of-hops-1587115620/1
