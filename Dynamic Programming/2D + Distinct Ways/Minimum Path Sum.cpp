// Program to find a path from top left to bottom right, which minimizes the sum of all numbers along its path ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "top down approach":
class TopDown {
public:
    // Method to find the path having the minimized sum to reach the bottom-right cell, using recursion with memoization - O(M*N) & O(M*N)
    int minPathSum(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        vector<vector<int>> memo(M+1, vector<int>(N+1, -1));
        return solveWithMemo(grid, memo, M, N, 0, 0);
    }

private:
    // O(2(M*N)) & O(M+N)
    int solveWithoutMemo(vector<vector<int>>& grid, int M, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(R >= M || C >= N)
            return INT_MAX; // Requires to update the "minimum sum" correctly

        // Edge case: If reached the bottom-right corner then return the value of the current cell
        if(R == M-1 && C == N-1)
            return grid[R][C];

        // There are always two possibilities at each cell
        int moveDown  = solveWithoutMemo(grid, M, N, R+1, C); // Is to go down from the current cell
        int moveRight = solveWithoutMemo(grid, M, N, R, C+1); // Is to go right from the current cell

        // As we're striving for the "minimum sum" thus store the minimum element from both the possibilities
        int minElement = min(moveDown, moveRight);

        // Add the value of the current cell with the minimum element and then return the sum
        return grid[R][C] + (minElement == INT_MAX ? 0 : minElement); 
    }

    // O(M*N) & O(M*N)
    int solveWithMemo(vector<vector<int>>& grid, vector<vector<int>>& memo, int M, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(R >= M || C >= N)
            return INT_MAX; // Requires to update the "minimum sum" correctly

        // Edge case: If reached the bottom-right corner then return the value of the current cell
        if(R == M-1 && C == N-1)
            return grid[R][C];

        // Memoization table: If the current state is already computed then return the computed value
        if(memo[R][C] != -1)
            return memo[R][C];

        // There are always two possibilities at each cell
        int moveDown  = solveWithMemo(grid, memo, M, N, R+1, C); // Is to go down from the current cell
        int moveRight = solveWithMemo(grid, memo, M, N, R, C+1); // Is to go right from the current cell

        // As we're striving for the "minimum sum" thus store the minimum element from both the possibilities
        int minElement = min(moveDown, moveRight);

        // Add the value of the current cell with the minimum element then store the sum to the "memoization table" and then return the sum
        return memo[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement); 
    }
};

// Class to implement the "bottom up approach":
class BottomUp {
public:
    // #1 Method to find the path having the minimized sum to reach the bottom-right cell, using 2D buffer for tabulation - O(M*N) & O(M*N)
    int minPathSum_V1(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        // 2D buffer for tabulation: By default it fills the value 0 for all the cells (dp[R][C]: stores the minimized sum (inclusive the cell value in the sum) to reach the cell (R, C) in the "grid")
        vector<vector<int>> dp(M, vector<int>(N));
        dp[0][0] = grid[0][0];

        // Fill the table for the first row
        for(int C=1; C<N; C++) {
            // Calculate and store the minimized sum to reach the current cell in the "grid"
            dp[0][C] = grid[0][C] + dp[0][C-1];
        }

        // Fill the table for the first column
        for(int R=1; R<M; R++) {
            // Calculate and store the minimized sum to reach the current cell in the "grid"
            dp[R][0] = grid[R][0] + dp[R-1][0];
        }

        // Fill the rest of the table
        for(int R=1; R<M; R++) {
            for(int C=1; C<N; C++) {
                // Calculate and store the minimized sum to reach the current cell in the "grid"
                dp[R][C] = grid[R][C] + min(dp[R][C-1], dp[R-1][C]);
            }
        }

        // Return the minimized sum to reach the bottom-right cell in the "grid"
        return dp[M-1][N-1];
    }

