// Program to find out the maximum amount of gold which the miner can collect until he can no longer move in the grid ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the maximum amount of gold the miner can collect, using recursion with memoization - O(N*M) & O(N*M)
    int collectMaximumGold(int N, int M, vector<vector<int>>& grid) {
        // Stores the maximum amount of gold the miner can collect (result value)
        int maxGold = 0;
        
        // 2D table for memoization
        vector<vector<int>> memory(N, vector<int>(M, -1));
        
        // Iterate the start points of the miner and get the maximum gold he can collect from it and then update the result by the maximum value
        for(int R = 0; R < N; ++R) {
            maxGold = max(maxGold, solveWithMemo(memory, grid, N, M, R, 0));
        }

        // Return the result value
        return maxGold;
    }
    
private:
    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If the miner walks out of the grid then he can get no gold
        if(R < 0 || R == N || C == M)
            return 0;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];
        
        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithMemo(memory, grid, N, M, R, C+1);   // Move to the right cell
        int moveUpRight   = solveWithMemo(memory, grid, N, M, R-1, C+1); // Move to the cell diagonally up towards the right
        int moveDownRight = solveWithMemo(memory, grid, N, M, R+1, C+1); // Move to the cell diagonally down towards the right
        
        // Store the result value to the memoization table and then return it
        return memory[R][C] = grid[R][C] + max({moveUpRight, moveRight, moveDownRight});
    }

    // O(N * 3^(N*M)) & O(N+M)
    int solveWithoutMemo(vector<vector<int>>& memory, vector<vector<int>>& grid, int N, int M, int R, int C) {
        // Edge case: If the miner walks out of the grid then he can get no gold
        if(R < 0 || R == N || C == M)
            return 0;
        
        // There are always three posibilities to perform at each cell
        int moveRight     = solveWithoutMemo(memory, grid, N, M, R, C+1);   // Move to the right cell
        int moveUpRight   = solveWithoutMemo(memory, grid, N, M, R-1, C+1); // Move to the cell diagonally up towards the right
        int moveDownRight = solveWithoutMemo(memory, grid, N, M, R+1, C+1); // Move to the cell diagonally down towards the right
        
        // Return the result value 
        return grid[R][C] + max({moveUpRight, moveRight, moveDownRight});
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the maximum amount of gold the miner can collect, using 2D tabulation - O(N*M) & O(N*M)
    int collectMaximumGold_A(int N, int M, vector<vector<int>>& grid) {
        // 2D table for tabulation: dp[R][C] stores the maximum amount of gold the miner can collect by reaching the cell (R, C)
        vector<vector<int>> dp(N, vector<int>(M, 0));
        
        // Fill the table
        for(int C = M-1; C >= 0; --C) {
            for(int R = 0; R < N; ++R) {
                int moveRight     = (C+1 < M) ? dp[R][C+1] : 0;
                int moveUpRight   = (R-1 >= 0 && C+1 < M) ? dp[R-1][C+1] : 0;
                int moveDownRight = (R+1 < N && C+1 < M) ? dp[R+1][C+1] : 0; 
                dp[R][C] = grid[R][C] + max({moveUpRight, moveRight, moveDownRight});
            }
        }
        
        // Stores the maximum amount of gold the miner can collect (result value)
        int maxGold = 0;
        
        // Explore the start points of the miner and update the result by the maximum value
        for(int R = 0; R < N; ++R) {
            maxGold = max(maxGold, dp[R][0]);
        }

        // Return the result value 
        return maxGold;
    }

    // #2 Method to find the maximum amount of gold the miner can collect, using constant auxiliary space - O(N*M) & O(1)
    int collectMaximumGold_B(int N, int M, vector<vector<int>>& grid) {
        // Fill the table
        for(int C = M-1; C >= 0; --C) {
            for(int R = 0; R < N; ++R) {
                int moveRight     = (C+1 < M) ? grid[R][C+1] : 0;
                int moveUpRight   = (R-1 >= 0 && C+1 < M) ? grid[R-1][C+1] : 0;
                int moveDownRight = (R+1 < N && C+1 < M) ? grid[R+1][C+1] : 0; 
                grid[R][C] += max({moveUpRight, moveRight, moveDownRight});
            }
        }
        
        // Stores the maximum amount of gold the miner can collect (result value)
        int maxGold = 0;
        
        // Explore the start points of the miner and update the result by the maximum value
        for(int R = 0; R < N; ++R) {
            maxGold = max(maxGold, grid[R][0]);
        }
        
        // Return the result value 
        return maxGold;
    }
};

// Driver code
int main() {
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the grid size
        int N, M;
        cout<<"Enter the total number of rows and columns of the grid: ";
        cin>>N>>M;

        // Check the given values are lying within the problem constraints or not
        if(N < 1 || M < 1 || N > 500 || M > 500) {
            cout<<"You must enter the grid size which lies between 1 and 500!";
        }
        else {
            vector<vector<int>> grid(N, vector<int>(M));

            // Input the grid values
            cout<<"\nNote: Positive integer will be considered as the amount of gold of any cell!\n";
            for(int R = 0; R < N; ++R) {
                for(int C = 0; C < M;) {
                    cout<<"Enter value of the "<<C<<"th column of the "<<R<<"th row: ";
                    cin>>grid[R][C];
                    // Check the given value is lying within the problem constraints or not
                    if(grid[R][C] < 0 || grid[R][C] > 100) {
                        cout<<"You must enter a value which lies between 0 and 100!\n";
                    }
                    else {
                        ++C;
                    }
                }
            }

            // Call to find the maximum amount of money the miner can collect
            BottomUp bottomUp;
            int maxGold = bottomUp.collectMaximumGold_B(N, M, grid);
            cout<<"\nThe maximum amount of money the minor can collect is: "<<maxGold;
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
    Link: https://www.geeksforgeeks.org/problems/gold-mine-problem2608/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
*/
