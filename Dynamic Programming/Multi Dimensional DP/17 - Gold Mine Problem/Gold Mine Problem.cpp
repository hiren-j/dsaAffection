// Code to find out the maximum amount of gold which the miner can collect until he can no longer move in the grid ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int M, N;

    // O(M * 3^(M*N)) & O(M+N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C) {
        if(R < 0 || R == M || C == N)
            return 0;
            
        int moveRight     = solveWithoutMemo(grid, R, C+1);
        int moveUpRight   = solveWithoutMemo(grid, R-1, C+1);
        int moveDownRight = solveWithoutMemo(grid, R+1, C+1);
        
        return max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
    }

    // O(M + 3*M*N) & O(M*N + M+N)
    int solveWithMemo(vector<vector<int>>& memory, const vector<vector<int>>& grid, int R, int C) {
        if(R < 0 || R == M || C == N)
            return 0;
            
        if(memory[R][C] != -1)
            return memory[R][C]; 
            
        int moveRight     = solveWithMemo(memory, grid, R, C+1);
        int moveUpRight   = solveWithMemo(memory, grid, R-1, C+1);
        int moveDownRight = solveWithMemo(memory, grid, R+1, C+1);
        
        return memory[R][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
    }
    
public:
    // Method to find maximum gold miner can collect, using recursion with memoization - O(M*N) & O(M*N)
    int maxGold(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        
        vector<vector<int>> memory(M, vector<int>(N, -1));
        int maxSum = 0;
        
        for(int R = 0; R < M; ++R) {
            int pathSum = solveWithMemo(memory, grid, R, 0);
            maxSum = max(maxSum, pathSum);
        }
        
        return maxSum;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int M, N;

    // O(M*N) & O(M*N)
    int solveBy2DShifting(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(M+2, vector<int>(N+1, -1));
        
        for(int C = 0; C <= N; ++C)
            dp[-1+1][C] = 0;
        for(int C = 0; C <= N; ++C)
            dp[M+1][C] = 0;
        for(int R = 0; R <= M; ++R)
            dp[R+1][N] = 0;
            
        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int moveRight     = dp[R+1][C+1];
                int moveUpRight   = dp[R-1+1][C+1];
                int moveDownRight = dp[R+1+1][C+1];
                dp[R+1][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
            }
        }
        
        int maxSum = 0;
        
        for(int R = 0; R < M; ++R) {
            int pathSum = dp[R+1][0];
            maxSum = max(maxSum, pathSum);
        }
        
        return maxSum;
    }
    
    // O(M*N) & O(M*N)
    int solveBy2DTable_V1(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, -1));
        
        for(int C = 0; C <= N; ++C)
            dp[M][C] = 0;
        for(int R = 0; R <= M; ++R)
            dp[R][N] = 0;
            
        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int moveRight     = dp[R][C+1];
                int moveUpRight   = (R-1 < 0) ? 0 : dp[R-1][C+1];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
            }
        }
        
        int maxSum = 0;
        
        for(int R = 0; R < M; ++R) {
            int pathSum = dp[R][0];
            maxSum = max(maxSum, pathSum);
        }
        
        return maxSum;
    }
    
    // O(M*N) & O(M*N)
    int solveBy2DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(M+1, vector<int>(N+1, 0));
            
        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int moveRight     = dp[R][C+1];
                int moveUpRight   = (R-1 < 0) ? 0 : dp[R-1][C+1];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
            }
        }
        
        int maxSum = 0;
        
        for(int R = 0; R < M; ++R) {
            int pathSum = dp[R][0];
            maxSum = max(maxSum, pathSum);
        }
        
        return maxSum;
    }
    
    // O(M*N) & O(M*N)
    int solveBy2DTable_V2(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(M, vector<int>(N, -1));
            
        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int moveRight     = (C+1 == N) ? 0 : dp[R][C+1];
                int moveUpRight   = (R-1 < 0  || C+1 == N) ? 0 : dp[R-1][C+1];
                int moveDownRight = (R+1 == M || C+1 == N) ? 0 : dp[R+1][C+1];
                dp[R][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
            }
        }
        
        int maxSum = 0;
        
        for(int R = 0; R < M; ++R) {
            int pathSum = dp[R][0];
            maxSum = max(maxSum, pathSum);
        }
        
        return maxSum;
    }
    
    // O(M*N) & O(1)
    int solveWithoutTable(vector<vector<int>>& grid) {
        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int moveRight     = (C+1 == N) ? 0 : grid[R][C+1];
                int moveUpRight   = (R-1 < 0  || C+1 == N) ? 0 : grid[R-1][C+1];
                int moveDownRight = (R+1 == M || C+1 == N) ? 0 : grid[R+1][C+1];
                grid[R][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
            }
        }
        
        int maxSum = 0;
        
        for(int R = 0; R < M; ++R) {
            int pathSum = grid[R][0];
            maxSum = max(maxSum, pathSum);
        }
        
        return maxSum;
    }
    
    // O(M*N) & O(1)
    int solveWithoutTableConcise(vector<vector<int>>& grid) {
        int maxSum = 0;
        
        for(int C = N-1; C >= 0; --C) {
            for(int R = M-1; R >= 0; --R) {
                int moveRight     = (C+1 == N) ? 0 : grid[R][C+1];
                int moveUpRight   = (R-1 < 0  || C+1 == N) ? 0 : grid[R-1][C+1];
                int moveDownRight = (R+1 == M || C+1 == N) ? 0 : grid[R+1][C+1];
                grid[R][C] = max({moveRight, moveUpRight, moveDownRight}) + grid[R][C];
                
                int pathSum = grid[R][0];
                maxSum = max(maxSum, pathSum);
            }
        }
        
        return maxSum;
    }
    
public:
    int maxGold(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveWithoutTableConcise(grid);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix
Link  : https://www.geeksforgeeks.org/problems/gold-mine-problem2608/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
