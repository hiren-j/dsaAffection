// Program to find the Nth number of the fibonacci sequence ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDownDP {
public:
    // Method to find the Nth number of the fibonacci sequence, using recursion with memoization - O(N) & O(N)
    int getNthFibonacci(int N) {
        vector<int> memo(N+1, -1);
        return solveWithMemo(N, memo);
    }

private:
    // O(2^N) & O(N)
    int solveWithoutMemo(int N) {
        // Edge case: When the value of N is less than 2
        if(N < 2)
            return N;
            
        // Recursively compute and return the sum of the two preceding values of N
        return solveWithoutMemo(N-1) + solveWithoutMemo(N-2);
    };

    // O(N) & O(N)
    int solveWithMemo(int N, vector<int>& memo) {
        // Edge case: When the value of N is less than 2
        if(N < 2)
            return N;

        // Memoization table: If the current state is already computed then return the computed value
        if(memo[N] != -1)
            return memo[N];

        // Recursively compute and return the sum of the two preceding values of N
        return memo[N] = solveWithMemo(N-1, memo) + solveWithMemo(N-2, memo);
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUpDP {
public:
    // #1 Method to find the Nth number of the fibonacci sequence, using buffer only - O(N) & O(N)
    int getNthFibonacci_V1(int N) {
        // Edge case: When the value of N is less than 2
        if(N < 2)
            return N;

        vector<int> dp(N+1, 0); 
        dp[1] = 1;

        // Compute and store the sum of the two preceding values
        for(int i=2; i<=N; i++)
            dp[i] = dp[i-1] + dp[i-2];

        // Return the Nth number of the sequence
        return dp[N];
    }

    // #2 Method to find the Nth number of the fibonacci sequence, using constant auxiliary space - O(N) & O(1)
    int getNthFibonacci_V2(int N) {
        // Edge case: When the value of N is less than 2
        if(N < 2)
            return N;

        int prevPrevNum = 0, prevNum = 1;
        int currNum;

        // Compute and store the sum of the two preceding values
        for(int i=2; i <= N; i++) {
            currNum = prevPrevNum + prevNum;
            prevPrevNum = prevNum;
            prevNum = currNum;
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

    while(testCases--) {
        int N;
        cout<<"\nEnter the value of N: ";
        cin>>N;
        BottomUpDP bottomUp;
        cout<<"The "<<N<<"th number of the fibonacci sequence is: "<<bottomUp.getNthFibonacci_V2(N)<<'\n';
    }

    return 0;
}
// Link: https://leetcode.com/problems/fibonacci-number/
