// Program to find the minimum sum of a falling path with non-zero shifts ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the minimum sum of a falling path with non zero shifts, using recursion with memoization - O(N^3) & O(N^2) : Where N let be the size of the grid
    int minFallingPathSum(vector<vector<int>>& grid) {
        int size = grid.size();
        vector<vector<int>> memory(size, vector<int>(size + 1, -1));
        return solveWithMemo(memory, grid, size, 0, -1);
    }

private:
    // O(N^3) & O(N^2)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int size, int currRow, int skipColumn) {
        // Edge case: If all the rows are exhausted then you can't pick any more elements
        if(currRow == size)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[currRow][skipColumn + 1] != -1)
            return memory[currRow][skipColumn + 1];

        // Stores the minimum sum of a falling path with non-zero shifts (result value)
        int minSum = INT_MAX;

        // Iterate each column of the current row
        for(int currColumn = 0; currColumn < size; ++currColumn) {
            // If the current column is not in the same column of its adjacent rows then pick the grid element and then move to the next row and also update the result value by the minimum sum only
            if(currColumn != skipColumn) {
                int currSum = grid[currRow][currColumn] + solveWithMemo(memory, grid, size, currRow + 1, currColumn);
                minSum = min(minSum, currSum);
            }
        }

        // Store the result value to the memoization table and then return it
        return memory[currRow][skipColumn + 1] = minSum;
    }

    // O(N^(N*N)) & O(N)
    int solveWithoutMemo(vector<vector<int>>& grid, int size, int currRow, int skipColumn) {
        // Edge case: If all the rows are exhausted then you can't pick any more elements
        if(currRow == size)
            return 0;

        // Stores the minimum sum of a falling path with non-zero shifts (result value)
        int minSum = INT_MAX;

        // Iterate each column of the current row
        for(int currColumn = 0; currColumn < size; ++currColumn) {
            // If the current column is not in the same column of its adjacent rows then pick the grid element and then move to the next row and also update the result value by the minimum sum only
            if(currColumn != skipColumn) {
                int currSum = grid[currRow][currColumn] + solveWithoutMemo(grid, size, currRow + 1, currColumn);
                minSum = min(minSum, currSum);
            }
        }

        // Return the result value
        return minSum;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the minimum sum of a falling path with non zero shifts, using 2D buffer for tabulation - O(N^3) & O(N^2) : Where N let be the size of the grid
    int minFallingPathSum_V1(vector<vector<int>>& grid) {
        int size = grid.size();

        // Tabulation buffer: dp[R][C] represents the minimum sum of a falling path from the topmost row to the Rth row reaching the Cth column with non-zero shifts
        vector<vector<int>> dp(size, vector<int>(size, INT_MAX));
        
        // Store the first row of the grid to the buffer
        dp[0] = grid[0];

        // Iterate the rows of the grid
        for(int R = 1; R < size; ++R) {
            // Iterate each column of the current row
            for(int C = 0; C < size; C++) {
                // Explore each column of non-zero shifts from the previous row
                for(int currColumn = 0; currColumn < size; ++currColumn) {
                    // If the current column is not in the same column of its adjacent rows then pick the minimum sum from it and update the result value by the minimum sum only
                    if(currColumn != C) {
                        dp[R][C] = min(dp[R][C], grid[R][C] + dp[R - 1][currColumn]);
                    }
                }
            }
        }

        // Return the minimum sum of a falling path with non-zero shifs (result value)
        return *min_element(begin(dp[size - 1]), end(dp[size - 1]));
    }

    // #2 Method to find the minimum sum of a falling path with non zero shifts, using 1D buffer for tabulation - O(N^3) & O(N) : Where N let be the size of the grid
    int minFallingPathSum_V2(vector<vector<int>>& grid) {
        int size = grid.size();

        // Tabulation buffer: Tracks the tabulation values of the previous row of the current row which is being seen
        vector<int> prevRow(size, INT_MAX); 

        // Store the first row of the grid to the buffer
        prevRow = grid[0];
    
        // Iterate the remaining rows of the grid
        for(int R = 1; R < size; ++R) {
            // Tracks the tabulation values of the current row
            vector<int> currRow(size, INT_MAX);
            // Iterate each column of the current row
            for(int C = 0; C < size; C++) {
                // Explore each column of non-zero shifts from the previous row
                for(int currColumn = 0; currColumn < size; ++currColumn) {
                    // If the current column is not in the same column of its adjacent rows then pick the minimum sum from it and update the result value by the minimum sum only
                    if(currColumn != C) {
                        currRow[C] = min(currRow[C], grid[R][C] + prevRow[currColumn]);
                    }
                }
            }
            // Update the previous row of the upcoming row
            prevRow = currRow;
        }

        // Return the minimum sum of a falling path with non-zero shifs (result value)
        return *min_element(begin(prevRow), end(prevRow));
    }

    // #3 Method to find the minimum sum of a falling path with non zero shifts, using constant auxiliary space - O(N^3) & O(1) : Where N let be the size of the grid
    int minFallingPathSum_V3(vector<vector<int>>& grid) {
        int size = grid.size();
    
        // Iterate the rows of the grid
        for(int R = 1; R < size; ++R) {
            // Iterate each column of the current row
            for(int C = 0; C < size; C++) {
                int gridElement = grid[R][C]; grid[R][C] = INT_MAX;
                // Explore each column of non-zero shifts from the previous row
                for(int currColumn = 0; currColumn < size; ++currColumn) {
                    // If the current column is not in the same column of its adjacent rows then pick the minimum sum from it and update the result value by the minimum sum only
                    if(currColumn != C) {
                        grid[R][C] = min(grid[R][C], gridElement + grid[R - 1][currColumn]);
                    }
                }
            }
        }

        // Return the minimum sum of a falling path with non-zero shifs (result value)
        return *min_element(begin(grid[size - 1]), end(grid[size - 1]));
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
        cout<<"The application considers square matrix! Enter the size of the grid: ";
        cin>>size;

        // Check the given size is lying within the problem constraints or not
        if(size < 1 || size > 200) {
            cout<<"You must enter a size which lies between 1 and 200!";
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
                    if(grid[R][C] < -99 || grid[R][C] > 99) {
                        cout<<"You must enter a value which lies between -99 and 99!\n";
                    }
                    else {
                        ++C;
                    }
                }
            }

            // Call to find the minimum sum of a falling path with non-zero shifts
            BottomUp bottomUp;
            int minSum = bottomUp.minFallingPathSum_V3(grid);
            cout<<"\nThe minimum sum of a falling path with non-zero shifts is: "<<minSum;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userRunsApplication = (userChoice == 'R');
    }
    
    return 0;
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/minimum-falling-path-sum-ii/description/?envType=daily-question&envId=2024-04-26
*/
