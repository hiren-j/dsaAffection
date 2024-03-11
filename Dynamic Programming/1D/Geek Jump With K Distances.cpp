// Program to find the minimum possible total cost incurred before the Geek reaches the Nth stone, the Geek can jump to any one of the following, stone L+1, L+2, ... L+K stone and cost will be [hi-hj] is incurred, where R is the stone to land on ~ coded by Hiren
#include <iostream>
#include <climits>
#include <cstdlib>
#include <vector>
#define controlAppFlow() {char userChoice; cout<<"\n\nPress \'R\' to restart the application, else it will exist: "; cin>>userChoice; userWantsOperation = (userChoice == 'R' ? true : false);}
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the minimum possible total cost, using recursion with memoization - O(N*K) & O(N)
    int minimizeCost(vector<int>& height, int N, int K) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(memory, height, N, K, 0);
    }
    
private:
    // O(N*K) & O(N)
    int solveWithMemo(vector<int>& memory, vector<int>& height, int N, int K, int L) {
        // Edge case: If Geek reached the last stone, then there's no need of cost anymore
        if(L == N-1)
            return 0;

        // Memoizatiob table: If the current state is already computed, then return the computed value
        if(memory[L] != -1)
            return memory[L];
        
        // Stores the "minimum possible total cost to reach the last stone / result value"
        int minCost = INT_MAX;
        
        // Try each possible jump from the current step and look for the minimum cost
        for(int R=1; (R<=K && L+R<N); R++) {
            int currCost = solveWithMemo(memory, height, N, K, L+R);
            if(currCost != INT_MAX) {
                minCost = min(minCost, currCost + abs(height[L] - height[L+R]));
            }
        }
        
        // Stores the result value to the memoization table and then return it
        return memory[L] = minCost;
    }

    // O(K^N) & O(N)
    int solveWithoutMemo(vector<int>& height, int N, int K, int L) {
        // Edge case: If Geek reached the last stone, then there's no need of cost anymore
        if(L == N-1)
            return 0;
        
        // Stores the "minimum possible total cost to reach the last stone / result value"
        int minCost = INT_MAX;
        
        // Try each possible jump from the current step and look for the minimum cost
        for(int R=1; (R<=K && L+R<N); R++) {
            int currCost = solveWithoutMemo(height, N, K, L+R);
            if(currCost != INT_MAX) {
                minCost = min(minCost, currCost + abs(height[L] - height[L+R]));
            }
        }
        
        // Return the result value            
        return minCost;
    }
};

// Class to implement the Bottom-up Approach:
class BottomUp {
public:
    // Method to find the minimum possible total cost, using 1D buffer for tabulation - O(N*K) & O(N)
    int minimizeCost(vector<int>& height, int N, int K) {
        // Tabulation buffer: dp[L] represents the minimum cost required to reach the Lth step
        vector<int> dp(N, INT_MAX);
        dp[0] = 0;                                              // Initially, if there is no step then no cost is required
        dp[1] = (N > 1 ? abs(height[0] - height[1]) : INT_MAX); // Compute the minimum cost by considering the first two steps
        
        // Treat each index as an individual step and find the minimum cost to reach the the step
        for(int L=2; L<N; L++) {
            // Try each possible jump from which the Geek can reach the Lth step and look for the minimum cost
            for(int R=1; (R<=K && L-R>=0); R++) {
                dp[L] = min(dp[L], abs(height[L] - height[L-R]) + dp[L-R]);
            }
        }
        
        // Return the minimum possible total cost to reach the last stone
        return dp[N-1];
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls the console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int N;
        cout<<"Enter the total number of steps: ";
        cin>>N;

        // Input the K value
        int K;
        cout<<"Enter the value of K: ";
        cin>>K;

        // Check the given values are valid or not
        if(N <= 0 || N >= 100001) {
            cout<<"You must enter a size which lies between 1 and 100000!";
            controlAppFlow(); // Call to control the flow of iterations of the application
            continue;
        }
        else if(K <= 0 || K >= 101) {
            cout<<"You must enter the value of K which lies between 1 and 100!";
            controlAppFlow(); // Call to control the flow of iterations of the application
            continue;
        }
        else {
            // Stores the array values
            vector<int> height(N);

            // Input the array values
            for(int L=0; L<N;) {
                cout<<"Enter the height of the "<<L<<"th step: ";
                cin>>height[L];
                if(height[L] <= 0 || height[L] >= 10001) {
                    cout<<"You must enter a height which lies between 1 and 10000!\n";
                    continue;
                }
                L++;
            }

            // Call to find the minimum cost required to reach the last stone
            BottomUp bottomUp;
            int minCost = bottomUp.minimizeCost(height, N, K);
            cout<<"\nThe minimum cost the Geek takes to reach the last stone is: "<<minCost;

            // Call to control the flow of iterations of the application
            controlAppFlow();
        }
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Links: https://www.geeksforgeeks.org/problems/minimal-cost/1
           https://www.codingninjas.com/studio/problems/minimal-cost_8180930?utm_source=striver&utm_medium=website&utm_campaign=a_zcoursetuf 
*/
