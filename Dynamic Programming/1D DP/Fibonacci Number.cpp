// Code to find the Nth number of the fibonacci sequence ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the Nth number of the fibonacci sequence, using recursion with memoization - O(N) & O(N)
    int getNthFibonacci(int N) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(2*N) & O(N+N)
    int solveWithMemo(int N, vector<int>& memory) {
        // Edge case: When the value of N is less than 2 then return the same value
        if(N < 2)
            return N;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N] != -1)
            return memory[N];

        // Store the result value to the memoization table and then return it
        return memory[N] = solveWithMemo(N-1, memory) + solveWithMemo(N-2, memory);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: When the value of N is less than 2 then return the same value
        if(N < 2)
            return N;
            
        // Recursively compute and return the sum of the two preceding values of N
        return solveWithoutMemo(N-1) + solveWithoutMemo(N-2);
    };
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the Nth number of the fibonacci sequence, using 1D tabulation - O(N) & O(N)
    int getNthFibonacci_V1(int N) {
        // Edge case: When the value of N is less than 2 then return the same value
        if(N < 2)
            return N;   

        // 1D table: dp[J] stores the Jth number of the fibonacci sequence
        vector<int> dp(N+1, 0); 
        dp[1] = 1;

        // Iterate and store the sum of the two preceding values
        for(int J=2; J<=N; J++)
            dp[J] = dp[J-1] + dp[J-2];

        // Return the Nth number of the sequence
        return dp[N];
    }

    // #2 Method to find the Nth number of the fibonacci sequence, using constant auxiliary space - O(N) & O(1)
    int getNthFibonacci_V2(int N) {
        // Edge case: When the value of N is less than 2 then return the same value
        if(N < 2)
            return N;

        int prevPrevNum = 0, prevNum = 1;
        int currNum;

        // Iterate and store the sum of the two preceding values
        for(int J=2; J<=N; J++) {
            currNum     = prevPrevNum + prevNum;
            prevPrevNum = prevNum;
            prevNum     = currNum;
        }

        // Return the Nth number of the sequence
        return currNum;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Maths | Dynamic Programming | Recursion | Memoization
Link  : https://leetcode.com/problems/fibonacci-number/
