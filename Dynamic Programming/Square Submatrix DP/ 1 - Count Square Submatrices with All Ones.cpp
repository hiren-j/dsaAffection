// Code to find how many square submatrices are there with all ones ~ coded by Hiren 

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N, M;
    
    // O(3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C) {
        if(R == N || C == M || grid[R][C] == 0)
            return 0;

        int moveRight     = solveWithoutMemo(grid, R, C+1);   
        int moveDown      = solveWithoutMemo(grid, R+1, C);   
        int moveDownRight = solveWithoutMemo(grid, R+1, C+1); 

        return 1 + min({moveRight, moveDown, moveDownRight});
    }
    // This function will be called O(N*M) times, hence overall time: O(N*M * 3^(N*M))

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& grid, int R, int C) {
        if(R == N || C == M || grid[R][C] == 0)
            return 0;

        if(dp[R][C] != -1)
            return dp[R][C];
        
        int moveRight     = solveWithMemo(dp, grid, R, C+1);   
        int moveDown      = solveWithMemo(dp, grid, R+1, C);   
        int moveDownRight = solveWithMemo(dp, grid, R+1, C+1); 

        return dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});
    }

public:
    int countSquares(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();

        vector<vector<int>> dp(N, vector<int>(M, -1));
        int count = 0;
        
        for(int R = 0; R < N; ++R)
            for(int C = 0; C < M; ++C)
                if(grid[R][C] == 1)
                    count += solveWithMemo(dp, grid, R, C);

        return count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N, M;

    int solveBy2DTable(const vector<vector<int>>& grid) {
        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0)
                    continue;
                int moveRight = dp[R][C+1];
                int moveDown  = dp[R+1][C];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});   
            }
        }

        int count = 0;

        for(int R = 0; R < N; ++R)
            for(int C = 0; C < M; ++C)
                if(grid[R][C] == 1)
                    count += dp[R][C];

        return count;
    }

    int solveBy2DEnhanced(const vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size(), count = 0;

        vector<vector<int>> dp(N+1, vector<int>(M+1, 0));

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0)
                    continue;

                int moveRight= dp[R][C+1];
                int moveDown = dp[R+1][C];
                int moveDownRight = dp[R+1][C+1];
                dp[R][C] = 1 + min({moveRight, moveDown, moveDownRight});  

                count += dp[R][C];
            }
        }

        return count;
    }


    int solveBy1DTable(const vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size(), count = 0;

        vector<int> nextRow(M+1, 0);

        for(int R = N-1; R >= 0; --R) {
            vector<int> currRow(M+1, 0);

            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0) 
                    continue;

                int moveRight = currRow[C+1];
                int moveDown  = nextRow[C];
                int moveDownRight = nextRow[C+1];
                currRow[C] = 1 + min({moveRight, moveDown, moveDownRight});  

                count += currRow[C];
            }

            swap(nextRow, currRow);
        }

        return count;
    }

    int solveWithoutTable(vector<vector<int>>& grid) {
        int N = grid.size(), M = grid[0].size(), count = 0;

        for(int R = N-1; R >= 0; --R) {
            for(int C = M-1; C >= 0; --C) {
                if(grid[R][C] == 0) 
                    continue;
                    
                int moveRight = (C+1 < M) ? grid[R][C+1] : 0;
                int moveDown  = (R+1 < N) ? grid[R+1][C] : 0;
                int moveDownRight = (R+1 < N && C+1 < M) ? grid[R+1][C+1] : 0;
                grid[R][C] = 1 + min({moveRight, moveDown, moveDownRight});  

                count += grid[R][C];
            }
        }

        return count;
    }

public:
    int countSquares_V1(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();   
        return solveWithoutTable(grid);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/count-square-submatrices-with-all-ones/description/
