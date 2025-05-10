// Code to find total number of paths available from top-left corner to bottom-right corner such that the XOR of all the values along the path is divisible by K ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    int M, N, K;

    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C, int pathXor) {
        if(R == M || C == N)
            return 0;

        if(R == M-1 && C == N-1) 
            return (pathXor ^ grid[R][C]) == K;

        int moveRight = solveWithoutMemo(grid, R, C+1, pathXor ^ grid[R][C]);
        int moveDown  = solveWithoutMemo(grid, R+1, C, pathXor ^ grid[R][C]);

        return (moveRight + moveDown) % MOD;
    }

    // O(2*M*N*16) & O(M*N*16 + M+N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& grid, int R, int C, int pathXor) {
        if(R == M || C == N)
            return 0;

        if(R == M-1 && C == N-1) 
            return (pathXor ^ grid[R][C]) == K;

        if(dp[R][C][pathXor] != -1)
            return dp[R][C][pathXor];

        int moveRight = solveWithMemo(dp, grid, R, C+1, pathXor ^ grid[R][C]);
        int moveDown  = solveWithMemo(dp, grid, R+1, C, pathXor ^ grid[R][C]);

        return dp[R][C][pathXor] = (moveRight + moveDown) % MOD;
    }

public:
    // Method to count paths whose XOR is divisible by k after reaching bottom right corner, using recursion with memoization - O(M*N) & O(M*N)
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        M = grid.size(), N = grid[0].size(), K = k;
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(16, -1)));
        return solveWithMemo(dp, grid, 0, 0, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    int M, N, K;

    // O(M*N*16) & O(M*N*16)
    int solveWith3DTable(vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(16, -1)));
        
        for(int pathXor = 0; pathXor < 16; ++pathXor) // Init second edge case
            dp[M-1][N-1][pathXor] = (pathXor ^ grid[M-1][N-1]) == K;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int pathXor = 15; pathXor >= 0; --pathXor) {
                    int moveRight = (C+1 < N) ? dp[R][C+1][pathXor ^ grid[R][C]] : 0;
                    int moveDown  = (R+1 < M) ? dp[R+1][C][pathXor ^ grid[R][C]] : 0;
                    dp[R][C][pathXor] = (moveRight + moveDown) % MOD;
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*16) & O(M*N*16)
    int solveWith3DEnhanced(vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(16, 0)));
        
        for(int pathXor = 0; pathXor < 16; ++pathXor) // Init second edge case
            dp[M-1][N-1][pathXor] = (pathXor ^ grid[M-1][N-1]) == K;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int pathXor = 15; pathXor >= 0; --pathXor) {
                    int moveRight = dp[R][C+1][pathXor ^ grid[R][C]];
                    int moveDown  = dp[R+1][C][pathXor ^ grid[R][C]];
                    dp[R][C][pathXor] = (moveRight + moveDown) % MOD;
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*16) & O(2*N*16)
    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> nextRow(N+1, vector<int>(16, 0)), idealRow(N+1, vector<int>(16, 0));

        for(int pathXor = 0; pathXor < 16; ++pathXor) // Init second edge case
            idealRow[N-1][pathXor] = (pathXor ^ grid[M-1][N-1]) == K;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int pathXor = 15; pathXor >= 0; --pathXor) {
                    int moveRight = idealRow[C+1][pathXor ^ grid[R][C]];
                    int moveDown  = nextRow[C][pathXor ^ grid[R][C]];
                    idealRow[C][pathXor] = (moveRight + moveDown) % MOD;
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0][0];
    }

public:
    int countPathsWithXorValue(vector<vector<int>>& grid, int k) {
        M = grid.size(), N = grid[0].size(), K = k;
        return solveWith2DTable(grid);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Matrix | Dynamic Programming  
Link  : https://leetcode.com/problems/count-paths-with-the-given-xor-value/description/
