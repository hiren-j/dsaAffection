// Program to find the number of possible unique paths that the robot can take to reach the bottom-right corner ~ coded by Hiren
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDownDP {
public:
    // Method to find the number of possible unique paths, using recursion with memoization - O(M*N) & O(M*N)
    int uniquePaths(int M, int N) {
        vector<vector<int>> memo(M+1, vector<int>(N+1, -1));
        return solveWithMemo(M, N, 0, 0, memo);
    }

private:
    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(int M, int N, int R = 0, int C = 0) {
        // Edge case: If all the cells are exhausted then we got no valid way
        if(R >= M || C >= N)
            return 0;

        // Edge case: If reached the bottom up corner then we got one valid way
        if(R == M-1 && C == N-1)
            return 1;   

        // There are always two possibilities at each cell
        int moveDown  = solveWithoutMemo(M, N, R+1, C); // Is to move to the down cell from the current cell
        int moveRight = solveWithoutMemo(M, N, R, C+1); // Is to move to the right cell from the current cell

        // Return the total number of ways got from both the possibilities
        return moveDown + moveRight;
    }

    // O(M*N) & O(M*N)
    int solveWithMemo(int M, int N, int R, int C, vector<vector<int>>& memo) {
        // Edge case: If all the cells are exhausted then we got no valid way
        if(R >= M || C >= N)
            return 0;

        // Edge case: If reached the bottom up corner then we got one valid way
        if(R == M-1 && C == N-1)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value 
        if(memo[R][C] != -1)
            return memo[R][C];

        // There are always two possibilities at each cell
        int moveDown  = solveWithMemo(M, N, R+1, C, memo); // Is to move to the down cell from the current cell
        int moveRight = solveWithMemo(M, N, R, C+1, memo); // Is to move to the right cell from the current cell

        // Store and return the total number of ways got from both the possibilities
        return memo[R][C] = moveDown + moveRight;
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUpDP {
public:
    // #1 Method to find the number of possible unique paths, using 2D buffer - O(M*N) & O(M*N)
    int uniquePaths_V1(int M, int N) {
        // 2D buffer for tabulation: By default it fills the value 0 for all the cells (dp[R][C]: represents the number of possible unique paths to reach the square (R, C) in the grid)
        vector<vector<int>> dp(M, vector<int>(N)); 

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If its the "first row / first column" then fill the table value by 1
                if(R == 0 || C == 0)
                    dp[R][C] = 1;
                // Else then fill the table value by adding the total number of ways to reach the current cell
                else
                    dp[R][C] = dp[R-1][C] + dp[R][C-1];
            }
        }

        // Return the total number of ways to reach the bottom-right cell
        return dp[M-1][N-1];
    }

    // #2 Method to find the number of possible unique paths, using buffer only - O(M*N) & O(N)
    int uniquePaths_V2(int M, int N) {
        vector<int> prevRow(N); // Tracks the tabulation values for the previous row
        vector<int> currRow(N); // Tracks the tabulation values for the current row

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If its the "first row / first column" then fill the table value by 1
                if(R == 0 || C == 0)
                    currRow[C] = 1;
                // Else then fill the table value by adding the total number of ways to reach the current cell
                else
                    currRow[C] = currRow[C-1] + prevRow[C];
            }
            // Update the table for the upcoming row 
            prevRow = currRow;
        }

        // Return the total number of ways to reach the bottom-right cell
        return currRow[N-1];
    }

    // #3 Method to find the number of possible unique paths, using buffer only - O(M*N) & O(N)
    int uniquePaths_V3(int M, int N) {
        // Tracks the tabulation values for the row
        vector<int> dp(N, 0);

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If its the "first row / first column" then fill the table value by 1
                if(R == 0 || C == 0) 
                    dp[C] = 1;
                // Else then fill the table value by adding the total number of ways to reach the current cell
                else
                    dp[C] = dp[C-1] + dp[C];
            }
        }

        // Return the total number of ways to reach the bottom-right cell
        return dp[N-1];
    }
};

// Driver code
int main() {
    bool userWantsOperation = true;

    while(userWantsOperation) {
        system("cls || clear");

        int M, N;
        cout<<"Enter the number of rows: "   ; cin>>M;
        cout<<"Enter the number of columns: "; cin>>N;
        
        BottomUpDP bottomUp;
        cout<<"The number of possible unique paths that the robot can take to reach the bottom-right corner is: "<<bottomUp.uniquePaths_V3(M, N)<<'\n';

        char userChoise;
        cout<<"\nPress \'R\' to restart the application, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false;
    }

    return 0;
}
// Link: https://leetcode.com/problems/unique-paths/description/
