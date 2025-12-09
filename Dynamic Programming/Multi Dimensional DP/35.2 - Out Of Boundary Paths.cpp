// Code to find the total number of paths to move the ball out of the grid boundary from the cell (startR, startC) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(4^maxMove) & O(maxMove)
    int solveWithoutMemo(int maxMove, int R, int C) {
        if(maxMove == 0)
            return 0;

        int count = 0;

        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];

            if(isValid(reachR, reachC)) {
                count = (count + solveWithoutMemo(maxMove - 1, reachR, reachC)) % MOD;
            } else {
                count = (count + 1) % MOD;
            }
        }

        return count;
    }

    // O(4 * maxMove*M*N) & O(maxMove*M*N + maxMove)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int maxMove, int R, int C) {
        if(maxMove == 0)
            return 0;

        if(dp[maxMove][R][C] != -1)
            return dp[maxMove][R][C];
        
        int count = 0;

        for(auto& dir : directions) {
            int reachR = R + dir[0];
            int reachC = C + dir[1];

            if(isValid(reachR, reachC)) {
                count = (count + solveWithMemo(dp, maxMove - 1, reachR, reachC)) % MOD;
            } else {
                count = (count + 1) % MOD;
            }
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

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(maxMove*M*N) & (maxMove*M*N)
    int solveWith3DTable(int maxMove, int startR, int startC) {
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M, vector<int>(N, 0)));
        
        for(int moves = 1; moves <= maxMove; ++moves) {
            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(auto& dir : directions) {
                        int reachR = R + dir[0];
                        int reachC = C + dir[1];

                        if(isValid(reachR, reachC)) {
                            count = (count + dp[moves - 1][reachR][reachC]) % MOD;
                        } else {
                            count = (count + 1) % MOD;
                        }
                    }

                    dp[moves][R][C] = count;
                }
            }
        }

        return dp[maxMove][startR][startC];
    }

    // O(maxMove*M*N) & (2*M*N)
    int solveWith2DTable(int maxMove, int startR, int startC) {
        vector<vector<int>> prevRow(M, vector<int>(N)), idealRow(M, vector<int>(N));

        for(int moves = 1; moves <= maxMove; ++moves) {
            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(auto& dir : directions) {
                        int reachR = R + dir[0];
                        int reachC = C + dir[1];

                        if(isValid(reachR, reachC)) {
                            count = (count + prevRow[reachR][reachC]) % MOD;
                        } else {
                            count = (count + 1) % MOD;
                        }
                    }

                    idealRow[R][C] = count;
                }
            }
            prevRow = idealRow;
        }

        return prevRow[startR][startC];
    }

public:
    int findPaths(int m, int n, int maxMove, int startR, int startC) {
        M = m, N = n;
        return solveWith2DTable(maxMove, startR, startC);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Matrix 
Link  : https://leetcode.com/problems/out-of-boundary-paths/description/
