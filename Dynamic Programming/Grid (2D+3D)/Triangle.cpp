// Program to find the minimum path sum from top to bottom in a triangle ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the "top down approach"
class TopDown {
public:
    // Method to find the minimum path sum, using recursion with memoization - O(M*M) & O(M*M) : Where M is the total number of rows.
    int minimumTotal(vector<vector<int>>& grid) {
        int M = grid.size();
        vector<vector<int>> memo(M+1, vector<int>(M+1, -1));
        return solveWithMemo(grid, memo, M, 0, 0);
    }

private:
    // O(2^(M*M)) & O(M) : Where M is the total number of rows.
    int solveWithoutMemo(vector<vector<int>>& grid, int M, int R, int C) {
        // Edge case: When all the cells of the "grid" are exhausted.
        if(R >= M || C >= M)
            return INT_MAX; // Requires to handle the "minimum sum" correctly.
        
        // There are always two possibilities at each cell
        int moveToSameColumn = solveWithoutMemo(grid, M, R+1, C);   // Is to move to the same column in the next row.
        int moveToNextColumn = solveWithoutMemo(grid, M, R+1, C+1); // Is to move to the next column in the next row.

        // As we're striving for the "minimum sum" thus store the minimum element from both the possibilities.
        int minElement = min(moveToSameColumn, moveToNextColumn);

        // Add the value of the current cell with the minimum element and then return the sum.
        return grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }

    // O(M*M) & O(M*M) : Where M is the total number of rows.
    int solveWithMemo(vector<vector<int>>& grid, vector<vector<int>>& memo, int M, int R, int C) {
        // Edge case: When all the cells of the "grid" are exhausted.
        if(R >= M || C >= M)
            return INT_MAX; // Requires to handle the "minimum sum" correctly.

        // Memoization table: If the current state is already computed then return the computed value.
        if(memo[R][C] != -1)
            return memo[R][C];

        // There are always two possibilities at each cell
        int moveToSameColumn = solveWithMemo(grid, memo, M, R+1, C);   // Is to move to the same column in the next row.
        int moveToNextColumn = solveWithMemo(grid, memo, M, R+1, C+1); // Is to move to the next column in the next row.

        // As we're striving for the "minimum sum" thus store the minimum element from both the possibilities.
        int minElement = min(moveToSameColumn, moveToNextColumn);

        // Add the value of the current cell with the minimum element then store the sum to the "memoization table" and then return the sum.
        return memo[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }
};

// Class to implement the "bottom up approach"
class BottomUp {
public:
    // #1 Method to find the minimum path sum, using 2d buffer for tabulation - O(M*M) & O(M*M) : Where M is the total number of rows.
    int minimumTotal_V1(vector<vector<int>>& grid) {
        int M = grid.size();

        // Edge case: If there's only a single cell then the "minimum sum" will be the value of the cell.
        if(M == 1)
            return grid[0][0];

        // Stores the "minimum path sum" from top to bottom.
        int minPathSum = INT_MAX;

        // 2d buffer for Tabulation: For each cell "(R,C)" of "dp", the value represents the "minimum sum" needed to reach that cell in the "grid". 
        vector<vector<int>> dp(M, vector<int>(M, 0));
        dp[0][0] = grid[0][0];

        for(int R=1; R<M; R++) {
            for(int C=0; C<R+1; C++) {
                // If its the first column then fill the minimized sum to reach the cell in the "grid".
                if(C == 0)
                    dp[R][C] = grid[R][C] + dp[R-1][C];

                // Else if its the last column then fill the minimized sum to reach the cell in the "grid".
                else if(C == R)
                    dp[R][C] = grid[R][C] + dp[R-1][C-1];

                // Else then fill the minimized sum to reach the current cell in the "grid".
                else
                    dp[R][C] = grid[R][C] + min(dp[R-1][C], dp[R-1][C-1]);

                // If its the last row then update the "minimum path sum / resultant value".
                if(R == M-1)
                    minPathSum = min(minPathSum, dp[R][C]);
            }
        }
        
        // Return the "minimum path sum" from top to bottom.
        return minPathSum;
    }

