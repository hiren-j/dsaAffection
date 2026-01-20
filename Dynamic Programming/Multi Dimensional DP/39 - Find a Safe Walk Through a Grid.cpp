// Code to check is if you can reach the final cell with a health value of 1 or more. You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1). You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive. Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
  DON'T IGNORE MUST READ: Creating a correct bottom-up solution for this problem is not possible and also memoization could also fail in such problems! Why? Watch The Video Lecture to know about it.
                          And I would say there are only 3 problems in the whole series which doesn't contain the bottom-up solution. These 3 problems lies in this folder (Multi-Dimensional DP Folder).
*/
  
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && R < M && C >= 0 && C < N;
    }

    // O(3^(M*N)) & O(M*N)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C, int health) {
        health -= (grid[R][C] == 1);
        
        if(health <= 0)
            return false;
        
        if(R == M-1 && C == N-1)
            return true;

        const int original = grid[R][C];
        grid[R][C] = -1;           // Mark cell (R, C) as visited

        for(const auto& D : dirs) {
            const int newR = R + D[0];
            const int newC = C + D[1];

            if(isValid(newR, newC) && grid[newR][newC] != -1) {
                bool canReachCorner = solveWithoutMemo(grid, newR, newC, health);
                if(canReachCorner) return true;
            }
        }
        
        grid[R][C] = original; // Mark cell (R, C) as unvisited
        return false;
    }

    // O(3*M*N*H) & O(M*N*H + M*N) : Where H = health
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& grid, int R, int C, int health) {
        health -= (grid[R][C] == 1);
        
        if(health <= 0)
            return false;
        
        if(R == M-1 && C == N-1)
            return true;

        if(dp[R][C][health] != -1)
            return dp[R][C][health];

        const int original = grid[R][C];
        grid[R][C] = -1;          // Mark cell (R, C) as visited

        for(const auto& D : dirs) {
            const int newR = R + D[0];
            const int newC = C + D[1];

            if(isValid(newR, newC) && grid[newR][newC] != -1) {
                bool canReachCorner = solveWithMemo(dp, grid, newR, newC, health);
                if(canReachCorner) return dp[R][C][health] = true;
            }
        }
        
        grid[R][C] = original; // Mark cell (R, C) as unvisited
        return dp[R][C][health] = false;
    }

public:
    // Method to check if you can reach final cell with a health value of 1 or more, using recursion with memoization - O(M*N*H) & (M*N*H) : Where H = health
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(health + 1, -1)));
        return solveWithMemo(dp, grid, 0, 0, health);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Memoization | Matrix
Link  : https://leetcode.com/problems/find-a-safe-walk-through-a-grid/
