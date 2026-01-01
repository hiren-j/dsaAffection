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

    // O(2*N*N*2) & O(N*N*2 + 2*N)
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
    bool solveBy3DTable(const vector<vector<int>>& maze) {
        vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(N+1, vector<int>(2, -1)));

        for(int C = 0; C <= N; ++C)
            for(int key = 0; key <= 1; ++key)
                dp[N][C][key] = false;
    
        for(int R = 0; R <= N; ++R)
            for(int key = 0; key <= 1; ++key)
                dp[R][N][key] = false;
    
        for(int key = 0; key <= 1; ++key)
            dp[N-1][N-1][key] = (key - maze[N-1][N-1] >= 0);	
    
        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int key = 0; key <= 1; ++key) {
                    bool moveRight = (key - maze[R][C] < 0) ? false : dp[R][C+1][key - maze[R][C]];
                    bool moveDown  = (key - maze[R][C] < 0) ? false : dp[R+1][C][key - maze[R][C]];
                    dp[R][C][key] = (moveRight || moveDown);
                }
            }
        }
    
        return dp[0][0][1];
    }
    
    // O(N*N*2) & O(N*N*2)
    bool solveBy3DEnhanced(const vector<vector<int>>& maze) {
        vector<vector<vector<bool>>> dp(N+1, vector<vector<bool>>(N+1, vector<bool>(2, false)));
    
        for(int key = 0; key <= 1; ++key)
            dp[N-1][N-1][key] = (key - maze[N-1][N-1] >= 0);	
    
        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                if(R == N-1 && C == N-1)
                    continue;
                for(int key = 0; key <= 1; ++key) {
                    bool moveRight = (key - maze[R][C] < 0) ? false : dp[R][C+1][key - maze[R][C]];
                    bool moveDown  = (key - maze[R][C] < 0) ? false : dp[R+1][C][key - maze[R][C]];
                    dp[R][C][key] = (moveRight || moveDown);
                }
            }
        }
    
        return dp[0][0][1];
    }
    
    // O(N*N*2) & O(2*N*2)
    bool solveBy2DTable(const vector<vector<int>>& maze) {
        vector<vector<bool>> next(N+1, vector<bool>(2, false)); // R + 1th table
        vector<vector<bool>> curr(N+1, vector<bool>(2, false)); // Rth table
    
        for(int R = N-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                for(int key = 0; key <= 1; ++key) {
                    if(R == N-1 && C == N-1) {
                        curr[N-1][key] = (key - maze[N-1][N-1] >= 0);	
                    }
                    else {
                        bool moveRight = (key - maze[R][C] < 0) ? false : curr[C+1][key - maze[R][C]];
                        bool moveDown  = (key - maze[R][C] < 0) ? false : next[C][key - maze[R][C]];
                        curr[C][key] = (moveRight || moveDown);
                    }
                }
            }
            swap(next, curr);
        }
    
        return next[0][1];
    }

public:
    bool canReachCornerWith1Key(vector<vector<int>>& maze, int n) {
        N = n;
        return solveBy2DTable(maze);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Matrix | Dynamic Programming   
Link  : https://www.naukri.com/code360/problems/maze-with-n-doors-and-1-key_839809?leftPanelTabValue=PROBLEM
