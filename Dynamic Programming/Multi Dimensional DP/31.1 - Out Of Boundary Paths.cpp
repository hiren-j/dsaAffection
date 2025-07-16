
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
    int findPaths(int m, int n, int maxMove, int startR, int startC) {
        M = m, N = n;
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M, vector<int>(N, -1)));
        return solveWithMemo(dp, maxMove, startR, startC);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;
    int M, N;

    // O(maxMove*M*N) & O(maxMove*M*N)    
    int solveWith3DTable(int maxMove, int startR, int startC) {
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M + 2, vector<int>(N + 2, 0)));

        /*
            dp[moves][0][C]     - we're assuming index 0 = negative index -1
            dp[moves][R][0]     - we're assuming index 0 = negative index -1
            dp[moves][M + 1][C] - we're assuming index M+1 = Mth index 
            dp[moves][R][N + 1] - we're assuming index N+1 = Nth index 
        */

        // Init edge case: (R < 0 || R == M)
        for(int moves = 0; moves <= maxMove; ++moves) {
            for(int C = 0; C <= N+1; ++C) {
                dp[moves][0][C]     = 1;
                dp[moves][M + 1][C] = 1;
            }
        }

        // Init edge case: (C < 0 || C == N)
        for(int moves = 0; moves <= maxMove; ++moves) {
            for(int R = 0; R <= M+1; ++R) {
                dp[moves][R][0]     = 1;
                dp[moves][R][N + 1] = 1;
            }
        }

        for(int moves = 1; moves <= maxMove; ++moves) {
            for(int R = 1; R <= M; ++R) {
                for(int C = 1; C <= N; ++C) {
                    int count = 0;
                    for(auto& dir : directions) {
                        int reachR = R + dir[0];
                        int reachC = C + dir[1];
                        if(reachR >= 0 && reachC >= 0 && reachR <= M+1 && reachC <= N+1) {
                            count = (count + dp[moves - 1][reachR][reachC]) % MOD;
                        }
                    }
                    dp[moves][R][C] = count;
                }
            }
        }

        return dp[maxMove][startR + 1][startC + 1];
    }

    // O(maxMove*M*N) & O(2*M*N)
    int solveWith2DTable(int maxMove, int startR, int startC) {
        vector<vector<int>> prevRow(M + 2, vector<int>(N + 2, 0)), idealRow(M + 2, vector<int>(N + 2, 0));

        // Init edge case: (R < 0 || R == M) for moves = 0
        for(int C = 0; C <= N+1; ++C) {
            prevRow[0][C]     = 1;
            prevRow[M + 1][C] = 1;
        }

        // Init edge case: (C < 0 || C == N) for moves = 0
        for(int R = 0; R <= M+1; ++R) {
            prevRow[R][0]     = 1;
            prevRow[R][N + 1] = 1;
        }
        
        for(int moves = 1; moves <= maxMove; ++moves) {
            for(int R = 1; R <= M; ++R) {
                // Init edge case: (R < 0 || R == M) for moves
                idealRow[R][0]     = 1;
                idealRow[R][N + 1] = 1;
                for(int C = 1; C <= N; ++C) {
                    // Init edge case: (C < 0 || C == N) for moves
                    idealRow[0][C]     = 1; 
                    idealRow[M + 1][C] = 1; 

                    int count = 0;
                    for(auto& dir : directions) {
                        int reachR = R + dir[0];
                        int reachC = C + dir[1];
                        if(reachR >= 0 && reachC >= 0 && reachR <= M+1 && reachC <= N+1) {
                            count = (count + prevRow[reachR][reachC]) % MOD;
                        }
                    }
                    idealRow[R][C] = count % MOD;
                }
            }
            prevRow = idealRow;
        }

        return prevRow[startR + 1][startC + 1];
    }
    
public:
    int findPaths(int m, int n, int maxMove, int startR, int startC) {   
        M = m, N = n;
        return solveWith3DTable(maxMove, startR, startC);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix 
Link  : https://leetcode.com/problems/out-of-boundary-paths/description/
