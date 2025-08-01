// Code to check is if you can reach the final cell with a health value of 1 or more. You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1). You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive. Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1 ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
  DON'T IGNORE MUST READ: Creating a correct bottom-up solution for this problem is not possible because of how cells are visited and marked during recursion. Even if you convert the memoized (top-down) solution to bottom-up, it won’t work properly. 
                          The issue comes from the fact that, in the recursive solution, cells are marked as "visited" and "unvisited" at different stages, which can't be handled in a bottom-up approach. In many cases, even memoization fails when handling these visited/unvisited states. 
                          However, for this specific problem, memoization works fine, but the bottom-up approach still cannot manage the visited/unvisited states correctly, the thing is grid state is also changing each and every time, if we try to memoize the grid too the we'll end up using a lot of space, more clearly MLE.
*/
  
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(4^(M*N)) & O(M*N)
    bool solveWithoutMemo(vector<vector<int>>& grid, int R, int C, int health) {            
        // Edge case: If you walk outside of the grid or if the cell is already visited then return false
        if(!isValid(R, C) || grid[R][C] == -1) 
            return false;

        // If the cell is unsafe then reduce the health by 1 
        if(grid[R][C] == 1)
            health--;
        
        if(health <= 0)
            return false;

        // Edge case: If you can reach the lower-right corner with a health value of 1 or more, then return true
        if(R == M-1 && C == N-1)
            return true;

        int val = grid[R][C];
        grid[R][C] = -1; // Mark cell (R, C) as visited

        // Check all the possible directions and return true if any direction returns true
        for(auto& dir : directions) { 
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(solveWithoutMemo(grid, newR, newC, health)) {
                return true;
            } 
        }

        grid[R][C] = val; // Mark cell (R, C) as unvisited
        return false;
    }

    // O(4*M*N*H) & O(M*N*H + M*N)
    bool solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& grid, int R, int C, int health) {            
        // Edge case: If you walk outside of the grid or if the cell is already visited then return false
        if(!isValid(R, C) || grid[R][C] == -1) 
            return false;

        // If the cell is unsafe then reduce the health by 1 
        if(grid[R][C] == 1)
            health--;
        
        if(health <= 0)
            return false;

        // Edge case: If you can reach the lower-right corner with a health value of 1 or more, then return true
        if(R == M-1 && C == N-1)
            return true;

        if(dp[R][C][health] != -1)
            return dp[R][C][health];

        int val = grid[R][C];
        grid[R][C] = -1; // Mark cell (R, C) as visited

        // Check all the possible directions and return true if any direction returns true
        for(auto& dir : directions) { 
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(solveWithMemo(dp, grid, newR, newC, health)) {
                return dp[R][C][health] = true;
            } 
        }

        grid[R][C] = val; // Mark cell (R, C) as unvisited
        return dp[R][C][health] = false;
    }

public:
    // Method to check if you can reach the final cell with a health value of 1 or more, using recursion with memoization - O(M*N*H) & (M*N*H) : Where H = health
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(health + 1, -1)));
        return solveWithMemo(dp, grid, 0, 0, health);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Depth-First Search | Breadth-First Search | Graph | Memoization | Matrix
Link  : https://leetcode.com/problems/find-a-safe-walk-through-a-grid/
