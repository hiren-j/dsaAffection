// Code to find the number of possible unique paths that the robot can take to reach the bottom-right corner ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(R == M || C == N || grid[R][C] == 1)
            return 0;

        if(R == M-1 && C == N-1)
            return 1;
        
        int moveRight = solveWithoutMemo(grid, R, C+1);
        int moveDown  = solveWithoutMemo(grid, R+1, C);

        return moveRight + moveDown;
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int C) {
        if(R == M || C == N || grid[R][C] == 1)
            return 0;

        if(R == M-1 && C == N-1)
            return 1;

        if(dp[R][C] != -1)
            return dp[R][C];
        
        int moveRight = solveWithMemo(dp, grid, R, C+1);
        int moveDown  = solveWithMemo(dp, grid, R+1, C);

        return dp[R][C] = moveRight + moveDown;
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        if(grid[0][0] == 1 || grid[M-1][N-1])
            return 0;
        M = grid.size(), N = grid[0].size();
        vector<vector<int>> dp(M, vector<int>(N, -1));
        return solveWithMemo(dp, grid, 0, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(M, vector<int>(N, -1));
        dp[M-1][N-1] = 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) {
                    continue;
                } else if(grid[R][C] == 1) {
                    dp[R][C] = 0;
                } else {
                    long moveRight = (C+1 < N) ? dp[R][C+1] : 0;
                    long moveDown  = (R+1 < M) ? dp[R+1][C] : 0;
                    dp[R][C] = moveRight + moveDown;
                }
            }
        }

        return dp[0][0];
    }

    int solveWith2DEnhanced(vector<vector<int>>& grid) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
        dp[M-1][N-1] = 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if((R == M-1 && C == N-1) || grid[R][C] == 1) 
                    continue;
                long moveRight = dp[R][C+1];
                long moveDown  = dp[R+1][C];
                dp[R][C] = moveRight + moveDown;
            }
        }

        return dp[0][0];
    }
    
    int solveWith1DTable(vector<vector<int>>& grid) {
        vector<int> nextRow(N+1, 0), idealRow(N+1, 0);
        idealRow[N-1] = 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) {
                    continue;
                }
                else if(grid[R][C] == 1) {
                    idealRow[C] = 0;   
                }
                else {
                    long moveRight = idealRow[C+1];
                    long moveDown  = nextRow[C];
                    idealRow[C] = moveRight + moveDown;
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0];
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        if(grid[0][0] == 1 || grid[M-1][N-1]) 
            return 0;
        M = grid.size(), N = grid[0].size();
        return solveWith2DTable(grid);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Links : https://leetcode.com/problems/unique-paths-ii/description
        https://cses.fi/problemset/task/1638
