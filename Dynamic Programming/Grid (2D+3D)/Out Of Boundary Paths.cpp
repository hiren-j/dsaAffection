// Program to find the total number of paths to move the ball out of the grid boundary from the cell (startRow, startColumn) ~ coded by Hiren
#define MOD 1000000007
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    
    // O(4^maxMove) & O(maxMove)
    int solveWithoutMemo(int M, int N, int maxMove, int startRow, int startColumn) {
        // Edge case: If the ball moves out of the grid boundary then you've one valid way
        if(startRow < 0 || startColumn < 0 || startRow >= M || startColumn >= N)
            return 1;

        // Edge case: If all the moves are exhausted then it's not possible to move the ball anymore
        if(maxMove == 0)
            return 0;

        // Stores the result value
        int numPaths = 0;

        // Explore all the 4 directions one by one from the cell and update the result value each time
        for(auto& dir : directions) {
            int reachRow    = startRow + dir[0];
            int reachColumn = startColumn + dir[1];
            numPaths = ((numPaths % MOD) + solveWithoutMemo(M, N, maxMove - 1, reachRow, reachColumn) % MOD);
        }

        // Return the result value
        return numPaths % MOD;
    }

    // O(4*maxMove*M*N) & O(maxMove*M*N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int M, int N, int maxMove, int startRow, int startColumn) {
        // Edge case: If the ball moves out of the grid boundary then you've one valid way
        if(startRow < 0 || startColumn < 0 || startRow >= M || startColumn >= N)
            return 1;

        // Edge case: If all the moves are exhausted then it's not possible to move the ball anymore
        if(maxMove == 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[maxMove][startRow][startColumn] != -1)
            return memory[maxMove][startRow][startColumn];

        // Stores the result value
        int numPaths = 0;

        // Explore all the 4 directions one by one from the cell and update the result value each time
        for(auto& dir : directions) {
            int reachRow    = startRow + dir[0];
            int reachColumn = startColumn + dir[1];
            numPaths = ((numPaths % MOD) + solveWithMemo(memory, M, N, maxMove - 1, reachRow, reachColumn) % MOD);
        }

        // Store the result value to the memoization table and then return it
        return memory[maxMove][startRow][startColumn] = numPaths % MOD;
    }

public:
    // Method to find the total number of paths, using recursion with memoization - O(maxMove*M*N) & O(maxMove*M*N)
    int findPaths(int M, int N, int maxMove, int startRow, int startColumn) {
        vector<vector<vector<int>>> memory(maxMove + 1, vector<vector<int>>(M, vector<int>(N, -1)));
        return solveWithMemo(memory, M, N, maxMove, startRow, startColumn);
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
    vector<vector<int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

public:
    // Method to find the total number of paths, using 3D tabulation - O(maxMove*M*N) & O(maxMove*M*N)
    int findPaths(int M, int N, int maxMove, int startRow, int startColumn) {
        // 3D table: dp[move][R][C] represents the total number of paths to move the ball out of the grid from the cell (R, C) in "move" moves
        vector<vector<vector<int>>> dp(maxMove + 1, vector<vector<int>>(M, vector<int>(N, 0)));

        // Fill the table
        for(int move = 1; move <= maxMove; ++move) {
            for(int R = 0; R < M; ++R) {
                for(int C = 0; C < N; ++C) {
                    for(auto& dir : directions) {
                        int reachRow    = R + dir[0];
                        int reachColumn = C + dir[1];
                        if(reachRow >= 0 && reachColumn >= 0 && reachRow < M && reachColumn < N) {
                            dp[move][R][C] = (dp[move][R][C] % MOD) + dp[move - 1][reachRow][reachColumn] % MOD;
                        }
                        else {
                            dp[move][R][C]++ % MOD;
                        }
                    } 
                }
            }
        }

        // Return the total number of paths to move the ball out of the grid from the cell (startRow, startColumn)
        return dp[maxMove][startRow][startColumn] % MOD;
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the row and column size
        int M, N;
        cout<<"Enter the total number of rows and columns: ";
        cin>>M>>N;

        // Input the moves size
        int maxMove;
        cout<<"Enter the maximum number of moves: ";
        cin>>maxMove;

        // Check the given values are lying within the problem constraints or not
        if(M < 1 || N < 1 || M > 50 || N > 50) {
            cout<<"You must enter the row and column size which lies between 1 and 50!";
        }
        else if(maxMove < 0 || maxMove > 50) {
            cout<<"You must enter the maximum moves which lies between 0 and 50!";
        }
        else {
            int startRow, startColumn;
            cout<<"\nEnter the start-row and start-column: ";
            cin>>startRow>>startColumn;

            // Check the given values are lying within the problem constraints or not
            if(startRow < 0 || startRow > M) {
                cout<<"You must enter a start-row which lies between 0 and "<<M<<"!";  
            }
            else if(startColumn < 0 || startColumn > N) {
                cout<<"You must enter a start-column which lies between 0 and "<<N<<"!";  
            }
            else {
                BottomUp bottomUp;
                int numPaths = bottomUp.findPaths(M, N, maxMove, startRow, startColumn);
                cout<<"The total number of paths to move the ball out of the grid boundary from the cell ("<<startRow<<", "<<startColumn<<") is: "<<numPaths;
            }
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
    Topics: Dynamic Programming | Matrix 
    Link: https://leetcode.com/problems/out-of-boundary-paths/description/
*/
