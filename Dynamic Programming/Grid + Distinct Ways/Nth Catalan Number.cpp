// Program to find the Nth number of the "Catalan's Sequence" ~ coded by Hiren
#include <iostream>
#include <vector>

// Class to implement the "Bottom Up Approach"
class BottomUP {
public:
    // #1 Method to find the Nth catalan number, using 2D buffer for tabulation - O(N^2) & O(N^2)
    int getNthCatalan_V1(int N) {
        const int mod = 1e9+7;

        // Stores the values of the "Catalan's Triangle"
        std::vector<std::vector<int>> dp;
        
        for(int R=0; R<=N; R++) {
            dp.emplace_back(R+1);
            for(int C=0; C<=R; C++) {
                // If its the first column then fill the cell value by 1 
                if(C == 0)
                    dp[R][C] = 1;

                // Else if its the last column then fill the cell value by the value lying at the "previous column in the current row"
                else if(C == R)
                    dp[R][C] = dp[R][C-1] % mod;

                // Else then fill the cell value by adding the value lying at the "current column in the previous row" and the value lying at the "previous column in the current row"
                else
                    dp[R][C] = (dp[R-1][C] + dp[R][C-1]) % mod;
            }
        }
        
        // Return the Nth number of the "Catalan's Sequence"
        return dp[N][N] % mod;
    }

    // #2 Method to find the Nth catalan number, using 1D buffer for tabulation - O(N^2) & O(N)
    int getNthCatalan_V2(int N) {
        const int mod = 1e9+7;
        
        std::vector<int> currRow(N+1); // Tracks the tabulation values for any current row 
        std::vector<int> prevRow(N+1); // Tracks the tabulation values for the previous row of the current row 
        
        for(int R=0; R<=N; R++) {
            for(int C=0; C<=R; C++) {
                // If its the first column then fill the cell value by 1 
                if(C == 0)
                    currRow[C] = 1;

                // Else if its the last column then fill the cell value by the value lying at the "previous column in the current row"
                else if(C == R)
                    currRow[C] = currRow[C-1] % mod;

                // Else then fill the cell value by adding the value lying at the "current column in the previous row" and the value lying at the "previous column in the current row"
                else
                    currRow[C] = (prevRow[C] + currRow[C-1]) % mod;
            }
            // Update the previous row for the upcoming row
            prevRow = currRow;
        }
        
        // Return the Nth number of the "Catalan's Sequence"
        return currRow[N] % mod;
    }
};

// Driver code
int main() {
    // Input section to handle the flow of iterations of the application
    int testCases;
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    while(testCases-- > 0) {
        // Input the value of N
        int N;
        std::cout<<"\nEnter the value of N: ";
        std::cin>>N;

        // Check the given value is valid or not
        if(N < 0) {
            std::cout<<"Enter a valid value, application expects a non-negative value!";
            return 0;
        }

        // Call to find the Nth number of the "Catalan's Sequence"
        BottomUP bottomUp;
        std::cout<<"The "<<N<<"th number of the sequence is: "<<bottomUp.getNthCatalan_V2(N)<<'\n';
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://www.geeksforgeeks.org/problems/nth-catalan-number0817/1
*/
