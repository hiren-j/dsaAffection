// Code to find the Nth number of the catalan's sequence ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------


class Solution {
    int N;
    
    int solveWithMemo(vector<vector<int>>& dp, int R, int C) {
        if(C == 0 || R == 1)
            return 1;
            
        if(C == R)
            return dp[R][C] = solveWithMemo(dp, R, C-1);
            
        if(dp[R][C] != -1)
            return dp[R][C];
            
        int moveUp   = solveWithMemo(dp, R-1, C); 
        int movePrev = solveWithMemo(dp, R, C-1);
  
        return dp[R][C] = moveUp + movePrev;
    }
    
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
    
public:
    int nthCatalanNumber(int n) {
        N = n;
        
        vector<vector<int>> dp;
        for(int R = 0; R <= N; ++R)
            dp.push_back(vector<int>(R+1, 1));
        
        // return solveWithMemo(dp, N, N); // To find Nth catalan number, then find the value of cell dp[N][N], dp represents the values of catalan's triangle
        
        return solveWith2DTable(dp);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://archive.lib.msu.edu/crcmath/math/math/c/c099.htm
        https://www.geeksforgeeks.org/problems/nth-catalan-number0817/1
