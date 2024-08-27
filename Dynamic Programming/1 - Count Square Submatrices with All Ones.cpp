// Code to find how many square submatrices are there with all ones ~ coded by Hiren 

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;
    
    // O(N*M * 3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        // Edge case: If at any point you move outside of the grid or you're at a cell containing zero, then you can't find and square submatrix of all ones
        if(R == N || C == M || grid[R][C] == 0)
            return 0;

        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithoutMemo(grid, R, C+1);   // Is to move right
        int moveDown      = solveWithoutMemo(grid, R+1, C);   // Is to move down
        int moveDownRight = solveWithoutMemo(grid, R+1, C+1); // Is to move diagonally down

        // A single cell having one is considered a square submatrix of 1x1. Now suppose a 2x2 submatrix in which if you're at the first cell then the remaining three cells must contain one to become a valid submatrix. So to correctly consider this we need to figure the minimum element from them and any of them is zero then that particular cell is not a valid square submatrix and cannot be a part of the square of the first cell
        return 1 + min({moveRight, moveDown, moveDownRight});
    }

    // O(N*M + 3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int R, int C) {
        // Edge case: If at any point you move outside of the grid or you're at a cell containing zero, then you can't find and square submatrix of all ones
        if(R == N || C == M || grid[R][C] == 0)
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
    // Method to count the total square submatrices having all ones, using recursion with memoization :-
    int countSquares(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();

        // Stores the result value
        int count = 0;

        // 2D memoization table
        vector<vector<int>> memory(N, vector<int>(M, -1));

        // Iterate and consider each square submatrix of 1x1 and find how many square submatrices can be made from that cell
        for(int R = 0; R < N; ++R)
            for(int C = 0; C < M; ++C)
                if(grid[R][C] == 1)
                    count += solveWithMemo(memory, grid, R, C);

        // Return the result value
        return count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to count the total square submatrices having all ones, using 2D tabulation - O(N*M + N*M) & O(N*M)
    int countSquares_V1(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size();
        
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0)
                    continue;
                int moveRight     = dp[R][C+1];
                int moveDown      = dp[R+1][C];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});   
            }
        }

        int count = 0;

        for(int R = 0; R < N; ++R)
            for(int C = 0; C < M; ++C)
                if(grid[R][C] == 1)
                    count += dp[R][C];

        return count;
    }

    // #2 Method to count the total square submatrices having all ones, using 2D tabulation - O(N*M) & O(N*M)
    int countSquares_V2(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size(), count = 0;

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0)
                    continue;
                    
                int moveRight     = dp[R][C+1];
                int moveDown      = dp[R+1][C];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});  

                count += dp[R][C];
            }
        }


        return count;
    }

    // #3 Method to count the total square submatrices having all ones, using 1D tabulation - O(N*M) & O(M)
    int countSquares_V3(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size(), count = 0;

        vector<int> nextRow(M+1, 0), currRow(M+1, 0);

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0) {
                    currRow[C] = 0; 
                    continue;
                }
                    
                int moveRight     = currRow[C+1];
                int moveDown      = nextRow[C];
                int moveDownRight = nextRow[C+1];
                currRow[C] = 1 + min({moveRight, moveDown, moveDownRight});  

                count += currRow[C];
            }
            nextRow = currRow;
        }


        return count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/count-square-submatrices-with-all-ones/description/
