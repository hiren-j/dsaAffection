// Program to find the total number of laser beams in the "bank" ~ coded by Hiren 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// #1 Method to find the total number of laser beams in the "bank", using buffer with (stl) map - O(M*N) & O(M) : Where M is the total number of rows and N is the length of a maximum string in it
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

// Driver code
int main() {
    vector<string> bank = {"011001","000000","010100","001000"};

    // Print values
    for(auto& row : bank) {
        for(char cell : row) {
            cout<<cell<<' ';
        }
        cout<<'\n';
    }

    // Call to find the total number of laser beams
    int beamsInTotal = numberOfBeams_V3(bank);
    cout<<"The total number of laser beams in the bank is "<<beamsInTotal;

    return 0;
}
// Link: https://leetcode.com/problems/number-of-laser-beams-in-a-bank/description/?envType=daily-question&envId=2024-01-03
