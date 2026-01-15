// Code to find the minimum cost of a path that starts from any cell in the first row and ends at any cell in the last row ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N;

    // O(N^(M*N)) & O(M)
    int solveWithoutMemo(const vector<vector<int>>& grid, const vector<vector<int>>& moveCost, int R, int C1) {
        if(R == M)
            return 0;
        
        int minPathCost = INT_MAX;

        for(int C2 = 0; C2 < N; ++C2) {
            int currPathCost = grid[R][C2] + solveWithoutMemo(grid, moveCost, R+1, C2);

            if(C1 != N) {
                int valueAtC1 = grid[R-1][C1];
                currPathCost += moveCost[valueAtC1][C2];
            }
            
            minPathCost = min(minPathCost, currPathCost);
        }

        return minPathCost;
    }

    // O(N*M*N) & O(M*N + M)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, const vector<vector<int>>& moveCost, int R, int C1) {
        if(R == M)
            return 0;

        if(dp[R][C1] != -1)
            return dp[R][C1];
        
        int minPathCost = INT_MAX;

        for(int C2 = 0; C2 < N; ++C2) {
            int currPathCost = grid[R][C2] + solveWithMemo(dp, grid, moveCost, R+1, C2);

            if(C1 != N) {
                int valueAtC1 = grid[R-1][C1];
                currPathCost += moveCost[valueAtC1][C2];            
            }

            minPathCost = min(minPathCost, currPathCost);
        }

        return dp[R][C1] = minPathCost;
    }

public:
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
    int solveBy2DTable(const vector<vector<int>>& grid, const vector<vector<int>>& moveCost) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, -1));

        for(int C1 = 0; C1 <= N; ++C1)
            dp[M][C1] = 0; 

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = 0; C1 <= N; ++C1) {
                int minPathCost = INT_MAX;

                for(int C2 = 0; C2 < N; ++C2) {
                    int currPathCost = grid[R][C2] + dp[R+1][C2];
                    
                    if(C1 != N && R-1 >= 0) {
                        int valueAtC1 = grid[R-1][C1];
                        currPathCost += moveCost[valueAtC1][C2];
                    }

                    minPathCost = min(minPathCost, currPathCost);
                }

                dp[R][C1] = minPathCost;
            }
        }

        return dp[0][N];
    }

    // O(M*N*N) & O(M*N)
    int solveBy2DEnhanced(const vector<vector<int>>& grid, const vector<vector<int>>& moveCost) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = 0; C1 <= N; ++C1) {
                int minPathCost = INT_MAX;

                for(int C2 = 0; C2 < N; ++C2) {
                    int currPathCost = grid[R][C2] + dp[R+1][C2];

                    if(C1 != N && R-1 >= 0) {
                        int valueAtC1 = grid[R-1][C1];
                        currPathCost += moveCost[valueAtC1][C2];
                    }

                    minPathCost = min(minPathCost, currPathCost);
                }

                dp[R][C1] = minPathCost;
            }
        }

        return dp[0][N];
    }

    // O(M*N*N) & O(2*N)
    int solveBy1DTable(const vector<vector<int>>& grid, const vector<vector<int>>& moveCost) {
        vector<int> nextRow(N+1, 0), idealRow(N+1, 0);

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = 0; C1 <= N; ++C1) {
                int minPathCost = INT_MAX;

                for(int C2 = 0; C2 < N; ++C2) {
                    int currPathCost = grid[R][C2] + nextRow[C2];

                    if(C1 != N && R-1 >= 0) {
                        int valueAtC1 = grid[R-1][C1];
                        currPathCost += moveCost[valueAtC1][C2];
                    }

                    minPathCost = min(minPathCost, currPathCost);
                }

                idealRow[C1] = minPathCost;
            }
            swap(nextRow, idealRow);
        }

        return nextRow[N];
    }

public:
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        M = grid.size(), N = grid[0].size();
        return solveBy1DTable(grid, moveCost);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-path-cost-in-a-grid/description/
