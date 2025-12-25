// Code to find the maximum number of cherries collected by both the robots by following the mentioned rules ~ coded by vHiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> directions = {{1, -1}, {1, 0}, {1, 1}};
    int M, N;

    // O(9^(M*N)) & O(M)
    int solveWithoutMemo(const vector<vector<int>>& grid, int R1, int C1, int R2, int C2) {
        if(R1 == M || C1 < 0 || C1 == N || R2 == M || C2 < 0 || C2 == N)
            return 0;

        int maxPathSum = 0;

        for(const auto& dir1 : directions) {
            const int newR1 = R1 + dir1[0];
            const int newC1 = C1 + dir1[1];

            for(const auto& dir2 : directions) {
                const int newR2 = R2 + dir2[0];
                const int newC2 = C2 + dir2[1];
                int nextSideSum = solveWithoutMemo(grid, newR1, newC1, newR2, newC2);
                maxPathSum = max(maxPathSum, nextSideSum);
            }
        }

        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
        return maxPathSum;
    }

    // O(9*M*N*M*N) & O(M*N*M*N + M)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, const vector<vector<int>>& grid, int R1, int C1, int R2, int C2) {
        if(R1 == M || C1 < 0 || C1 == N || R2 == M || C2 < 0 || C2 == N)
            return 0;

        if(dp[R1][C1][R2][C2] != -1)
            return dp[R1][C1][R2][C2];

        int maxPathSum = 0;

        for(const auto& dir1 : directions) {
            const int newR1 = R1 + dir1[0];
            const int newC1 = C1 + dir1[1];

            for(const auto& dir2 : directions) {
                const int newR2 = R2 + dir2[0];
                const int newC2 = C2 + dir2[1];
                int nextSideSum = solveWithMemo(dp, grid, newR1, newC1, newR2, newC2);
                maxPathSum = max(maxPathSum, nextSideSum);
            }
        }

        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
        return dp[R1][C1][R2][C2] = maxPathSum;
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();

        vector<vector<vector<vector<int>>>> dp(M, 
                vector<vector<vector<int>>>(N, 
                        vector<vector<int>>(M, 
                                vector<int>(N, -1))));

        return solveWithMemo(dp, grid, 0, 0, 0, N-1);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const vector<vector<int>> directions = {{1, -1}, {1, 0}, {1, 1}};
    int M, N;

    // O(M*N*M*N) & O(M*N*M*N)
    int solveBy4DShifting(const vector<vector<int>>& grid) {
        vector<vector<vector<vector<int>>>> dp(M+1, 
                vector<vector<vector<int>>>(N+2, 
                        vector<vector<int>>(M+1, 
                                vector<int>(N+2, -1))));
        // R1 == M
        for(int C1 = 0; C1 <= N; ++C1)
            for(int R2 = 0; R2 <= M; ++R2)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[M][C1+1][R2][C2+1] = 0;

        // C1 < 0
        for(int R1 = 0; R1 <= M; ++R1)
            for(int R2 = 0; R2 <= M; ++R2)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[R1][-1+1][R2][C2+1] = 0;

        // C1 == N
        for(int R1 = 0; R1 <= M; ++R1)
            for(int R2 = 0; R2 <= M; ++R2)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[R1][N+1][R2][C2+1] = 0;

        // R2 == M
        for(int R1 = 0; R1 <= M; ++R1)
            for(int C1 = 0; C1 <= N; ++C1)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[R1][C1+1][M][C2+1] = 0;
         
        // C2 == N
        for(int R1 = 0; R1 <= M; ++R1)
            for(int C1 = 0; C1 <= N; ++C1)
                for(int R2 = 0; R2 <= M; ++R2)
                    dp[R1][C1+1][R2][N+1] = 0;

        // C2 < 0
        for(int R1 = 0; R1 <= M; ++R1)
            for(int C1 = 0; C1 <= N; ++C1)
                for(int R2 = 0; R2 <= M; ++R2)
                    dp[R1][C1+1][R2][-1+1] = 0;

        for(int R1 = M-1; R1 >= 0; --R1) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int maxPathSum = 0;

                        for(const auto& dir1 : directions) {
                            const int newR1 = R1 + dir1[0];
                            const int newC1 = C1 + dir1[1];

                            for(const auto& dir2 : directions) {
                                const int newR2 = R2 + dir2[0];
                                const int newC2 = C2 + dir2[1];
                                int nextSideSum = dp[newR1][newC1 + 1][newR2][newC2 + 1];
                                maxPathSum = max(maxPathSum, nextSideSum);
                            }
                        }

                        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        dp[R1][C1+1][R2][C2+1] = maxPathSum;
                    }
                }
            }
        }

        return dp[0][0+1][0][N-1+1];
    }

    // O(M*N*M*N) & O(M*N*M*N)
    int solveBy4DTable_V1(const vector<vector<int>>& grid) {
        vector<vector<vector<vector<int>>>> dp(M+1, 
                vector<vector<vector<int>>>(N+1, 
                        vector<vector<int>>(M+1, 
                                vector<int>(N+1, -1))));
        // R1 == M
        for(int C1 = 0; C1 <= N; ++C1)
            for(int R2 = 0; R2 <= M; ++R2)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[M][C1][R2][C2] = 0;
    
        // C1 == N
        for(int R1 = 0; R1 <= M; ++R1)
            for(int R2 = 0; R2 <= M; ++R2)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[R1][N][R2][C2] = 0;

        // R2 == M
        for(int R1 = 0; R1 <= M; ++R1)
            for(int C1 = 0; C1 <= N; ++C1)
                for(int C2 = 0; C2 <= N; ++C2)
                    dp[R1][C1][M][C2] = 0;
         
        // C2 == N
        for(int R1 = 0; R1 <= M; ++R1)
            for(int C1 = 0; C1 <= N; ++C1)
                for(int R2 = 0; R2 <= M; ++R2)
                    dp[R1][C1][R2][N] = 0;

        for(int R1 = M-1; R1 >= 0; --R1) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int maxPathSum = 0;

                        for(const auto& dir1 : directions) {
                            const int newR1 = R1 + dir1[0];
                            const int newC1 = C1 + dir1[1];

                            for(const auto& dir2 : directions) {
                                const int newR2 = R2 + dir2[0];
                                const int newC2 = C2 + dir2[1];
                                int nextSideSum = (newC1 < 0 || newC2 < 0) ? 0 : dp[newR1][newC1][newR2][newC2];
                                maxPathSum = max(maxPathSum, nextSideSum);
                            }
                        }

                        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        dp[R1][C1][R2][C2] = maxPathSum;
                    }
                }
            }
        }

        return dp[0][0][0][N-1];
    }

    // O(M*N*M*N) & O(M*N*M*N)
    int solveBy4DTable_V2(const vector<vector<int>>& grid) {
        vector<vector<vector<vector<int>>>> dp(M+1, 
                vector<vector<vector<int>>>(N+1, 
                        vector<vector<int>>(M+1, 
                                vector<int>(N+1, -1))));
                                
        for(int R1 = M-1; R1 >= 0; --R1) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int maxPathSum = 0;

                        for(const auto& dir1 : directions) {
                            const int newR1 = R1 + dir1[0];
                            const int newC1 = C1 + dir1[1];

                            for(const auto& dir2 : directions) {
                                const int newR2 = R2 + dir2[0];
                                const int newC2 = C2 + dir2[1];
                                int nextSideSum = (newR1 == M || newC1 < 0 || newC1 == N || newR2 == M || newC2 < 0 || newC2 == N) 
                                                ? 0 
                                                : dp[newR1][newC1][newR2][newC2];
                                maxPathSum = max(maxPathSum, nextSideSum);
                            }
                        }

                        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        dp[R1][C1][R2][C2] = maxPathSum;
                    }
                }
            }
        }

        return dp[0][0][0][N-1];
    }
    
   // O(M*N*M*N) & O(M*N*M*N)
    int solveBy4DEnhanced(const vector<vector<int>>& grid) {
        vector<vector<vector<vector<int>>>> dp(M+1, 
                vector<vector<vector<int>>>(N+1, 
                        vector<vector<int>>(M+1, 
                                vector<int>(N+1, 0))));

        for(int R1 = M-1; R1 >= 0; --R1) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int maxPathSum = 0;

                        for(const auto& dir1 : directions) {
                            const int newR1 = R1 + dir1[0];
                            const int newC1 = C1 + dir1[1];

                            for(const auto& dir2 : directions) {
                                const int newR2 = R2 + dir2[0];
                                const int newC2 = C2 + dir2[1];
                                int nextSideSum = (newC1 < 0 || newC2 < 0) ? 0 : dp[newR1][newC1][newR2][newC2];
                                maxPathSum = max(maxPathSum, nextSideSum);
                            }
                        }

                        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        dp[R1][C1][R2][C2] = maxPathSum;
                    }
                }
            }
        }

        return dp[0][0][0][N-1];
    }

    // O(M*N*M*N) & O(2*N*M*N)
    int solveBy3DTable(const vector<vector<int>>& grid) {
        // R + 1th table
        vector<vector<vector<int>>> next(N+1, 
                vector<vector<int>>(M+1, 
                        vector<int>(N+1, 0)));

        for(int R1 = M-1; R1 >= 0; --R1) {
            // Rth table
            vector<vector<vector<int>>> curr(N+1, 
                    vector<vector<int>>(M+1, 
                            vector<int>(N+1, 0)));

            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int maxPathSum = 0;

                        for(const auto& dir1 : directions) {
                            const int newR1 = R1 + dir1[0];
                            const int newC1 = C1 + dir1[1];

                            for(const auto& dir2 : directions) {
                                const int newR2 = R2 + dir2[0];
                                const int newC2 = C2 + dir2[1];
                                int nextSideSum = (newC1 < 0 || newC2 < 0) ? 0 : next[newC1][newR2][newC2];
                                maxPathSum = max(maxPathSum, nextSideSum);
                            }
                        }

                        maxPathSum += (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        curr[C1][R2][C2] = maxPathSum;
                    }
                }
            }

            swap(next, curr);
        }

        return next[0][0][N-1];
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveBy3DTable(grid);
    }
};
// Note: This solution will lead to TLE

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/cherry-pickup-ii/description/
