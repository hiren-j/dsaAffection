// Program to find the nCr of two integers n and r ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "Bottom Up Approach":
class BottomUp {
public:
    // #1 Method to find the nCr of two integers n and r, using 2D buffer for tabulation - O(N^2) & O(N^2) 
    int nCr_V1(int N, int R) {
        // Edge case: If the value of R is greater than N, then nCr is always zero.
        if(R > N)
            return 0;
        
        const int mod = 1e9+7;
        
        // Stores the values of the "Pascal's Triangle".
        vector<vector<int>> pascalTable;
        
        // Fill the values of the table.
        for(int K=0; K<N+1; K++) {
            // Create a new buffer to store the values of the current row of the "Pascal's Triangle".
            pascalTable.push_back(vector<int>(K+1, 1));
            // Iterate and fill the values for the columns of the current row.
            for(int C=1; C<K; C++) {
                pascalTable[K][C] = (pascalTable[K-1][C] % mod + pascalTable[K-1][C-1] % mod) % mod;
            }
        }
        
        // Return the nCr of given integers n and r.
        return pascalTable[N][R];
    }

    // #2 Method to find the nCr of two integers n and r, using 1D buffer for tabulation - O(N^2) & O(N) 
    int nCr_V2(int N, int R) {
        // Edge case: If the value of R is greater than N, then nCr is always zero.
        if(R > N)
            return 0;
        
        const int mod = 1e9+7;
        
        vector<int> currRow(N+1, 1); // Tracks the tabulation values for any current row.
        vector<int> prevRow(N+1, 1); // Tracks the tabulation values for the previous row of the current row.
        
        // Fill the values of the table.
        for(int K=0; K<N+1; K++) {
            // Iterate and fill the values for the columns of the current row.
            for(int C=1; C<K; C++) {
                currRow[C] = (prevRow[C] % mod + prevRow[C-1] % mod) % mod;
            }
            // Update the previous row for the upcoming row.
            prevRow = currRow;
        }
        
        // Return the nCr of given integers n and r.
        return currRow[R];
    }
};

// Driver code
int main() {
    // Input section to handle the flow of iterations of the application.
    int testCases;
    cout<<"Enter the number of testcases you want: ";
    cin>>testCases;

    while(testCases-- > 0) {
        int N, R;
        cout<<"\nEnter the value of N: "; cin>>N;
        cout<<"Enter the value of R: "; cin>>R;
        BottomUp bottomUp;
        cout<<"The nCr value is: "<<bottomUp.nCr_V2(N, R)<<'\n';
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming | Matrix
    Link: https://www.geeksforgeeks.org/problems/ncr1019/1
*/
