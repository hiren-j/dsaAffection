// Code to find the total number of paths to move the ball out of the grid boundary from the cell (startR, startC) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<vector<int>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
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

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];

            if(isValid(newR, newC)) {
                count = (count + solveWithoutMemo(maxMove - 1, newR, newC)) % MOD;
            } else {
                count = (count + 1) % MOD;
            }
        }

        return count;
    }

    // O(4*maxMove*M*N) & O(maxMove*M*N + maxMove)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int maxMove, int R, int C) {
        if(maxMove == 0)
            return 0;

        if(dp[maxMove][R][C] != -1)
            return dp[maxMove][R][C];
        
        int count = 0;

        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];

            if(isValid(newR, newC)) {
                count = (count + solveWithMemo(dp, maxMove - 1, newR, newC)) % MOD;
            } else {
                count = (count + 1) % MOD;
            }
        }

        return dp[maxMove][R][C] = count;
    }

public:
    // Method to find total number of paths, using recursion with memoization - O(maxMove*M*N) & (maxMove*M*N)
    int findPaths(int m, int n, int maxMove, int startR, int startC) {
        M = m, N = n;
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M, vector<int>(N, -1)));
        return solveWithMemo(dp, maxMove, startR, startC);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> dirs = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    const int MOD = 1e9+7;
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(GM*M*N) & (GM*M*N) : Where GM = givenMove
    int solveWith3DTable(int givenMove, int startR, int startC) {
        vector<vector<vector<int>>> dp(givenMove + 1, vector<vector<int>>(M, vector<int>(N, 0)));
        
        for(int maxMove = 1; maxMove <= givenMove; ++maxMove) {
            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];

                        if(isValid(newR, newC)) {
                            count = (count + dp[maxMove - 1][newR][newC]) % MOD;
                        } else {
                            count = (count + 1) % MOD;
                        }
                    }

                    dp[maxMove][R][C] = count;
                }
            }
        }

        return dp[givenMove][startR][startC];
    }

    // O(GM*M*N) & (2*M*N) : Where GM = givenMove
    int solveWith2DTable(int givenMove, int startR, int startC) {
        vector<vector<int>> prevRow(M, vector<int>(N)), idealRow(M, vector<int>(N));

        for(int maxMove = 1; maxMove <= givenMove; ++maxMove) {
            for(int R = M-1; R >= 0; --R) {
                for(int C = N-1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];

                        if(isValid(newR, newC)) {
                            count = (count + prevRow[newR][newC]) % MOD;
                        } else {
                            count = (count + 1) % MOD;
                        }
                    }

                    idealRow[R][C] = count;
                }
            }
            swap(prevRow, currRow);
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
