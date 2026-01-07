// Code to find the minimum sum of a falling path with non-zero shifts ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;
    
    // O(N^(N*N)) & O(N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int skipCol) {
        if(R == N)
            return 0;
            
        int minPathSum = INT_MAX;
        
        for(int C = 0; C < N; ++C) {
            if(C != skipCol) {
                int nextSideSum = solveWithoutMemo(grid, R+1, C);
                int currPathSum = nextSideSum + grid[R][C];
                minPathSum = min(minPathSum, currPathSum);
            }
        }
        
        return minPathSum;
    }
  
    // O(N*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int skipCol) {
        if(R == N)
            return 0;
            
        if(dp[R][skipCol] != INT_MAX)
            return dp[R][skipCol];
            
        int minPathSum = INT_MAX;
        
        for(int C = 0; C < N; ++C) {
            if(C != skipCol) {
                int nextSideSum = solveWithMemo(dp, grid, R+1, C);
                int currPathSum = nextSideSum + grid[R][C];
                minPathSum = min(minPathSum, currPathSum);
            }
        }
        
        return dp[R][skipCol] = minPathSum;
    }
  
    // O(N*N*N) & O(N*N + N)
    int solveWithMemoShifting(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int skipCol) {
        if(R == N)
            return 0;
            
        if(dp[R][skipCol + 1] != INT_MAX)
            return dp[R][skipCol + 1];
            
        int minPathSum = INT_MAX;
        
        for(int C = 0; C < N; ++C) {
            if(C != skipCol) {
                int nextSideSum = solveWithMemoShifting(dp, grid, R+1, C);
                int currPathSum = nextSideSum + grid[R][C];
                minPathSum = min(minPathSum, currPathSum);
            }
        }
        
        return dp[R][skipCol + 1] = minPathSum;
    }

public:
    // Method to find minimum sum of a falling path, using recursion with memoization - O(N^3) & O(N^2)
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N + 1, INT_MAX));
        return solveWithMemo(dp, grid, 0, N);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N;

    // O(N^3) & O(N^2)
    int solveBy2DShifting(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, -1));
        
        for(int skipCol = 0; skipCol <= N; ++skipCol)
            dp[N][skipCol + 1] = 0;
            
        for(int R = N-1; R >= 0; --R) {
            for(int skipCol = N; skipCol >= -1; --skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < N; ++C) {
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
    
    // O(N^3) & O(N^2)
    int solveBy2DTable(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, -1));
        
        for(int skipCol = 0; skipCol <= N; ++skipCol)
            dp[N][skipCol] = 0;
            
        for(int R = N-1; R >= 0; --R) {
            for(int skipCol = 0; skipCol <= N; ++skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < N; ++C) {
                    if(C != skipCol) {
                        int nextSideSum = dp[R+1][C];
                        int currPathSum = nextSideSum + grid[R][C];
                        minPathSum = min(minPathSum, currPathSum);
                    }
                }
                
                dp[R][skipCol] = minPathSum; 
            }
        }
        
        return dp[0][N];
    }
    
    // O(N^3) & O(N^2)
    int solveBy2DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, 0));
        
        for(int R = N-1; R >= 0; --R) {
            for(int skipCol = 0; skipCol <= N; ++skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < N; ++C) {
                    if(C != skipCol) {
                        int nextSideSum = dp[R+1][C];
                        int currPathSum = nextSideSum + grid[R][C];
                        minPathSum = min(minPathSum, currPathSum);
                    }
                }
                
                dp[R][skipCol] = minPathSum; 
            }
        }
        
        return dp[0][N];
    }
    
    // O(N^3) & O(2*N)
    int solveBy1DTable(const vector<vector<int>>& grid) {
        vector<int> nextRow(N+1, 0), currRow(N+1, 0); 
        
        for(int R = N-1; R >= 0; --R) {    
            for(int skipCol = 0; skipCol <= N; ++skipCol) {
                int minPathSum = INT_MAX;
                
                for(int C = 0; C < N; ++C) {
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
        
        return nextRow[N];
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        return solveBy2DTable(grid);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-falling-path-sum-ii/description/?envType=daily-question&envId=2024-04-26
