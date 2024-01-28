// Program to find the number of possible unique paths that the robot can take to reach the bottom-right corner ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDown {
public:
    // Method to find the number of possible unique paths, using recursion with memoization - O(M*N) & O(M*N)
    int uniquePathsWithObstacles(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        vector<vector<int>> memo(M+1, vector<int>(N+1, -1));
        return solveWithMemo(grid, memo, M, N, 0, 0);
    }

private:
    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(vector<vector<int>>& grid, int M, int N, int R, int C) {
        // Edge case: "If all the cells are exhausted" or "the current cell contains an obstacle" then we got no valid way
        if(R >= M || C >= N || grid[R][C] == 1)
            return 0;

        // Edge case: If reached the bottom up corner then we got one valid way
        if(R == M-1 && C == N-1)
            return 1;   

        // There are always two possibilities at each cell
        int moveDown  = solveWithoutMemo(grid, M, N, R+1, C); // Is to move to the down cell from the current cell
        int moveRight = solveWithoutMemo(grid, M, N, R, C+1); // Is to move to the right cell from the current cell

        // Return the total number of ways got from both the possibilities
        return moveDown + moveRight;
    }

    // O(M*N) & O(M*N)
    int solveWithMemo(vector<vector<int>>& grid, vector<vector<int>>& memo, int M, int N, int R, int C) {
        // Edge case: "If all the cells are exhausted" or "the current cell contains an obstacle" then we got no valid way
        if(R >= M || C >= N || grid[R][C] == 1)
            return 0;

        // Edge case: If reached the bottom up corner then we got one valid way
        if(R == M-1 && C == N-1)
            return 1;   
        
        // Memoization table: If the current state is already computed then return the computed value 
        if(memo[R][C] != -1)
            return memo[R][C];

        // There are always two possibilities at each cell
        int moveDown  = solveWithMemo(grid, memo, M, N, R+1, C); // Is to move to the down cell from the current cell
        int moveRight = solveWithMemo(grid, memo, M, N, R, C+1); // Is to move to the right cell from the current cell

        // Store and return the total number of ways got from both the possibilities
        return memo[R][C] = moveDown + moveRight;
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUp {
public:
    // #1 Method to find the number of possible unique paths, using 2D buffer for tabulation - O(M*N) & O(M*N)
    int uniquePathsWithObstacles_V1(vector<vector<int>>& grid) {
        // Edge case: If the first cell contains an obstacle then we got no valid way
        if(grid[0][0] == 1)
            return 0;

        int M = grid.size(), N = grid[0].size();
        
        // 2D buffer for tabulation: By default it fills the value 0 for all the cells (dp[R][C]: represents the number of possible unique paths to reach the square (R, C) in the grid)
        vector<vector<int>> dp(M, vector<int>(N));
        dp[0][0] = 1;

        // Fill the table for the first row
        for(int C=1; C<N; C++) {
            // If the current cell doesn't contain an obstacle then fill the value for it
            if(grid[0][C] == 0)
                dp[0][C] = dp[0][C-1];
        }

        // Fill the table for the first column
        for(int R=1; R<M; R++) {
            // If the current cell doesn't contain an obstacle then fill the value for it
            if(grid[R][0] == 0)
                dp[R][0] = dp[R-1][0];
        }

        // Fill the rest of the table
        for(int R=1; R<M; R++) {
            for(int C=1; C<N; C++) {
                // If the current cell doesn't contain an obstacle then fill the value by adding the total number of ways to reach the current cell
                if(grid[R][C] == 0)
                    dp[R][C] = dp[R-1][C] + dp[R][C-1];
            }
        }

        // Return the total number of ways to reach the bottom-right cell
        return dp[M-1][N-1];
    }

    // #2 Method to find the number of possible unique paths, using 2D buffer for tabulation - O(M*N) & O(M*N)
    int uniquePathsWithObstacles_V2(vector<vector<int>>& grid) {
        // Edge case: If the first cell contains an obstacle then we got no valid way
        if(grid[0][0] == 1)
            return 0;

        int M = grid.size(), N = grid[0].size();
        
        // 2D buffer for tabulation: By default it fills the value 0 for all the cells (dp[R][C]: represents the number of possible unique paths to reach the square (R, C) in the grid)
        vector<vector<int>> dp(M, vector<int>(N));
        dp[0][0] = 1;

        // Fill the table
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If the current cell doesn't contain an obstacle then fill the value for it
                if(grid[R][C] == 0) {
                    // If its the first row then fill the value for the cell
                    if(R == 0 && C > 0)
                        dp[0][C] = dp[0][C-1];

                    // Else if its the first column then fill the value for the cell
                    else if(R > 0 && C == 0)
                        dp[R][0] = dp[R-1][0];
                        
                    // Else then fill the value by adding the total number of ways to reach the current cell
                    else if(R > 0 && C > 0)
                        dp[R][C] = dp[R-1][C] + dp[R][C-1];
                }
            }
        }

        // Return the total number of ways to reach the bottom-right cell
        return dp[M-1][N-1];
    }

    // #3 Method to find the number of possible unique paths, using 1D buffer for tabulation - O(M*N) & O(N)
    int uniquePathsWithObstacles_V3(vector<vector<int>>& grid) {
        // Edge case: If the first cell contains an obstacle then we got no valid way
        if(grid[0][0] == 1)
            return 0;

        int M = grid.size(), N = grid[0].size();
        
        vector<int> prevRow(N); // Tracks the tabulation values for the previous row
        vector<int> currRow(N); // Tracks the tabulation values for the current row
        currRow[0] = 1;

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If the current cell contains an obstacle then fill the value by 0
                if(grid[R][C] == 1)
                    currRow[C] = 0;

                // If its the first row then fill the value for the cell
                else if(R == 0 && C > 0)
                    currRow[C] = currRow[C-1];

                // If its the first column then fill the value for the cell
                else if(R > 0 && C == 0)
                    currRow[C] = prevRow[C];
                    
                // Else then fill the table value by adding the total number of ways to reach the current cell
                else if(R > 0 && C > 0)
                    currRow[C] = prevRow[C] + currRow[C-1];
            }
            // Update the table for the upcoming row 
            prevRow = currRow;
        }

        // Return the total number of ways to reach the bottom-right cell
        return currRow[N-1];
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearence for both "windows" and "linux" user
        system("cls || clear");

        // Input section for the number of "rows" and "columns" of the matrix
        int M, N;
        cout<<"Enter the number of rows for the matrix: "   ; cin>>M;
        cout<<"Enter the number of columns for the matrix: "; cin>>N;

        // Check for the given size of "rows" and "columns" is valid or not
        if(M <= 0 || N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Initialize the number of "rows" and "columns" of the matrix
        vector<vector<int>> grid(M, vector<int>(N));
        cout<<"\nEnter the values for the matrix (\'1\' means the cell contains obstacle | \'0\' means the cell contains no obstacle):\n";

        // Input section for values of the matrix
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                cin>>grid[R][C];
            }
        }
        
        // Call to find the total number of distinct ways
        BottomUp bottomUp;    
        cout<<"The number of possible unique paths that the robot can take to reach the bottom-right corner is: "<<bottomUp.uniquePathsWithObstacles_V3(grid)<<'\n';

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\nPress \'R\' to restart the application, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false;
    }

    return 0;
}
/*
    Topics: Maths | Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/unique-paths-ii/description/
*/
