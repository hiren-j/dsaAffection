// Program to find the minimum cost of a path that starts from any cell in the first row and ends at any cell in the last row ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    int N, M;

    // O(M^(N*M)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, vector<vector<int>>& moveCost, int R, int prevCol) {
        // Edge case: If all the rows are exhausted then 
        if(R == N)
            return 0;

        int minPathCost = INT_MAX;

        // Explore all the paths from the cell and update the result value by the minimum cost
        for(int C = 0; C < M; ++C) {
            int currPathCost = grid[R][C] + solveWithoutMemo(grid, moveCost, R+1, C);
            if(prevCol != -1) {
                currPathCost += moveCost[grid[R-1][prevCol]][C];
            }
            minPathCost = min(minPathCost, currPathCost);
        }

        return minPathCost;
    }

    // O(M*N*M) & O(N*M + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, vector<vector<int>>& moveCost, int R, int prevCol) {
        // 
        if(R == N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][prevCol + 1] != -1)
            return memory[R][prevCol + 1];
        
        int minPathCost = INT_MAX;

        // Explore all the paths from the cell and update the result value by the minimum cost
        for(int C = 0; C < M; ++C) {
            int currPathCost = grid[R][C] + solveWithMemo(memory, grid, moveCost, R+1, C);
            if(prevCol != -1) {
                currPathCost += moveCost[grid[R-1][prevCol]][C];
            }
            minPathCost = min(minPathCost, currPathCost);
        }

        // Store the result value to the memoization table and then return it
        return memory[R][prevCol + 1] = minPathCost;
    }

public:
    // Method to find the minimum cost, using recursion with memoization :-
    int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        N = grid.size(), M = grid[0].size();
        vector<vector<int>> memory(N, vector<int>(M+1, -1));
        return solveWithMemo(memory, grid, moveCost, 0, -1);
    }
};

---------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the minimum cost, using 2D tabulation - O(M*N*M) & O(N*M)
    int minPathCost_V1(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int N = grid.size(), M = grid[0].size();

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int prevCol = M-1; prevCol >= -1; --prevCol) {
                int minPathCost = INT_MAX;

                for(int C = 0; C < M; ++C) {
                    int currPathCost = grid[R][C] + dp[R+1][C+1];
                    if(prevCol != -1 && R-1 >= 0) {
                        currPathCost += moveCost[grid[R-1][prevCol]][C];
                    }
                    minPathCost = min(minPathCost, currPathCost);
                }

                dp[R][prevCol + 1] = minPathCost;
            }
        }

        return dp[0][0];
    }

    // Method to find the minimum cost, using 1D tabulation - O(M*N*M) & O(M)
    int minPathCost_V2(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
        int N = grid.size(), M = grid[0].size();

        vector<int> nextRow(M+1, 0), currRow(M+1, 0);

        for(int R = N-1; R >= 0; --R) {
            for(int prevCol = M-1; prevCol >= -1; --prevCol) {
                int minPathCost = INT_MAX;

                for(int C = 0; C < M; ++C) {
                    int currPathCost = grid[R][C] + nextRow[C+1];
                    if(prevCol != -1 && R-1 >= 0) {
                        currPathCost += moveCost[grid[R-1][prevCol]][C];
                    }
                    minPathCost = min(minPathCost, currPathCost);
                }

                currRow[prevCol + 1] = minPathCost;
            }
            nextRow = currRow;
        }

        return currRow[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------

Link   : https://leetcode.com/problems/minimum-path-cost-in-a-grid/description/
Topics : Array | Dynamic Programming | Matrix
