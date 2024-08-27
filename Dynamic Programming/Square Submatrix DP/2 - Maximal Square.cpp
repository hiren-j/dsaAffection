// Code to find the area of the largest square containing only 1's ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;
    
    // O(N*M * 3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<char>>& grid, int R, int C) {
        // Edge case: If at any point you move outside of the grid or you're at a cell containing zero, then you can't find and square submatrix of all ones
        if(R == N || C == M || grid[R][C] == '0')
            return 0;

        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithoutMemo(grid, R, C+1);   // Is to move right
        int moveDown      = solveWithoutMemo(grid, R+1, C);   // Is to move down
        int moveDownRight = solveWithoutMemo(grid, R+1, C+1); // Is to move diagonally down

        // A single cell having one is considered a square submatrix of 1x1. Now suppose a 2x2 submatrix in which if you're at the first cell then the remaining three cells must contain one to become a valid submatrix. So to correctly consider this we need to figure the minimum element from them and any of them is zero then that particular cell is not a valid square submatrix and cannot be a part of the square of the first cell
        return 1 + min({moveRight, moveDown, moveDownRight});
    }

    // O(N*M + 3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<char>>& grid, int R, int C) {
        // Edge case: If at any point you move outside of the grid or you're at a cell containing zero, then you can't find and square submatrix of all ones
        if(R == N || C == M || grid[R][C] == '0')
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];
        
        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithMemo(memory, grid, R, C+1);   // Is to move right
        int moveDown      = solveWithMemo(memory, grid, R+1, C);   // Is to move down
        int moveDownRight = solveWithMemo(memory, grid, R+1, C+1); // Is to move diagonally down

        // Store the result value to the memoization table and then return it
        return memory[R][C] = 1 + min({moveRight, moveDown, moveDownRight});
    }

public:
    // Method to find the area of the largest square containing only 1's, using recursion with memoization :-
    int maximalSquare(vector<vector<char>>& grid) {
        N = grid.size(), M = grid[0].size();

        // Stores the side of the largest square containing only 1's
        int maxSide = 0;

        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(M, -1));

        // Consider each square cell of 1x1 and find the side of the largest square through each of them and then store the maximum among all 
        for(int R = 0; R < N; ++R) 
            for(int C = 0; C < M; ++C) 
                if(grid[R][C] == '1') 
                    maxSide = max(maxSide, solveWithMemo(memory, grid, R, C));

        // Return the result value
        return maxSide * maxSide;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the area of the largest square containing only 1's, using 2D tabulation - O(N*M + N*M) & O(N*M)
    int maximalSquare_V1(vector<vector<char>>& grid) {
        int N = grid.size(), M = grid[0].size();

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == '0')
                    continue;
                int moveRight     = dp[R][C+1]; 
                int moveDown      = dp[R+1][C];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});
            }
        }

        int maxSide = 0;

        for(int R = 0; R < N; ++R) 
            for(int C = 0; C < M; ++C) 
                if(grid[R][C] == '1') 
                    maxSide = max(maxSide, dp[R][C]);

        return maxSide * maxSide;
    }

    // #2 Method to find the area of the largest square containing only 1's, using 2D tabulation - O(N*M) & O(N*M)
    int maximalSquare_V2(vector<vector<char>>& grid) {
        int N = grid.size(), M = grid[0].size(), maxSide = 0;

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == '0')
                    continue;

                int moveRight     = dp[R][C+1]; 
                int moveDown      = dp[R+1][C];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});
                
                maxSide = max(maxSide, dp[R][C]);
            }
        }

        return maxSide * maxSide;
    }

    // #3 Method to find the area of the largest square containing only 1's, using 1D tabulation - O(N*M) & O(M)
    int maximalSquare_V3(vector<vector<char>>& grid) {
        int N = grid.size(), M = grid[0].size(), maxSide = 0;

        vector<int> nextRow(M+1, 0), currRow(M+1, 0);

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == '0') {
                    currRow[C] = 0;
                    continue;
                }

                int moveRight     = currRow[C+1]; 
                int moveDown      = nextRow[C];
                int moveDownRight = nextRow[C+1];
                currRow[C] = 1 + min({moveRight, moveDown, moveDownRight});

                maxSide = max(maxSide, currRow[C]);
            }
            nextRow = currRow;
        }

        return maxSide * maxSide;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/maximal-square/description/
