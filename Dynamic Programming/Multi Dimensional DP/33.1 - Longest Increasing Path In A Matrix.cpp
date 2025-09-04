// Code to find the length of the longest increasing path in matrix. From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed) ~ coded by Hiren

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
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    int N, M;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < N && C < M;
    }

    // O(N*M * 4^(N*M)) & O(N*M + 4*2)
    int solveWithoutMemo(vector<vector<int>>& matrix, int R, int C) {
        // Edge case: If you walk outside of the matrix or if you visit the cell which is already been visited in the path then you can't find the increasing path anymore
        if(!isValid(R, C) || matrix[R][C] == -1)
            return 0;

        int maxLength = 1, currCellValue = matrix[R][C];

        // Mark the cell (R, C) as visited
        matrix[R][C] = -1;

        // Explore all the four directions and find the length of the increasing path through cell (R, C). Among all the possibilities pick the length which is the maximum one
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            if(isValid(reachRow, reachCol) && matrix[reachRow][reachCol] > currCellValue) {
                maxLength = max(maxLength, 1 + solveWithoutMemo(matrix, reachRow, reachCol));
            }
        }

        // Mark the cell (R, C) as unvisited
        matrix[R][C] = currCellValue;

        return maxLength;
    }

    // O(N*M + 4*N*M) & O(N*M + N*M + 4*2)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& matrix, int R, int C) {
        // Edge case: If you walk outside of the matrix or if you visit the cell which is already been visited in the path then you can't find the increasing path anymore
        if(!isValid(R, C) || matrix[R][C] == -1)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(dp[R][C] != -1)
            return dp[R][C];

        int maxLength = 1, currCellValue = matrix[R][C];

        // Mark the cell (R, C) as visited
        matrix[R][C] = -1;

        // Explore all the four directions and find the length of the increasing path through cell (R, C). Among all the possibilities pick the length which is the maximum one
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            if(isValid(reachRow, reachCol) && matrix[reachRow][reachCol] > currCellValue) {
                maxLength = max(maxLength, 1 + solveWithMemo(dp, matrix, reachRow, reachCol));
            }
        }

        // Mark the cell (R, C) as unvisited
        matrix[R][C] = currCellValue;

        // Store the result value to the memoization table and then return it
        return dp[R][C] = maxLength;
    }

public:
    // Method to find the length of the longest increasing path in the matrix, using recursion with memoization - O(N*M) & O(N*M)
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        N = matrix.size(), M = matrix[0].size();
        int maxLength = 0;

        // 2D memoization table
        vector<vector<int>> dp(N, vector<int>(M, -1));

        // Consider each cell as an unique start point and find the length of the longest increasing path through each of them. Among all the possibilities pick the length which is the maximum one
        for(int R = 0; R < N; ++R)
            for(int C = 0; C < M; ++C)
                maxLength = max(maxLength, solveWithMemo(dp, matrix, R, C));

        return maxLength;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Topological Sort | Memoization | Matrix
Link  : https://leetcode.com/problems/longest-increasing-path-in-a-matrix/description/
