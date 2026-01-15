// Code to find the minimum cost of a path that starts from any cell in the first row and ends at any cell in the last row ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    // O(N^(M*N)) & O(M)
    int solveWithoutMemo(vector<vector<int>>& grid, vector<vector<int>>& moveCost, int R, int prevCol) {
        if(R == M)
            return 0;
        
        int minPathCost = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathCost = grid[R][C] + solveWithoutMemo(grid, moveCost, R+1, C);
            if(prevCol != N) {
                currPathCost += moveCost[grid[R-1][prevCol]][C];
            }
            minPathCost = min(minPathCost, currPathCost);
        }

        return minPathCost;
    }

    // O(N*M*N) & O(M*N + M)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, vector<vector<int>>& moveCost, int R, int prevCol) {
        if(R == M)
            return 0;

        if(dp[R][prevCol] != -1)
            return dp[R][prevCol];
        
        int minPathCost = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathCost = grid[R][C] + solveWithMemo(dp, grid, moveCost, R+1, C);
            if(prevCol != N) {
                currPathCost += moveCost[grid[R-1][prevCol]][C];
            }
            minPathCost = min(minPathCost, currPathCost);
        }

        return dp[R][prevCol] = minPathCost;
    }

public:
    // Method to find the minimum cost, using recursion with memoization - O(M*N*N) & O(M*N)
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        M = grid.size(), N = grid[0].size();
        vector<vector<int>> dp(M, vector<int>(N+1, -1));
        return solveWithMemo(dp, grid, moveCost, 0, N);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    // O(M*N*N) & O(M*N)
    int solveWith2DTable(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        vector<vector<int>> dp(M, vector<int>(N+1, -1));

        for(int R = M-1; R >= 0; --R) {
            for(int prevCol = 0; prevCol <= N; ++prevCol) {
                int minPathCost = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int currPathCost = grid[R][C] + (R+1 < M ? dp[R+1][C] : 0);
                    if(prevCol != N && R-1 >= 0) {
                        currPathCost += moveCost[grid[R-1][prevCol]][C];
                    }
                    minPathCost = min(minPathCost, currPathCost);
                }

                dp[R][prevCol] = minPathCost;
            }
        }

        return dp[0][N];
    }

    // O(M*N*N) & O(M*N)
    int solveWith2DEnhanced(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));

        for(int R = M-1; R >= 0; --R) {
            for(int prevCol = 0; prevCol <= N; ++prevCol) {
                int minPathCost = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int currPathCost = grid[R][C] + dp[R+1][C];
                    if(prevCol != N && R-1 >= 0) {
                        currPathCost += moveCost[grid[R-1][prevCol]][C];
                    }
                    minPathCost = min(minPathCost, currPathCost);
                }

                dp[R][prevCol] = minPathCost;
            }
        }

        return dp[0][N];
    }

    // O(M*N*N) & O(2*N)
    int solveWith1DTable(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        vector<int> nextRow(N+1, 0), idealRow(N+1, 0);

        for(int R = M-1; R >= 0; --R) {
            for(int prevCol = 0; prevCol <= N; ++prevCol) {
                int minPathCost = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    int currPathCost = grid[R][C] + nextRow[C];
                    if(prevCol != N && R-1 >= 0) {
                        currPathCost += moveCost[grid[R-1][prevCol]][C];
                    }
                    minPathCost = min(minPathCost, currPathCost);
                }

                idealRow[prevCol] = minPathCost;
            }
            nextRow = idealRow;
        }

        return nextRow[N];
    }

public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        M = grid.size(), N = grid[0].size();
        return solveWith1DTable(grid, moveCost);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-path-cost-in-a-grid/description/
