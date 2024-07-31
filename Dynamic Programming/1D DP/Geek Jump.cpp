// Code to find the minimum energy that can be used by the Geek to jump from step 0 to step N-1 ~ coded by Hirn

-------------------------------------------------------------------------------------------------------------------------------------------

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
    // O(2*N*maxElement) & O(N*maxElement + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& heights, int N, int step, int prevHeight) {
        // Edge case: If we're not able to reach the last step, then it's not possible to have a valid way
        if(step >= N)
            return INT_MAX;
        
        // Edge case: If we reached the last step, then return the energy value as a valid indication of a valid way
        if(step == N-1)
            return abs(prevHeight - heights[step]);
        
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[step][prevHeight] != -1)
            return memory[step][prevHeight];

        // There are always two possibilities to perform at each step
        int climbOneStep = solveWithMemo(memory, heights, N, step+1, heights[step]); // Is to advance one step ahead from this step
        int climbTwoStep = solveWithMemo(memory, heights, N, step+2, heights[step]); // Is to advance two steps ahead from this step
            
        // Store the result value to the memoization table and then return it
        return memory[step][prevHeight] = abs(prevHeight - heights[step]) + min(climbOneStep, climbTwoStep);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& heights, int N, int step, int prevHeight) {
        // Edge case: If we're not able to reach the last step, then it's not possible to have a valid way
        if(step >= N)
            return INT_MAX;
            
        // Edge case: If we reached the last step, then return the energy value as an valid indication 
        if(step == N-1)
            return abs(prevHeight - heights[step]);
            
        // There are always two possibilities to perform at each step
        int climbOneStep = solveWithoutMemo(heights, N, step+1, heights[step]); // Is to advance one step ahead from this step
        int climbTwoStep = solveWithoutMemo(heights, N, step+2, heights[step]); // Is to advance two steps ahead from this step
        
        // As we're striving for the minimum energy hence return the minimum value     
        return abs(prevHeight - heights[step]) + min(climbOneStep, climbTwoStep);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the minimum energy, using recursion with memoization - O(N) & O(N)
    int minimumEnergy(vector<int>& heights, int N) {
        vector<int> memory(N+1, -1);
        return solveWithMemo(memory, heights, N, 0);
    }
    
private:
    // O(2*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<int>& heights, int N, int step) {
        // Edge case: If we reached the last step then we don't have to compute more energy
        if(step == N-1)
            return 0;
            
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[step] != -1)
            return memory[step];
            
        // There are always two possibilities to perform at each step
        int climbOneStep = abs(heights[step] - heights[step+1]) + solveWithMemo(memory, heights, N, step+1); // Is to advance one step ahead from this step
        int climbTwoStep = INT_MAX;                                                                          // Is to advance two steps ahead from this step
                    
        // If it's possible then advance two steps ahead from this step
        if(step+2 < N)
            climbTwoStep = abs(heights[step] - heights[step+2]) + solveWithMemo(memory, heights, N, step+2);
            
        // Store the result value to the memoization table and then return it
        return memory[step] = min(climbOneStep, climbTwoStep);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& heights, int N, int step) {
        // Edge case: If we reached the last step then we don't have to compute more energy
        if(step == N-1)
            return 0;
            
        // There are always two possibilities to perform at each step
        int climbOneStep = abs(heights[step] - heights[step+1]) + solveWithoutMemo(heights, N, step+1); // Is to advance one step ahead from this step
        int climbTwoStep = INT_MAX;                                                                     // Is to advance two steps ahead from this step
                    
        // If it's possible to advance two steps ahead from this step
        if(step+2 < N)
            climbTwoStep = abs(heights[step] - heights[step+2]) + solveWithoutMemo(heights, N, step+2);
            
        // As we're striving for the minimum energy hence return the minimum value
        return min(climbOneStep, climbTwoStep);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the minimum energy, using 1D tabulation - O(N) & O(N)
    int minimumEnergy_V1(vector<int>& heights, int N) {
        // 1D table: dp[step] represents the minimum energy required to reach the step
        vector<int> dp(N);
        dp[0] = 0;                                          // Initially, if there's no steps then no energy is required
        dp[1] = (N > 1) ? abs(heights[0] - heights[1]) : 0; // Compute the minimum energy by considering the first two steps
        
        // Iterate and compute the minimum energy required to reach each step
        for(int step=2; step<N; step++) 
            dp[step] = min(abs(heights[step] - heights[step-1]) + dp[step-1], abs(heights[step] - heights[step-2]) + dp[step-2]);
        
        // Return the minimum energy required to reach the last step (N-1 step)
        return dp[N-1];
    }

    // #2 Method to find the minimum energy, using constant auxiliary space - O(N) & O(1)
    int minimumEnergy_V2(vector<int>& heights, int N) {
        int prevPrevEnergy = 0;                                      // Initially, if there's no steps then no energy is required
        int prevEnergy = (N > 1) ? abs(heights[0] - heights[1]) : 0; // Compute the minimum energy by considering the first two steps
        int currEnergy = prevEnergy;                                 // Stores the minimum energy of the first two steps
        
        // Iterate and compute the minimum energy required to reach the each step
        for(int step=2; step<N; step++) 
            currEnergy = min(abs(heights[step] - heights[step-1]) + prevEnergy, abs(heights[step] - heights[step-2]) + prevPrevEnergy),
            prevPrevEnergy = prevEnergy,
            prevEnergy = currEnergy;
        
        // Return the minimum energy required to reach the last step (N-1 step)
        return currEnergy;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/geek-jump/1 
        https://www.codingninjas.com/studio/problems/frog-jump_3621012
