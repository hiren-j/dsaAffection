// Program to find the minimum cost to reach the top of the floor ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Class to implement the "Top Down Approach":
class TopDown {
public:
    // Method to find the minimum cost to reach the top of the floor, using recursion with memoization - O(N) & O(N)
    int minCostClimbingStairs(vector<int>& cost) {
        int N = cost.size();

        // Memoization tables
        vector<int> memory1(N+1, -1), memory2(N+1, -1);

        int startFromZero = solveWithMemo(cost, memory1, N, 0); // Start movements from the 0th step
        int startFromOne  = solveWithMemo(cost, memory2, N, 1); // Start movements from the 1th step

        // Return the minimum cost to reach the top of the floor
        return min(startFromZero, startFromOne);
    }

private:
    // O(N) & O(N)
    int solveWithMemo(vector<int>& cost, vector<int>& memory, int N, int J) {
        // Edge case: If we reached the top of the floor, then we don't need any cost
        if(J >= N)
            return 0;

        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[J] != -1)
            return memory[J];
        
        // There are always two possibilities at each step
        int climbOneStep = solveWithMemo(cost, memory, N, J+1); // Is to jump and advance one step ahead from this step
        int climbTwoStep = solveWithMemo(cost, memory, N, J+2); // Is to jump and advance two steps ahead from this step

        // Store the value of the minimum cost to the memoization table and then return it
        return memory[J] = cost[J] + min(climbOneStep, climbTwoStep);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& cost, int N, int J) {
        // Edge case: If we reached the top of the floor, then we don't need any cost
        if(J >= N)
            return 0;

        // There are always two possibilities at each step
        int climbOneStep = solveWithoutMemo(cost, N, J+1); // Is to jump and advance one step ahead from this step
        int climbTwoStep = solveWithoutMemo(cost, N, J+2); // Is to jump and advance two steps ahead from this step

        // Return the value of the minimum cost
        return cost[J] + min(climbOneStep, climbTwoStep);
    }
};

// Class to implement the "Bottom Up Approach":
class BottomUp {
public:
    // #1 Method to find the minimum cost to reach the top of the floor, using 1d buffer for tabulation - O(N) & O(N)
    int minCostClimbingStairs_V1(vector<int>& cost) {
        int N = cost.size();

        // Tabulation buffer: dp[J] represents the minimum cost needed to reach the Jth floor
        vector<int> dp(N, 0);
        dp[0] = cost[0]; // For the 0th step the minimum cost needed to reach it is the cost that the step have
        dp[1] = cost[1]; // For the 1th step the minimum cost needed to reach it is the cost that the step have

        // Iterate and compute the minimum cost needed to reach the Jth step
        for(int J=2; J<N; J++)
            dp[J] = cost[J] + min(dp[J-1], dp[J-2]);

        // Return the minimum cost needed to reach the top of the floor
        return min(dp[N-1], dp[N-2]);
    }

    // #2 Method to find the minimum cost to reach the top of the floor, using constant auxiliary space - O(N) & O(1)
    int minCostClimbingStairs_V2(vector<int>& cost) {
        int N = cost.size();

        int prevPrevCost = cost[0];           // For the 0th step the minimum cost needed to reach it is the cost that the step have
        int prevCost = cost[1];               // For the 1th step the minimum cost needed to reach it is the cost that the step have            
        int currCost = min(cost[0], cost[1]); // Compute and store the minimum cost needed to reach the top (considering the first two steps only)

        // Iterate and compute the minimum cost needed to reach the Jth step
        for(int J=2; J<N; J++)
            currCost = cost[J] + min(prevPrevCost, prevCost),
            prevPrevCost = prevCost,
            prevCost = currCost;

        // Return the minimum cost needed to reach the top of the floor
        return min(currCost, prevPrevCost);
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls the console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the array size
        int N;
        cout<<"Enter the total number of steps: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0 || N >= 1001) {
            cout<<"Enter the value which lies within the problem constraints, application expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<int> cost(N);

        // Input the array values
        for(int J=0; J<N; J++) {
            cout<<"Enter the cost of the "<<J<<"th step: ";
            cin>>cost[J];
        }

        // Call to find the minimum cost to reach the top of the floor
        BottomUp bottomUp;
        int minCostReachTop = bottomUp.minCostClimbingStairs_V2(cost);
        cout<<"\nThe minimum cost to reach the top of the floor is: "<<minCostReachTop;

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
    Link: https://leetcode.com/problems/min-cost-climbing-stairs/description/
*/
