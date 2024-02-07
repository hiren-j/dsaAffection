// Program to find the knight's minimum initial health so that he can rescue the princess ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the "Top Down Apporach"
class TopDown {
public:
    // Method to find the knight's minimum initial health, using recursion with memoization - O(M*N) & O(M*N)
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        int M = dungeon.size(), N = dungeon[0].size();
        vector<vector<int>> memory(M+1, vector<int>(N+1, -1));
        return solveWithMemo(dungeon, memory, M, N, 0, 0);
    }
private:
    // O(2^(M*N)) & O(M+N)
    int solveWithoutMemo(vector<vector<int>>& dungeon, int M, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then its not possible to play the game anymore
        if(R == M || C == N)
            // Requires to handle the "minimum health" correctly
            return INT_MAX; 

        // Edge case: If reached the bottom-right corner then "rescue the princess"
        if(R == M-1 && C == N-1)
            // Calculate and return the "minimum health" required for the "knight" to defeat the "demon" of the current room or not a "demon" then he requires minimum of "single health to live"
            return (dungeon[R][C] <= 0) ? -dungeon[R][C] + 1 : 1;

        // There are always two possibilities at each room for the "knight"
        int moveRight = solveWithoutMemo(dungeon, M, N, R, C+1); // Is to move to the right room from the current room
        int moveDown  = solveWithoutMemo(dungeon, M, N, R+1, C); // Is to move to the down room from the current room 

        // Stores the "minimum health" required for the "knight" to "live" at the current room
        int roomMinHealth = min(moveRight, moveDown) - dungeon[R][C];

        // Ensure the "knight" dies or not, if dies then he must need "single health to live" at the current room 
        return (roomMinHealth <= 0) ? 1 : roomMinHealth;
    }

    // O(M*N) & O(M*N)
    int solveWithMemo(vector<vector<int>>& dungeon, vector<vector<int>>& memory, int M, int N, int R, int C) {
        // Edge case: If all the cells are exhausted then its not possible to play the game anymore
        if(R == M || C == N)
            // Requires to handle the "minimum health" correctly
            return INT_MAX;

        // Edge case: If reached the bottom-right corner then "rescue the princess"
        if(R == M-1 && C == N-1)
            // Calculate and return the "minimum health" required for the "knight" to defeat the "demon" of the current room or not a "demon" then he requires minimum of "single health to live"
            return (dungeon[R][C] <= 0) ? -dungeon[R][C] + 1 : 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[R][C] != -1)
            return memory[R][C];

        // There are always two possibilities at each room for the "knight"
        int moveRight = solveWithMemo(dungeon, memory, M, N, R, C+1); // Is to move to the right room from the current room
        int moveDown  = solveWithMemo(dungeon, memory, M, N, R+1, C); // Is to move to the down room from the current room 

        // Stores the "minimum health" required for the "knight" to "live" at the current room
        int roomMinHealth = min(moveRight, moveDown) - dungeon[R][C];

        // Ensure the "knight" dies or not, if dies then he must need "single health to live" at the current room 
        return memory[R][C] = (roomMinHealth <= 0) ? 1 : roomMinHealth;
    }
};

