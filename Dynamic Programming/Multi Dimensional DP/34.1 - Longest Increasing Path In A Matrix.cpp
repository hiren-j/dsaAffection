// Code to find the length of the longest increasing path in grid. From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: As you work on this problem, you'll notice that there isn't a bottom-up solution provided. 
                            This is one of the problem in the multi-dimensional folder where I couldn't get the bottom-up approach to pass all the test cases. 
                            The issue wasn't with time limits but with incorrect results. So, I've only included the top-down (memoized) solution for this problem. 
                            There are only 2 problem in the entire DP series without bottom-up solution. 
                            Creating a correct bottom-up solution for this problem is not possible because of how cells are visited and marked during recursion. Even if you convert the memoized (top-down) solution to bottom-up, it won’t work properly. 
                            The issue comes from the fact that, in the recursive solution, cells are marked as "visited" and "unvisited" at different stages, which can't be handled in a bottom-up approach. In many cases, even memoization fails when handling these visited/unvisited states. 
                            However, for this specific problem, memoization works fine, but the bottom-up approach still cannot manage the visited/unvisited states correctly, the thing is grid state is also changing each and every time, 
                            if we try to memoize the grid too the we'll end up using a lot of space, more clearly MLE.
*/
  
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(M*N * 4^(M*N)) & O(M*N)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(!isValid(R, C) || grid[R][C] == -1)
            return 0;

        int maxLength = 1, val = grid[R][C];
        grid[R][C] = -1; // Mark cell (R, C) as visited

        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];
            if(isValid(reachR, reachC) && grid[reachR][reachC] > val) {
                int nextLength = solveWithoutMemo(grid, reachR, reachC);
                maxLength = max(maxLength, nextLength + 1);
            }
        }

        grid[R][C] = val; // Mark cell (R, C) as unvisited
        return maxLength;
    }

    // O(M*N + 4*M*N) & O(2*M*N)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int C) {
        if(!isValid(R, C) || grid[R][C] == -1)
            return 0;

        if(dp[R][C] != -1)
            return dp[R][C];

        int maxLength = 1, val = grid[R][C];
        grid[R][C] = -1; // Mark cell (R, C) as visited

        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];
            if(isValid(reachR, reachC) && grid[reachR][reachC] > val) {
                int nextLength = solveWithMemo(dp, grid, reachR, reachC);
                maxLength = max(maxLength, nextLength + 1);
            }
        }

        grid[R][C] = val; // Mark cell (R, C) as unvisited
        return dp[R][C] = maxLength;
    }

public:
    // Method to find length of longest increasing path in grid, using recursion with memoization - O(M*N) & O(M*N)
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

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Topological Sort | Memoization | Matrix
Link  : https://leetcode.com/problems/longest-increasing-path-in-a-grid/description/
