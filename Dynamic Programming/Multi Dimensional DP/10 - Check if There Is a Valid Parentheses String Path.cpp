// Code to check whether there exists a valid parentheses string path to the bottom right corner of the grid or not ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N, maxStackLen;

    // O(2^(M*N)) & O(M+N)
    bool solveWithoutMemo(vector<vector<char>>& grid, int R, int C, int stackLen) {
        if(R == M || C == N)
            return false;

        // If it's a opening parentheses then assume we're pushing it to the stack hence increase the stack length by 1, else assuming poping from stack so reduce length by 1 
        (grid[R][C] == '(') ? stackLen++ : stackLen--;

        // Edge case: If the stack length becomes negative then there doesn't exist a valid path
        if(stackLen < 0)
            return false;

        // Edge case: If you reached the bottom right corner and the stack becomes empty then we've found a valid path
        if(R == M-1 && C == N-1)
            return stackLen == 0;

        bool moveRight = solveWithoutMemo(grid, R, C+1, stackLen);
        bool moveDown  = solveWithoutMemo(grid, R+1, C, stackLen);

        return moveRight || moveDown;
    }

    // O(2*M*N*MSL) & O(M*N*MSL + M+N) : Where MSL = maxStackLen
    bool solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<char>>& grid, int R, int C, int stackLen) {
        if(R == M || C == N)
            return false;

        // If it's a opening parentheses then assume we're pushing it to the stack hence increase the stack length by 1, else assuming poping from stack so reduce length by 1 
        (grid[R][C] == '(') ? stackLen++ : stackLen--;

        // Edge case: If the stack length becomes negative then there doesn't exist a valid path
        if(stackLen < 0)
            return false;

        // Edge case: If you reached the bottom right corner and the stack becomes empty then we've found a valid path
        if(R == M-1 && C == N-1)
            return stackLen == 0;

        if(dp[R][C][stackLen] != -1)
            return dp[R][C][stackLen];

        bool moveRight = solveWithMemo(dp, grid, R, C+1, stackLen);
        bool moveDown  = solveWithMemo(dp, grid, R+1, C, stackLen);

        return dp[R][C][stackLen] = moveRight || moveDown;
    }

public:
    // Method to check whether there exists a valid parentheses string path, using recursion with memoization - O(M*N*MSL) & O(M*N*MSL) : Where MSL = maxStackLen
    bool hasValidPath(vector<vector<char>>& grid) {
        M = grid.size(), N = grid[0].size(), maxStackLen = M+N;     
        if(grid[M-1][N-1] == '(') 
            return false;
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(maxStackLen, -1)));
        return solveWithMemo(dp, grid, 0, 0, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(M*N*MSL) & O(M*N*MSL)
    int solveWith3DTable(vector<vector<char>>& grid) {
        vector<vector<vector<bool>>> dp(M+1, vector<vector<bool>>(N+1, vector<bool>(maxStackLen, false)));

        // Init third edge case: Only valid if we have exactly 1 opening before
        dp[M-1][N-1][1] = true;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) 
                    continue;
                for(int stackLen = maxStackLen-1; stackLen >= 0; --stackLen) {
                    int newLen = (grid[R][C] == '(') ? stackLen + 1 : stackLen - 1; 
                    if(newLen >= 0 && newLen < maxStackLen) {
                        bool moveRight = dp[R][C+1][newLen];
                        bool moveDown  = dp[R+1][C][newLen];
                        dp[R][C][stackLen] = moveRight || moveDown;
                    }
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*MSL) & O(2*N*MSL)
    int solveWith2DTable(vector<vector<char>>& grid) {
        vector<vector<bool>> nextRow(N+1, vector<bool>(maxStackLen, false));
        vector<vector<bool>> idealRow(N+1, vector<bool>(maxStackLen, false));

        // Init third edge case: Only valid if we have exactly 1 opening before
        idealRow[N-1][1] = true;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) 
                    continue;
                for(int stackLen = maxStackLen-1; stackLen >= 0; --stackLen) {
                    int newLen = (grid[R][C] == '(') ? stackLen + 1 : stackLen - 1; 
                    if(newLen >= 0 && newLen < maxStackLen) {
                        bool moveRight = idealRow[C+1][newLen];
                        bool moveDown  = nextRow[C][newLen];
                        idealRow[C][stackLen] = moveRight || moveDown;
                    } else {
                        idealRow[C][stackLen] = false;
                    }
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0][0];
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        M = grid.size(), N = grid[0].size(), maxStackLen = M+N;     
        if(grid[M-1][N-1] == '(') 
            return false;
        return solveWith2DTable(grid);
    }
};  

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/description/
