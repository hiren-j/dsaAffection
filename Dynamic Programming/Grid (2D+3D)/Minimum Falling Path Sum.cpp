// Program to find the minimum sum of any falling path through matrix ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach"
class TopDown {
public: 
    // Method to find the minimum sum of any falling path, using recursion with memoization - O(N^3) & O(N^2)
    int minFallingPathSum(vector<vector<int>>& grid) {
        int N = grid.size();

        // Stores the "minimum falling path sum / resultant value"
        int minPathSum = INT_MAX;

        // 2D buffer for memoization
        vector<vector<int>> cache(N+1, vector<int>(N+1, INT_MAX));
        
        // Explore the "falling path of minimum sum" from each column of the first row
        for(int C=0; C<N; C++) {
            minPathSum = min(minPathSum, solveWithMemo(grid, cache, N, 0, C));
        }

        // Return the "minimum falling path sum / resultant value"
        return minPathSum;
    }

private:
    // O(N(3^(N*N))) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(R < 0 || C < 0 || R >= N || C >= N)
            return INT_MAX; // Requires to handle the "minimum sum" correctly

        // There are always three possibilities at each cell
        int moveToPrevColumn = solveWithoutMemo(grid, N, R+1, C-1); // Is to move to the left column in the next row
        int moveToSameColumn = solveWithoutMemo(grid, N, R+1, C);   // Is to move to the same column in the next row
        int moveToNextColumn = solveWithoutMemo(grid, N, R+1, C+1); // Is to move to the right column in the next row

        // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
        int minElement = min({moveToPrevColumn, moveToSameColumn, moveToNextColumn});

        // Add the value of the current cell with the minimum element and then return the sum
        return grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }

    // O(N^3) & O(N^2)
    int solveWithMemo(vector<vector<int>>& grid, vector<vector<int>>& cache, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then we have no values left
        if(R < 0 || C < 0 || R >= N || C >= N)
            return INT_MAX; // Requires to handle the "minimum sum" correctly

        // Memoization table: If the current state is already computed then return the computed value
        if(cache[R][C] != INT_MAX)
            return cache[R][C];

        // There are always three possibilities at each cell
        int moveToPrevColumn = solveWithMemo(grid, cache, N, R+1, C-1); // Is to move to the left column in the next row
        int moveToSameColumn = solveWithMemo(grid, cache, N, R+1, C);   // Is to move to the same column in the next row
        int moveToNextColumn = solveWithMemo(grid, cache, N, R+1, C+1); // Is to move to the right column in the next row

        // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
        int minElement = min({moveToPrevColumn, moveToSameColumn, moveToNextColumn});

        // Add the value of the current cell with the minimum element then store the sum to the "memoization table" and then return the sum
        return cache[R][C] = grid[R][C] + (minElement == INT_MAX ? 0 : minElement);
    }
};

// Class to implement the "Bottom Up Approach"
class BottomUp {
public: 
    // #1 Method to find the minimum sum of any falling path, using 2D buffer for tabulation - O(N^2) & O(N^2)
    int minFallingPathSum_V1(vector<vector<int>>& grid) {
        int N = grid.size();

        // 2D buffer for tabulation: For each cell "(R,C)" of "dp" represents the "minimum path sum" needed to reach that cell in the "grid"
        vector<vector<int>> dp(N, vector<int>(N, 0));
        dp[0] = grid[0];

        for(int R=1; R<N; R++) {
            for(int C=0; C<N; C++) {
                int numFromSameCol = dp[R-1][C];                          // Stores the value of the same column of the previous row    
                int numFromPrevCol = (C-1 >= 0) ? dp[R-1][C-1] : INT_MAX; // Stores the value of the previous column of the previous row 
                int numFromNextCol = (C+1 <  N) ? dp[R-1][C+1] : INT_MAX; // Stores the value of the next column of the previous row    
                // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
                dp[R][C] = grid[R][C] + min({numFromSameCol, numFromPrevCol, numFromNextCol});
            }
        }        

        // Find and return the "minimum falling path sum / resultant value" from the last row of the 2D buffer
        return *min_element(begin(dp[N-1]), end(dp[N-1]));
    }

    // #2 Method to find the minimum sum of any falling path, using 1D buffer for tabulation - O(N^2) & O(N)
    int minFallingPathSum_V2(vector<vector<int>>& grid) {
        int N = grid.size();

        vector<int> prevRow(N);
        vector<int> currRow(N);
        prevRow = grid[0];

        for(int R=1; R<N; R++) {
            for(int C=0; C<N; C++) {
                int numFromSameCol = prevRow[C];                          // Stores the value of the same column of the previous row    
                int numFromPrevCol = (C-1 >= 0) ? prevRow[C-1] : INT_MAX; // Stores the value of the previous column of the previous row  
                int numFromNextCol = (C+1 <  N) ? prevRow[C+1] : INT_MAX; // Stores the value of the next column of the previous row     
                // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
                currRow[C] = grid[R][C] + min({numFromSameCol, numFromPrevCol, numFromNextCol});
            }
            // Update the previous row for the upcoming row
            prevRow = currRow;
        }        

        // Find and return the "minimum falling path sum / resultant value" from the last row of the 2D buffer
        return *min_element(begin(prevRow), end(prevRow));
    }

    // #3 Method to find the minimum sum of any falling path, using constant auxiliary space - O(N^2) & O(1)
    int minFallingPathSum_V3(vector<vector<int>>& grid) {
        int N = grid.size();
        int minPathSum = INT_MAX;
        
        for(int R=1; R<N; R++) {
            for(int C=0; C<N; C++) {
                int numFromSameCol = grid[R-1][C];                          // Stores the value of the same column of the previous row    
                int numFromPrevCol = (C-1 >= 0) ? grid[R-1][C-1] : INT_MAX; // Stores the value of the previous column of the previous row
                int numFromNextCol = (C+1 <  N) ? grid[R-1][C+1] : INT_MAX; // Stores the value of the next column of the previous row    
                // As we're striving for the "minimum falling path sum" thus store the minimum element from all the possibilities
                grid[R][C] += min({numFromSameCol, numFromPrevCol, numFromNextCol});
            }
        }        

        // Find and return the "minimum falling path sum / resultant value" from the last row of the 2D buffer
        return *min_element(begin(grid[N-1]), end(grid[N-1]));
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the "matrix"
        int N;
        cout<<"Note: Application will consider square matrix!\n\nEnter the size of the matrix: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Stores the values of the "matrix"
        vector<vector<int>> grid(N, vector<int>(N, 0));
        cout<<"\nEnter the values of the matrix:\n";

        // Input the values of the "matrix"
        for(int R=0; R<N; R++) {
            for(int C=0; C<N; C++) {
                cin>>grid[R][C];
            }
        }

        // Call to find the minimum sum of any falling path
        BottomUp bottomUp;
        int minPathSum = bottomUp.minFallingPathSum_V3(grid);
        cout<<"The minimum sum of any falling path is: "<<minPathSum;


        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        canPerformOperation = (userChoise == 'R') ? true : false ;
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/minimum-falling-path-sum/description/
*/
