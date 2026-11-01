// Code to find total number of ways to reach bottom right corner from the top left corner ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    int dp[501][501][2];
    int M, N;

    int solveWithMemo(const vector<vector<int>>& grid, int R, int C, int prevDir) {
        if(R == M || C == N)
            return 0;
        
        if(R == M-1 && C == N-1)
            return 1;
        
        if(dp[R][C][prevDir] != -1)
            return dp[R][C][prevDir];
 
        int count = 0;

        if(grid[R][C] == 1) {
            count = prevDir == 1 
                    ? solveWithMemo(grid, R+1, C, 0)
                    : solveWithMemo(grid, R, C+1, 1); 
        }
        else {
            count = (count + solveWithMemo(grid, R+1, C, 0)) % MOD;
            count = (count + solveWithMemo(grid, R, C+1, 1)) % MOD;
        }

        return dp[R][C][prevDir] = count;
    }

public:
    // O(M*N) & O(M*N)
    int uniquePaths(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(grid, 0, 0, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    int M, N;

    // O(M*N) & O(M*N)
    int solveBy3DTable(const vector<vector<int>>& grid) {
        int dp[501][501][2];
        memset(dp, 0, sizeof(dp));

        dp[M-1][N-1][0] = 1;
        dp[M-1][N-1][1] = 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int prevDir = 1; prevDir >= 0; --prevDir) {
                    int count = 0;

                    if(grid[R][C] == 1) {
                        count = prevDir == 1 
                                ? dp[R+1][C][0]
                                : dp[R][C+1][1]; 
                    }
                    else {
                        count = (count + dp[R+1][C][0]) % MOD;
                        count = (count + dp[R][C+1][1]) % MOD;
                    }

                    dp[R][C][prevDir] = count;
                }
            }
        }
        
        return dp[0][0][0];
    }

    // O(M*N) & O(N)
    int solveBy2DTable(const vector<vector<int>>& grid) {
        int next[501][2];
        int curr[501][2];

        memset(next, 0, sizeof(next));
        memset(curr, 0, sizeof(curr));

        curr[N-1][0] = 1;
        curr[N-1][1] = 1;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1)
                    continue;
                for(int prevDir = 1; prevDir >= 0; --prevDir) {
                    int count = 0;

                    if(grid[R][C] == 1) {
                        count = prevDir == 1 
                                ? next[C][0]
                                : curr[C+1][1]; 
                    }
                    else {
                        count = (count + next[C][0]) % MOD;
                        count = (count + curr[C+1][1]) % MOD;
                    }

                    curr[C][prevDir] = count;
                }
            }

            swap(next, curr);
        }
        
        return next[0][0];
    }

public:
    int uniquePaths(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveBy3DTable(grid);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Matrix | Dynamic Programming
Link  : https://leetcode.com/problems/twisted-mirror-path-count/description/
