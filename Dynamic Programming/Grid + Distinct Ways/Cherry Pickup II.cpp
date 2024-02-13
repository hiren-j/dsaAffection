// Program to find the maximum number of cherries collected by both the robots by following the mentioned rules ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach"
class TopDown {
    int M, N;

    // O(9^(M*N)) & O(M+N)
    int solveWithoutMemo(vector<vector<int>>& grid, int R, int C1, int C2) {
        // Edge case: When all the cells are exhausted then its not possible to collect more cherries
        if(R >= M || C1 < 0 || C1 >= N || C2 < 0 || C2 >= N)
            return 0;

        // If both the robots are not at same column then collect the cherries from both of them, else collect it from any one robot
        int currCherries = (C1 != C2 ? grid[R][C1] + grid[R][C2] : grid[R][C1]);

        // Stores the "maximum number of cherries collected" by anyone from all the 9 possibilities
        int maxFromAll = 0;

        // Explore all the 3 possibilities of robot2 from each possibility of robot1
        for(int val1 = -1; val1 <= 1; ++val1) {
            for(int val2 = -1; val2 <= 1; ++val2) {
                maxFromAll = max(maxFromAll, solveWithoutMemo(grid, R + 1, C1 + val1, C2 + val2));
            }
        }

        // Return the value of "total number of cherries collected"
        return maxFromAll + currCherries;
    }

    // O(M*N*N) & O(M*N*N)
    int solveWithMemo(vector<vector<int>>& grid, vector<vector<vector<int>>>& memory, int R, int C1, int C2) {
        // Edge case: When all the cells are exhausted then its not possible to collect more cherries
        if(R >= M || C1 < 0 || C1 >= N || C2 < 0 || C2 >= N)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C1][C2] != -1)
            return memory[R][C1][C2];

        // If both the robots are not at same column then collect the cherries from both of them, else collect it from any one robot
        int currCherries = (C1 != C2 ? grid[R][C1] + grid[R][C2] : grid[R][C1]);

        // Stores the "maximum number of cherries collected" by anyone from all the 9 possibilities
        int maxFromAll = 0;

        // Explore all the 3 possibilities of robot2 from each possibility of robot1
        for(int val1 = -1; val1 <= 1; ++val1) {
            for(int val2 = -1; val2 <= 1; ++val2) {
                maxFromAll = max(maxFromAll, solveWithMemo(grid, memory, R + 1, C1 + val1, C2 + val2));
            }
        }

        // Store the value of "total number of cherries collected" to the "memoization table" and then return it
        return memory[R][C1][C2] = maxFromAll + currCherries;
    }


public:
    // Method to find the maximum number of cherries collected by both the robots, using recursion with memoization - O(M*N*N) & O(M*N*N)
    int cherryPickup(vector<vector<int>>& grid) {
        M = grid.size(), N = grid[0].size();
        vector<vector<vector<int>>> memory(M+1, vector<vector<int>>(N+1, vector<int>(N+1, -1)));
        return solveWithMemo(grid, memory, 0, 0, N-1);
    }
};

