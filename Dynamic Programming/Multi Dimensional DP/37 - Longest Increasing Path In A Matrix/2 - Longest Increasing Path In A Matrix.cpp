
// Code to find the length of the longest increasing path in matrix. From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: For the bottom-up solution of this problem, I created it and run it but it didn't passed all the testcases.
                            So I would say there are only 3 problems in the whole series which doesn't contain the bottom-up solution 
                            due to this reason. These 3 problems lies in this folder (Multi-Dimensional DP Folder).
*/
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(M*N * 3^(M*N)) & O(M*N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C) {
        int maxLen = 1;

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];

            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                int nextLen = solveWithoutMemo(grid, newR, newC);
                maxLen = max(maxLen, nextLen + 1);
            }
        }

        return maxLen;
    }

    // O(4*M*N) & O(2*M*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& grid, int R, int C) {
        if(dp[R][C] != -1)
            return dp[R][C];

        int maxLen = 1;

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];

            if(isValid(newR, newC) && grid[newR][newC] > grid[R][C]) {
                int nextLen = solveWithMemo(dp, grid, newR, newC);
                maxLen = max(maxLen, nextLen + 1);
            }
        }

        return dp[R][C] = maxLen;
    }

public:
    int longestIncreasingPath(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        
        vector<vector<int>> dp(M, vector<int>(N, -1));
        int result = 0;

        for(int R = 0; R < M; ++R)
            for(int C = 0; C < N; ++C)
                result = max(result, solveWithMemo(dp, grid, R, C));

        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Topological Sort | Memoization | Matrix
Link  : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/
