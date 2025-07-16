// Code to find the total number of paths to move the ball out of the grid boundary from the cell (startR, startC) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;
    int M, N;

    // O(4^maxMove) & O(maxMove)
    int solveWithoutMemo(int maxMove, int R, int C) {
        // Edge case: If the ball moves out of the grid boundary then you've one way
        if(R < 0 || C < 0 || R == M || C == N)
            return 1;

        // Edge case: If all moves are over then it's not possible to move the ball anymore
        if(maxMove == 0)
            return 0;

        int count = 0;

        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];
            count      = (count + solveWithoutMemo(maxMove - 1, reachR, reachC)) % MOD;
        }

        return count;
    }

    // O(4 * maxMove*M*N) & O(maxMove*M*N + maxMove)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int maxMove, int R, int C) {
        // Edge case: If the ball moves out of the grid boundary then you've one way
        if(R < 0 || C < 0 || R == M || C == N)
            return 1;

        // Edge case: If all moves are over then it's not possible to move the ball anymore
        if(maxMove == 0)
            return 0;

        if(dp[maxMove][R][C] != -1)
            return dp[maxMove][R][C];

        int count = 0;

        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];
            count      = (count + solveWithMemo(dp, maxMove - 1, reachR, reachC)) % MOD;
        }

        return dp[maxMove][R][C] = count;
    }

public:
    // Method to find the number of paths, using recursion with memoization - O(maxMove*M*N) & (maxMove*M*N)
    int findPaths(int m, int n, int maxMove, int startR, int startCol) {
        M = m, N = n;
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M, vector<int>(N, -1)));
        return solveWithMemo(dp, maxMove, startR, startCol);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;

public:
    // Method to find the number of paths, using 3D tabulation - O(maxMove*M*N) & O(maxMove*M*N)
    int findPaths(int M, int N, int maxMove, int startR, int startCol) {
        // 3D DP table
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M + 2, vector<int>(N + 2, 0)));

        /*
            dp[move][0][C]     - we're assuming index 0 as negative index
            dp[move][R][0]     - we're assuming index 0 as negative index
            dp[move][M + 1][C] - we're assuming index M+1 as Mth index 
            dp[move][R][N + 1] - we're assuming index N+1 as Nth index 
        */

        // Initialize edge case: (R < 0 || R == M)
        for(int move = 0; move <= maxMove; ++move) {
            for(int C = 0; C <= N+1; ++C) {
                dp[move][0][C]     = 1;
                dp[move][M + 1][C] = 1;
            }
        }

        // Initialize edge case: (C < 0 || C == N)
        for(int move = 0; move <= maxMove; ++move) {
            for(int R = 0; R <= M+1; ++R) {
                dp[move][R][0]     = 1;
                dp[move][R][N + 1] = 1;
            }
        }

        for(int move = 1; move <= maxMove; ++move) {
            for(int R = 1; R <= M; ++R) {
                for(int C = 1; C <= N; ++C) {
                    int count = 0;
                    for(auto& dir : directions) {
                        int reachR = R + dir[0];
                        int reachC = C + dir[1];
                        if(reachR >= 0 && reachC >= 0 && reachR <= M+1 && reachC <= N+1) {
                            count = (count + dp[move - 1][reachR][reachC]) % MOD;
                        }
                    }
                    dp[move][R][C] = count % MOD;
                }
            }
        }

        return dp[maxMove][startR + 1][startCol + 1];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix 
Link  : https://leetcode.com/problems/out-of-boundary-paths/description/
