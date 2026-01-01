// Code to find the maximum number of cherries collected by both the robots by following the mentioned rules ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> directions = {{1, -1}, {1, 0}, {1, 1}};
    int M, N;

    // O(9^(M*N)) & O(M)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R, int C1, int C2) {
        if(R == M || C1 < 0 || C1 == N || C2 < 0 || C2 == N)
            return 0;

        int maxPathSum = 0;

        for(const auto& dir1 : directions) {
            const int newR  = R + dir1[0];
            const int newC1 = C1 + dir1[1];

            for(const auto& dir2 : directions) {
                const int newC2 = C2 + dir2[1];
                int nextSideSum = solveWithoutMemo(grid, newR, newC1, newC2);
                maxPathSum = max(maxPathSum, nextSideSum);
            }
        }

        maxPathSum += (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
        return maxPathSum;
    }

    // O(9*M*N*N) & O(M*N*N + M)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<vector<int>>& grid, int R, int C1, int C2) {
        if(R == M || C1 < 0 || C1 == N || C2 < 0 || C2 == N)
            return 0;

        if(dp[R][C1][C2] != -1)
            return dp[R][C1][C2];

        int maxPathSum = 0;

        for(const auto& dir1 : directions) {
            const int newR = R + dir1[0];
            const int newC1 = C1 + dir1[1];

            for(const auto& dir2 : directions) {
                const int newR2 = R + dir2[0];
                const int newC2 = C2 + dir2[1];
                int nextSideSum = solveWithMemo(dp, grid, newR, newC1, newC2);
                maxPathSum = max(maxPathSum, nextSideSum);
            }
        }

        maxPathSum += (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
        return dp[R][C1][C2] = maxPathSum;
    }

public:
    // Method to find maximum cherries can collect, using recursion with memoization - O(M*N*N) & O(M*N*N)
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        
        vector<vector<vector<int>>> dp(M, 
                vector<vector<int>>(N, 
                        vector<int>(N, -1)));

        return solveWithMemo(dp, grid, 0, 0, N-1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const vector<vector<int>> directions = {{1, -1}, {1, 0}, {1, 1}};
    int M, N;

    // O(M*N*N) & O(M*N*N)
    int solveBy3DShifting(const vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M+1, 
                vector<vector<int>>(N+2, 
                        vector<int>(N+2, -1)));
        // R == M
        for(int C1 = 0; C1 <= N; ++C1)
            for(int C2 = 0; C2 <= N; ++C2)
                dp[M][C1+1][C2+1] = 0;
        
        // C1 < 0
        for(int R = 0; R <= M; ++R)
            for(int C2 = 0; C2 <= N; ++C2)
                dp[R][-1+1][C2+1] = 0;

        // C1 == N
        for(int R = 0; R <= M; ++R)
            for(int C2 = 0; C2 <= N; ++C2)
                dp[R][N+1][C2+1] = 0;

        // C2 == N
        for(int R = 0; R <= M; ++R)
            for(int C1 = 0; C1 <= N; ++C1)
                dp[R][C1+1][N+1] = 0;
        
        // C2 < 0
        for(int R = 0; R <= M; ++R)
            for(int C1 = 0; C1 <= N; ++C1)
                dp[R][C1+1][-1+1] = 0;

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int C2 = 0; C2 <= N-1; ++C2) {
                    int maxPathSum = 0;

                    for(const auto& dir1 : directions) {
                        const int newR = R + dir1[0];
                        const int newC1 = C1 + dir1[1];

                        for(const auto& dir2 : directions) {
                            const int newR2 = R + dir2[0];
                            const int newC2 = C2 + dir2[1];
                            int nextSideSum = dp[newR][newC1 + 1][newC2 + 1];
                            maxPathSum = max(maxPathSum, nextSideSum);
                        }
                    }

                    maxPathSum += (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
                    dp[R][C1+1][C2+1] = maxPathSum;
                }
            }
        }

        return dp[0][0+1][N-1+1];
    }

    // O(M*N*N) & O(M*N*N)
    int solveBy3DTable(const vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M+1, 
                vector<vector<int>>(N+1, 
                        vector<int>(N+1, -1)));
        // R == M
        for(int C1 = 0; C1 <= N; ++C1)
            for(int C2 = 0; C2 <= N; ++C2)
                dp[M][C1][C2] = 0;
        
        // C1 == N
        for(int R = 0; R <= M; ++R)
            for(int C2 = 0; C2 <= N; ++C2)
                dp[R][N][C2] = 0;

        // C2 == N
        for(int R = 0; R <= M; ++R)
            for(int C1 = 0; C1 <= N; ++C1)
                dp[R][C1][N] = 0;
        
        for(int R = M-1; R >= 0; --R) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int C2 = 0; C2 <= N-1; ++C2) {
                    int maxPathSum = 0;

                    for(const auto& dir1 : directions) {
                        const int newR = R + dir1[0];
                        const int newC1 = C1 + dir1[1];

                        for(const auto& dir2 : directions) {
                            const int newR2 = R + dir2[0];
                            const int newC2 = C2 + dir2[1];
                            int nextSideSum = (newC1 < 0 || newC2 < 0) ? 0 : dp[newR][newC1][newC2];
                            maxPathSum = max(maxPathSum, nextSideSum);
                        }
                    }

                    maxPathSum += (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
                    dp[R][C1][C2] = maxPathSum;
                }
            }
        }

        return dp[0][0][N-1];
    }

    // O(M*N*N) & O(M*N*N)
    int solveBy3DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M+1, 
                vector<vector<int>>(N+1, 
                        vector<int>(N+1, 0)));
                        
        for(int R = M-1; R >= 0; --R) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int C2 = 0; C2 <= N-1; ++C2) {
                    int maxPathSum = 0;

                    for(const auto& dir1 : directions) {
                        const int newR = R + dir1[0];
                        const int newC1 = C1 + dir1[1];

                        for(const auto& dir2 : directions) {
                            const int newR2 = R + dir2[0];
                            const int newC2 = C2 + dir2[1];
                            int nextSideSum = (newC1 < 0 || newC2 < 0) ? 0 : dp[newR][newC1][newC2];
                            maxPathSum = max(maxPathSum, nextSideSum);
                        }
                    }

                    maxPathSum += (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
                    dp[R][C1][C2] = maxPathSum;
                }
            }
        }

        return dp[0][0][N-1];
    }

    // O(M*N*N) & O(2*N*N)
    int solveBy2DTable(const vector<vector<int>>& grid) { 
        vector<vector<int>> next(N+1, vector<int>(N+1, 0)); // R + 1th table
        vector<vector<int>> curr(N+1, vector<int>(N+1, 0)); // Rth table
                        
        for(int R = M-1; R >= 0; --R) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int C2 = 0; C2 <= N-1; ++C2) {
                    int maxPathSum = 0;

                    for(const auto& dir1 : directions) {
                        const int newR = R + dir1[0];
                        const int newC1 = C1 + dir1[1];

                        for(const auto& dir2 : directions) {
                            const int newR2 = R + dir2[0];
                            const int newC2 = C2 + dir2[1];
                            int nextSideSum = (newC1 < 0 || newC2 < 0) ? 0 : next[newC1][newC2];
                            maxPathSum = max(maxPathSum, nextSideSum);
                        }
                    }

                    maxPathSum += (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
                    curr[C1][C2] = maxPathSum;
                }
            }
            swap(next, curr);
        }

        return next[0][N-1];
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveBy2DTable(grid);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/cherry-pickup-ii/description/
