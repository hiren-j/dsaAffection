// Code to find the total number of ways the frog can take to reach the top of the Nth step, a frog can jump either 1, 2, or 3 steps to go to the top ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int solveWithoutMemo(int n) {
        if(n <= 0)
            return (n == 0);
        
        int jump1Step = solveWithoutMemo(n - 1);
        int jump2Step = solveWithoutMemo(n - 2);
        int jump3Step = solveWithoutMemo(n - 3);
        
        return jump1Step + jump2Step + jump3Step;
    }
    
    int solveWithMemo(vector<int>& memory, int n) {
        if(n <= 0)
            return (n == 0);
        
        if(memory[n] != -1)
            return memory[n];
        
        int jump1Step = solveWithMemo(memory, n - 1);
        int jump2Step = solveWithMemo(memory, n - 2);
        int jump3Step = solveWithMemo(memory, n - 3);
        
        return memory[n] = (jump1Step + jump2Step + jump3Step);
    }
    
public:
    int numWaysToReachTop(int n) {
        vector<int> memory(n + 1, -1);
        return solveWithoutMemo(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int solveWith1DTable(int n) {
        vector<int> dp(n + 1, -1);
        dp[0] = 1; // Init the edge case of (n == 0) then exists 1 way
        
        for(int i = 1; i <= n; ++i) {
            int jump1Step = dp[i - 1];
            int jump2Step = (i - 2 >= 0) ? dp[i - 2] : 0;
            int jump3Step = (i - 3 >= 0) ? dp[i - 3] : 0;
            dp[i] = jump1Step + jump2Step + jump3Step;
        }
        
        return dp[n];
    }
    
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
    int countWays(int n) {
        return solveWith1DTable(n);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/count-number-of-hops-1587115620/1
