// Program to find the least number of perfect square numbers that sums to N ~ coded by Hiren
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the least number of perfect square numbers that sums to N, using recursion with memoization - O(N*sqrt(N)) & O(N)
    int numSquares(int N) {
        vector<int> cache(N+1, -1);
        return solveWithMemo(N, cache);
    }

private:
    // O(N*sqrt(N)) & O(N)
    int solveWithMemo(int N, vector<int>& cache) {
        // Edge case: If N is negative or equal to 0, then its not possible to get any perfect square number
        if(N <= 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(cache[N] != -1)
            return cache[N];

        // Stores the "least number of perfect square numbers that sums to N / result value"
        int minCount = INT_MAX;

        // Explore all the possibilities which can sum to N
        for(int J=1; J*J<=N; J++) {
            // Update the "result value" by the "minimum value" each time
            minCount = min(minCount, 1 + solveWithMemo(N - J*J, cache));
        }

        // Store the result value to the "memoization table" and then return it
        return cache[N] = minCount;
    }

    // O(sqrt(N)^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: If N is negative or equal to 0, then its not possible to get any perfect square number
        if(N <= 0)
            return 0;

        // Stores the "least number of perfect square numbers that sums to N / result value"
        int minCount = INT_MAX;

        // Explore all the possibilities which can sum to N
        for(int J=1; J*J<=N; J++) {
            // Update the "result value" by the "minimum value" each time
            minCount = min(minCount, 1 + solveWithoutMemo(N - J*J));
        }

        // Return the "result value"
        return minCount;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the least number of perfect square numbers that sums to N, using 1D buffer for tabulation - O(N*sqrt(N)) & O(N)
    int numSquares(int N) {
        // Edge case: If N is negative or equal to 0, then its not possible to get any perfect square number
        if(N <= 0)
            return 0;

        // Tabulation buffer: dp[num] stores the least number of perfect square numbers which can sum to "num"
        vector<int> dp(N+1, INT_MAX);
        dp[0] = 0;
        
        // Consider each index as an individual N and calculate the least number of perfect square numbers that sums to it
        for(int num=1; num<=N; num++) {
            // Explore all the possibilities which can sum to "num"
            for(int J=1; J*J<=num; J++) {
                // Update the value by the "minimum value" each time
                dp[num] = min(dp[num], 1 + dp[num - J*J]);
            }
        }

        // Return the least number of perfect square numbers that sums to N
        return dp[N];
    }
};

// Driver code
int main() {
    // Input section to control the flow of iterations of the application
    int testCases;
    cout<<"Enter the number of cases to test: "; 
    cin>>testCases;

    while(testCases-- > 0) {
        // Input the value of N
        int N;
        cout<<"\nEnter a value: ";
        cin>>N;

        // Check the given value is valid or not
        if(N <= 0 || N >= 10001) {
            cout<<"You must a enter a value which lies between 1 and 10000!\n";
            continue;
        }

        // Call to find the least number of perfect square numbers that sums to N 
        BottomUp bottomUp;
        cout<<"The least number of perfect square numbers that sums to "<<N<<" is: "<<bottomUp.numSquares(N)<<'\n';
    }

    return 0;
}
/*  
    Topics: Math | Dynamic Programming
    Link: https://leetcode.com/problems/perfect-squares/description/
*/
