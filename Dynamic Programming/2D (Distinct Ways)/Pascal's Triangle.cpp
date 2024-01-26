// Program to find the first "numRows" of "Pascal's triangle" ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "Bottom Up Approach":
class BottomUpDP {
public:
    // Method to find the first "numRows" of Pascal's triangle, using tabulation - O(numRows^2) & O(numRows^2) 
    vector<vector<int>> generateTable(int numRows) {
        // Stores the values of the "Pascal's Triangle"
        vector<vector<int>> pascalTable;

        for(int row = 0; row < numRows; row++) {
            // Create a new buffer to store the values of the current row of the "Pascal's Triangle".
            pascalTable.emplace_back(vector<int>(row+1, 1));

            // Iterate and fill the values for the columns of the current row.
            for(int col = 1; col < row; col++) {
                pascalTable[row][col] = pascalTable[row-1][col] + pascalTable[row-1][col-1];
            }

        }   

        // Return the table of the "Pascal's Triangle". 
        return pascalTable;
    }
};
// Note: The auxiliary space is considered because even if its not the user's demand then still we have to create the table of "pascalTable".

// Method to print the table of the "Pascal's Triangle" - O(numRows^2) & O(1)
void printTable(vector<vector<int>>& pascalTable, int numRows) {
    cout<<'\n';

    for(int row = 0; row < numRows; ++row) {
        int rowSize = pascalTable[row].size();
        cout<<"[";
        for(int col = 0; col < rowSize; ++col) {
            (col < rowSize-1) ? cout<<pascalTable[row][col]<<", " : cout<<pascalTable[row][col] ;
        }
        cout<<"]\n";
    }

    cout<<'\n';
}

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not.
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearence for both "windows" and "linux" user.
        system("cls || clear");

        // Input section for the number of rows.
        int numRows;
        cout<<"Enter the number of rows for the pascal's triangle: ";
        cin>>numRows;

        // Call to get the "Pascal's Triangle".
        BottomUpDP bottomUp;
        vector<vector<int>> pascalTable = bottomUp.generateTable(numRows);

        // Print table.
        printTable(pascalTable, numRows);

        // Input section to handle the flow of iterations of the application. 
        char userChoise;
        cout<<"Press \'R\' to restart the application, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false ;
    }

    return 0;
}
// Link: https://leetcode.com/problems/pascals-triangle/description/