// Class to implement the "Bottom Up Approach"
class BottomUp {
public:
    // #1 Method to find the knight's minimum initial health, using 2D buffer for tabulation - O(M*N) & O(M*N)
    int calculateMinimumHP_V1(vector<vector<int>>& dungeon) {
        int M = dungeon.size(), N = dungeon[0].size();

        // Tabulation buffer: For each room "(R,C)" of "dp" represents the "minimum health" required for the "knight" to "live at the room" in the "dungeon"
        vector<vector<int>> dp(M, vector<int>(N, 0));
        
        // Calculate and store the "minimum health" required for the "knight" to defeat the "demon" of the bottom-right room or not a "demon" then he requires minimum of "single health to live"
        dp[M-1][N-1] = max(1, 1 - dungeon[M-1][N-1]);
        
        // Fill the values for the rightmost column of the buffer
        for(int R = M-2; R >= 0; --R) {
            // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
            int roomMinHealth = dp[R+1][N-1] - dungeon[R][N-1];
            // Ensure the "knight" dies or not, if dies then he must need "single health to live" at the current room 
            dp[R][N-1] = max(1, roomMinHealth);
        }

        // Fill the values for the last row of the buffer
        for(int C = N-2; C >= 0; --C) {
            // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
            int roomMinHealth = dp[M-1][C+1] - dungeon[M-1][C];
            // Ensure the "knight" dies or not, if dies then he must need "single health to live" at the current room 
            dp[M-1][C] = max(1, roomMinHealth);
        }

        // Fill the values for the rest of the rows and columns of the buffer
        for(int R = M-2; R >= 0; --R) {
            for(int C = N-2; C >= 0; --C) {
                // As we're striving for the "minimum health" thus store the "minimum element" from the "value lying at the next column of the current row" and the value "lying at the same column in the next row" 
                int minElement = min(dp[R][C+1], dp[R+1][C]);
                // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                int roomMinHealth = minElement - dungeon[R][C];
                // Ensure the "knight" dies or not, if dies then he must need "single health to live" at the current room 
                dp[R][C] = max(1, roomMinHealth);
            } 
        }

        // Return the "minimum initial health" of the "knight" so that he can "rescue the princes"
        return dp[0][0];
    }

    // #2 Method to find the knight's minimum initial health, using 2D buffer for tabulation - O(M*N) & O(M*N)
    int calculateMinimumHP_V2(vector<vector<int>>& dungeon) {
        int M = dungeon.size(), N = dungeon[0].size();

        // Tabulation buffer: For each room "(R,C)" of "dp" represents the "minimum health" required for the "knight" to "live at the room" in the "dungeon"
        vector<vector<int>> dp(M, vector<int>(N, 0));

        // Calculate and store the "minimum health" required for the "knight" to defeat the "demon" of the bottom-right room or not a "demon" then he requires minimum of "single health to live"
        dp[M-1][N-1] = max(1, 1 - dungeon[M-1][N-1]);

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {    
                // Fill the values for the rightmost column of the buffer
                if(R <= M-2 && C == N-1) {
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    dp[R][N-1] = max(1, dp[R+1][N-1] - dungeon[R][N-1]);
                }
                
                // Fill the values for the last row of the buffer
                else if(R == M-1 && C <= N-2) {
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    dp[M-1][C] = max(1, dp[M-1][C+1] - dungeon[M-1][C]);
                }

                // Fill the values for the rest of the rows and columns of the buffer
                else if(R <= M-2 && C <= N-2) {
                    // As we're striving for the "minimum health" thus store the "minimum element" from the "value lying at the next column of the current row" and the value "lying at the same column in the next row" 
                    int minElement = min(dp[R][C+1], dp[R+1][C]);
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    dp[R][C] = max(1, minElement - dungeon[R][C]);
                }
            } 
        }

