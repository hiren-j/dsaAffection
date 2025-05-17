// Code to find out the maximum amount of gold which the miner can collect until he can no longer move in the grid ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
/*
    DON'T IGNORE MUST READ (NOTE ON TIME COMPLEXITY CALCULATION):
    
    As you’ve noticed, for this problem, the time complexity of the solveWithMemo function is O(N + 3*N*M) I want to clarify that the N comes from the loop that calls the recursive function, it's not from the function's auxiliary time. Specifically:

        For solveWithMemo, in O(N + 3*N*M), the term 3*N*M represents the auxiliary time of the function itself, while N reflects the time from the loop that invokes the function.
        For solveWithoutMemo, in O(N * 3^(N*M)), the term 3^(N*M) represents the auxiliary time of the function itself, while N indicates the number of times the loop calls the function.
    
    So for future problems, be sure to identify any loops from which the function is called. This is crucial for providing a complete time complexity analysis, so I can’t ignore these terms.
*/  
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;
    
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(R < 0 || R == N || C == M)
            return 0;
    
        int moveRight     = solveWithoutMemo(grid, R, C+1);
        int moveUpRight   = solveWithoutMemo(grid, R-1, C+1);
        int moveDownRight = solveWithoutMemo(grid, R+1, C+1);
        
        return grid[R][C] + max({moveRight, moveUpRight, moveDownRight});
    }
    
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int R, int C) {
        if(R < 0 || R == N || C == M)
            return 0;
            
        if(memory[R][C] != -1)
            return memory[R][C];
    
        int moveRight     = solveWithMemo(memory, grid, R, C+1);
        int moveUpRight   = solveWithMemo(memory, grid, R-1, C+1);
        int moveDownRight = solveWithMemo(memory, grid, R+1, C+1);
        
        return memory[R][C] = grid[R][C] + max({moveRight, moveUpRight, moveDownRight});
    }

public:
    int collectMaxGold(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();
        return solveWithoutTableConcise(grid);   
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N, M;
    
    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N, vector<int>(M, -1));
        
        for(int C = M-1; C >= 0; --C) {
            for(int R = N-1; R >= 0; --R) {
                int moveRight     = (C+1 < M) ? dp[R][C+1] : 0; 
                int moveUpRight   = (R-1 >= 0 && C+1 < M) ? dp[R-1][C+1] : 0; 
                int moveDownRight = (R+1 < N && C+1 < M)  ? dp[R+1][C+1] : 0;
                dp[R][C] = grid[R][C] + max({moveRight, moveUpRight, moveDownRight});
            }
        }
        
        int maximumGold = 0;
        for(int R = 0; R < N; ++R)
            maximumGold = max(maximumGold, dp[R][0]);
        
        return maximumGold;
    }
    
   int solveWith2DEnhanced(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+2, vector<int>(M+1, 0));
        
        for(int C = M-1; C >= 0; --C) {
            for(int R = N; R >= 1; --R) {
                int moveRight     = dp[R][C+1]; 
                int moveUpRight   = dp[R-1][C+1]; 
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = grid[R-1][C] + max({moveRight, moveUpRight, moveDownRight});   
            }
        }
        
        int maximumGold = 0;
        for(int R = 0; R < N; ++R)
            maximumGold = max(maximumGold, dp[R+1][0]);
            
        return maximumGold;
    }
    
    int solveWithoutTable(vector<vector<int>>& grid) {
        for(int C = M-1; C >= 0; --C) {
            for(int R = N-1; R >= 0; --R) {
                int moveRight     = (C+1 < M) ? grid[R][C+1] : 0; 
                int moveUpRight   = (R-1 >= 0 && C+1 < M) ? grid[R-1][C+1] : 0; 
                int moveDownRight = (R+1 < N && C+1 < M)  ? grid[R+1][C+1] : 0;
                grid[R][C] += max({moveRight, moveUpRight, moveDownRight});
            }
        }
        
        int maximumGold = 0;
        for(int R = 0; R < N; ++R)
            maximumGold = max(maximumGold, grid[R][0]);
        
        return maximumGold;
    }
    
    int solveWith2DConcise(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));
        int maximumGold = 0;
        
        for(int C = M-1; C >= 0; --C) {
            for(int R = N-1; R >= 0; --R) {
                int moveRight     = dp[R][C+1]; 
                int moveUpRight   = (R-1 >= 0) ? dp[R-1][C+1] : 0; 
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = grid[R][C] + max({moveRight, moveUpRight, moveDownRight});   
                maximumGold = max(maximumGold, dp[R][0]);
            }
        }
        
        return maximumGold;
    }
    
    int solveWithoutTableConcise(vector<vector<int>>& grid) {
        int maximumGold = 0;
        
        for(int C = M-1; C >= 0; --C) {
            for(int R = N-1; R >= 0; --R) {
                int moveRight     = (C+1 < M) ? grid[R][C+1] : 0; 
                int moveUpRight   = (R-1 >= 0 && C+1 < M) ? grid[R-1][C+1] : 0; 
                int moveDownRight = (R+1 < N && C+1 < M)  ? grid[R+1][C+1] : 0;
                grid[R][C] += max({moveRight, moveUpRight, moveDownRight});
                maximumGold = max(maximumGold, grid[R][0]);
            }
        }
        
        return maximumGold;
    }

public:
    int collectMaxGold(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();
        return solveWithoutTableConcise(grid);   
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix
Link  : https://www.geeksforgeeks.org/problems/gold-mine-problem2608/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
