// Program to find the minimum energy that can be used by the Geek to jump from step 0 to step N-1 ~ coded by Hirn
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the minimum energy, using recursion with memoization - O(N * maxElement) & O(N * maxElement)
    int minimumEnergy(vector<int>& heights, int N) {
        int maxElement = *max_element(begin(heights), end(heights));
        vector<vector<int>> memory(N+1, vector<int>(maxElement+1, -1));
        return solveWithMemo(memory, heights, N, 0, heights[0]);
    }
    
private:
    // O(N * maxElement) & O(N * maxElement)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& heights, int N, int J, int prevHeight) {
        // Edge case: If we're not able to reach the last step, then it's not possible to have a valid way
        if(J >= N)
            return INT_MAX;
        
        // Edge case: If we reached the last step, then return the energy value as a valid indication of a valid way
        if(J == N-1)
            return abs(prevHeight - heights[J]);
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[J][prevHeight] != -1)
            return memory[J][prevHeight];

        // There are always two possibilities at each step
        int climbOneStep = solveWithMemo(memory, heights, N, J+1, heights[J]); // Is to advance one step ahead from this step
        int climbTwoStep = solveWithMemo(memory, heights, N, J+2, heights[J]); // Is to advance two steps ahead from this step
            
        // Store the value of the minimum energy to the memoization table and then return it
        return memory[J][prevHeight] = abs(prevHeight - heights[J]) + min(climbOneStep, climbTwoStep);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& heights, int N, int J, int prevHeight) {
        // Edge case: If we're not able to reach the last step, then it's not possible to have a valid way
        if(J >= N)
            return INT_MAX;
            
        // Edge case: If we reached the last step, then return the energy value as a valid indication of a valid way
        if(J == N-1)
            return abs(prevHeight - heights[J]);
            
        // There are always two possibilities at each step
        int climbOneStep = solveWithoutMemo(heights, N, J+1, heights[J]); // Is to advance one step ahead from this step
        int climbTwoStep = solveWithoutMemo(heights, N, J+2, heights[J]); // Is to advance two steps ahead from this step
        
        // Compute the value of the minimum energy and then return it        
        return abs(prevHeight - heights[J]) + min(climbOneStep, climbTwoStep);
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the minimum energy, using recursion with memoization - O(N) & O(N)
    int minimumEnergy(vector<int>& heights, int N) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(memory, heights, N, 0);
    }
    
private:
    // O(N) & O(N)
    int solveWithMemo(vector<int>& memory, vector<int>& heights, int N, int J) {
        // Edge case: If we reached the last step, then we don't have to compute more energy
        if(J == N-1)
            return 0;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[J] != -1)
            return memory[J];
            
        // There are always two possibilities at each step
        int climbOneStep = INT_MAX; // Is to advance one step ahead from this step
        int climbTwoStep = INT_MAX; // Is to advance two steps ahead from this step
        
        // Move if it's possible to advance one step ahead from this step
        if(J+1 < N)
            climbOneStep = abs(heights[J] - heights[J+1]) + solveWithMemo(memory, heights, N, J+1);
            
        // Move if it's possible to advance two steps ahead from this step
        if(J+2 < N)
            climbTwoStep = abs(heights[J] - heights[J+2]) + solveWithMemo(memory, heights, N, J+2);
            
        // Store the value of the minimum energy to the memoization table and then return it
        return memory[J] = min(climbOneStep, climbTwoStep);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& heights, int N, int J) {
        // Edge case: If we reached the last step, then we don't have to compute more energy
        if(J == N-1)
            return 0;
            
        // There are always two possibilities at each step
        int climbOneStep = INT_MAX; // Is to advance one step ahead from this step
        int climbTwoStep = INT_MAX; // Is to advance two steps ahead from this step
        
        // Move if it's possible to advance one step ahead
        if(J+1 < N)
            climbOneStep = abs(heights[J] - heights[J+1]) + solveWithoutMemo(heights, N, J+1);
            
        // Move if it's possible to advance two steps ahead from this step
        if(J+2 < N)
            climbTwoStep = abs(heights[J] - heights[J+2]) + solveWithoutMemo(heights, N, J+2);
            
        // Return the value of the minimum energy
        return min(climbOneStep, climbTwoStep);
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the minimum energy, using 1d buffer for tabulation - O(N) & O(N)
    int minimumEnergy_V1(vector<int>& heights, int N) {
        // Tabulation buffer: dp[J] represents the minimum energy required to reach the Jth step
        vector<int> dp(N);
        dp[0] = 0;                                          // Initially, if there's no steps then no energy required
        dp[1] = (N > 1) ? abs(heights[0] - heights[1]) : 0; // Compute the minimum energy by considering the first two steps
        
        // Iterate and compute the minimum energy required to reach the Jth step
        for(int J=2; J<N; J++) 
            dp[J] = min(abs(heights[J] - heights[J-1]) + dp[J-1], abs(heights[J] - heights[J-2]) + dp[J-2]);
        
        // Return the minimum energy required to reach the last step (N-1 step)
        return dp[N-1];
    }

    // #2 Method to find the minimum energy, using constant auxiliary space - O(N) & O(1)
    int minimumEnergy_V2(vector<int>& heights, int N) {
        int prevPrevEnergy = 0;                                      // Initially, if there's no steps then no energy required
        int prevEnergy = (N > 1) ? abs(heights[0] - heights[1]) : 0; // Compute the minimum energy by considering the first two steps
        int currEnergy = prevEnergy;                                 // Stores the minimum energy of the first two steps
        
        // Iterate and compute the minimum energy required to reach the Jth step
        for(int J=2; J<N; J++) 
            currEnergy = min(abs(heights[J] - heights[J-1]) + prevEnergy, abs(heights[J] - heights[J-2]) + prevPrevEnergy),
            prevPrevEnergy = prevEnergy,
            prevEnergy = currEnergy;
        
        // Return the minimum energy required to reach the last step (N-1 step)
        return currEnergy;
    }
};

// Driver code
int main() {
    // Input section to control the flow of iterations of the application
    int testCases;
    cout<<"Enter the number of cases to test: ";
    cin>>testCases;

    while(testCases-- > 0) {
        // Input the array size
        int N;
        cout<<"\nEnter the total number of steps: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0 || N >= 100001) {
            cout<<"Enter a value which lies within the problem constraints, application expects a positive integer!\n";
        }
        else {
            // Stores the array values
            vector<int> heights(N, 0);

            // Input the array values
            for(int J=0; J<N;) {
                cout<<"Enter the height of "<<J<<"th index: ";
                cin>>heights[J];
                if(heights[J] <= 0 || heights[J] >= 1001) {
                    cout<<"You must enter a height which lies within the range [1 - 1000]\n";
                    continue;
                }
                J++;
            }

            // Call to find the minimum energy that can be used by the Geek to jump from step 0 to step N-1 
            BottomUp bottomUp;
            int minEnergy = bottomUp.minimumEnergy_V2(heights, N);
            cout<<"The minimum energy that can be used by the Geek to jump from step 0 to step N-1 is: "<<minEnergy<<'\n';
        }
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Links: https://www.geeksforgeeks.org/problems/geek-jump/1 
           https://www.codingninjas.com/studio/problems/frog-jump_3621012
*/