    // #2 Method to find the minimum path sum, using 2d buffer for tabulation - O(M*M) & O(M*M) : Where M is the total number of rows.
    int minimumTotal_V2(vector<vector<int>>& grid) {
        int M = grid.size();

        // Edge case: If there's only a single cell then the "minimum sum" will be the value of the cell.
        if(M == 1)
            return grid[0][0];

        // 2d buffer for Tabulation: For each cell "(R,C)" of "dp", the value represents the "minimum sum" needed to reach that cell in the "grid". 
        vector<vector<int>> dp;

        // Stores the "minimum path sum" from top to bottom.
        int minPathSum = INT_MAX;

        for(int R=0; R<M; R++) {
            dp.emplace_back(vector<int>(R+1));
            for(int C=0; C<R+1; C++) {
                // If its the first row then fill the minimized sum to reach the cell in the "grid".
                if(R == 0)
                    dp[R][C] = grid[R][C];

                // Else if its the first column then fill the minimized sum to reach the cell in the "grid".
                else if(C == 0)
                    dp[R][C] = grid[R][C] + dp[R-1][C]; 
                    
                // Else if its the last column then fill the minimized sum to reach the cell in the "grid".
                else if(C == R)
                    dp[R][C] = grid[R][C] + dp[R-1][C-1];

                // Else then fill the minimized sum to reach the current cell in the "grid".
                else
                    dp[R][C] = grid[R][C] + min(dp[R-1][C], dp[R-1][C-1]);

                // If its the last row then update the "minimum path sum / resultant value".
                if(R == M-1)
                    minPathSum = min(minPathSum, dp[R][C]);
            }
        }
        
        // Return the "minimum path sum" from top to bottom.
        return minPathSum;
    }

    // #3 Method to find the minimum path sum, using 1d buffer for tabulation - O(M*M) & O(M) : Where M is the total number of rows.
    int minimumTotal_V3(vector<vector<int>>& grid) {
        int M = grid.size();

        // Edge case: If there's only a single cell then the "minimum sum" will be the value of the cell.
        if(M == 1)
            return grid[0][0];

        // Stores the "minimum path sum" from top to bottom.
        int minPathSum = INT_MAX;

        vector<int> currRow(M); // Tracks the tabulation values for any current row.
        vector<int> prevRow(M); // Tracks the tabulation values for the previous row of the current row.
        prevRow[0] = grid[0][0];

        for(int R=1; R<M; R++) {
            for(int C=0; C<R+1; C++) {
                // If its the first column then fill the minimized sum to reach the cell in the "grid".
                if(C == 0)
                    currRow[C] = grid[R][C] + prevRow[C];

                // Else if its the last column then fill the minimized sum to reach the cell in the "grid".
                else if(C == R)
                    currRow[C] = grid[R][C] + prevRow[C-1];

                // Else then fill the minimized sum to reach the current cell in the "grid".
                else
                    currRow[C] = grid[R][C] + min(prevRow[C], prevRow[C-1]);

                // If its the last row then update the "minimum path sum / resultant value".
                if(R == M-1)
                    minPathSum = min(minPathSum, currRow[C]);
            }
            // Update the previous row for the upcoming row.
            prevRow = currRow;
        }
        
        // Return the "minimum path sum" from top to bottom.
        return minPathSum;
    }

    // #4 Method to find the minimum path sum, using constant auxiliary space - O(M*M) & O(1) : Where M is the total number of rows.
    int minimumTotal_V4(vector<vector<int>>& grid) {
        int M = grid.size();

        // Edge case: If there's only a single cell then the "minimum sum" will be the value of the cell.
        if(M == 1)
            return grid[0][0];

        // Stores the "minimum path sum" from top to bottom.
        int minPathSum = INT_MAX;

        for(int R=1; R<M; R++) {
            for(int C=0; C<R+1; C++) {
                // If its the first column then fill the minimized sum to reach the cell in the "grid".
                if(C == 0)
                    grid[R][C] += grid[R-1][C]; 

                // Else if its the last column then fill the minimized sum to reach the cell in the "grid".
                else if(C == R)
                    grid[R][C] += grid[R-1][C-1];

                // Else then fill the minimized sum to reach the current cell in the "grid".
                else
                    grid[R][C] += min(grid[R-1][C], grid[R-1][C-1]);
                    
                // If its the last row then update the "minimum path sum / resultant value".
                if(R == M-1)
                    minPathSum = min(minPathSum, grid[R][C]);
            }
        }
        
        // Return the "minimum path sum" from top to bottom.
        return minPathSum;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not.
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user.
        system("cls || clear");

        // Input the number of rows for the "grid".
        int M;
        cout<<"Enter the number of rows for the grid: ";
        cin>>M;

        // Check the given size is valid or not.
        if(M <= 0) {
            cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }

        // 2d buffer to store the "triangle" values.
        vector<vector<int>> grid;

        // Input the values of the "grid".
        for(int R=0; R<M; R++) {
            grid.emplace_back(vector<int>(R+1));
            cout<<"Enter "<<R+1<<" values for the "<<R<<"th row: ";
            for(int C=0; C<R+1; C++) {
                cin>>grid[R][C];
            }
        }

        // Call to find the "minimum path sum".
        BottomUp bottomUp;
        int minPathSum = bottomUp.minimumTotal_V4(grid);
        cout<<"\nThe minimum path sum from top to bottom is: "<<minPathSum;

        // Input section to handle the flow of iterations of the application.
        char userChoise;
        cout<<"\n\nPress \'Y\' to perform the same operation on an another grid, else application will exit automatically: ";
        cin>>userChoise;
        canPerformOperation = (userChoise == 'Y') ? true : false ;
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/triangle/
*/