    // #2 Method to find the path having the minimized sum to reach the bottom-right cell, using 2D buffer for tabulation - O(M*N) & O(M*N)
    int minPathSum_V2(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        // 2D buffer for tabulation: By default it fills the value 0 for all the cells (dp[R][C]: stores the minimized sum (inclusive the cell value in the sum) to reach the cell (R, C) in the "grid")
        vector<vector<int>> dp(M, vector<int>(N));
        dp[0][0] = grid[0][0];

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If its the first row then fill the minimized sum to reach the current cell in the "grid"
                if(R == 0 && C > 0)
                    dp[0][C] = grid[0][C] + dp[0][C-1];

                // Else if its the first column then fill the minimized sum to reach the current cell in the "grid"
                else if(R > 0 && C == 0)
                    dp[R][0] = grid[R][0] + dp[R-1][0];

                // Else then fill the minimized sum to reach the current cell in the "grid"
                else if(R > 0 && C > 0)
                    dp[R][C] = grid[R][C] + min(dp[R][C-1], dp[R-1][C]);
            }
        }

        // Return the minimized sum to reach the bottom-right cell in the "grid"
        return dp[M-1][N-1];
    }

    // #3 Method to find the path having the minimized sum to reach the bottom-right cell, using 1D buffer for tabulation - O(M*N) & O(N)
    int minPathSum_V3(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        vector<int> prevRow(N); // Tracks the tabulation values for the previous row
        vector<int> currRow(N); // Tracks the tabulation values for any current row
        currRow[0] = grid[0][0];

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If its the first row then fill the minimized sum to reach the current cell in the "grid"
                if(R == 0 && C > 0)
                    currRow[C] = grid[0][C] + currRow[C-1];

                // Else if its the first column then fill the minimized sum to reach the current cell in the "grid"
                else if(R > 0 && C == 0)
                    currRow[C] = grid[R][0] + prevRow[C];
                    
                // Else then fill the minimized sum to reach the current cell in the "grid"
                else if(R > 0 && C > 0)
                    currRow[C] = grid[R][C] + min(currRow[C-1], prevRow[C]);
            }
            // Update the table for the upcoming row
            prevRow = currRow;
        }

        // Return the minimized sum to reach the bottom-right cell in the "grid"
        return currRow[N-1];
    }

    // #4 Method to find the path having the minimized sum to reach the bottom-right cell, using 1D buffer for tabulation - O(M*N) & O(N)
    int minPathSum_V4(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();
        
        // 1D buffer of tabulation: By default it fills the value 0 for all the cells
        vector<int> dp(N);
        dp[0] = grid[0][0];

        // Fill the table for the first row
        for(int C=1; C<N; C++) {
            // Calculate and store the minimized sum to reach the current cell in the "grid"
            dp[C] = grid[0][C] + dp[C-1];
        }

        // Update the table for the rest of the rows
        for(int R=1; R<M; R++) {
            dp[0] += grid[R][0];
            
            // Iterate and fill the table for the cells of the current row of the "grid"
            for(int C=1; C<N; C++) {
                dp[C] = grid[R][C] + min(dp[C-1], dp[C]);
            }

        }

        // Return the minimized sum to reach the bottom-right cell in the "grid"
        return dp[N-1];
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearence for both "windows" and "linux" user
        system("cls || clear");

        // Input section for the number of "rows" and "columns" of the grid
        int M, N;
        cout<<"Enter the number of rows for the grid: "   ; cin>>M;
        cout<<"Enter the number of columns for the grid: "; cin>>N;

        // Check for the given size of "rows" and "columns" is valid or not
        if(M <= 0 || N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Initialize the number of "rows" and "columns" of the grid
        vector<vector<int>> grid(M, vector<int>(N));
        cout<<"\nEnter the values for the grid:\n";

        // Input section for values of the grid
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                cin>>grid[R][C];
            }
        }
        
        // Call to find the minimized sum to reach the bottom-right cell of the grid
        BottomUp bottomUp;    
        cout<<"\nThe path having the minimum sum is: "<<bottomUp.minPathSum_V4(grid)<<'\n';

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\nPress \'R\' to restart the application, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false;
    }

    return 0;
}
// Link: https://leetcode.com/problems/minimum-path-sum/description/
