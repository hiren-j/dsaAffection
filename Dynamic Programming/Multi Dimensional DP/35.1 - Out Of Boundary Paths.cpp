// Code to find the total number of paths to move the ball out of the grid boundary from the cell (startR, startC) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const int MOD = 1e9 + 7;
    int M, N;

    // O(4^maxMove) & O(maxMove)
    int solveWithoutMemo(int maxMove, int R, int C) {
        if(R < 0 || C < 0 || R == M || C == N)
            return 1;
        
        if(maxMove == 0)
            return 0;

        int count = 0;

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];
            int nextCount = solveWithoutMemo(maxMove - 1, newR, newC);
            count = (count + nextCount) % MOD;
        }

        return count;
    }

    // O(4*maxMove*M*N) & O(maxMove*M*N + maxMove)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int maxMove, int R, int C) {
        if(R < 0 || C < 0 || R == M || C == N)
            return 1;
        
        if(maxMove == 0)
            return 0;

        if(dp[maxMove][R][C] != -1)
            return dp[maxMove][R][C];

        int count = 0;

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];
            int nextCount = solveWithMemo(dp, maxMove - 1, newR, newC);
            count = (count + nextCount) % MOD;
        }

        return dp[maxMove][R][C] = count;
    }

public:
    // Method to find total number of paths, using recursion with memoization - O(maxMove*M*N) & O(maxMove*M*N)
    int findPaths(int m, int n, int maxMove, int startR, int startC) {
        M = m, N = n;
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M, vector<int>(N, -1)));
        return solveWithMemo(dp, maxMove, startR, startC);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const int MOD = 1e9 + 7;
    int M, N;

    // O(GM*M*N) & O(GM*M*N) : Where GM = givenMove
    int solveBy3DShifting(int givenMove, int startR, int startC) {
        vector<vector<vector<int>>> dp(givenMove + 1, vector<vector<int>>(M + 2, vector<int>(N + 2, 0)));

        /*
            dp[maxMove][0][C]     - we're assuming index 0 = negative index -1
            dp[maxMove][R][0]     - we're assuming index 0 = negative index -1
            dp[maxMove][M + 1][C] - we're assuming index M+1 = Mth index 
            dp[maxMove][R][N + 1] - we're assuming index N+1 = Nth index 
        */

        // Init edge case: (R < 0 || R == M)
        for(int maxMove = 0; maxMove <= givenMove; ++maxMove) {
            for(int C = 0; C <= N+1; ++C) {
                dp[maxMove][0][C]     = 1;
                dp[maxMove][M + 1][C] = 1;
            }
        }

        // Init edge case: (C < 0 || C == N)
        for(int maxMove = 0; maxMove <= givenMove; ++maxMove) {
            for(int R = 0; R <= M+1; ++R) {
                dp[maxMove][R][0]     = 1;
                dp[maxMove][R][N + 1] = 1;
            }
        }

        for(int maxMove = 1; maxMove <= givenMove; ++maxMove) {
            for(int R = M; R >= 1; --R) {
                for(int C = N; C >= 1; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        if(newR >= 0 && newC >= 0 && newR <= M+1 && newC <= N+1) {
                            int nextCount = dp[maxMove - 1][newR][newC];
                            count = (count + nextCount) % MOD;
                        }
                    }

                    dp[maxMove][R][C] = count;
                }
            }
        }

        return dp[givenMove][startR + 1][startC + 1];
    }

    // O(GM*M*N) & O(GM*M*N) : Where GM = givenMove
    int solveBy3DTable(int givenMove, int startR, int startC) {
        vector<vector<vector<int>>> dp(givenMove + 1, vector<vector<int>>(M + 1, vector<int>(N + 1, -1)));

        for(int R = 0; R <= M; ++R)
            for(int C = 0; C <= N; ++C)
                dp[0][R][C] = 0;

        for(int maxMove = 1; maxMove <= givenMove; ++maxMove) {
            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR == M || newC == N) 
                                        ? 1 
                                        : dp[maxMove - 1][newR][newC];
                        count = (count + nextCount) % MOD;
                    }

                    dp[maxMove][R][C] = count;
                }
            }
        }

        return dp[givenMove][startR][startC];
    }

    // O(GM*M*N) & O(GM*M*N) : Where GM = givenMove
    int solveBy3DEnhanced(int givenMove, int startR, int startC) {
        vector<vector<vector<int>>> dp(givenMove + 1, vector<vector<int>>(M + 1, vector<int>(N + 1, 0)));

        for(int maxMove = 1; maxMove <= givenMove; ++maxMove) {
            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR == M || newC == N) 
                                        ? 1 
                                        : dp[maxMove - 1][newR][newC];
                        count = (count + nextCount) % MOD;
                    }

                    dp[maxMove][R][C] = count;
                }
            }
        }

        return dp[givenMove][startR][startC];
    }

    // O(GM*M*N) & O(2*M*N) : Where GM = givenMove
    int solveBy2DTable(int givenMove, int startR, int startC) {
        vector<vector<int>> prev(M + 1, vector<int>(N + 1, 0)); // maxMove - 1th table

        for(int maxMove = 1; maxMove <= givenMove; ++maxMove) {
            vector<vector<int>> curr(M + 1, vector<int>(N + 1, 0)); // maxMove table

            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR == M || newC == N) 
                                        ? 1 
                                        : prev[newR][newC];
                        count = (count + nextCount) % MOD;
                    }

                    curr[R][C] = count;
                }
            }

            swap(prev, curr);
        }

        return prev[startR][startC];
    }

public:
    int findPaths(int m, int n, int maxMove, int startR, int startC) {
        M = m, N = n;
        return solveBy2DTable(maxMove, startR, startC);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix 
Link  : https://leetcode.com/problems/out-of-boundary-paths/description/
