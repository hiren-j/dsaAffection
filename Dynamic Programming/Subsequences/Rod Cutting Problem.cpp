// Program to find the maximum value obtainable by cutting up the rod and selling the pieces ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the maximum value obtainable by cutting up the rod and selling the pieces, using recursion with memoization - O(N*N) & O(N*N)
    int cutRod(vector<int>& price, int N) {
        vector<vector<int>> memory(N, vector<int>(N + 1, -1));
        return solveWithMemo(memory, price, N, 1, N);
    }
    
private:
    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& price, int N, int cutLength, int rodLength) {
        // Edge case: If all the lengths are exhausted, then you can't cut the rod into more peices
        if(cutLength - 1 == N)
            return (rodLength == 0) ? 0 : INT_MIN;
        
        // Edge case: If you can cut the whole rod, then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[cutLength - 1][rodLength] != -1)
            return memory[cutLength - 1][rodLength];
        
        // There are always two possibilities to perform at each length
        int currSkip = solveWithMemo(memory, price, N, cutLength + 1, rodLength); // Is to skip the rod-cut in the current length and move to the next length
        int currTake = INT_MIN;                                                   // Is to cut the rod in the current length and then stay on the same length 
        
        // If possible then take the length value
        if(cutLength <= rodLength) {
            currTake = solveWithMemo(memory, price, N, cutLength, rodLength - cutLength);
            currTake = (currTake != INT_MIN) ? price[cutLength - 1] + currTake : currTake;
        }
        
        // Store the maximum value to the memoization table and then return it
        return memory[cutLength - 1][rodLength] = max(currSkip, currTake);    
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& price, int N, int cutLength, int rodLength) {
        // Edge case: If all the lengths are exhausted, then you can't cut the rod into more peices
        if(cutLength - 1 == N)
            return (rodLength == 0) ? 0 : INT_MIN;
            
        // Edge case: If you can cut the whole rod, then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;
            
        // There are always two possibilities to perform at each length
        int currSkip = solveWithoutMemo(price, N, cutLength + 1, rodLength); // Is to skip the rod-cut in the current length and move to the next length
        int currTake = INT_MIN;                                              // Is to cut the rod in the current length and then stay on the same length
        
        // If possible then take the length value
        if(cutLength <= rodLength) {
            currTake = solveWithoutMemo(price, N, cutLength, rodLength - cutLength);
            currTake = (currTake != INT_MIN) ? price[cutLength - 1] + currTake : currTake;
        }
        
        // Return the maximum value
        return max(currSkip, currTake);    
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the maximum value obtainable by cutting up the rod and selling the pieces, using recursion with memoization - O(N*N) & O(N*N)
    int cutRod(vector<int>& price, int N) {
        vector<vector<int>> memory(N, vector<int>(N + 1, -1));
        return solveWithMemo(memory, price, N, 1, N);
    }
    
private:
    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& price, int N, int startLength, int rodLength) {
        // Edge case: If all the lengths are exhausted, then you can't cut the rod into more peices
        if(startLength - 1 == N)
            return (rodLength == 0) ? 0 : INT_MIN;
            
        // Edge case: If you can cut the whole rod, then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;
            
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[startLength - 1][rodLength] != -1)
            return memory[startLength - 1][rodLength];
        
        // Stores the "maximum value / result value"
        int maxValue = INT_MIN;
        
        // Iterate and if possible, then take the length value and update the maximum value each time
        for(int cutLength = startLength; cutLength <= N; ++cutLength) {
            if(cutLength <= rodLength) {
                int currValue = solveWithMemo(memory, price, N, cutLength, rodLength - cutLength);
                currValue = (currValue != INT_MIN) ? price[cutLength - 1] + currValue : currValue;
                maxValue = max(maxValue, currValue);
            }    
        }
        
        // Store the maximum value to the memoization table and then return it
        return memory[startLength - 1][rodLength] = maxValue;    
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& price, int N, int startLength, int rodLength) {
        // Edge case: If all the lengths are exhausted, then you can't cut the rod into more peices
        if(startLength - 1 == N)
            return (rodLength == 0) ? 0 : INT_MIN;
            
        // Edge case: If you can cut the whole rod, then return 0 as a valid indication of it 
        if(rodLength == 0)
            return 0;
        
        // Stores the "maximum value / result value"
        int maxValue = INT_MIN;
        
        // Iterate and if possible, then take the length value and update the maximum value each time
        for(int cutLength = startLength; cutLength <= N; ++cutLength) {
            if(cutLength <= rodLength) {
                int currValue = solveWithoutMemo(price, N, cutLength, rodLength - cutLength);
                currValue = (currValue != INT_MIN) ? price[cutLength - 1] + currValue : currValue;
                maxValue = max(maxValue, currValue);
            }    
        }
        
        // Return the maximum value
        return maxValue;    
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the maximum value obtainable by cutting up the rod and selling the pieces, using 2D buffer for tabulation - O(N*N) & O(N*N)
    int cutRod_V1(vector<int>& price, int N) {
        // Tabulation buffer: dp[cutLength][rodLength] represents the maximum value which is obtainable by cutting a rod of length "rodLength" in the length of "cutLength"
        vector<vector<int>> dp(N + 1, vector<int>(N + 1, INT_MIN));

        // Edge case: If the length of rod is 0 and the length of cut is also 0, then we can't cut the rod into peices, hence no value is obtainable
        dp[0][0] = 0;
        
        // Treat each "cutLength" as the length of the cut that we can perform on the rod of length "rodLength" and find the maximum value which is obtainable
        for(int cutLength = 1; cutLength <= N; ++cutLength) {
            for(int rodLength = 0; rodLength <= N; ++rodLength) {
                int currSkip = dp[cutLength - 1][rodLength];
                int currTake = INT_MIN;
                if(cutLength <= rodLength) {
                    currTake = dp[cutLength][rodLength - cutLength];
                    currTake = (currTake != INT_MIN) ? price[cutLength - 1] + currTake : currTake;
                }
                dp[cutLength][rodLength] = max(currTake, currSkip);
            }
        }
        
        // Return the maximum value obtainable by cutting up the whole rod of length N
        return dp[N][N];
    }

    // #2 Method to find the maximum value obtainable by cutting up the rod and selling the pieces, using 1D buffer for tabulation - O(N*N) & O(N)
    int cutRod_V2(vector<int>& price, int N) {
        // Tabulation buffer: "prevRow[rodLength] / currRow[rodLength]" represents the maximum value which is obtainable by cutting a rod of length "rodLength" in the length of "cutLength"
        vector<int> prevRow(N + 1, 0), currRow(N + 1, 0);
        
        // Edge case: If the length of rod is 0 and the length of cut is also 0, then we can't cut the rod into peices, hence no value is obtainable
        prevRow[0] = 0;
        
        // Treat each "cutLength" as the length of the cut that we can perform on the rod of length "rodLength" and find the maximum value which is obtainable
        for(int cutLength = 1; cutLength <= N; ++cutLength) {
            for(int rodLength = 0; rodLength <= N; ++rodLength) {
                int currSkip = prevRow[rodLength];
                int currTake = INT_MIN;
                if(cutLength <= rodLength) {
                    currTake = currRow[rodLength - cutLength];
                    currTake = (currTake != INT_MIN) ? price[cutLength - 1] + currTake : currTake;
                }
                currRow[rodLength] = max(currTake, currSkip);
            }
            prevRow = currRow;
        }
        
        // Return the maximum value obtainable by cutting up the whole rod of length N
        return prevRow[N];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int N;
        cout<<"Enter the total length of the rod: ";
        cin>>N;

        // Check the given values are valid or not
        if(N <= 0 || N >= 1001) {
            cout<<"You must enter a size which lies between 1 and 10^3!";
        }
        else {
            // Stores the array values
            vector<int> price(N, 0);

            // Input the array values
            for(int length = 0; length < N;) {
                cout<<"Enter value of the "<<length<<"th length: ";
                cin>>price[length];
                if(price[length] <= 0 || price[length] >= 100001) {
                    cout<<"You must enter a value which lies within the range 1 and 10^5!\n";
                    continue;
                }
                length++;
            }

            // Call to find the maximum value obtainable by cutting up the rod and selling the pieces
            BottomUp bottomUp;
            int maxValue = bottomUp.cutRod_V2(price, N);
            cout<<"\nThe maximum value which is obtainable by cutting up the whole rod of length "<<N<<" is: "<<maxValue;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://www.geeksforgeeks.org/problems/rod-cutting0840/1
*/
