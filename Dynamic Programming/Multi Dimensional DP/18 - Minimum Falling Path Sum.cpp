// Code to find the minimum sum of any falling path through the matrix ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: I've initialized the cell values by INT_MAX: [vector<vector<int>> dp(N, vector<int>(N, INT_MAX))]
                            Why INT_MAX? Why not -1 as we used before? See in the problem constraints its given that in worst case the minimum value of a cell could be -100, 
                            maximum could be 100: 
                                -100 <= matrix[i][j] <= 100
                                n == matrix.length == matrix[i].length
                                1 <= n <= 100
                            The worst minimum sum could be -100*n = -100*100 = -10000
                            The worst maximum sum could be  100*n =  100*100 =  10000
                            This means you should not use any of the value lying in range [-10000, 10000], Its because those values are contributing in result making.
                            If we use any of that value for dp matrix initialization then this will lead our solution to hit TLE. So it's better to avoid any value of that range, 
                            So I would prefer to use lesser values than -10000, or greater values than 10000 for dp initialization, just don't use values within that range.
*/
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> directions = {{1, 0}, {1, -1}, {1, 1}};
    int N;

    // O(N * 3^(N*N)) & O(N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C) {
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        if(R == N-1)
            return grid[R][C];

        int moveDown      = solveWithoutMemo(grid, R+1, C); 
        int moveDownLeft  = solveWithoutMemo(grid, R+1, C-1); 
        int moveDownRight = solveWithoutMemo(grid, R+1, C+1);

        int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
        return (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C];
    }
    
    // O(N + 3*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int C) {
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        if(R == N-1)
            return grid[R][C];

        if(dp[R][C] != INT_MAX)
            return dp[R][C];

        int moveDown      = solveWithMemo(dp, grid, R+1, C); 
        int moveDownLeft  = solveWithMemo(dp, grid, R+1, C-1); 
        int moveDownRight = solveWithMemo(dp, grid, R+1, C+1);

        int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
        return dp[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C];
    }

    // O(N + 3*N*N) & O(N*N + N)
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int C) {
        if(C < 0 || C == N || R == N)
            return INT_MAX;

        if(R == N-1)
            return grid[R][C];

        if(dp[R][C] != INT_MAX)
            return dp[R][C];

        int minPathSum = INT_MAX;

        for(const auto& dir : directions) {
            const int newR = R + dir[0];
            const int newC = C + dir[1];
            minPathSum = min(minPathSum, solveWithMemoLoop(dp, grid, newR, newC));
        }

        return dp[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C];
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();

        vector<vector<int>> dp(N, vector<int>(N, INT_MAX));
        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = solveWithMemoLoop(dp, grid, 0, C);
            result = min(result, currPathSum);
        }

        return result;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int N;

    // O(N*N) & O(N*N)
    int solveBy2DShifting(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+2, INT_MAX));

        for(int R = 0; R <= N; ++R)
            dp[R][-1+1] = INT_MAX;
        for(int R = 0; R <= N; ++R)
            dp[R][N+1] = INT_MAX;
        for(int C = 0; C <= N; ++C)
            dp[N][C+1] = INT_MAX;
    
        for(int C = 0; C < N; ++C)
            dp[N-1][C+1] = grid[N-1][C];

        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = dp[R+1][C+1]; 
                int moveDownLeft  = dp[R+1][C-1+1]; 
                int moveDownRight = dp[R+1][C+1+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                dp[R][C+1] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C]; 
            }
        }

        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = dp[0][C+1];
            result = min(result, currPathSum);
        }

        return result;
    }

    // O(N*N) & O(N*N)
    int solveBy2DTable_V1(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, INT_MAX));

        for(int R = 0; R <= N; ++R)
            dp[R][N] = INT_MAX;
        for(int C = 0; C <= N; ++C)
            dp[N][C] = INT_MAX;
    
        for(int C = 0; C < N; ++C)
            dp[N-1][C] = grid[N-1][C];

        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = dp[R+1][C]; 
                int moveDownLeft  = (C-1 < 0) ? INT_MAX : dp[R+1][C-1]; 
                int moveDownRight = dp[R+1][C+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                dp[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C]; 
            }
        }

        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = dp[0][C];
            result = min(result, currPathSum);
        }

        return result;
    }

    // O(N*N) & O(N*N)
    int solveBy2DTable_V2(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, INT_MAX));
    
        for(int C = 0; C < N; ++C)
            dp[N-1][C] = grid[N-1][C];

        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = (R+1 == N) ? INT_MAX : dp[R+1][C]; 
                int moveDownLeft  = (R+1 == N || C-1 < 0)  ? INT_MAX : dp[R+1][C-1]; 
                int moveDownRight = (R+1 == N || C+1 == N) ? INT_MAX : dp[R+1][C+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                dp[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C]; 
            }
        }

        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = dp[0][C];
            result = min(result, currPathSum);
        }

        return result;
    }

    // O(N*N) & O(N*N)
    int solveBy2DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, INT_MAX));
    
        for(int C = 0; C < N; ++C)
            dp[N-1][C] = grid[N-1][C];

        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = dp[R+1][C]; 
                int moveDownLeft  = (C-1 < 0) ? INT_MAX : dp[R+1][C-1]; 
                int moveDownRight = dp[R+1][C+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                dp[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C]; 
            }
        }

        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = dp[0][C];
            result = min(result, currPathSum);
        }

        return result;
    }

    // O(N*N) & O(2*N)
    int solveBy1DTable(const vector<vector<int>>& grid) {
        vector<int> nextRow(N+1, INT_MAX); // R + 1th row
    
        for(int C = 0; C < N; ++C)
            nextRow[C] = grid[N-1][C];

        for(int R = N-2; R >= 0; --R) {
            vector<int> currRow(N+1, INT_MAX); // Rth row

            for(int C = N-1; C >= 0; --C) {
                int moveDown      = nextRow[C]; 
                int moveDownLeft  = (C-1 < 0) ? INT_MAX : nextRow[C-1]; 
                int moveDownRight = nextRow[C+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                currRow[C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C]; 
            }

            swap(nextRow, currRow);
        }

        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = nextRow[C];
            result = min(result, currPathSum);
        }

        return result;
    }

    // O(N*N) & O(1)
    int solveWithoutTable(vector<vector<int>>& grid) {
        for(int C = 0; C < N; ++C)
            grid[N-1][C] = grid[N-1][C];

        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = (R+1 == N) ? INT_MAX : grid[R+1][C]; 
                int moveDownLeft  = (R+1 == N || C-1 < 0)  ? INT_MAX : grid[R+1][C-1]; 
                int moveDownRight = (R+1 == N || C+1 == N) ? INT_MAX : grid[R+1][C+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                grid[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C]; 
            }
        }

        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            int currPathSum = grid[0][C];
            result = min(result, currPathSum);
        }

        return result;
    }
    
    // O(N*N) & O(1)
    int solveWithoutTableConcise(vector<vector<int>>& grid) {
        int result = INT_MAX;

        for(int C = 0; C < N; ++C) {
            grid[N-1][C] = grid[N-1][C];
            int currPathSum = grid[0][C];
            if(N-1 == 0) result = min(result, currPathSum); 
        }

        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = (R+1 == N) ? INT_MAX : grid[R+1][C]; 
                int moveDownLeft  = (R+1 == N || C-1 < 0)  ? INT_MAX : grid[R+1][C-1]; 
                int moveDownRight = (R+1 == N || C+1 == N) ? INT_MAX : grid[R+1][C+1];
                int minPathSum = min({moveDown, moveDownLeft, moveDownRight});
                grid[R][C] = (minPathSum == INT_MAX) ? INT_MAX : minPathSum + grid[R][C];

                int currPathSum = grid[0][C];
                if(R == 0) result = min(result, currPathSum); 
            }
        }

        return result;
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        return solveWithoutTableConcise(grid);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
public:
    // O(N*N) & O(1)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();
        
        for(int R = N-2; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                int moveDown      = grid[R+1][C];   
                int moveDownLeft  = (C-1 >= 0) ? grid[R+1][C-1] : INT_MAX; 
                int moveDownRight = (C+1 < N)  ? grid[R+1][C+1] : INT_MAX; 
                grid[R][C] += min({moveDown, moveDownLeft, moveDownRight});
            }
        }

        return *min_element(begin(grid[0]), end(grid[0]));
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-falling-path-sum/description/
