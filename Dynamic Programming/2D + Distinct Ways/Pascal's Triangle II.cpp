// Program to find the first "rowIndex" of "Pascal's triangle" ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "Bottom Up Approach":
class BottomUpDP {
public:
    // #1 Method to find the first "rowIndex" of Pascal's triangle, using tabulation - O(rowIndex^2) & O(rowIndex^2) 
    vector<int> getRow_V1(int rowIndex) {
        // Stores the values of the "Pascal's Triangle".
        vector<vector<int>> pascalTable;

        for(int row = 0; row < rowIndex; row++) {
            // Create a new buffer to store the values of the current row of the "Pascal's Triangle".
            pascalTable.emplace_back(vector<int>(row+1, 1));

            // Iterate and fill the values for the columns of the current row.
            for(int col = 1; col < row; col++) {
                pascalTable[row][col] = pascalTable[row-1][col] + pascalTable[row-1][col-1];
            }

        }   

        // Return the "rowIndex" row of the "Pascal's Triangle". 
        return pascalTable[rowIndex];
    }

    // #2 Method to find the first "rowIndex" of Pascal's triangle, using tabulation - O(rowIndex^2) & O(rowIndex) 
    vector<int> getRow_V2(int rowIndex) {
        vector<int> prevRow(rowIndex+1, 1); // Tracks the tabulation values for the previous row.
        vector<int> currRow(rowIndex+1, 1); // Tracks the tabulation values for any current row.

        // Fill the values for the table
        for(int r = 0; r < rowIndex+1; ++r) {
            // Iterate and fill the values for the columns of the current row.
            for(int c = 1; c < r; ++c) {
                currRow[c] = prevRow[c] + prevRow[c-1];
            }
            // Update the previous row for the upcoming row.
            prevRow = currRow;
        }

        // Return the "rowIndex" row of the "Pascal's Triangle".
        return currRow;
    }

    // #3 Method to find the first "rowIndex" of Pascal's triangle, using tabulation - O(rowIndex^2) & O(rowIndex) 
    vector<int> getRow_V3(int rowIndex) {
        // Tracks the tabulation values for any current row.
        vector<int> currRow(rowIndex+1, 1);

        // Fill the values for the table
        for(int r = 2; r <= rowIndex; ++r) {
            // Iterate and fill the values for the columns of the current row.
            for(int c = r-1; c > 0; --c) {
                currRow[c] += currRow[c - 1];
            }
        }

        // Return the "rowIndex" row of the "Pascal's Triangle".
        return currRow;
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not.
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearence for both "windows" and "linux" user.
        system("cls || clear");

        // Input section for the number of rows.
        int rowIndex;
        cout<<"Enter the index of the row which you want from the pascal's triangle: ";
        cin>>rowIndex;

        // Check for the given size for the row is valid or not.
        if(rowIndex < 0) {
            cout<<"Enter a valid size for the row, application expects a non-negative integer!";
            return 0;
        }

        // Call to get the "rowIndex" row of the "Pascal's Triangle".
        BottomUpDP bottomUp;
        vector<int> row = bottomUp.getRow_V3(rowIndex);

        // Print values.
        cout<<"\nThe values of the "<<rowIndex<<"th row is: [";
        int size = row.size();
        for(int i=0; i<size; i++) {
            (i < size-1) ? cout<<row[i]<<", " : cout<<row[i] ;
        }
        cout<<"]";

        // Input section to handle the flow of iterations of the application. 
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false ;
    }

    return 0;
}
// Link: https://leetcode.com/problems/pascals-triangle-ii/
