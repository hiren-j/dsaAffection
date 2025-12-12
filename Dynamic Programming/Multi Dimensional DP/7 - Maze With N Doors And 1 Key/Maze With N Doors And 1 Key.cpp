// Code to find if there exists a path from the top-left cell to the bottom right cell of the maze provided only downward and rightward movements are allowed. Note that some cells have a door while some do not and a key that can be used only once to open a door ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    // O(2^(N*N)) & O(2*N)
    bool solveWithoutMemo(vector<vector<int>>& maze, int R, int C, int key) {
        if(R == N || C == N || key < 0)
            return false;
    
        if(R == N-1 && C == N-1)
            return (key - maze[R][C] >= 0);

        bool moveRight = solveWithoutMemo(maze, R, C+1, key - maze[R][C]);
        bool moveDown  = solveWithoutMemo(maze, R+1, C, key - maze[R][C]);

        return moveRight || moveDown;
    }

    // O(2*N*N) & O(N*N + 2*N)
    bool solveWithMemo(vector<vector<vector<int>>>& dp, vector<vector<int>>& maze, int R, int C, int key) {
        if(R == N || C == N || key < 0)
            return false;
    
        if(R == N-1 && C == N-1)
            return (key - maze[R][C] >= 0);

        if(dp[R][C][key] != -1)
            return dp[R][C][key];

        bool moveRight = solveWithMemo(dp, maze, R, C+1, key - maze[R][C]);
        bool moveDown  = solveWithMemo(dp, maze, R+1, C, key - maze[R][C]);

        return dp[R][C][key] = moveRight || moveDown;
    }

public:
    // Method to check if its possible to reach bottom right corner with 1 key, using recursion with memoization - O(N*N) & O(N*N)
    bool canReachCornerWith1Key(vector<vector<int>>& maze, int n) {
        N = n;
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(2, -1)));
        return solveWithMemo(dp, maze, 0, 0, 1);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N;

    // O(N*N*2) & O(N*N*2)
    bool solveWith3DTable(vector<vector<int>>& maze) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(N, vector<int>(2, -1)));
        dp[N-1][N-1][0] = (0 - maze[N-1][N-1] >= 0); // Init second edge case
        dp[N-1][N-1][1] = (1 - maze[N-1][N-1] >= 0); // Init second edge case

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int key = 0; key <= 1; ++key) {
                    bool moveRight = (C+1 < N) ? dp[R][C+1][key - maze[R][C]] : false;
                    bool moveDown  = (R+1 < N) ? dp[R+1][C][key - maze[R][C]] : false;
                    dp[R][C][key]  = moveRight || moveDown;
                }
            }
        }

        return dp[0][0][1];
    }

    // O(N*N*2) & O(N*N*2)
    bool solveWith3DEnhanced(vector<vector<int>>& maze) {
        vector<vector<vector<bool>>> dp(N+1, vector<vector<bool>>(N+1, vector<bool>(2, false)));
        dp[N-1][N-1][0] = (maze[N-1][N-1] == 0); // 0 - maze[N-1][N-1] >= 0;
        dp[N-1][N-1][1] = true;                  // 1 - maze[N-1][N-1] >= 0;

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int key = 0; key <= 1; ++key) {
                    bool moveRight = dp[R][C+1][key - maze[R][C]];
                    bool moveDown  = dp[R+1][C][key - maze[R][C]];
                    dp[R][C][key]  = moveRight || moveDown;
                }
            }
        }

        return dp[0][0][1];
    }

    // O(N*N*2) & O(2*N*2)
    bool solveWith2DTable(vector<vector<int>>& maze) {
        vector<vector<bool>> nextRow(N+1, vector<bool>(2, false)), idealRow(N+1, vector<bool>(2, false));
        idealRow[N-1][0] = (maze[N-1][N-1] == 0); // 0 - maze[N-1][N-1] >= 0;
        idealRow[N-1][1] = true;                  // 1 - maze[N-1][N-1] >= 0;

        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int key = 0; key <= 1; ++key) {
                    bool moveRight = idealRow[C+1][key - maze[R][C]];
                    bool moveDown  = nextRow[C][key - maze[R][C]];
                    idealRow[C][key]  = moveRight || moveDown;
                }
            }
            nextRow = idealRow;
        }

        return nextRow[0][1];
    }

public:
    bool canReachCornerWith1Key(vector<vector<int>>& maze, int n) {
        N = n;
        return solveWith2DTable(maze);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Matrix | Dynamic Programming   
Link  : https://www.naukri.com/code360/problems/maze-with-n-doors-and-1-key_839809?leftPanelTabValue=PROBLEM
