// Code to find the number of paths where the sum of the elements on the path is divisible by k. Since the answer may be very large, return it modulo 1e9 + 7 ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    int M, N, K;

    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C, int pathSum) {
        if(R == M || C == N)
            return 0;
        
        if(R == M-1 && C == N-1) 
            return (pathSum + grid[R][C]) % K == 0;

        int moveRight = solveWithoutMemo(grid, R, C+1, (pathSum + grid[R][C]) % K);
        int moveDown  = solveWithoutMemo(grid, R+1, C, (pathSum + grid[R][C]) % K);

        return (moveRight + moveDown) % MOD;
    }

    // O(2*M*N*K) & O(M*N*K + M+N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<vector<int>>& grid, int R, int C, int pathSum) {
        if(R == M || C == N)
            return 0;

        if(R == M-1 && C == N-1) 
            return (pathSum + grid[R][C]) % K == 0;

        if(dp[R][C][pathSum] != -1)
            return dp[R][C][pathSum];

        int moveRight = solveWithMemo(dp, grid, R, C+1, (pathSum + grid[R][C]) % K);
        int moveDown  = solveWithMemo(dp, grid, R+1, C, (pathSum + grid[R][C]) % K);

        return dp[R][C][pathSum] = (moveRight + moveDown) % MOD;
    }

public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        M = grid.size(), N = grid[0].size(), K = k;
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(K, -1)));
        return solveWithMemo(dp, grid, 0, 0, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    int M, N, K;

    // O(M*N*K) & O(M*N*K)
    int solveBy3DTable(const vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(K, -1)));

        for(int C = 0; C <= N; ++C)
            for(int pathSum = 0; pathSum < K; ++pathSum)
                dp[M][C][pathSum] = 0;

        for(int R = 0; R <= M; ++R)
            for(int pathSum = 0; pathSum < K; ++pathSum)
                dp[R][N][pathSum] = 0;

        for(int pathSum = 0; pathSum < K; ++pathSum)
            dp[M-1][N-1][pathSum] = (pathSum + grid[M-1][N-1]) % K == 0;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) 
                    continue;
                for(int pathSum = K-1; pathSum >= 0; --pathSum) {
                    int moveRight = dp[R][C+1][(pathSum + grid[R][C]) % K];
                    int moveDown  = dp[R+1][C][(pathSum + grid[R][C]) % K];
                    dp[R][C][pathSum] = (moveRight + moveDown) % MOD;
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*K) & O(M*N*K)
    int solveBy3DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(K, 0)));

        for(int pathSum = 0; pathSum < K; ++pathSum)
            dp[M-1][N-1][pathSum] = (pathSum + grid[M-1][N-1]) % K == 0;

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == M-1 && C == N-1) 
                    continue;
                for(int pathSum = K-1; pathSum >= 0; --pathSum) {
                    int moveRight = dp[R][C+1][(pathSum + grid[R][C]) % K];
                    int moveDown  = dp[R+1][C][(pathSum + grid[R][C]) % K];
                    dp[R][C][pathSum] = (moveRight + moveDown) % MOD;
                }
            }
        }

        return dp[0][0][0];
    }

    // O(M*N*K) & O(2*N*K)
    int solveBy2DTable(const vector<vector<int>>& grid) {
        vector<vector<int>> next(N+1, vector<int>(K, 0)); // R + 1th table
        
        for(int R = M-1; R >= 0; --R) {
            vector<vector<int>> curr(N+1, vector<int>(K, 0)); // Rth table
            
            for(int C = N-1; C >= 0; --C) {
                for(int pathSum = K-1; pathSum >= 0; --pathSum) {
                    if(R == M-1 && C == N-1) {
                        curr[N-1][pathSum] = (pathSum + grid[M-1][N-1]) % K == 0;
                    }
                    else {
                        int moveRight = curr[C+1][(pathSum + grid[R][C]) % K];
                        int moveDown  = next[C][(pathSum + grid[R][C]) % K];
                        curr[C][pathSum] = (moveRight + moveDown) % MOD;
                    }
                }
            }

            swap(next, curr);
        }

        return next[0][0];
    }

public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        M = grid.size(), N = grid[0].size(), K = k;
        return solveBy2DTable(grid);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix | Weekly Contest 314
Link  : https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/description/
