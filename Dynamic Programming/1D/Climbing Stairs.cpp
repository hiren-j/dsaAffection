// Program to find the total number of distinct ways from which you can climb to the top ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDown {
public:
    // Method to find the total number of distinct ways, using recursion with memoization - O(N) & O(N)
    int climbStairs(int N) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(N) & O(N)
    int solveWithMemo(int N, vector<int>& memory) {
        // Edge case: When N is less than 2, then there's just a 1 way to reach to it
        if(N < 2) 
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N] != -1)
            return memory[N];

        // There are always two possibilities to reach the Nth stair
        int climbOneStep = solveWithMemo(N-1, memory); // Is to jump from the immediate 1st stair below the Nth stair
        int climbTwoStep = solveWithMemo(N-2, memory); // Is to jump from the immediate 2nd stair below the Nth stair

        // Store the number of ways to reach the Nth stair to the "memoization table" and then return it
        return memory[N] = climbOneStep + climbTwoStep;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: When N is less than 2, then there's just 1 way to reach the stair
        if(N < 2) 
            return 1;

        // There are always two possibilities to reach the Nth stair
        int climbOneStep = solveWithoutMemo(N-1); // Is to jump from the immediate 1st stair below the Nth stair
        int climbTwoStep = solveWithoutMemo(N-2); // Is to jump from the immediate 2nd stair below the Nth stair

        // Return the number of ways to reach the Nth stair
        return climbOneStep + climbTwoStep;
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUp {
public:
    // #1 Method to find the total number of distinct ways, using 1D buffer for tabulation - O(N) & O(N)
    int climbStairs_V1(int N) {
        // Edge case: If N is negative, then no valid stairs exist, as because there can't be negative stairs
        if(N < 0)
            return 0;

        // Tabulation buffer: dp[J] represents the number of ways to reach the Jth stair 
        vector<int> dp(N+1);
        dp[0] = 1; // Initially, if there is no stair that means we're already on it
        dp[1] = 1; // If there is 1 stair that means we can reach it from the 0th stair

        // Iterate and compute the number of ways to reach the Jth stair
        for(int J=2; J<=N; J++)
            dp[J] = dp[J-1] + dp[J-2];

        // Return the number of ways to reach the Nth stair
        return dp[N];
    }

    // #2 Method to find the total number of distinct ways, using constant auxiliary space - O(N) & O(1)
    int climbStairs_V2(int N) {
        // Edge case: If N is negative, then no valid stairs exist, as because there can't be negative stairs
        if(N < 0)
            return 0;

        int prevPrevWays = 1; // Initially, if there is no stair that means we're already on it
        int prevWays = 1;     // If there is 1 stair that means we can reach it from the 0th stair
        int currWays = 1;     // The total number of ways to reach the 1th stair is 1

        // Iterate and compute the number of ways to reach the Jth stair
        for(int J=2; J<=N; J++)
            currWays = prevPrevWays + prevWays,
            prevPrevWays = prevWays,
            prevWays = currWays;

        // Return the number of ways to reach the Nth stair
        return currWays;
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
        if(N > 45) {
            cout<<"\nApplication expects a value which lies within the problem constraints!";
            return 0;
        }

        // Call to find the number of ways to reach the Nth stair
        BottomUp bottomUp;
        cout<<"The total number of distinct ways to reach the "<<N<<"th stair is: "<<bottomUp.climbStairs_V2(N)<<'\n';
    }

    return 0;
}
/*
    Topics: Math | Dynamic Programming | Memoization
    Link: https://leetcode.com/problems/climbing-stairs/description/
*/
