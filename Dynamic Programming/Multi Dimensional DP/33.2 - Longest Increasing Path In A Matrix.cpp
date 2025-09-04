
// Code to find the length of the longest increasing path in matrix. From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: For the bottom-up solution of this problem, I created it and run it but it didn't passed all the testcases.
                            So I would say there are only 2 problems in the whole series which doesn't contain the bottom-up solution 
                            due to this reason. These 2 problems lies in this folder (Multi-Dimensional DP Folder).

    REGARDING INTUITION OF THE SOLUTION: In the previous solution, we're doing backtracking, In this one we're not doing backtracking. Because If
                                         you notice then It's not required, as we need to consider strictly increasing paths, which means from a cell
                                         (R, C) we'll only move to cells (newR, newC) which contains strictly greater values, which means we'll never 
                                         end up having a stack-overflow or endless recursion.
*/
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(M*N * 4^(M*N)) & O(M*N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C) {
        int maxLength = 1;

        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                int nextLength = solveWithoutMemo(grid, newR, newC);
                maxLength = max(maxLength, nextLength + 1);
            }
        }

        return maxLength;
    }

    // O(M*N + 4*M*N) & O(2*M*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int C) {
        if(dp[R][C] != -1)
            return dp[R][C];

        int maxLength = 1;

        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                int nextLength = solveWithMemo(dp, grid, newR, newC);
                maxLength = max(maxLength, nextLength + 1);
            }
        }

        return dp[R][C] = maxLength;
    }

public:
    // Method to find the length of the longest increasing path in the matrix, using recursion with memoization - O(N*M) & O(N*M)
    int longestIncreasingPath(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        int result = 0;

        vector<vector<int>> dp(M, vector<int>(N, -1));

        for(int R = 0; R < M; ++R)
            for(int C = 0; C < N; ++C)
                result = max(result, solveWithMemo(dp, grid, R, C));

        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Topological Sort | Memoization | Matrix
Link  : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/
