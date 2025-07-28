// Code to find the maximum number of cherries collected by both the robots by following the mentioned rules ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<vector<int>> directions = {{1,0}, {1,-1}, {1,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    // 
    int solveWithoutMemo(vector<vector<int>>& grid, int R1, int C1, int R2, int C2) {
        if(!isValid(R1, C1) || !isValid(R2, C2))
            return 0;

        int cellCherry = (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
        int maxFromAll = 0;

        for(auto& dir1 : directions) { // Explore all 3 possibilities of robot2 from each possibility of robot1
            int newR1 = R1 + dir1[0];
            int newC1 = C1 + dir1[1];
            
            for(auto& dir2 : directions) {
                int newR2 = R2 + dir2[0];
                int newC2 = C2 + dir2[1];
                int nextCherry = solveWithoutMemo(grid, newR1, newC1, newR2, newC2);
                maxFromAll = max(maxFromAll, nextCherry + cellCherry);
            }
        }

        return maxFromAll;
    }

    // 
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, vector<vector<int>>& grid, int R1, int C1, int R2, int C2) {
        if(!isValid(R1, C1) || !isValid(R2, C2))
            return 0;

        if(dp[R1][C1][R2][C2] != -1)
            return dp[R1][C1][R2][C2];

        int cellCherry = (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
        int maxFromAll = 0;

        for(auto& dir1 : directions) { // Explore all 3 possibilities of robot2 from each possibility of robot1
            int newR1 = R1 + dir1[0];
            int newC1 = C1 + dir1[1];
            
            for(auto& dir2 : directions) {
                int newR2 = R2 + dir2[0];
                int newC2 = C2 + dir2[1];
                int nextCherry = solveWithMemo(dp, grid, newR1, newC1, newR2, newC2);
                maxFromAll = max(maxFromAll, nextCherry + cellCherry);
            }
        }

        return dp[R1][C1][R2][C2] = maxFromAll;
    }

public:
    // Method to find maximum cherries can collect, using recursion with memoization - O() & O()
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<vector<int>>>> dp(M, vector<vector<vector<int>>>(N, vector<vector<int>>(M, vector<int>(N, -1))));
        return solveWithMemo(dp, grid, 0, 0, 0, N-1);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<vector<int>> directions = {{1,0}, {1,-1}, {1,1}};
    int M, N;

    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < M && C < N;
    }

    int solveWith4DTable(vector<vector<int>>& grid) {
        vector<vector<vector<vector<int>>>> dp(M, vector<vector<vector<int>>>(N, vector<vector<int>>(M, vector<int>(N, -1))));

        for(int R1 = M-1; R1 >= 0; --R1) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int cellCherry = (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        int maxFromAll = 0;

                        for(auto& dir1 : directions) {
                            int newR1 = R1 + dir1[0];
                            int newC1 = C1 + dir1[1];

                            for(auto& dir2 : directions) {
                                int newR2 = R2 + dir2[0];
                                int newC2 = C2 + dir2[1];
                                int nextCherry = (!isValid(newR1, newC1) || !isValid(newR2, newC2)) ? 0 : dp[newR1][newC1][newR2][newC2];
                                maxFromAll = max(maxFromAll, nextCherry + cellCherry);
                            }
                        }

                        dp[R1][C1][R2][C2] = maxFromAll;
                    }
                }
            }
        }

        return dp[0][0][0][N-1];
    }

    int solveWith3DTable(vector<vector<int>>& grid) {
        vector<vector<vector<int>>> nextRow(N, vector<vector<int>>(M, vector<int>(N, -1)));
        vector<vector<vector<int>>> idealRow(N, vector<vector<int>>(M, vector<int>(N, -1)));
        
        for(int R1 = M-1; R1 >= 0; --R1) {
            for(int C1 = N-1; C1 >= 0; --C1) {
                for(int R2 = M-1; R2 >= 0; --R2) {
                    for(int C2 = 0; C2 <= N-1; ++C2) {
                        int cellCherry = (C1 == C2) ? grid[R1][C1] : grid[R1][C1] + grid[R2][C2];
                        int maxFromAll = 0;

                        for(auto& dir1 : directions) {
                            int newR1 = R1 + dir1[0];
                            int newC1 = C1 + dir1[1];

                            for(auto& dir2 : directions) {
                                int newR2 = R2 + dir2[0];
                                int newC2 = C2 + dir2[1];
                                int nextCherry = (!isValid(newR1, newC1) || !isValid(newR2, newC2)) ? 0 : nextRow[newC1][newR2][newC2];
                                maxFromAll = max(maxFromAll, nextCherry + cellCherry);
                            }
                        }

                        idealRow[C1][R2][C2] = maxFromAll;
                    }
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0][0][N-1];
    }

public:
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        return solveWith3DTable(grid);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/cherry-pickup-ii/description/
