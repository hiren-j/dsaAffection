// Code to find the number of possible unique paths that the robot can take to reach the bottom-right corner ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the number of possible unique paths, using recursion with memoization - O(M*N) & O(M*N)
    int uniquePaths(int M, int N) {
        vector<vector<int>> memory(M, vector<int>(N, -1));
        return solveWithMemo(memory, M, N, 0, 0);
    }

private:
    // O(2*M*N) & O(M*N + M+N)
    int solveWithMemo(vector<vector<int>>& memory, int M, int N, int R, int C) {
        // Edge case: If reached the bottom up corner then you've one valid way
        if(R == M-1 && C == N-1)
            return 1;

        // Edge case: If all the cells are exhausted then you've no valid way
        if(R == M || C == N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value 
        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities to perform at each cell
        int moveRight = solveWithMemo(memory, M, N, R, C+1); // Is to move right
        int moveDown  = solveWithMemo(memory, M, N, R+1, C); // Is to move down

        // Store the result value to the memoization table and then return it
        return memory[R][C] = moveDown + moveRight;
    }
    
    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(int M, int N, int R, int C) {
        // Edge case: If reached the bottom up corner then you've one valid way
        if(R == M-1 && C == N-1)
            return 1;

        // Edge case: If all the cells are exhausted then you've no valid way
        if(R == M || C == N)
            return 0;

        // There are always two possibilities to perform at each cell
        int moveRight = solveWithoutMemo(M, N, R, C+1); // Is to move right
        int moveDown  = solveWithoutMemo(M, N, R+1, C); // Is to move down

        // Return the result value
        return moveDown + moveRight;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the number of possible unique paths, using 2D tabulation - O(M*N) & O(M*N)
    int uniquePaths_V1(int M, int N) {
        // 2D DP table
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));

        // Initialize the edge case: If reached the bottom up corner then you've one valid way
        dp[M-1][N-1] = 1;

        // Fill the rest of the table
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) 
                    continue;
                int moveRight = dp[R][C+1]; 
                int moveDown  = dp[R+1][C]; 
                dp[R][C] = moveDown + moveRight;
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the number of possible unique paths, using 1D tabulation - O(M*N) & O(N)
    int uniquePaths_V2(int M, int N) {
        // 1D DP tables
        vector<int> nextRow(N+1, 0), currRow(N+1, 0);

        // Initialize the edge case: If reached the bottom up corner then you've one valid way
        currRow[N-1] = 1;

        // Fill the rest of the table 
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                int moveRight = currRow[C+1]; 
                int moveDown  = nextRow[C]; 
                currRow[C] = moveDown + moveRight;
            }
            nextRow = currRow;
        }

        // Return the result value
        return currRow[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Maths | Dynamic Programming | Combinatorics
Link  : https://leetcode.com/problems/unique-paths/description/
