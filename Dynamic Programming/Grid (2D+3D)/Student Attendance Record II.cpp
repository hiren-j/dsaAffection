// Program to find the number of possible attendance records of length n that make a student eligible for an attendance award ~ coded by Hiren
#define MOD 1000000009
#include <iostream>
#include <vector>
using namespace std;

class TopDown {
public:
    // Method to find the total number of specified attendance records of length N, using recursion with memoization - O(N) & O(N)
    int checkRecord(int N) {
        vector<vector<vector<int>>> memory(N + 1, vector<vector<int>>(2, vector<int>(3, -1)));
        return solveWithMemo(memory, N, 0, 0);
    }

private:
    // O(3*N*2*3) & O(N*2*3)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int N, int absences, int consecutiveLate) {
        // Edge case: If the student goes absent for 2 days or goes late for 3 days consecutively then there's no valid way
        if(absences == 2 || consecutiveLate == 3)
            return 0;

        // Edge case: If it's possible to create a valid attendence record of length N then there's 1 valid way
        if(N == 0)
            return 1;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N][absences][consecutiveLate] != -1)
            return memory[N][absences][consecutiveLate];

        // There are three possibilities which the student can perform at each day
        int A = solveWithMemo(memory, N - 1, absences + 1, 0) % MOD;               // Is to go absent 
        int L = solveWithMemo(memory, N - 1, absences, consecutiveLate + 1) % MOD; // Is to go late
        int P = solveWithMemo(memory, N - 1, absences, 0) % MOD;                   // Is to present 

        // Store the result value to the memoization table and then return it
        return memory[N][absences][consecutiveLate] = ((A + L) % MOD + P) % MOD;
    }

    // O(3^N) & O(N)
    int solveWithoutMemo(vector<vector<vector<int>>>& memory, int N, int absences, int consecutiveLate) {
        // Edge case: If the student goes absent for 2 days or goes late for 3 days consecutively then there's no valid way
        if(absences == 2 || consecutiveLate == 3)
            return 0;

        // Edge case: If it's possible to create a valid attendence record of length N then there's 1 valid way
        if(N == 0)
            return 1;

        // There are three possibilities which the student can perform at each day
        int A = solveWithoutMemo(memory, N - 1, absences + 1, 0) % MOD;               // Is to go absent
        int L = solveWithoutMemo(memory, N - 1, absences, consecutiveLate + 1) % MOD; // Is to go late 
        int P = solveWithoutMemo(memory, N - 1, absences, 0) % MOD;                   // Is to present   

        // Return the result value
        return ((A + L) % MOD + P) % MOD;
    }
};

class BottomUp {
public:
    // #1 Method to find the total number of specified attendance records of length N, using 3D tabulation - O(N) & O(N)
    int checkRecord_A(int N) {
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        // Edge case: When the length is 0 then there's always 1 valid way
        for(int absences = 0; absences < 2; ++absences) {
            for(int consecutiveLate = 0; consecutiveLate < 3; ++consecutiveLate) {
                dp[0][absences][consecutiveLate] = 1;
            }
        }

        // Fill the rest of the table
        for(int length = 1; length <= N; ++length) {
            for(int absences = 0; absences < 2; ++absences) {
                for(int consecutiveLate = 0; consecutiveLate < 3; ++consecutiveLate) {
                    int A = (absences < 1) ? dp[length - 1][absences + 1][0] % MOD : 0;
                    int L = (consecutiveLate < 2) ? dp[length - 1][absences][consecutiveLate + 1] % MOD : 0;
                    int P = dp[length - 1][absences][0] % MOD;
                    dp[length][absences][consecutiveLate] = ((A + L) % MOD + P) % MOD;
                }
            }
        }

        // Return the result value
        return dp[N][0][0];
    }

    // #2 Method to find the total number of specified attendance records of length N, using constant auxiliary space - O(N) & O(1)
    int checkRecord_B(int N) {
        vector<vector<int>> currRow(2, vector<int>(3, 0)), prevRow(2, vector<int>(3, 0));

        // Edge case: When the length is 0 then there's always 1 valid way
        for(int absences = 0; absences < 2; ++absences) {
            for(int consecutiveLate = 0; consecutiveLate < 3; ++consecutiveLate) {
                prevRow[absences][consecutiveLate] = 1;
            }
        }

        // Fill the rest of the table
        for(int length = 1; length <= N; ++length) {
            for(int absences = 0; absences < 2; ++absences) {
                for(int consecutiveLate = 0; consecutiveLate < 3; ++consecutiveLate) {
                    int A = (absences < 1) ? prevRow[absences + 1][0] % MOD : 0;
                    int L = (consecutiveLate < 2) ? prevRow[absences][consecutiveLate + 1] % MOD : 0;
                    int P = prevRow[absences][0] % MOD;
                    currRow[absences][consecutiveLate] = ((A + L) % MOD + P) % MOD;
                }
            }
            prevRow = currRow;
        }

        // Return the result value
        return prevRow[0][0];
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

    int testCases;
    cout<<"Enter the total number of cases to test: ";
    cin>>testCases;

    while(testCases--) {
        int N;
        cout<<"\nEnter value of N: ";
        cin>>N;

        if(N < 1 || N > 1e5 + 1) {
            cout<<"You must enter a value which lies between 1 and 10^5!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The total number of attendance records of length "<<N<<" that make a student eligible for an attendance award is: "<<bottomUp.checkRecord_B(N)<<'\n';
        }        
    }

    return 0;
}
/*
    Topics: Dynamic Programming
    Link: https://leetcode.com/problems/student-attendance-record-ii/description/?envType=daily-question&envId=2024-05-26
*/
