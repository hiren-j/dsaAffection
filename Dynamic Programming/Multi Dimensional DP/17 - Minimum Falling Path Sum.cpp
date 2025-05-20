// Code to find the minimum sum of any falling path through the matrix ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    // O(N * 3^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        int moveToSameCol = solveWithoutMemo(grid, R+1, C);   
        int moveToPrevCol = solveWithoutMemo(grid, R+1, C-1); 
        int moveToNextCol = solveWithoutMemo(grid, R+1, C+1); 

        int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});

        return grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }

    // O(N + 3*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int C) {
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        if(dp[R][C] != -101)
            return dp[R][C];

        int moveToSameCol = solveWithMemo(dp, grid, R+1, C);   
        int moveToPrevCol = solveWithMemo(dp, grid, R+1, C-1); 
        int moveToNextCol = solveWithMemo(dp, grid, R+1, C+1); 

        int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});

        return dp[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }

public:
    // Method to find the minimum sum of a falling path, using recursion with memoization - O(N*N) & O(N*N)
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        
        vector<vector<int>> dp(N, vector<int>(N, -101));
        
        int minPathSum = INT_MAX;
        for(int C = 0; C < N; ++C) 
            minPathSum = min(minPathSum, solveWithMemo(dp, grid, 0, C));
        
        return minPathSum;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N;

    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N, vector<int>(N, -101));

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveToSameCol = (R+1 < N) ? dp[R+1][C] : INT_MAX; 
                int moveToPrevCol = (R+1 < N && C-1 >= 0) ? dp[R+1][C-1] : INT_MAX;
                int moveToNextCol = (R+1 < N && C+1 < N)  ? dp[R+1][C+1] : INT_MAX;
                int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});
                dp[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
            }
        }

        int minPathSum = INT_MAX;
        for(int C = 0; C < N; ++C) 
            minPathSum = min(minPathSum, dp[0][C]);
        
        return minPathSum;
    }
    
    int solveWith2DEnhanced(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+2, INT_MAX));

        for(int R = N-1; R >= 0; --R) {
            for(int C = N; C >= 1; --C) {
                int moveToSameCol = dp[R+1][C]; 
                int moveToPrevCol = dp[R+1][C-1];
                int moveToNextCol = dp[R+1][C+1];
                int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});
                dp[R][C] = grid[R][C-1] + (minElement == INT_MAX ? 0 : minElement);
            }
        }

        int minPathSum = INT_MAX;
        for(int C = 0; C < N; ++C) 
            minPathSum = min(minPathSum, dp[0][C+1]);
        
        return minPathSum;
    }

    int solveWithoutTable(vector<vector<int>>& grid) {
        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveToSameCol = (R+1 < N) ? grid[R+1][C] : INT_MAX; 
                int moveToPrevCol = (R+1 < N && C-1 >= 0) ? grid[R+1][C-1] : INT_MAX;
                int moveToNextCol = (R+1 < N && C+1 < N)  ? grid[R+1][C+1] : INT_MAX;
                int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});
                grid[R][C] += (minElement == INT_MAX ? 0 : minElement);
            }
        }

        int minPathSum = INT_MAX;
        for(int C = 0; C < N; ++C) 
            minPathSum = min(minPathSum, grid[0][C]);
        
        return minPathSum;
    }

    int solveWith2DConcise(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+2, INT_MAX));
        int minPathSum = INT_MAX;

        for(int R = N-1; R >= 0; --R) {
            for(int C = N; C >= 1; --C) {
                int moveToSameCol = dp[R+1][C]; 
                int moveToPrevCol = dp[R+1][C-1];
                int moveToNextCol = dp[R+1][C+1];
                int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});
                dp[R][C] = grid[R][C-1] + (minElement == INT_MAX ? 0 : minElement);
                if(R == 0) minPathSum = min(minPathSum, dp[0][C]);
            }
        }
        
        return minPathSum;
    }

    int solveWith1DTable(vector<vector<int>>& grid) {
        vector<int> nextRow(N+2, INT_MAX), idealRow(N+2, INT_MAX);
        int minPathSum = INT_MAX;

        for(int R = N-1; R >= 0; --R) {
            for(int C = N; C >= 1; --C) {
                int moveToSameCol = nextRow[C]; 
                int moveToPrevCol = nextRow[C-1];
                int moveToNextCol = nextRow[C+1];
                int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});
                idealRow[C] = grid[R][C-1] + (minElement == INT_MAX ? 0 : minElement);
                if(R == 0) minPathSum = min(minPathSum, idealRow[C]);
            }
            nextRow = idealRow;
        }
        
        return minPathSum;
    }

    int solveWithoutTableConcise(vector<vector<int>>& grid) {
        int minPathSum = INT_MAX;

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveToSameCol = (R+1 < N) ? grid[R+1][C] : INT_MAX; 
                int moveToPrevCol = (R+1 < N && C-1 >= 0) ? grid[R+1][C-1] : INT_MAX;
                int moveToNextCol = (R+1 < N && C+1 < N)  ? grid[R+1][C+1] : INT_MAX;
                int minElement = min({moveToSameCol, moveToPrevCol, moveToNextCol});
                grid[R][C] += (minElement == INT_MAX ? 0 : minElement);
                if(R == 0) minPathSum = min(minPathSum, grid[0][C]);
            }
        }

        return minPathSum;
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        return solveWithoutTableConcise(grid);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();
        
        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveToSameCol = grid[R+1][C];   
                int moveToPrevCol = (C-1 >= 0) ? grid[R+1][C-1] : INT_MAX; 
                int moveToNextCol = (C+1 < N)  ? grid[R+1][C+1] : INT_MAX; 
                grid[R][C] += min({moveToSameCol, moveToPrevCol, moveToNextCol});
            }
        }

        return *min_element(begin(grid[0]), end(grid[0]));
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-falling-path-sum/description/
