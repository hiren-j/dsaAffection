// Code to find the number of possible unique paths that the robot can take to reach the bottom-right corner ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the number of possible unique paths, using recursion with memoization - O(N*M) & O(N*M)
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();
        if(grid[N-1][M-1] == 1) return 0;
        vector<vector<int>> memory(N, vector<int>(M, -1));
        return solveWithMemo(memory, grid, N, M, 0, 0);
    }

private:
    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If all the cells are exhausted or the cell contains an obstacle then you've no valid way
        if(R == N || C == M || grid[R][C] == 1)
            return 0;

        // Edge case: If reached the bottom up corner then you've one valid way
        if(R == N-1 && C == M-1)
            return 1;   
        
        // Memoization table: If the current state is already computed then return the computed value 
        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities to perform at each cell
        int moveRight = solveWithMemo(memory, grid, N, M, R, C+1); // Is to move right
        int moveDown  = solveWithMemo(memory, grid, N, M, R+1, C); // Is to move down

        // Store the result value to the memoization table and then return it
        return memory[R][C] = moveRight + moveDown;
    }

    // O(2^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If all the cells are exhausted or the cell contains an obstacle then you've no valid way
        if(R == N || C == M || grid[R][C] == 1)
            return 0;

        // Edge case: If reached the bottom up corner then you've one valid way
        if(R == N-1 && C == M-1)
            return 1;   
        
        // There are always two possibilities to perform at each cell
        int moveRight = solveWithoutMemo(grid, N, M, R, C+1); // Is to move right
        int moveDown  = solveWithoutMemo(grid, N, M, R+1, C); // Is to move down

        // Return the result value
        return moveRight + moveDown;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the number of possible unique paths, using 2D tabulation - O(N*M) & O(N*M)
    int uniquePathsWithObstacles_V1(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // Early exit: If the destination cell contains an obstacle then you can't reach it
        if(grid[N-1][M-1] == 1)
            return 0;

        // 2D DP table
        vector<vector<long>> dp(N+1, vector<long>(M+1, 0));

        // Initialize the edge case: If all the cells are exhausted or the cell contains an obstacle then you've no valid way
        dp[N-1][M-1] = 1;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if((R == N-1 && C == M-1) || grid[R][C] == 1)
                    continue;   
                long moveRight = dp[R][C+1]; 
                long moveDown  = dp[R+1][C]; 
                dp[R][C] = moveRight + moveDown;
            }
        }

        // Return the result value
        return dp[0][0];
    }

    // #2 Method to find the number of possible unique paths, using 1D tabulation - O(N*M) & O(M)
    int uniquePathsWithObstacles_V2(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();

        // Early exit: If the destination cell contains an obstacle then you can't reach it
        if(grid[N-1][M-1] == 1)
            return 0;

        // 1D DP tables
        vector<long> nextRow(M+1, 0), currRow(M+1, 0);

        // Initialize the edge case: If all the cells are exhausted or the cell contains an obstacle then you've no valid way
        currRow[M-1] = 1;

        // Fill the rest of the table
        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(R == N-1 && C == M-1) {   
                    continue;   
                }
                else if(grid[R][C] == 1) {
                    currRow[C] = 0;
                }
                else {
                    long moveRight = currRow[C+1]; 
                    long moveDown  = nextRow[C]; 
                    currRow[C] = moveRight + moveDown;
                }
            }
            nextRow = currRow;
        }

        // Return the result value
        return currRow[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Links : https://leetcode.com/problems/unique-paths-ii/description
        https://cses.fi/problemset/task/1638
