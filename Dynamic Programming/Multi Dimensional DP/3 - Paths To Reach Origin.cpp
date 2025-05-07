// Code to find the total number of paths you can take from the points (X, Y) to reach the origin (0, 0) ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    
    int solveWithoutMemo(int X, int Y) {
        if(X == 0 && Y == 0)
            return 1;
        
        if(X < 0 || Y < 0)
            return 0;
            
        int moveLeft = solveWithoutMemo(X, Y-1);
        int moveUp   = solveWithoutMemo(X-1, Y);
        
        return (moveLeft + moveUp) % MOD;
    }
    
    int solveWithMemo(vector<vector<int>>& dp, int X, int Y) {
        if(X == 0 && Y == 0)
            return 1;
        
        if(X < 0 || Y < 0)
            return 0;
            
        if(dp[X][Y] != -1)
            return dp[X][Y];
            
        int moveLeft = solveWithMemo(dp, X, Y-1);
        int moveUp   = solveWithMemo(dp, X-1, Y);
        
        return dp[X][Y] = (moveLeft + moveUp) % MOD;
    }
    
public:
    int waysToReachOrigin(int X, int Y) {
        return solveWithoutMemo(X, Y);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;

    int solveWith2DTable(int X, int Y) {
        vector<vector<int>> dp(X+1, vector<int>(Y+1, -1));
        dp[0][0] = 1;
        
        for(int R = 0; R <= X; ++R) {
            for(int C = 0; C <= Y; ++C) {
                if(R == 0 && C == 0)
                    continue;
                int moveLeft = (C-1 >= 0) ? dp[R][C-1] : 0;
                int moveUp   = (R-1 >= 0) ? dp[R-1][C] : 0;
                dp[R][C] = (moveLeft + moveUp) % MOD;
            }
        }
        
        return dp[X][Y];
    }
    
    int solveWith1DTable(int X, int Y) {
        vector<int> prevRow(Y+1, -1);

        for(int R = 0; R <= X; ++R) {
            vector<int> currRow(Y+1, -1);
            
            for(int C = 0; C <= Y; ++C) {
                if(R == 0 && C == 0) {
                    currRow[0] = 1; 
                    continue;
                }
                int moveLeft = (C-1 >= 0) ? currRow[C-1] : 0;
                int moveUp   = (R-1 >= 0) ? prevRow[C] : 0;
                currRow[C] = (moveLeft + moveUp) % MOD;
            }
            
            prevRow = currRow;
        }
        
        return prevRow[Y];
    }
    
public:
    int waysToReachOrigin(int X, int Y) {
        vector<vector<int>> dp(X+1, vector<int>(Y+1, -1));
        return solveWithMemo(dp, X, Y);
    }
};
    
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUpIntuitive {
    const int MOD = 1e9+7;

public:
    // #1 Method to find the total number of paths from points to the origin, using 2D tabulation - O(X*Y) & O(X*Y)
    int numPaths_V1(int X, int Y) {
        // 2D DP table
        vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

        // Logically when the value of X is zero then for any value of Y you've only one valid path
        for(int stepY = 0; stepY <= Y; ++stepY)
            dp[0][stepY] = 1;

        // Logically when the value of Y is zero then for any value of X you've only one valid path
        for(int stepX = 0; stepX <= X; ++stepX)
            dp[stepX][0] = 1;

        // Fill the rest of the table
        for(int stepX = 1; stepX <= X; ++stepX) {
            for(int stepY = 1; stepY <= Y; ++stepY) {
                int numPathsFromX = dp[stepX - 1][stepY];  
                int numPathsFromY = dp[stepX][stepY - 1];  
                dp[stepX][stepY]  = (numPathsFromX + numPathsFromY) % MOD;
            }
        }

        // Return the result value
        return dp[X][Y];
    }

    // #2 Method to find the total number of paths from points to the origin, using 2D tabulation - O(X*Y) & O(X*Y)
    int numPaths_V2(int X, int Y) {
        // 2D DP table: Suppose you're on a cell and that cell is also a destination cell then you've only one valid path it's because you're already on the cell. So, initially fill all the cells by value one
        vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 1));

        // Fill the rest of the table
        for(int stepX = 1; stepX <= X; ++stepX) {
            for(int stepY = 1; stepY <= Y; ++stepY) {
                int numPathsFromX = dp[stepX - 1][stepY];  
                int numPathsFromY = dp[stepX][stepY - 1];  
                dp[stepX][stepY]  = (numPathsFromX + numPathsFromY) % MOD;
            }
        }

        // Return the result value
        return dp[X][Y];
    }

    // #3 Method to find the total number of paths from points to the origin, using 1D tabulation - O(X*Y) & O(Y)
    int numPaths_V3(int X, int Y) {
        vector<int> prevRow(Y + 1, 1), currRow(Y + 1, 1);

        for(int stepX = 1; stepX <= X; ++stepX) {
            for(int stepY = 1; stepY <= Y; ++stepY) {
                int numPathsFromX = prevRow[stepY];  
                int numPathsFromY = currRow[stepY - 1];  
                currRow[stepY] = (numPathsFromX + numPathsFromY) % MOD;
            }
            prevRow = currRow;
        }

        return currRow[Y];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Matrix
Link  : https://www.geeksforgeeks.org/problems/paths-to-reach-origin3850/1