// Class to implement the "Bottom Up Approach"
class BottomUp {
public:
    // #1 Method to find the maximum number of cherries collected by both the robots, using 3D buffer for tabulation - O(M*N*N) & O(M*N*N)
    int cherryPickup_V1(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        // Tabulation buffer: For each cell (R, C1, C2) in "dp", stores the maximum number of cherries collected by both the robots, in which, from robot1 by being at (R, C1) cell and robot2 by being at (R, C2) cell
        vector<vector<vector<int>>> dp(M+1, vector<vector<int>>(N+1, vector<int>(N+1, 0)));

        // If there is only a single cell it means both the robots are at same column hence collect the cherries from any one robot, else collect the cherries from both of them 
        dp[0][0][N-1] = (N == 1 ? grid[0][0] : grid[0][0] + grid[0][N-1]);

        // Iterate and fill the values of the tabulation buffer
        for(int R = 1; R < M; R++) {
            // Move to the maximum number of cells the robot1 can move at each row
            for(int C1 = 0; C1 <= min(R, N-1); C1++) {
                // Move to the maximum number of cells the robot2 can move at each row
                for(int C2 = max(N-R-1, 0); C2 < N; C2++) {
                    // Stores the maximum number of cherries collected by both the robots till the previous row
                    int prevMaxCherries = 0;
                    // Explore all the 3 possibilities of robot2 from each possibility of robot1
                    for(int prevRowC1 = max(C1-1, 0); prevRowC1 <= min(C1+1, N-1); prevRowC1++) {
                        for(int prevRowC2 = max(C2-1, 0); prevRowC2 <= min(C2+1, N-1); prevRowC2++) {
                            prevMaxCherries = max(prevMaxCherries, dp[R-1][prevRowC1][prevRowC2]);
                        }
                    }
                    // If both the robots are not at same column then collect the cherries from both of them, else collect it from any one robot
                    dp[R][C1][C2] = prevMaxCherries + grid[R][C1];
                    dp[R][C1][C2] += (C1 != C2 ? grid[R][C2] : 0); 
                }
            } 
        }

        // Stores the value of "maximum number of cherries collected / result value" from the last row of the 3D buffer
        int maxFromAll = 0;

        // Iterate the last row of the 3D buffer
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                maxFromAll = max(maxFromAll, dp[M-1][i][j]);
            }
        }

        // Return the value of "maximum number of cherries collected" by both the robots
        return maxFromAll;
    }

    // #2 Method to find the maximum number of cherries collected by both the robots, using 2D buffer for tabulation - O(M*N*N) & O(N*N)
    int cherryPickup_V2(vector<vector<int>>& grid) {
        int M = grid.size(), N = grid[0].size();

        vector<vector<int>> currRow(N+1, vector<int>(N+1, 0)); // Stores the tabulation values for any current row
        vector<vector<int>> prevRow(N+1, vector<int>(N+1, 0)); // Stores the tabulation values for the previous row of the current row

        // If there is only a single cell it means both the robots are at same column hence collect the cherries from any one robot, else collect the cherries from both of them 
        prevRow[0][N-1] = (N == 1 ? grid[0][0] : grid[0][0] + grid[0][N-1]);

        // Iterate and fill the values of the tabulation buffer
        for(int R = 1; R < M; R++) {
            // Move to the maximum number of cells the robot1 can move at each row
            for(int C1 = 0; C1 <= min(R, N-1); C1++) {
                // Move to the maximum number of cells the robot2 can move at each row
                for(int C2 = max(N-R-1, 0); C2 < N; C2++) {
                    // Stores the maximum number of cherries collected by both the robots till the previous row
                    int prevMaxCherries = 0;                    
                    // Explore all the 3 possibilities of robot2 from each possibility of robot1
                    for(int prevRowC1 = max(C1-1, 0); prevRowC1 <= min(C1+1, N-1); prevRowC1++) {
                        for(int prevRowC2 = max(C2-1, 0); prevRowC2 <= min(C2+1, N-1); prevRowC2++) {
                            prevMaxCherries = max(prevMaxCherries, prevRow[prevRowC1][prevRowC2]);
                        }
                    }
                    // If both the robots are not at same column then collect the cherries from both of them, else collect it from any one robot
                    currRow[C1][C2] = prevMaxCherries + grid[R][C1];
                    currRow[C1][C2] += (C1 != C2 ? grid[R][C2] : 0); 
                }
            }
            // Update the previous row (2D buffer) for the upcoming row (2D buffer)
            prevRow = currRow; 
        }

        // Stores the value of "maximum number of cherries collected / result value" from the last row of the 3D buffer
        int maxFromAll = 0;

        // Iterate the last row of the 3D buffer
        for(int i=0; i<N; i++) {
            for(int j=0; j<N; j++) {
                maxFromAll = max(maxFromAll, currRow[i][j]);
            }
        }

        // Return the value of "maximum number of cherries collected" by both the robots
        return maxFromAll;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the grid
        int M, N;
        cout<<"Enter the number of rows of the grid: "   ; cin>>M;
        cout<<"Enter the number of columns of the grid: "; cin>>N;

        // Check the given size is valid or not
        if(M <= 0 || N <= 0) {
            cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }

        // Stores the values of the grid
        vector<vector<int>> grid(M, vector<int>(N, 0));

        // Input the values of the grid
        cout<<"\nEnter the values of the matrix:\n";
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                cin>>grid[R][C];
            }
        }

        // Call to find the maximum number of cherries collected by both the robots
        BottomUp bottomUp;
        int maxCherries = bottomUp.cherryPickup_V2(grid);
        cout<<"The maximum number of cherries collected by both the robots is: "<<maxCherries;

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/cherry-pickup-ii/description/
*/
