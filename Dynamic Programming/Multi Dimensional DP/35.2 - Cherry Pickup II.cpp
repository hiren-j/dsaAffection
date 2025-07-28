// Code to find the maximum number of cherries collected by both the robots by following the mentioned rules ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{1,0}, {1,-1}, {1,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(9^(M*N)) & O(M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C1, int C2) {
        if(!isValid(R, C1) || !isValid(R, C2))
            return 0;

        int cellCherry = (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
        int maxFromAll = 0;

        for(auto& dir1 : directions) {
            int newR = R + 1;
            for(auto& dir2 : directions) {
                int newC1 = C1 + dir1[1];
                int newC2 = C2 + dir2[1];
                int nextCherry = solveWithoutMemo(grid, newR, newC1, newC2);
                maxFromAll = max(maxFromAll, nextCherry + cellCherry);
            }
        }

        return maxFromAll;
    }

    // O(9*M*N*N) & O(M*N*N + M)
    int solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& grid, int R, int C1, int C2) {
        if(!isValid(R, C1) || !isValid(R, C2))
            return 0;

        if(dp[R][C1][C2] != -1)
            return dp[R][C1][C2];

        int cellCherry = (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
        int maxFromAll = 0;

        for(auto& dir1 : directions) {
            int newR = R + 1;
            for(auto& dir2 : directions) {
                int newC1 = C1 + dir1[1];
                int newC2 = C2 + dir2[1];
                int nextCherry = solveWithMemo(dp, grid, newR, newC1, newC2);
                maxFromAll = max(maxFromAll, nextCherry + cellCherry);
            }
        }

        return dp[R][C1][C2] = maxFromAll;
    }

public:
    // Method to find maximum cherries can collect, using recursion with memoization - O(M*N*N) & O(M*N*N)
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(N, -1)));
        return solveWithMemo(dp, grid, 0, 0, N-1);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{1,0}, {1,-1}, {1,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // O(M*N*N) & O(M*N*N)
    int solveWith3DTable(vector<vector<int>>& grid) {
        vector<vector<vector<int>>> dp(M, vector<vector<int>>(N, vector<int>(N, -1)));

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int C2 = 0; C2 <= N-1; ++C2) {
                    int cellCherry = (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
                    int maxFromAll = 0;

                    for(auto& dir1 : directions) {
                        int newR = R + 1;
                        for(auto& dir2 : directions) {
                            int newC1 = C1 + dir1[1];
                            int newC2 = C2 + dir2[1];
                            int nextCherry = (!isValid(newR, newC1) || !isValid(newR, newC2)) ? 0 : dp[newR][newC1][newC2];
                            maxFromAll = max(maxFromAll, nextCherry + cellCherry);
                        }
                    }

                    dp[R][C1][C2] = maxFromAll;
                }
            }
        }

        return dp[0][0][N-1];
    }

    // O(M*N*N) & O(2*N*N)
    int solveWith2DTable(vector<vector<int>>& grid) {
        vector<vector<int>> nextRow(N, vector<int>(N, -1)), idealRow(N, vector<int>(N, -1));        

        for(int R = M-1; R >= 0; --R) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int C2 = 0; C2 <= N-1; ++C2) {
                    int cellCherry = (C1 == C2) ? grid[R][C1] : grid[R][C1] + grid[R][C2];
                    int maxFromAll = 0;
                    
                    for(auto& dir1 : directions) {
                        int newR = R + 1;
                        for(auto& dir2 : directions) {
                            int newC1 = C1 + dir1[1];
                            int newC2 = C2 + dir2[1];
                            int nextCherry = (!isValid(newR, newC1) || !isValid(newR, newC2)) ? 0 : nextRow[newC1][newC2];
                            maxFromAll = max(maxFromAll, nextCherry + cellCherry);
                        }
                    }

                    idealRow[C1][C2] = maxFromAll;
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0][N-1];
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveWith2DTable(grid);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/cherry-pickup-ii/description/
