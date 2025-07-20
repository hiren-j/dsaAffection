// Code to find the maximum number of moves that you can perform in the grid. You can start at any cell in the first column of the matrix, and traverse the grid in the following way: From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,1}, {0,1}, {1,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(M * 3^(M*N)) & O(max(M,N))
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        int maxMoves = 0;

        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                maxMoves = max(maxMoves, 1 + solveWithoutMemo(grid, newR, newC));
            }
        }

        return maxMoves;
    }

    // O(M + 3*M*N) & O(M*N + max(M,N))
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int C) {
        if(dp[R][C] != -1)
            return dp[R][C];

        int maxMoves = 0;

        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                maxMoves = max(maxMoves, 1 + solveWithMemo(dp, grid, newR, newC));
            }
        }

        return dp[R][C] = maxMoves;
    }

public:
    // Method to find maximum number of moves you can perform in grid, using recursion with memoization - O(N*M) & O(N*M)
    int maxMoves(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();

        vector<vector<int>> dp(M, vector<int>(N, -1));

        int result = 0;
        for(int R = 0; R < M; ++R) {
            result = max(result, solveWithMemo(dp, grid, R, 0));
        }
        return result;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{-1,1}, {0,1}, {1,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(M*N) & O(M*N)
    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(M, vector<int>(N, -1));

        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int maxMoves = 0;

                for(auto& dir : directions) {
                    int newR = R + dir[0];
                    int newC = C + dir[1];
                    if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                        maxMoves = max(maxMoves, 1 + dp[newR][newC]);
                    }
                }

                dp[R][C] = maxMoves;
            }
        }

        int result = 0;
        for(int R = 0; R < M; ++R) {
            result = max(result, dp[R][0]);
        }
        return result;
    }

    // O(M*N) & O(M*N)
    int solveWith2DEnhanced(vector<vector<int>>& grid) {
        vector<vector<int>> dp(M, vector<int>(N, 0));
        int result = 0;

        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int maxMoves = 0;

                for(auto& dir : directions) {
                    int newR = R + dir[0];
                    int newC = C + dir[1];
                    if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                        maxMoves = max(maxMoves, 1 + dp[newR][newC]);
                    }
                }

                dp[R][C] = maxMoves;
                result = max(result, dp[R][0]);
            }
        }

        return result;
    }

public:
    int maxMoves(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveWith2DEnhanced(grid);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/?envType=daily-question&envId=2024-10-29
