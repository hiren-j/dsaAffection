// Program to find the total number of paths you can take from the points (X, Y) to reach the origin (0, 0) ~ coded by Hiren
#include <iostream>
#include <vector>
#define mod 1000000007;
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the total number of paths from points to the origin, using recursion with memoization - O(X*Y) & O(X*Y)
    int numPaths(int X, int Y) {
        vector<vector<int>> memory(X + 1, vector<int>(Y + 1, -1));
        return solveWithMemo(memory, X, Y);
    }

private:    
    // O(X*Y) & O(X*Y)
    int solveWithMemo(vector<vector<int>>& memory, int X, int Y) {
        // Edge case: If the points reaches the origin (0, 0) then you've one valid path
        if(X == 0 && Y == 0)
            return 1;
        
        // Edge case: If the points becomes negative then you've no valid path
        if(X < 0 || Y < 0)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[X][Y] != -1)
            return memory[X][Y];

        // There are always two possibilites to perform at each step
        int numPathsFromX = solveWithMemo(memory, X - 1, Y); // Is to move one-step to the up-side 
        int numPathsFromY = solveWithMemo(memory, X, Y - 1); // Is to move one-step to the left-side 

        // Store the value of the total number of paths to the memoization table and then return it
        return memory[X][Y] = (numPathsFromX + numPathsFromY) % mod;
    }

    // O(2^(X*Y)) & O(X+Y)
    int solveWithoutMemo(int X, int Y) {
        // Edge case: If the points reaches the origin (0, 0) then you've one valid path
        if(X == 0 && Y == 0)
            return 1;
            
        // Edge case: If the points becomes negative then you've no valid path
        if(X < 0 || Y < 0)
            return 0;
            
        // There are always two possibilites to perform at each step
        int numPathsFromX = solveWithoutMemo(X - 1, Y); // Is to move one-step to the up-side 
        int numPathsFromY = solveWithoutMemo(X, Y - 1); // Is to move one-step to the left-side

        // Return the value of the total number of paths
        return (numPathsFromX + numPathsFromY) % mod;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the total number of paths from points to the origin, using 2D buffer for tabulation - O(X*Y) & O(X*Y)
    int numPaths_V1(int X, int Y) {        
        // Tabulation buffer: dp[R][C] represents the total number of paths you can take to reach the origin (0, 0) from the cell (R, C)
        vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 1));
        
        // Iterate and find the total number of paths you can take to reach the origin from each cell
        for(int R = 1; R <= X; ++R) {
            for(int C = 1; C <= Y; ++C) {
                // There are always two possibilites to perform at each step
                int numPathsFromX = dp[R - 1][C]; // Is to move one-step to the up-side 
                int numPathsFromY = dp[R][C - 1]; // Is to move one-step to the left-side
                // Store the total number of paths you can take to reach the origin (0, 0) from the cell (R, C)
                dp[R][C] = (numPathsFromX + numPathsFromY) % mod; 
            }
        }
        
        // Return the total number of paths you can take to reach the origin (0, 0) from the points (X, Y)
        return dp[X][Y];
    }

    // Method to find the total number of paths from points to the origin, using 1D buffer for tabulation - O(X*Y) & O(Y)
    int numPaths_V2(int X, int Y) {
        vector<int> currRow(Y + 1, 1); // Tracks the tabulation values of any current row 
        vector<int> prevRow(Y + 1, 1); // Tracks the tabulation values of the previous row of the current row 

        // Iterate and find the total number of paths you can take to reach the origin from each cell
        for(int R = 1; R <= X; ++R) {
            for(int C = 1; C <= Y; ++C) {
                // There are always two possibilites to perform at each step
                int numPathsFromX = prevRow[C];     // Is to move one-step to the up-side 
                int numPathsFromY = currRow[C - 1]; // Is to move one-step to the left-side
                // Store the total number of paths you can take to reach the origin (0, 0) from the cell (R, C)
                currRow[C] = (numPathsFromX + numPathsFromY) % mod; 
            }
            // Update the previous row of the upcoming row
            prevRow = currRow;
        }
        
        // Return the total number of paths you can take to reach the origin (0, 0) from the points (X, Y)
        return prevRow[Y];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the value of X and Y
        int X, Y;
        cout<<"Enter the value of X and Y: ";
        cin>>X>>Y;

        // Check the given values are lying within the problem constraints or not
        if(X < 0 || X > 500 || Y < 0 || Y > 500) {
            cout<<"You must enter the value of X and Y, which lies between 0 and 500!";
        }
        else {
            // Call to find the total number of paths you can take from the points (X, Y) to the origin (0, 0)
            BottomUp bottomUp;
            cout<<"The total number of paths you can take from the points ("<<X<<", "<<Y<<") to reach the origin (0, 0) is: "<<bottomUp.numPaths_V2(X, Y);
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://www.geeksforgeeks.org/problems/paths-to-reach-origin3850/1
*/
