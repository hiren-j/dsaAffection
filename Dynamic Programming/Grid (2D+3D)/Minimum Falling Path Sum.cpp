// Program to find the minimum sum of any falling path through the matrix ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public: 
    // Method to find the minimum sum of any falling path, using recursion with memoization - O(N^2) & O(N^2)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();

        // Stores the "minimum falling path sum / result value"
        int minPathSum = INT_MAX;

        // 2D buffer for memoization
        vector<vector<int>> memory(N+1, vector<int>(N+1, INT_MAX));
        
        // Explore the "falling path of minimum sum" from each column of the first row
        for(int C=0; C<N; C++) {
            minPathSum = min(minPathSum, solveWithMemo(grid, memory, N, 0, C));
        }

        // Return the "minimum falling path sum / result value"
        return minPathSum;
    }

private:
    // O(N^2) & O(N^2)
    int solveWithMemo(vector<vector<int>>& grid, vector<vector<int>>& memory, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(R < 0 || C < 0 || R >= N || C >= N)
            return INT_MAX; // Requires to handle the "minimum sum" correctly

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != INT_MAX)
            return memory[R][C];

        // There are always three possibilities to perform at each cell
        int moveToPrevColumn = solveWithMemo(grid, memory, N, R+1, C-1); // Is to move to the left column in the next row
        int moveToSameColumn = solveWithMemo(grid, memory, N, R+1, C);   // Is to move to the same column in the next row
        int moveToNextColumn = solveWithMemo(grid, memory, N, R+1, C+1); // Is to move to the right column in the next row

        // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
        int minElement = min({moveToPrevColumn, moveToSameColumn, moveToNextColumn});

        // Add the value of the current cell with the minimum element then store the sum to the "memoization table" and then return the sum
        return memory[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }

    // O(3^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(R < 0 || C < 0 || R >= N || C >= N)
            return INT_MAX; // Requires to handle the "minimum sum" correctly

        // There are always three possibilities to perform at each cell
        int moveToPrevColumn = solveWithoutMemo(grid, N, R+1, C-1); // Is to move to the left column in the next row
        int moveToSameColumn = solveWithoutMemo(grid, N, R+1, C);   // Is to move to the same column in the next row
        int moveToNextColumn = solveWithoutMemo(grid, N, R+1, C+1); // Is to move to the right column in the next row

        // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
        int minElement = min({moveToPrevColumn, moveToSameColumn, moveToNextColumn});

        // Add the value of the current cell with the minimum element and then return the sum
        return grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public: 
    // #1 Method to find the minimum sum of any falling path, using 2D buffer for tabulation - O(N^2) & O(N^2)
    int minFallingPathSum_V1(vector<vector<int>>& grid) {
        int N = grid.size();

        // Tabulation buffer: dp[R][C] represents the minimum sum of a falling path from the topmost row to the cell (R, C)
        vector<vector<int>> dp(N, vector<int>(N, 0));

        // Store the first row of the grid to the buffer
        dp[0] = grid[0];

        // Iterate each row of the grid
        for(int R=1; R<N; R++) {
            // Iterate each column of the current row
            for(int C=0; C<N; C++) {
                int numFromSameCol = dp[R-1][C];                          // Stores the value of the same column of the previous row    
                int numFromPrevCol = (C-1 >= 0) ? dp[R-1][C-1] : INT_MAX; // Stores the value of the previous column of the previous row 
                int numFromNextCol = (C+1 <  N) ? dp[R-1][C+1] : INT_MAX; // Stores the value of the next column of the previous row    
                // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
                dp[R][C] = grid[R][C] + min({numFromSameCol, numFromPrevCol, numFromNextCol});
            }
        }        

        // Find and return the "minimum falling path sum / result value" from the last row of the 2D buffer
        return *min_element(begin(dp[N-1]), end(dp[N-1]));
    }

    // #2 Method to find the minimum sum of any falling path, using 1D buffer for tabulation - O(N^2) & O(N)
    int minFallingPathSum_V2(vector<vector<int>>& grid) {
        int N = grid.size();

        vector<int> prevRow(N); // Tracks the tabulation values of any current row
        vector<int> currRow(N); // Tracks the tabulation values of the previous row of the current row
        
        // Store the first row of the grid to the buffer
        prevRow = grid[0];

        // Iterate the remaining rows of the grid
        for(int R=1; R<N; R++) {
            // Iterate each column of the current row
            for(int C=0; C<N; C++) {
                int numFromSameCol = prevRow[C];                          // Stores the value of the same column of the previous row    
                int numFromPrevCol = (C-1 >= 0) ? prevRow[C-1] : INT_MAX; // Stores the value of the previous column of the previous row  
                int numFromNextCol = (C+1 <  N) ? prevRow[C+1] : INT_MAX; // Stores the value of the next column of the previous row     
                // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
                currRow[C] = grid[R][C] + min({numFromSameCol, numFromPrevCol, numFromNextCol});
            }
            // Update the previous row of the upcoming row
            prevRow = currRow;
        }        

        // Find and return the "minimum falling path sum / result value" from the last row of the 1D buffer
        return *min_element(begin(prevRow), end(prevRow));
    }

    // #3 Method to find the minimum sum of any falling path, using constant auxiliary space - O(N^2) & O(1)
    int minFallingPathSum_V3(vector<vector<int>>& grid) {
        int N = grid.size();

        // Iterate each row of the grid 
        for(int R=1; R<N; R++) {
            // Iterate each column of the current row
            for(int C=0; C<N; C++) {
                int numFromSameCol = grid[R-1][C];                          // Stores the value of the same column of the previous row    
                int numFromPrevCol = (C-1 >= 0) ? grid[R-1][C-1] : INT_MAX; // Stores the value of the previous column of the previous row
                int numFromNextCol = (C+1 <  N) ? grid[R-1][C+1] : INT_MAX; // Stores the value of the next column of the previous row    
                // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
                grid[R][C] += min({numFromSameCol, numFromPrevCol, numFromNextCol});
            }
        }        

        // Find and return the "minimum falling path sum / result value" from the last row of the grid
        return *min_element(begin(grid[N-1]), end(grid[N-1]));
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApplication = true;

    while(userRunsApplication) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the size of the grid
        int size;
        cout<<"The application will consider square matrix! Enter the size of the grid: ";
        cin>>size;

        // Check the given size is lying within the problem constraints or not
        if(size < 1 || size > 100) {
            cout<<"You must enter a size which lies between 1 and 100!";
        }
        else {
            // Stores the value of the grid
            vector<vector<int>> grid(size, vector<int>(size, 0));

            // Input the values of the grid
            for(int R = 0; R < size; ++R) {
                for(int C = 0; C < size;) {
                    cout<<"Enter value of the "<<C<<"th column of the "<<R<<"th row: ";
                    cin>>grid[R][C];
                    // Check the given value is lying within the problem constraints or not
                    if(grid[R][C] < -100 || grid[R][C] > 100) {
                        cout<<"You must enter a value which lies between -100 and 100!\n";
                    }
                    else {
                        ++C;
                    }
                }
            }

            // Call to find the minimum sum of any falling path
            BottomUp bottomUp;
            int minPathSum = bottomUp.minFallingPathSum_V3(grid);
            cout<<"\nThe minimum sum of any falling path through the matrix is: "<<minPathSum;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userRunsApplication = (userChoice == 'R');
    }
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/minimum-falling-path-sum/description/
*/
