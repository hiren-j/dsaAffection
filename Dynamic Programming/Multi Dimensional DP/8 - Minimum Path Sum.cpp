// Code to find a path from top left to bottom right, which minimizes the sum of all numbers along its path ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(R == M || C == N)
            return INT_MAX;
        
        if(R == M-1 && C == N-1)
            return grid[R][C];

        int moveRight = solveWithoutMemo(grid, R, C+1);
        int moveDown  = solveWithoutMemo(grid, R+1, C);
        
        return min(moveRight, moveDown) + grid[R][C];
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int C) {
        if(R == M || C == N)
            return INT_MAX;
        
        if(R == M-1 && C == N-1)
            return grid[R][C];

        if(dp[R][C] != -1)
            return dp[R][C];

        int moveRight = solveWithMemo(dp, grid, R, C+1);
        int moveDown  = solveWithMemo(dp, grid, R+1, C);
        
        return dp[R][C] = min(moveRight, moveDown) + grid[R][C];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        vector<vector<int>> dp(M, vector<int>(N, -1));
        return solveWithMemo(dp, grid, 0, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(M, vector<int>(N, -1));
        dp[M-1][N-1] = grid[M-1][N-1];

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)    
                    continue;
                int moveRight = (C+1 < N) ? dp[R][C+1] : INT_MAX;
                int moveDown  = (R+1 < M) ? dp[R+1][C] : INT_MAX;
                dp[R][C] = min(moveRight, moveDown) + grid[R][C];
            }
        }

        return dp[0][0];
    }

    int solveWith2DEnhanced(vector<vector<int>>& grid) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, INT_MAX));
        dp[M-1][N-1] = grid[M-1][N-1];

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)    
                    continue;
                int moveRight = dp[R][C+1];
                int moveDown  = dp[R+1][C];
                dp[R][C] = min(moveRight, moveDown) + grid[R][C];
            }
        }

        return dp[0][0];
    }

    int solveWith1DTable(vector<vector<int>>& grid) {
        vector<int> nextRow(N+1, INT_MAX), idealRow(N+1, INT_MAX);
        idealRow[N-1] = grid[M-1][N-1];

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)    
                    continue;
                int moveRight = idealRow[C+1];
                int moveDown  = nextRow[C];
                idealRow[C] = min(moveRight, moveDown) + grid[R][C];
            }
            nextRow = idealRow;
        }

        return nextRow[0];
    }

    int solveWithoutTable(vector<vector<int>>& grid) {
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)    
                    continue;
                int moveRight = (C+1 < N) ? grid[R][C+1] : INT_MAX;
                int moveDown  = (R+1 < M) ? grid[R+1][C] : INT_MAX;
                grid[R][C] += min(moveRight, moveDown);
            }
        }

        return grid[0][0];
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveWithoutTable(grid);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
    // O(M*N) & O(1)
    int minPathSum(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        // When there's only one column in grid then you can reach any cell through it's previous row only
        for(int R = 1; R < M; ++R) 
            grid[R][0] += grid[R-1][0];

        // When there's only one row in the then you can reach any cell through it's previous column only
        for(int C = 1; C < N; ++C) 
            grid[0][C] += grid[0][C-1];

        // When there are multiple rows and columns in the grid then you can reach any cell through it's previous row and previous column
        for(int R = 1; R < M; ++R) {
            for(int C = 1; C < N; ++C) {
                int moveDown  = grid[R-1][C]; 
                int moveRight = grid[R][C-1]; 
                grid[R][C] += min(moveDown, moveRight);
            }
        }

        return grid[M-1][N-1];
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-path-sum/description/
