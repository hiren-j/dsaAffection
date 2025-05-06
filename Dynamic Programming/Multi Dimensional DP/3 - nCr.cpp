// Code to find the nCr of given two integers ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Solution {
    int solveWithMemo(vector<vector<int>>& dp, int R, int C) {
        if(C == 0 || C == R)
            return 1;
            
        if(dp[R][C] != -1)
            return dp[R][C];
            
        int moveUp     = solveWithMemo(dp, R-1, C);
        int moveUpPrev = solveWithMemo(dp, R-1, C-1);
        
        return dp[R][C] = moveUp + moveUpPrev;
    }
    
    int solveWith2DTable(int N, int R) {
        vector<vector<int>> dp(N+1, vector<int>(N+1, -1));
        
        for(int R = 0; R <= N; ++R)
            dp[R][0] = dp[R][R] = 1;
        
        for(int R = 1; R <= N; ++R) {
            for(int C = 1; C < R; ++C) {
                int moveUp     = dp[R-1][C];
                int moveUpPrev = dp[R-1][C-1];
                dp[R][C] = moveUp + moveUpPrev;
            }
        }
        
        return dp[N][R];
    }
    
    int solveWith1DTable(int N, int R) {
        vector<int> prevRow(N, 1);
        // prevRow[0] = 1; // If yow want array like this: vector<int> prevRow(N, -1); then uncomment this line
    
        for(int R = 1; R <= N; ++R) {
            vector<int> currRow(R+1, 1); // Setting to 1 also initializes the base case, but if you want array like: vector<int> currRow(R+1, -1); then do this: currRow[0] = currRow[R] = 1;
            for(int C = 1; C < R; ++C) {
                int moveUp     = prevRow[C];
                int moveUpPrev = prevRow[C-1];
                currRow[C] = moveUp + moveUpPrev;
            }
            prevRow = currRow;
        }
        
        return prevRow[R];
    }
    
public:
    int nCr(int N, int R) {
        if(R > N) 
            return 0;
        return solveWith1DTable(N, R); // To find nCr, just find the value of pascal[N][C], where (N,C) are 0-based indexing and pascal represents the 2D array storing values of pascal triangle
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/ncr1019/1
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Multi%20Dimensional%20DP/Pascal's%20Triangle%20II.cpp
