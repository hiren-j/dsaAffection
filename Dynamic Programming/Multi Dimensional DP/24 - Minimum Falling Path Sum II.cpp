// Code to find the minimum sum of a falling path with non-zero shifts ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: I've initialized the cell values by INT_MAX: [vector<vector<int>> dp(N, vector<int>(N + 1, INT_MAX))]
                            Why INT_MAX? Why not -1 as we used before? See in the problem constraints its given that in worst case the minimum value of a cell could be -100, 
                            maximum could be 100: 
                                n == grid.length == grid[i].length
                                1 <= n <= 200
                                -99 <= grid[i][j] <= 99
                            The worst minimum sum could be -99*n = -99*200 = -19800
                            The worst maximum sum could be  99*n =  99*200 =  19800
                            This means you should not use any of the value lying in range [-19800, 19800], Its because those values are contributing in result making.
                            If we use any of that value for dp matrix initialization then this will lead our solution to hit TLE. So it's better to avoid any value of that range, 
                            So I would prefer to use lesser values than -19800, or greater values than 19800 for dp initialization, just don't use values within that range.
*/
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    int solveWithoutMemo(vector<vector<int>>& grid, int R, int skipColumn) {
        if(R == N)
            return 0;

        int minPathSum = INT_MAX;

        for(int C = 0; C < N; ++C)
            if(C != skipColumn)
                minPathSum = min(minPathSum, grid[R][C] + solveWithoutMemo(grid, R + 1, C)); 

        return minPathSum;
    }

    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int skipColumn) {
        if(R == N)
            return 0;

        if(dp[R][skipColumn] != INT_MAX)
            return dp[R][skipColumn];

        int minPathSum = INT_MAX;

        for(int C = 0; C < N; ++C)
            if(C != skipColumn)
                minPathSum = min(minPathSum, grid[R][C] + solveWithMemo(dp, grid, R + 1, C)); 

        return dp[R][skipColumn] = minPathSum;
    }

public:
    int minFallingPathSum(vector<vector<int>>& grid) {
        N = grid.size();
        vector<vector<int>> dp(N, vector<int>(N + 1, INT_MAX));
        return solveWithMemo(dp, grid, 0, N);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, INT_MAX));

        for(int skipColumn = 0; skipColumn <= N; ++skipColumn)
            dp[N][skipColumn] = 0;

        for(int R = N-1; R >= 0; --R) {
            for(int skipColumn = 0; skipColumn <= N; ++skipColumn) {
                int minPathSum = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    if(C != skipColumn) {
                        minPathSum = min(minPathSum, grid[R][C] + dp[R + 1][C]);
                    }
                }

                dp[R][skipColumn] = minPathSum;
            }
        }

        return dp[0][N];
    }

    int solveWith1DTable(vector<vector<int>>& grid) {
        vector<int> nextRow(N + 1, INT_MAX), idealRow(N + 1, INT_MAX);

        for(int skipColumn = 0; skipColumn <= N; ++skipColumn)
            nextRow[skipColumn] = 0;

        for(int R = N-1; R >= 0; --R) {
            for(int skipColumn = 0; skipColumn <= N; ++skipColumn) {
                int minPathSum = INT_MAX;

                for(int C = 0; C < N; ++C) {
                    if(C != skipColumn) {
                        minPathSum = min(minPathSum, grid[R][C] + nextRow[C]);
                    }
                }

                idealRow[skipColumn] = minPathSum;
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
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();

        for(int R = N-2; R >= 0; --R) {
            for(int C = 0; C < N; ++C) {
                int minPathSum = INT_MAX;

                for(int skipColumn = 0; skipColumn < N; ++skipColumn) {
                    if(C != skipColumn) {
                        minPathSum = min(minPathSum, grid[R + 1][skipColumn]);
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
