// Program to find the Nth number of the tribonacci sequence ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDownDP {
public:
    // Method to find the Nth number of the tribonacci sequence, using recursion with memoization - O(N) & O(N)
    int getNthTribonacci(int N) {
        vector<int> memo(N+1, -1);
        return solveWithMemo(N, memo);
    }

private:
    // O(3^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        // Recursively compute and return the sum of the three preceding values of N
        return solveWithoutMemo(N-1) + solveWithoutMemo(N-2) + solveWithoutMemo(N-3);
    };

    // O(N) & O(N)
    int solveWithMemo(int N, vector<int>& memo) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memo[N] != -1)
            return memo[N];

        // Recursively compute and return the sum of the three preceding values of N
        return memo[N] = solveWithMemo(N-1, memo) + solveWithMemo(N-2, memo) + solveWithMemo(N-3, memo);
    }
};

// Class to implement the "Bottom UP Approach":
class BottomUpDP {
public:
    // #1 Method to find the Nth number of the sequence, using buffer only - O(N) & O(N)
    int getNthTribonacci_V1(int N) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        vector<int> dp(N+1, 0);
        dp[1] = 1;
        dp[2] = 1;

        // Compute and store the sum of the three preceding values
        for(int i=3; i<=N; i++)
            dp[i] = dp[i-3] + dp[i-2] + dp[i-1];

        // Return the Nth number of the sequence
        return dp[N];
    }

    // #2 Method to find the Nth number of the sequence, using constant auxiliary space - O(N) & O(1)
    int getNthTribonacci_V2(int N) {
        // Edge case: When the value of N is less than 3
        if(N < 3)
            return (N == 0) ? 0 : 1;

        int prevA = 0, prevB = 1, prevC = 1;
        int currNum;

        // Compute and store the sum of the three preceding values
        for(int i=3; i<=N; i++) {
            currNum = prevA + prevB + prevC;
            prevA = prevB;
            prevB = prevC;
            prevC = currNum;
        }

        // Return the Nth number of the sequence
        return currNum;
    }
};

// Driver code
int main() {
    int testCases;
    cout<<"Enter the number of testcases you want: ";
    cin>>testCases;

    while(testCases-- > 0) {
        int N;
        cout<<"\nEnter the value of N: ";
        cin>>N;
        BottomUpDP bottomUp;
        cout<<"The "<<N<<"th number of the tribonacci sequence is: "<<bottomUp.getNthTribonacci_V2(N)<<'\n';
    }

    return 0;
}
/*
    Topics: Maths | Dynamic Programming | Recursion | Memoization
    Link: https://leetcode.com/problems/N-th-tribonacci-number/description/
*/
