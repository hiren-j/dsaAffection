// Program to find the maximum amount of gold you can collect under the specified conditions ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Solution class:
class Solution {
    int N, M;
    vector<vector<int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
//                                      Up      Down     Left    Right

    // Method to find the maximum gold you can collect from the specifed cell :-
    int backtrack(vector<vector<int>>& grid, int R, int C) {
        // Edge case: If at any point you walk outside of the grid or walked into the cell not containing gold then you can't find gold anymore
        if(R < 0 || C < 0 || R == N || C == M || grid[R][C] == 0)
            return 0;

        // Stores the maximum gold you can collect from the current cell
        int currMaxGold = 0;

        // Mark the cell as visited
        int gridElement = grid[R][C];
        grid[R][C] = 0;

        // Explore all the 4 directions one by one from the current cell
        for(auto& dir : directions) {
            // Find the maximum gold you can collect and update the result by the maximum value each time
            currMaxGold = max(currMaxGold, gridElement + backtrack(grid, R + dir[0], C + dir[1]));
        }

        // Mark the cell as unvisited
        grid[R][C] = gridElement;                                                           

        // Return the maximum gold you can collect from the current cell
        return currMaxGold;
    }

public:
    // Method to find the maximum amount of gold you can collect under the specified conditions - O(4^(N*M)) & O(N*M)
    int getMaximumGold(vector<vector<int>>& grid) {
        N = grid.size(), M = grid[0].size();

        // Stores the maximum gold you can collect from the grid (result value)
        int resMaxGold = 0;

        // Consider each cell (cell containing gold) as a start point and find the maximum gold you can collect from it and then update the result value by the maximum value each time 
        for(int R = 0; R < N; ++R) {
            for(int C = 0; C < M; ++C) {
                if(grid[R][C] != 0) {
                    resMaxGold = max(resMaxGold, backtrack(grid, R, C));
                }
            }
        }

        // Return the maximum gold you can collect from the gird
        return resMaxGold;   
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both windows and linux user
        system("cls || clear");

        cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the row size
        int N;
        cout<<"Enter the total number of rows: ";
        cin>>N;

        // Input the column size
        int M;
        cout<<"Enter the total number of columns: ";
        cin>>M;

        // Check the given values are lying within the problem constraints or not
        if(N < 1 || N > 15 || M < 1 || M > 15) {
            cout<<"You must the row and column size which lies between 1 and 15!";
        } 
        else {
            vector<vector<int>> grid(N, vector<int>(M, 0));

            // Input the grid values
            cout<<"\nNote: Each cell in the grid with positive integer will be considered as the amount of gold in that cell or empty if 0!\n";
            for(int R = 0; R < N; ++R) { 
                for(int C = 0; C < M;) {
                    cout<<"Enter value of "<<C<<"th column of the "<<R<<"th row: ";
                    cin>>grid[R][C];
                    if(grid[R][C] < 0 || grid[R][C] > 100) {
                        cout<<"You must enter a value which lies between 0 and 100!\n";
                    }
                    else {
                        ++C;
                    }
                }
            }

            // Call to find the maximum amount of gold you can collect under the specified conditions 
            Solution solution;
            cout<<"\nThe maximum amount of gold you can collect is: "<<solution.getMaximumGold(grid);
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application else it will exit: ";
        cin>>userChoice;
        userRunsApp = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Backtracking | Matrix
    Link: https://leetcode.com/problems/path-with-maximum-gold/description/
*/
