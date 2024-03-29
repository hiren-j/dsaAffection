// Program to break the given N into the sum of K positive integers, where K >= 2, and maximize the product of those integers ~ coded by Hiren
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to break the given N and find the maximum product you can get, using recursion with memoization - O(N*N) & O(N)
    int integerBreak(int N) {
        vector<int> memory(N + 1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(N*N) & O(N)
    int solveWithMemo(int N, vector<int>& memory) {
        // Edge case: If N is less than or equal to 2 then the maximum product you can get is 1
        if(N <= 2)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N] != -1)
            return memory[N];

        // Stores the "maximum product you can get by breaking the N / result value"
        int maxProduct = INT_MIN;

        // Iterate and explore all the possibilities of breaking the N and update the result value by the maximum value each time
        for(int num = 1; num <= N-1; ++num) {
            int currProduct = max(N - num, solveWithMemo(N - num, memory));
            maxProduct = max(maxProduct, num * currProduct);
        }

        // Store the result value to the memoization table and then return it
        return memory[N] = maxProduct;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: If N is less than or equal to 2 then the maximum product you can get is 1
        if(N <= 2)
            return 1;

        // Stores the "maximum product you can get by breaking the N / result value"
        int maxProduct = INT_MIN;

        // Iterate and explore all the possibilities of breaking the N and update the result value by the maximum value each time
        for(int num = 1; num <= N-1; ++num) {
            int currProduct = max(N - num, solveWithoutMemo(N - num));
            maxProduct = max(maxProduct, num * currProduct);
        }

        // Return the result value
        return maxProduct;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to break the given N and find the maximum product you can get, using 1D buffer for tabulation - O(N*N) & O(N)
    int integerBreak(int N) {
        // Tabulation buffer: dp[J] represents the maximum product you can get by breaking the Jth index
        vector<int> dp(N + 1, INT_MIN);

        // Edge case: If N is equal to 2 then the maximum product you can get is 1
        dp[2] = 1; 

        // Treat each index 'J' as an individual N and then break it and then look for the maximum product you can get
        for(int J = 3; J <= N; ++J) {
            // Explore all the possibilities of breaking the J and update the result value by the maximum value each time
            for(int num = 1; num <= J-1; ++num) {
                int currProduct = max(J - num, dp[J - num]);
                dp[J] = max(dp[J], num * currProduct);    
            }
        }
        
        // Return the maximum product you can get by breaking the N
        return dp[N];       
    }
};

// Driver code
int main() {
    cout<<"The application only accepts non-decimal numeric type value!\n\n";

    int testCases;
    cout<<"Enter the number of cases to test: ";
    cin>>testCases;

    while(testCases-- > 0) {
        int N;
        cout<<"\nEnter the value of N: ";
        cin>>N;
        if(N <= 1 || N >= 59) {
            cout<<"You must enter a value which lies between 2 and 58!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The maximum product you can get by breaking the "<<N<<" is: "<<bottomUp.integerBreak(N)<<'\n';
        }
    }

    return 0;
}
/*
    Topics: Dynamic Programming
    Link: https://leetcode.com/problems/integer-break/description/
*/
