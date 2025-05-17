// Code to find the Nth number of the catalan's sequence ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;
    
    int solveWithoutMemo(int R, int C) {
        // Base case: 0th column and 1th row always contains value 1
        if(C == 0 || R == 1)
            return 1;
            
        // Base case: last column value of any row is the same as previous one
        if(C == R) 
            return solveWithoutMemo(R, C-1);
            
        // Value of any cell (R, C) is the sum of two values, the coordinates of those values are: 
        int moveUp   = solveWithoutMemo(R-1, C); 
        int movePrev = solveWithoutMemo(R, C-1);
  
        return moveUp + movePrev;
    }

    int solveWithMemo(vector<vector<int>>& dp, int R, int C) {
        // Base case: 0th column and 1th row always contains value 1
        if(C == 0 || R == 1)
            return dp[R][C] = 1;
            
        // Base case: last column value of any row is the same as previous one
        if(C == R) 
            return dp[R][C] = solveWithMemo(dp, R, C-1);
            
        if(dp[R][C] > 1)
            return dp[R][C];
        
        // Value of any cell (R, C) is the sum of two values, the coordinates of those values are: 
        int moveUp   = solveWithMemo(dp, R-1, C); 
        int movePrev = solveWithMemo(dp, R, C-1);
  
        return dp[R][C] = moveUp + movePrev;
    }

public:
    int nthCatalanNumber(int n) {
        N = n;

        // Create rows of catalan's triangle, if we consider R for rows with 0-based indexing then if we're at Rth row, then total values on that row will be R+1
        vector<vector<int>> dp;
        for(int R = 0; R <= N; ++R)
            dp.push_back(vector<int>(R+1, 1));
        
        return solveWithMemo(dp, N, N); // To find Nth catalan number, then find the value of cell dp[N][N], dp stores the values of catalan's triangle
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int N;
    
    int solveWith2DTable(vector<vector<int>>& dp) {
        /*
            // If you want row insertions like this: dp.push_back(vector<int>(R+1, -1)); then uncomment the base case initializations
            for(int R = 0; R <= N; ++R) dp[R][0] = 1; // Init first base case
            for(int C = 0; C <= 1; ++C) dp[1][C] = 1; // Init first base case
        */
    
        for(int R = 2; R <= N; ++R) {
            for(int C = 1; C <= R; ++C) {
                if(C == R) { 
                    dp[R][C] = dp[R][C-1]; // Handle second base case
                }
                else {
                    int moveUp   = dp[R-1][C]; 
                    int movePrev = dp[R][C-1];
                    dp[R][C] = moveUp + movePrev;
                }
            }
        }
        
        return dp[N][N];
    }

    int solveWith1DTable(vector<vector<int>>& dp) {
        vector<int> prevRow(N+1, 1);
        
        for(int R = 2; R <= N; ++R) {
            vector<int> idealRow(R+1, 1);
            
            for(int C = 1; C <= R; ++C) {
                if(C == R) {
                    idealRow[C] = idealRow[C-1];
                }
                else {
                    int moveUp   = prevRow[C]; 
                    int movePrev = idealRow[C-1];
                    idealRow[C] = moveUp + movePrev;
                }
            }
            
            prevRow = idealRow;
        }
        
        return prevRow[N];
    }

public:
    int nthCatalanNumber(int n) {
        N = n;

        vector<vector<int>> dp;
        for(int R = 0; R <= N; ++R)
            dp.push_back(vector<int>(R+1, 1));
 
        return solveWith1DTable(dp);
    }
};    

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpIntuitive {
    int solveWith2DTable(int N) {
        vector<vector<int>> dp;
        
        for(int R = 0; R <= N; ++R) {
            dp.push_back(vector<int>(R+1, 1));
            
            for(int C = 1; C <= R; ++C) {
                if(C == R) {
                    dp[R][C] = dp[R][C-1];
                }
                else {
                    int moveUp   = dp[R-1][C];
                    int movePrev = dp[R][C-1];
                    dp[R][C] = moveUp + movePrev;
                }
            }
        }
        
        return dp[N][N];
    }

    int solveWith2DConcice(int N) {
        vector<vector<int>> dp;
        
        for(int R = 0; R <= N; ++R) {
            dp.push_back(vector<int>(R+1, 1));
            
            for(int C = 1; C <= R; ++C) {
                dp[R][C] = (C == R) ? dp[R][C-1] 
                                    : dp[R-1][C] + dp[R][C-1];
            }
        }
        
        return dp[N][N];
    }
    
    int solveWith1DTable(int N) {
        vector<int> prevRow(N+1, 1);
        
        for(int R = 0; R <= N; ++R) {
            vector<int> idealRow(R+1, 1);
            
            for(int C = 1; C <= R; ++C) {
                idealRow[C] = (C == R) ? idealRow[C-1] 
                                       : prevRow[C] + idealRow[C-1];
            }
            
            prevRow = idealRow;
        }
        
        return prevRow[N];
    }
    
public:
    int nthCatalanNumber(int N) {
        return solveWith1DTable(N);
    }
};    
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

// NOTE: If you want to print the Catalan's Triangle then print the values of dp matrix 
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://archive.lib.msu.edu/crcmath/math/math/c/c099.htm
        https://www.geeksforgeeks.org/problems/nth-catalan-number0817/1