        // Return the "minimum initial health" of the "knight" so that he can "rescue the princes"
        return dp[0][0];
    }

    // #3 Method to find the knight's minimum initial health, using 1D buffer for tabulation - O(M*N) & O(N)
    int calculateMinimumHP_V3(vector<vector<int>>& dungeon) {
        int M = dungeon.size(), N = dungeon[0].size();

        vector<int> currRow(N, 0); // Tracks the tabulation values for any current row
        vector<int> nextRow(N, 0); // Tracks the tabulation values for the next row of the current row

        // Calculate and store the "minimum health" required for the "knight" to defeat the "demon" of the bottom-right room or not a "demon" then he requires minimum of "single health to live"
        nextRow[N-1] = max(1, 1 - dungeon[M-1][N-1]);
        currRow[N-1] = max(1, 1 - dungeon[M-1][N-1]);

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                // Fill the values for the rightmost column of the buffer
                if(R <= M-2 && C == N-1) {
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    currRow[N-1] = max(1, nextRow[N-1] - dungeon[R][N-1]);
                }

                // Fill the values for the last row of the buffer
                else if(R == M-1 && C <= N-2) {
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    currRow[C] = max(1, currRow[C+1] - dungeon[M-1][C]);
                }

                // Fill the values for the rest of the rows and columns of the buffer
                else if(R <= M-2 && C <= N-2) {
                    // As we're striving for the "minimum health" thus store the "minimum element" from the "value lying at the next column of the current row" and the value "lying at the same column in the next row" 
                    int minElement = min(currRow[C+1], nextRow[C]);
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    currRow[C] = max(1, minElement - dungeon[R][C]);
                }
            } 
            // Update the next row for the upcoming previous row
            nextRow = currRow;
        }

        // Return the "minimum initial health" of the "knight" so that he can "rescue the princes"
        return currRow[0];
    }

    // #4 Method to find the knight's minimum initial health, using constant auxiliary space - O(M*N) & O(1)
    int calculateMinimumHP_V4(vector<vector<int>>& dungeon) {
        int M = dungeon.size(), N = dungeon[0].size();

        // Calculate and store the "minimum health" required for the "knight" to defeat the "demon" of the bottom-right room or not a "demon" then he requires minimum of "single health to live"
        dungeon[M-1][N-1] = max(1, 1 - dungeon[M-1][N-1]);

        for(int R = M-1; R >= 0; --R) {
            for(int C = N-1; C >= 0; --C) {
                // Fill the values for the rightmost column of the buffer
                if(R <= M-2 && C == N-1) {
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    dungeon[R][N-1] = max(1, dungeon[R+1][N-1] - dungeon[R][N-1]);
                }

                // Fill the values for the last row of the buffer
                else if(R == M-1 && C <= N-2) {
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    dungeon[M-1][C] = max(1, dungeon[M-1][C+1] - dungeon[M-1][C]);
                }

                // Fill the values for the rest of the rows and columns of the buffer
                else if(R <= M-2 && C <= N-2) {
                    // As we're striving for the "minimum health" thus store the "minimum element" from the "value lying at the next column of the current row" and the value "lying at the same column in the next row" 
                    int minElement = min(dungeon[R][C+1], dungeon[R+1][C]);
                    // Calculate and store the "minimum health" required for the "knight" to "live" at the current room
                    dungeon[R][C] = max(1, minElement - dungeon[R][C]);
                }
            } 
        }

        // Return the "minimum initial health" of the "knight" so that he can "rescue the princes"
        return dungeon[0][0];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        // Prompt the information about values for the "dungeon"
        cout<<"-> Rooms guarded by demons (represented by negative integers)";
        cout<<"\n-> Empty rooms (represented by 0)";
        cout<<"\n-> Rooms contain magic orbs that increase the knight's health (represented by positive integers)\n\n";
        
        // Input the size of row and column for the "dungeon"
        int M, N;
        cout<<"Enter the number of rows for the dungeon: "; cin>>M;
        cout<<"Enter the number of columns for the dungeon: "; cin>>N;

        // Check the given size of row and column is valid or not
        if(M <= 0 || N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Stores the values for the "dungeon"
        vector<vector<int>> dungeon(M, vector<int>(N, 0));
        cout<<"\nEnter the values for the dungeon:\n";

        // Input the values for the "dungeon"
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                cin>>dungeon[R][C];
            }
        }

        // Call to find the "knight's minimum initial health"
        BottomUp bottomUp;
        int minInitialHealth = bottomUp.calculateMinimumHP_V4(dungeon);
        cout<<"\nThe knight's minimum initial health should be: "<<minInitialHealth;

        // Prompt section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'Y\' to perform the same operation on an another dungeon, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false ;
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/dungeon-game/description/
*/
