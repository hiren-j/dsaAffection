// Program to find the total number of laser beams in the "bank" ~ coded by Hiren 
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Solution class:
class Solution {
public:
    // #1 Method to find the total number of laser beams in the "bank", using buffer with map - O(M*N) & O(M) : Where M is the total number of rows and N is the length of a maximum string in it
    int numberOfBeams_V1(vector<string>& bank) {
        int m = bank.size();

        vector<int> rowsHavingDevices;            // Stores the index of the rows which contain at least 1 security device
        unordered_map<int, int> numDevicesOnRows; // Stores the total number of security devices existing in each row

        for(int currRow = 0; currRow < m; ++currRow) {
            // Stores the total number of security devices of the current row
            int currRowDevices = 0; 
            // Iterate the current row and count the number of security devices
            for(char cell : bank[currRow]) {
                currRowDevices += (cell == '1') ? 1 : 0;
            }
            // If the count of devices is at least 1 then update the "buffer" and the "map"
            if(currRowDevices) {
                // Store the row index with its count of devices to the "map"
                numDevicesOnRows[currRow] = currRowDevices; 
                // Store the current row index to the "buffer"
                rowsHavingDevices.push_back(currRow);       
            } 
        }

        // Stores the total number of laser beams in the "bank"
        int beamsInTotal = 0, size = rowsHavingDevices.size();

        for(auto [currRowIndex, currRowDevices] : numDevicesOnRows) {
            int idx = upper_bound(begin(rowsHavingDevices), end(rowsHavingDevices), currRowIndex) - begin(rowsHavingDevices);
            // If the "idx" is a valid index
            if(idx < size) {
                // Extract the index of the "just greater row" for the "current row index"
                int justGreaterRow = rowsHavingDevices[idx]; 
                // Calculate and store the current number of laser beams
                beamsInTotal += currRowDevices * (numDevicesOnRows[justGreaterRow]);
            }
        }

        // Return the total number of laser beams seen in the "bank"
        return beamsInTotal;
    }

    // #2 Method to find the total number of laser beams in the "bank", using buffer only - O(M*N) & O(M) : Where M is the total number of rows and N is the length of a maximum string in it
    int numberOfBeams_V2(vector<string>& bank) {
        int m = bank.size();    

        // Stores the total number of security devices existing in each row
        vector<int> numDevices;

        for(int currRow = 0; currRow < m; ++currRow) {
            // Stores the total number of security devices of the current row
            int currRowDevices = 0; 
            // Iterate the current row and count the number of security devices
            for(char cell : bank[currRow]) {
                currRowDevices += (cell == '1') ? 1 : 0;
            }
            // If the count of devices is at least 1 then store the count value to the "buffer"
            if(currRowDevices) {
                numDevices.push_back(currRowDevices);
            }
        }

        // Stores the total number of laser beams in the "bank"
        int beamsInTotal = 0, size = numDevices.size(); 

        // Iterate and calculate the total number of laser beams in the "bank"
        for(int row = 1; row < size; ++row) {
            beamsInTotal += numDevices[row-1] * numDevices[row];
        }

        // Return the total number of laser beams seen in the "bank"
        return beamsInTotal;
    }

    // #3 Method to find the total number of laser beams in the "bank", using constant auxiliary space - O(M*N) & O(1) : Where M is the total number of rows and N is the length of a maximum string in it
    int numberOfBeams_V3(vector<string>& bank) {
        int m = bank.size();
        int prevRowDevices = 0; // Stores the total number of security devices seen in the previous row
        int beamsInTotal   = 0; // Stores the total number of laser beams in the "bank"

        for(int currRow = 0; currRow < m; ++currRow) {
            // Stores the total number of security devices of the current row
            int currRowDevices = 0; 
            // Iterate the current row and count the number of security devices
            for(char cell : bank[currRow]) {
                currRowDevices += (cell == '1') ? 1 : 0;
            }
            // Calculate and store the current number of laser beams  
            beamsInTotal += prevRowDevices * currRowDevices;
            // Update the value of the security devices for the upcoming row
            prevRowDevices = (currRowDevices) ? currRowDevices : prevRowDevices;
        }

        // Return the total number of laser beams seen in the "bank"
        return beamsInTotal;
    }
};


// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input section for the "number of rows"
        int m; 
        cout<<"Enter the number of rows for the bank: ";
        cin>>m;

        // Check for the given size of the row is valid or not
        if(m <= 0) {
            cout<<"Enter a valid size for the row, application expects a positive integer!";
            return 0;
        }

        vector<string> bank(m);
        cout<<"\nNote: Digit '0' means the cell is empty, while '1' means the cell has a security device! (Example: 010101)\n\n";

        // Input the values for the "bank"
        for(int row = 0; row < m; ++row) {
            cout<<"Enter the digits for the "<<row+1<<"th row: ";
            cin>>bank[row];
        }

        // Call to find the total number of laser beams
        Solution solution;
        int beamsInTotal = solution.numberOfBeams_V3(bank);
        cout<<"\nThe total number of laser beams in the bank is "<<beamsInTotal;
        
        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nDo you want to perform the same operation on an another bank! (Write Y for \"Yes\" else application will exit automatically): ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
// Link: 
/*
    Topics: Array | Maths | String | Matrix
    Link: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/description/?envType=daily-question&envId=2023-12-18
*/
