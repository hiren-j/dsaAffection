// Code to find the number of possible unique paths that the robot can take to reach the bottom-right corner ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(int R, int C) {
        if(R == M || C == N)    
            return 0;
        
        if(R == M-1 && C == N-1)
            return 1;

        int moveRight = solveWithoutMemo(R, C+1);
        int moveDown  = solveWithoutMemo(R+1, C);

        return moveRight + moveDown;
    }

    // O(2*M*N) & O(M*N + M+N)
    int solveWithMemo(vector<vector<int>>& memory, int R, int C) {
        if(R == M || C == N)    
            return 0;
        
        if(R == M-1 && C == N-1)
            return 1;

        if(memory[R][C] != -1)
            return memory[R][C];

        int moveRight = solveWithMemo(memory, R, C+1);
        int moveDown  = solveWithMemo(memory, R+1, C);

        return memory[R][C] = moveRight + moveDown;
    }

public:
    // Method to count total ways to reach the bottom right corner, using recursion with memoization - O(M*N) & O(M*N)
    int uniquePaths(int m, int n) {
        M = m, N = n;
        vector<vector<int>> memory(M, vector<int>(N, -1));
        return solveWithMemo(memory, 0, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(M*N) & O(M*N)
    int solveBy2DTable(int M, int N) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, -1));
        dp[M-1][N-1] = 1; // if(R == M-1 && C == N-1) return 1

        for(int C = 0; C <= N; ++C) // if(R == M) return 0
            dp[M][C] = 0;
        for(int R = 0; R <= M; ++R) // if(C == N) return 0
            dp[R][N] = 0;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue; 
                int moveRight = dp[R][C+1];
                int moveDown  = dp[R+1][C];
                dp[R][C] = (moveRight + moveDown);
            }
        }

        return dp[0][0];
    }

    // O(M*N) & O(M*N)
    int solveBy2DEnhanced_V1(int M, int N) {
        vector<vector<int>> dp(M, vector<int>(N, -1));
        dp[M-1][N-1] = 1;
        
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)    
                    continue;
                int moveRight = (C+1 == N) ? 0 : dp[R][C+1];
                int moveDown  = (R+1 == M) ? 0 : dp[R+1][C];
                dp[R][C] = moveRight + moveDown;
            }
        }

        return dp[0][0];
    }

    // O(M*N) & O(M*N)
    int solveBy2DEnhanced_V2(int M, int N) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
        dp[M-1][N-1] = 1;
        
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)    
                    continue;
                int moveRight = dp[R][C+1];
                int moveDown  = dp[R+1][C];
                dp[R][C] = moveRight + moveDown;
            }
        }

        return dp[0][0];
    }

    // O(M*N) & O(2*N)
    int solveBy1DTable(int M, int N) {
        vector<int> nextRow(N+1, 0), currRow(N+1, 0);
        currRow[N-1] = 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                int moveRight = currRow[C+1]; 
                int moveDown  = nextRow[C]; 
                currRow[C] = moveDown + moveRight;
            }
            swap(nextRow, currRow);
        }

        return nextRow[0]; // Return currRow[0] will also work
    }

public:
    int uniquePaths(int M, int N) {
        return solveBy1DTable(M, N);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitve {
    // O(M*N) & O(M*N)
    int solveWith2DTable(int M, int N) {
        //  Suppose you're on a cell and that cell is also a destination cell then you've only 1 way it's because you're already on the cell. So, initially fill all the cells by value 1
        vector<vector<int>> dp(M, vector<int>(N, 1));

        for(int R = 1; R < M; ++R)
            for(int C = 1; C < N; ++C)
                dp[R][C] = dp[R-1][C] + dp[R][C-1];

        return dp[M-1][N-1];
    }

    // O(M*N) & O(2*N)
    int solveBy1DTable(int M, int N) {
        vector<int> prevRow(N, 1), currRow(N, 1);

        for(int R = 1; R < M; ++R) {
            for(int C = 1; C < N; ++C) {
                currRow[C] = prevRow[C] + currRow[C-1];
            }
            swap(prevRow, currRow);
        }

        return prevRow[N-1];
    }

public:
    int uniquePaths(int M, int N) {
        return solveBy1DTable(M, N);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Maths | Dynamic Programming | Combinatorics
Link  : https://leetcode.com/problems/unique-paths/description/
