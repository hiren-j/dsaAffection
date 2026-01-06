// Code to find the minimum cost of painting all houses such that no adjacent houses are painted with the same colour ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;
    
    // O(2^(N*M)) & O(N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int skipCol) {
        if(R == N)
            return 0;
            
        int minPathSum = INT_MAX;
        
        for(int C = 0; C < M; ++C) {
            if(C != skipCol) {
                int nextSideSum = solveWithoutMemo(grid, R+1, C);
                int currPathSum = nextSideSum + grid[R][C];
                minPathSum = min(minPathSum, currPathSum);
            }
        }
        
        return minPathSum;
    }
  
    // O(2*N*M) & O(N*M + N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int skipCol) {
        if(R == N)
            return 0;
            
        if(dp[R][skipCol] != -1)
            return dp[R][skipCol];
            
        int minPathSum = INT_MAX;
        
        for(int C = 0; C < M; ++C) {
            if(C != skipCol) {
                int nextSideSum = solveWithMemo(dp, grid, R+1, C);
                int currPathSum = nextSideSum + grid[R][C];
                minPathSum = min(minPathSum, currPathSum);
            }
        }
        
        return dp[R][skipCol] = minPathSum;
    }
  
    // O(2*N*M) & O(N*M + N)
    int solveWithMemoShifting(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int skipCol) {
        if(R == N)
            return 0;
            
        if(dp[R][skipCol + 1] != -1)
            return dp[R][skipCol + 1];
            
        int minPathSum = INT_MAX;
        
        for(int C = 0; C < M; ++C) {
            if(C != skipCol) {
                int nextSideSum = solveWithMemoShifting(dp, grid, R+1, C);
                int currPathSum = nextSideSum + grid[R][C];
                minPathSum = min(minPathSum, currPathSum);
            }
        }
        
        return dp[R][skipCol + 1] = minPathSum;
    }
    
public:
    int minCostToPaintHouses(vector<vector<int>>& grid) {
        N = grid.size(), M = 3;
        vector<vector<int>> dp(N, vector<int>(M+1, -1));
        return solveWithMemo(dp, grid, 0, M);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N, M;

    // O(N*M*2) & O(N*M)
    int solveBy2DShifting(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(M+1, -1));
        
        for(int skipCol = 0; skipCol <= M; ++skipCol)
            dp[N][skipCol + 1] = 0;
            
        for(int R = N-1; R >= 0; --R) {
            for(int skipCol = M; skipCol >= -1; --skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < M; ++C) {
                    if(C != skipCol) {
                        int nextSideSum = dp[R+1][C+1];
                        int currPathSum = nextSideSum + grid[R][C];
                        minPathSum = min(minPathSum, currPathSum);
                    }
                }
                
                dp[R][skipCol + 1] = minPathSum; 
            }
        }
        
        return dp[0][-1+1];
    }
    
    // O(N*M*2) & O(N*M)
    int solveBy2DTable(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(M+1, -1));
        
        for(int skipCol = 0; skipCol <= M; ++skipCol)
            dp[N][skipCol] = 0;
            
        for(int R = N-1; R >= 0; --R) {
            for(int skipCol = 0; skipCol <= M; ++skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < M; ++C) {
                    if(C != skipCol) {
                        int nextSideSum = dp[R+1][C];
                        int currPathSum = nextSideSum + grid[R][C];
                        minPathSum = min(minPathSum, currPathSum);
                    }
                }
                
                dp[R][skipCol] = minPathSum; 
            }
        }
        
        return dp[0][M];
    }
    
    // O(N*M*2) & O(N*M)
    int solveBy2DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
        
        for(int R = N-1; R >= 0; --R) {
            for(int skipCol = 0; skipCol <= M; ++skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < M; ++C) {
                    if(C != skipCol) {
                        int nextSideSum = dp[R+1][C];
                        int currPathSum = nextSideSum + grid[R][C];
                        minPathSum = min(minPathSum, currPathSum);
                    }
                }
                
                dp[R][skipCol] = minPathSum; 
            }
        }
        
        return dp[0][M];
    }
    
    // O(N*M*2) & O(2*M)
    int solveBy1DTable(const vector<vector<int>>& grid) {
        vector<int> nextRow(M+1, 0), currRow(M+1, 0); 
        
        for(int R = N-1; R >= 0; --R) {    
            for(int skipCol = 0; skipCol <= M; ++skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < M; ++C) {
                    if(C != skipCol) {
                        int nextSideSum = nextRow[C];
                        int currPathSum = nextSideSum + grid[R][C];
                        minPathSum = min(minPathSum, currPathSum);
                    }
                }
                
                currRow[skipCol] = minPathSum; 
            }
            swap(nextRow, currRow);
        }
        
        return nextRow[M];
    }

public:
    int minCostToPaintHouses(vector<vector<int>>& grid) {
        N = grid.size(), M = 3;
        return solveBy1DTable(grid);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
    int N, M;

    // O(N*M) & O(1)
    int solveWithoutTable_V1(vector<vector<int>>& grid) {
        for(int R = N-2; R >= 0; --R) {
            for(int C = 0; C < M; ++C) {
                int minCost = INT_MAX; // To earn minimum cost, get minimum value from from next row but the only cell which you shouldn't consider is the same cell from the next row
                
                for(int skipCol = 0; skipCol < 3; ++skipCol) { 
                    if(C != skipCol) { 
                        minCost = min(minCost, grid[R + 1][skipCol]); 
                    }
                }
                
                grid[R][C] += minCost;
            }
        }
        
        return *min_element(begin(grid[0]), end(grid[0]));
    }

    // O(N*M) & O(1)
    int solveWithoutTable_V2(vector<vector<int>>& grid) {
        // Suppose you're on a cell so to earn minimum cost, get minimum value from from previous row but the only cell which you shouldn't consider is the same cell from the previous row
        for(int R = 1; R < N; ++R) {
            for(int C = 0; C < M; ++C) {
                if(C == 0)
                    grid[R][C] += min(grid[R - 1][C + 1], grid[R - 1][C + 2]); 
                else if(C == 1)
                    grid[R][C] += min(grid[R - 1][C - 1], grid[R - 1][C + 1]);
                else
                    grid[R][C] += min(grid[R - 1][C - 1], grid[R - 1][C - 2]);
            }
        }
        
        return *min_element(begin(grid[N - 1]), end(grid[N - 1]));
    }

public:
    int minCostToPaintHouses(vector<vector<int>>& grid) {
        N = grid.size(), M = 3;
        return solveWithoutTable_V2(grid);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Matrix | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/geeks-training/1
