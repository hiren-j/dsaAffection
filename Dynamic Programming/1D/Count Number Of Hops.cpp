// Program to find the total number of ways the frog can take to reach the top of Nth step, a frog can jump either 1, 2, or 3 steps to go to the top ~ coded by Hiren
#include <iostream>
#include <vector>
#define ll long long
#define mod 1000000007
using namespace std;

// Class to implement the "Top Down Approach":
class TopDown {    
public:
    // Method to find the total number of ways, using recursion with memoization - O(N) & O(N)
    ll countWays(int N) {
        vector<ll> memory(N+1, -1);
        return solveWithMemo(N, memory);
    }

private:
    // O(N) & O(N)
    ll solveWithMemo(int N, vector<ll>& memory) {
        // Edge case: If the frog reaches the top, then there exist a valid way to reach it
        if(N == 0)
            return 1;
        
        // Edge case: If the frog misses the top, then there's no valid way to reach it
        if(N < 0)
            return 0;
            
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[N] != -1)
            return memory[N];
        
        // There are always three posibilities at each step for the frog
        ll jumpOneStep   = solveWithMemo(N-1, memory) % mod; // Is to jump from the immediate 1st step below the Nth step  
        ll jumpTwoStep   = solveWithMemo(N-2, memory) % mod; // Is to jump from the immediate 2nd step below the Nth step     
        ll jumpThreeStep = solveWithMemo(N-3, memory) % mod; // Is to jump from the immediate 3rd step below the Nth step   
            
        // Store the value of the "total number of ways the frog can take to reach the Nth step" to the memoization table and then return it
        return memory[N] = (jumpOneStep + jumpTwoStep + jumpThreeStep) % mod;   
    }

    // O(3^N) & O(N)
    ll solveWithoutMemo(int N) {
        // Edge case: If the frog reaches the top, then there exist a valid way to reach it
        if(N == 0)
            return 1;
            
        // Edge case: If the frog misses the top, then there's no valid way to reach it
        if(N < 0)
            return 0;
            
        // There are always three posibilities at each step for the frog
        ll jumpOneStep   = solveWithoutMemo(N-1) % mod; // Is to jump from the immediate 1st step below the Nth step  
        ll jumpTwoStep   = solveWithoutMemo(N-2) % mod; // Is to jump from the immediate 2nd step below the Nth step     
        ll jumpThreeStep = solveWithoutMemo(N-3) % mod; // Is to jump from the immediate 3rd step below the Nth step   
            
        // Return the value of the total number of ways the frog can take to reach the Nth step
        return (jumpOneStep + jumpTwoStep + jumpThreeStep) % mod;   
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUp {
public:
    // #1 Method to find the total number of ways, using 1D buffer for tabulation - O(N) & O(N)
    ll countWays_V1(int N) {
        // Edge case: If N is negative, then no valid steps exist, as because there can't be negative steps
        if(N < 0)
            return 0;
                    
        // Tabulation buffer: dp[J] represents the total number of ways the frog can take to reach the Jth step
        vector<ll> dp(N+1, -1);
        dp[0] = 1;               // Stores the total number of ways the frog can take to reach the 0th step
        dp[1] = 1;               // Stores the total number of ways the frog can take to reach the 1th step
        dp[2] = (N > 1) ? 2 : 0; // Stores the total number of ways the frog can take to reach the top (considering the first two steps only)
        
        for(int J=3; J<=N; ++J) {
            // There are always three posibilities at each step for the frog
            ll jumpOneStep   = dp[J-1] % mod; // Is to jump from the immediate 1st step below the Jth step  
            ll jumpTwoStep   = dp[J-2] % mod; // Is to jump from the immediate 2nd step below the Jth step  
            ll jumpThreeStep = dp[J-3] % mod; // Is to jump from the immediate 3rd step below the Jth step  
            // Store the value of the total number of ways the frog can take to reach the Jth step
            dp[J] = (jumpOneStep + jumpTwoStep + jumpThreeStep) % mod;
        }
        
        // Return the total number of ways the frog can take to reach the Nth step
        return dp[N];
    }

    // #2 Method to find the total number of ways, using constant auxiliary space - O(N) & O(1)
    ll countWays_V2(int N) {
        // Edge case: If N is negative, then no valid steps exist, as because there can't be negative steps
        if(N < 0)
            return 0;
            
        ll jumpThreeStep = 0; // Stores the jump from the immediate 3rd step below the 0th step 
        ll jumpTwoStep   = 0; // Stores the jump from the immediate 2nd step below the 0th step
        ll jumpOneStep   = 1; // Stores the jump from the immediate 1st step below the 0th step
        ll numWays       = 0; // Stores the total number of ways the frog can take to reach the Nth step
        
        for(int J=1; J<=N; ++J) {
            // Store the value of the total number of ways the frog can take to reach the Jth step
            numWays       = (jumpThreeStep + jumpTwoStep + jumpOneStep) % mod;
            jumpThreeStep = jumpTwoStep % mod; // Is to jump from the immediate 3rd step below the Jth step
            jumpTwoStep   = jumpOneStep % mod; // Is to jump from the immediate 2nd step below the Jth step
            jumpOneStep   = numWays % mod;     // Is to jump from the immediate 1st step below the Jth step
        }
            
        // Return the total number of ways the frog can take to reach the Nth step
        return numWays;
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
        if(N > 100000) {
            cout<<"Application expects a value which lies within the problem constraints!\n";
            continue;
        }

        // Call to find the number of ways to reach the Nth step
        BottomUp bottomUp;
        cout<<"The total number of ways the frog can take to reach the "<<N<<"th step is: "<<bottomUp.countWays_V2(N)<<'\n';
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://www.geeksforgeeks.org/problems/count-number-of-hops-1587115620/1
*/
