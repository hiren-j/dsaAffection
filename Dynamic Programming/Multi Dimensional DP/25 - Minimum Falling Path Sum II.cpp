// Code to find the minimum sum of a falling path with non-zero shifts ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    // O(N^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int prevColumn) {
        if(R == N)
            return 0;

        int minPathSum = INT_MAX;

        for(int C = 0; C < N; ++C)
            if(C != prevColumn)
                minPathSum = min(minPathSum, grid[R][C] + solveWithoutMemo(grid, R + 1, C)); 

        return minPathSum;
    }

    // O(N^3) & O(N^2 + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int prevColumn) {
        if(R == N)
            return 0;

        if(dp[R][prevColumn] != INT_MAX)
            return dp[R][prevColumn];

        int minPathSum = INT_MAX;

        for(int C = 0; C < N; ++C)
            if(C != prevColumn)
                minPathSum = min(minPathSum, grid[R][C] + solveWithMemo(dp, grid, R + 1, C)); 

        return dp[R][prevColumn] = minPathSum;
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
    // O(N^3) & O(N^2)
    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, INT_MAX));

        for(int prevColumn = 0; prevColumn <= N; ++prevColumn) // Init first edge case
            dp[N][prevColumn] = 0;

        for(int R = N-1; R >= 0; --R) {
            for(int prevColumn = 0; prevColumn <= N; ++prevColumn) {
                int minPathSum = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    if(C != prevColumn) {
                        minPathSum = min(minPathSum, grid[R][C] + dp[R + 1][C]);
                    }
                }

                dp[R][prevColumn] = minPathSum;
            }
        }

        return dp[0][N];
    }

    // O(N^3) & O(2*N)
    int solveWith1DTable(vector<vector<int>>& grid) {
        vector<int> nextRow(N + 1, INT_MAX), idealRow(N + 1, INT_MAX);

        for(int prevColumn = 0; prevColumn <= N; ++prevColumn)
            nextRow[prevColumn] = 0;

        for(int R = N-1; R >= 0; --R) {
            for(int prevColumn = 0; prevColumn <= N; ++prevColumn) {
                int minPathSum = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    if(C != prevColumn) {
                        minPathSum = min(minPathSum, grid[R][C] + nextRow[C]);
                    }
                }

                idealRow[prevColumn] = minPathSum;
            }
            nextRow = idealRow;
        }

        return nextRow[N];
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        return solveWith1DTable(grid);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUpIntuitive {
public:
    // O(N^3) & O(1)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();

        for(int R = N-2; R >= 0; --R) {
            for(int C = 0; C < N; ++C) {
                int minPathSum = INT_MAX;

                for(int prevColumn = 0; prevColumn < N; ++prevColumn) {
                    if(C != prevColumn) {
                        minPathSum = min(minPathSum, grid[R + 1][prevColumn]);
                    }
                }

                grid[R][C] += minPathSum;
            }
        }

        return *min_element(begin(grid[0]), end(grid[0]));
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/minimum-falling-path-sum-ii/description/?envType=daily-question&envId=2024-04-26
