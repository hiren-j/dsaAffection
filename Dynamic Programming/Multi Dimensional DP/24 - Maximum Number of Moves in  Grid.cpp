// Code to find the maximum number of moves that you can perform in the grid. You can start at any cell in the first column of the matrix, and traverse the grid in the following way: From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    vector<vector<int>> directions = {{-1,1}, {0,1}, {1,1}};
    int N, M;

    bool isValid(int R, int C) {
        return R >= 0 && R < N && C < M;
    }

    // O(N * 3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        // Edge case: If you walk outside of the grid then you can't perform any moves
        if(!isValid(R, C))
            return INT_MIN;

        int maxMoves = 0;

        // Explore all the directions from the current cell and move to the cell with strictly bigger values and update the result by the maximum value
        for(auto& dir : directions) {
            int reachRow  = R + dir[0];
            int reachCol  = C + dir[1];
            int nextMoves = INT_MIN;

            if(isValid(reachRow, reachCol) && grid[reachRow][reachCol] > grid[R][C]) {
                nextMoves = solveWithoutMemo(grid, reachRow, reachCol);
            }
            if(nextMoves != INT_MIN) {
                maxMoves = max(maxMoves, 1 + nextMoves);
            }
        }

        return maxMoves;
    }
    
    // O(N + 3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int R, int C) {
        // Edge case: If you walk outside of the grid then you can't perform any moves
        if(!isValid(R, C))
            return INT_MIN;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];

        int maxMoves = 0;

        // Explore all the directions from the current cell and move to the cell with strictly bigger values and update the result by the maximum value
        for(auto& dir : directions) {
            int reachRow  = R + dir[0];
            int reachCol  = C + dir[1];
            int nextMoves = INT_MIN;

            if(isValid(reachRow, reachCol) && grid[reachRow][reachCol] > grid[R][C]) {
                nextMoves = solveWithMemo(memory, grid, reachRow, reachCol);
            }
            if(nextMoves != INT_MIN) {
                maxMoves = max(maxMoves, 1 + nextMoves);
            }
        }

        // Store the value to the memoization table and then return it
        return memory[R][C] = maxMoves;
    }

public:
    // Method to find the maximum number of moves that you can perform in the grid, using recursion with memoization - O(N*M) & O(N*M)
    int maxMoves(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size(); 

        int result = 0;

        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(M, -1));

        // Start from the first column of each row and update the result by the maximum value
        for(int R = 0; R < N; ++R)  
            result = max(result, solveWithMemo(memory, grid, R, 0));

        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/description/
