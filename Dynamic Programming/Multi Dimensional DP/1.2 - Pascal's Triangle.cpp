// Code to find the first N rows of Pascal's triangle ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
  NOTE: In the previous solution, we are considering an unique start point from the last row using a loop, 
        but we could do the same thing without using the loop, just move to the next cell of the last row in the recursion.
*/
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int N;

    // O(2^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& pascal, int R, int C) {
        // Base case: In pascal's triangle, cells of first column and last column of any row always have value 1
        if(C == 0 || C == R || C == N)
            return 1;
        
        // In pascal's triangle, here cell value is the sum of two values, the coordinates of those values are
        int moveUp     = solveWithoutMemo(pascal, R-1, C);
        int moveUpPrev = solveWithoutMemo(pascal, R-1, C-1);

        if(R == N-1) // After finding the value of cell (R,C) move to the next cell of last row
            solveWithoutMemo(pascal, R, C+1);
        
        return pascal[R][C] = moveUp + moveUpPrev;
    }

    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, vector<vector<int>>& pascal, int R, int C) {
        // Base case: In pascal's triangle, cells of first column and last column of any row always have value 1
        if(C == 0 || C == R || C == N)
            return 1;
        
        if(dp[R][C] != -1)
            return dp[R][C];

        // In pascal's triangle, here cell value is the sum of two values, the coordinates of those values are
        int moveUp     = solveWithMemo(dp, pascal, R-1, C);
        int moveUpPrev = solveWithMemo(dp, pascal, R-1, C-1);
        
        if(R == N-1) // After finding the value of cell (R,C) move to the next cell of last row
            solveWithMemo(dp, pascal, R, C+1);

        return dp[R][C] = pascal[R][C] = moveUp + moveUpPrev;
    }
    // Note: the dp array is not actually required, we could simply use the same pascal array as dp array, but still I am doing it just so you could learn bottom up, we can also do bottom up with that pascal array too, but that would be easy for you, that's why I am going with this one

public: 
    // Method to find first N rows of pascal triangle, using recursion with memoization - O(N^2) & O(N^2)
    vector<vector<int>> generate(int numRows) {
        N = numRows;

        // Create rows of pascal's triangle, if we consider R for rows with 0-based indexing then if we're at Rth row, then total values on that row will be R+1
        vector<vector<int>> pascal;
        for(int R = 0; R < N; ++R) {
            pascal.push_back(vector<int>(R+1, 1));
        }   

        // Start from the last row of pascal's triangle and then find the value of each cell
        vector<vector<int>> dp(N, vector<int>(N, -1));
        solveWithMemo(dp, pascal, N-1, 1);
        return pascal;
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
  NOTE: REST OF THE SOLUTIONS REMAINS THE SAME. 
*/
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/pascals-triangle/description/
