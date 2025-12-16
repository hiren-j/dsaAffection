// Code to check whether there exists a valid parentheses string path to the bottom right corner of the grid or not ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int M, N, LIMIT;

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

    // O(2*M*N*L) & O(M*N*L + M+N) : Where L = LIMIT
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
    // Method to check whether there exists a valid parentheses string path, using recursion with memoization - O(M*N*L) & O(M*N*L) : Where L = LIMIT
    bool hasValidPath(vector<vector<char>>& grid) {
        M = grid.size(), N = grid[0].size(), LIMIT = M+N;     
        if(grid[0][0] == ')' || grid[M-1][N-1] == '(') 
                return false;
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(LIMIT, -1)));
        return solveWithMemo(dp, grid, 0, 0, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int LIMIT;
    int M, N;

    // O(M*N*L) & O(M*N*L)
    bool solveBy3DTable(const vector<vector<char>>& grid) {
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(LIMIT, -1)));

        for(int C = 0; C <= N; ++C)
            for(int stackLen = 0; stackLen < LIMIT; ++stackLen)
                dp[M][C][stackLen] = false;

        for(int R = 0; R <= M; ++R)
            for(int stackLen = 0; stackLen < LIMIT; ++stackLen)
                dp[R][N][stackLen] = false;

        for(int stackLen = 0; stackLen < LIMIT; ++stackLen)
            dp[M-1][N-1][stackLen] = (grid[M-1][N-1] == '(' && stackLen + 1 == 0) || 
                                     (grid[M-1][N-1] == ')' && stackLen - 1 == 0);
        
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                for(int stackLen = LIMIT-1; stackLen >= 0; --stackLen) {
                    if(R == M-1 && C == N-1)
                        continue;
                    int newLen     = grid[R][C] == '(' ? stackLen + 1 : stackLen - 1;
                    bool moveRight = (newLen < 0 || newLen >= LIMIT) ? false : dp[R][C+1][newLen];
                    bool moveDown  = (newLen < 0 || newLen >= LIMIT) ? false : dp[R+1][C][newLen];
                    dp[R][C][stackLen] = (moveRight || moveDown);
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*L) & O(M*N*L)
    bool solveBy3DEnhanced(const vector<vector<char>>& grid) {
        vector<vector<vector<bool>>> dp(M+1, vector<vector<bool>>(N+1, vector<bool>(LIMIT, false)));

        for(int stackLen = 0; stackLen < LIMIT; ++stackLen)
            dp[M-1][N-1][stackLen] = (grid[M-1][N-1] == '(' && stackLen + 1 == 0) || 
                                     (grid[M-1][N-1] == ')' && stackLen - 1 == 0);
        
        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                for(int stackLen = LIMIT-1; stackLen >= 0; --stackLen) {
                    if(R == M-1 && C == N-1)
                        continue;
                    int newLen     = grid[R][C] == '(' ? stackLen + 1 : stackLen - 1;
                    bool moveRight = (newLen < 0 || newLen >= LIMIT) ? false : dp[R][C+1][newLen];
                    bool moveDown  = (newLen < 0 || newLen >= LIMIT) ? false : dp[R+1][C][newLen];
                    dp[R][C][stackLen] = (moveRight || moveDown);
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*L) & O(2*N*L)
    bool solveBy2DTable(const vector<vector<char>>& grid) {
        vector<vector<bool>> next(N+1, vector<bool>(LIMIT, false)); // R + 1th table
        
        for(int R = M-1; R >= 0; --R) {
            vector<vector<bool>> curr(N+1, vector<bool>(LIMIT, false)); // Rth table

            for(int C = N-1; C >= 0; --C) {
                for(int stackLen = LIMIT-1; stackLen >= 0; --stackLen) {
                    if(R == M-1 && C == N-1) {
                        curr[N-1][stackLen] = (grid[M-1][N-1] == '(' && stackLen + 1 == 0) || 
                                              (grid[M-1][N-1] == ')' && stackLen - 1 == 0);
                        continue;
                    }
                    int newLen     = grid[R][C] == '(' ? stackLen + 1 : stackLen - 1;
                    bool moveRight = (newLen < 0 || newLen >= LIMIT) ? false : curr[C+1][newLen];
                    bool moveDown  = (newLen < 0 || newLen >= LIMIT) ? false : next[C][newLen];
                    curr[C][stackLen] = (moveRight || moveDown);
                }
            }

            swap(next, curr);
        }

        return next[0][0];
    }

public:
    bool hasValidPath(vector<vector<char>>& grid) {
        M = grid.size(), N = grid[0].size(), LIMIT = M+N;
        if(grid[0][0] == ')' || grid[M-1][N-1] == '(') 
            return false;
        return solveBy2DTable(grid);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/description/
