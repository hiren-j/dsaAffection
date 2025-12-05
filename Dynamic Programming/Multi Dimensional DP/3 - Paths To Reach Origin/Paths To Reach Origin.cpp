// Code to find the total number of paths you can take from the points (X, Y) to reach the origin (0, 0) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(2^(X*Y)) & O(X+Y)
    int solveWithoutMemo(int X, int Y) {
        if(X == 0 && Y == 0)
            return 1;
        
        if(X < 0 || Y < 0)
            return 0;
            
        int moveLeft = solveWithoutMemo(X, Y - 1);
        int moveUp   = solveWithoutMemo(X - 1, Y);
        
        return (moveLeft + moveUp) % MOD;
    }
    
    // O(2*X*Y) & O(X*Y + X+Y)
    int solveWithMemo(vector<vector<int>>& dp, int X, int Y) {
        if(X == 0 && Y == 0)
            return 1;
        
        if(X < 0 || Y < 0)
            return 0;
            
        if(dp[X][Y] != -1)
            return dp[X][Y];
            
        int moveLeft = solveWithMemo(dp, X, Y - 1);
        int moveUp   = solveWithMemo(dp, X - 1, Y);
        
        return dp[X][Y] = (moveLeft + moveUp) % MOD;
    }
    
public:
    // Method to count total ways to reach the origin point, using recursion with memoization - O(X*Y) & O(X*Y)
    int waysToReachOrigin(int X, int Y) {
        vector<vector<int>> dp(X + 1, vector<int>(Y + 1, -1));
        return solveWithMemo(dp, X, Y);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;

    // O(X*Y) & O(X*Y) : Where X = given_X, Y = given_Y
    int solveBy2DTable(int given_X, int given_Y) {
        vector<vector<int>> dp(given_X + 1, vector<int>(given_Y + 1, -1));

        // Init first edge case
        dp[0][0] = 1; 
        
        for(int X = 0; X <= given_X; ++X) {
            for(int Y = 0; Y <= given_Y; ++Y) {
                if(X == 0 && Y == 0)
                    continue;
                int moveLeft = (Y - 1 < 0) ? 0 : dp[X][Y - 1];
                int moveUp   = (X - 1 < 0) ? 0 : dp[X - 1][Y];
                dp[X][Y] = (moveLeft + moveUp) % MOD;
            }
        }
        
        return dp[given_X][given_Y];
    }
    
    // O(X*Y) & O(2*Y) : Where X = given_X, Y = given_Y
    int solveBy1DTable(int given_X, int given_Y) {
        vector<int> prevRow(given_Y + 1, -1);

        for(int X = 0; X <= given_X; ++X) {
            vector<int> currRow(given_Y + 1, -1);
            
            for(int Y = 0; Y <= given_Y; ++Y) {
                if(X == 0 && Y == 0) {
                    currRow[0] = 1; // Init first edge case
                    continue;
                }
                int moveLeft = (Y - 1 < 0) ? 0 : currRow[Y - 1];
                int moveUp   = (X - 1 < 0) ? 0 : prevRow[Y];
                currRow[Y] = (moveLeft + moveUp) % MOD;
            }
            
            prevRow = currRow;
        }
        
        return prevRow[given_Y];
    }
    
public:
    int waysToReachOrigin(int X, int Y) {
        return solveBy1DTable(X, Y);
    }
};
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUpIntuitive {
    const int MOD = 1e9 + 7;
    
    // O(X*Y) & O(X*Y)
    int solveBy2DTable(int given_X, int given_Y) {
        vector<vector<int>> dp(given_X + 1, vector<int>(given_Y + 1, 0));

        // Logically when the value of X is 0 then for any value of Y you can reach point 0
        for(int Y = 0; Y <= given_Y; ++Y)
            dp[0][Y] = 1;

        // Logically when the value of Y is 0 then for any value of X you can reach point 0
        for(int X = 0; X <= given_X; ++X)
            dp[X][0] = 1;

        for(int X = 1; X <= given_X; ++X) {
            for(int Y = 1; Y <= given_Y; ++Y) {
                int moveLeft = dp[X][Y - 1];  
                int moveUp   = dp[X - 1][Y];  
                dp[X][Y]  = (moveUp + moveLeft) % MOD;
            }
        }

        return dp[given_X][given_Y];
    }

    // O(X*Y) & O(X*Y)
    int solveBy2DEnhanced(int given_X, int given_Y) {
        //  Suppose you're on a cell and that cell is also a destination cell then you've only 1 path it's because you're already on the cell. So, initially fill all the cells by value 1
        vector<vector<int>> dp(given_X + 1, vector<int>(given_Y + 1, 1));

        for(int X = 1; X <= given_X; ++X) {
            for(int Y = 1; Y <= given_Y; ++Y) {
                int moveLeft = dp[X][Y - 1];  
                int moveUp   = dp[X - 1][Y];  
                dp[X][Y]  = (moveUp + moveLeft) % MOD;
            }
        }

        return dp[given_X][given_Y];
    }

    // O(X*Y) & O(2*Y)
    int solveBy1DTable(int given_X, int given_Y) {
        vector<int> prevRow(given_Y + 1, 1);

        for(int X = 1; X <= given_X; ++X) {
            vector<int> currRow(given_Y + 1, 1);

            for(int Y = 1; Y <= given_Y; ++Y) {
                int moveLeft = currRow[Y - 1];  
                int moveUp   = prevRow[Y];  
                currRow[Y] = (moveUp + moveLeft) % MOD;
            }

            prevRow = currRow;
        }

        return prevRow[given_Y];
    }

public:
    int waysToReachOrigin(int X, int Y) {
        return solveBy1DTable(X, Y);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming | Matrix
Link  : https://www.geeksforgeeks.org/problems/paths-to-reach-origin3850/1
