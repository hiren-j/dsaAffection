// Program to find the number of ways such that your pointer is still at index 0 after exactly "steps" steps ~ coded by Hiren
#define MOD 1000000007
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {        
public:
    // Method to find the total number of ways using recursion with memoization - O((steps * min(arrLen, steps)) & O(steps * min(arrLen, steps))
    int numWays(int steps, int arrLen) {
        arrLen = min(arrLen, steps);
        vector<vector<int>> memory(steps + 1, vector<int>(arrLen, -1));
        return solveWithMemo(memory, steps, arrLen, 0);
    }

private:
    // O((steps * min(arrLen, steps)) & O(steps * min(arrLen, steps))
    int solveWithMemo(vector<vector<int>>& memory, int steps, int arrLen, int pointer) {
        // Edge case: If the pointer is still at index 0 after exactly "steps" steps then you've one valid way
        if(steps == 0)
            return (pointer == 0);

        // Edge case: If the steps becomes negative or the pointer is placed outside of the array at any time then you've no valid way
        if(steps < 0 || pointer < 0 || pointer >= arrLen)
            return 0;

        // Memoization memory: If the current state is already computed then return the computed value
        if(memory[steps][pointer] != -1)
            return memory[steps][pointer];

        // There are always three posibilities to perform at each step
        int moveToLeft  = solveWithMemo(memory, steps - 1, arrLen, pointer - 1); // Is to move 1 position to the left  
        int moveToRight = solveWithMemo(memory, steps - 1, arrLen, pointer + 1); // Is to move 1 position to the right 
        int stayAtSame  = solveWithMemo(memory, steps - 1, arrLen, pointer);     // Is to stay at the same place      

        // Store the result value to the memoization memory and then return it
        return memory[steps][pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
    }
    
    // O(3^steps) & O(min(arrLen, steps))
    int solveWithoutMemo(int steps, int arrLen, int pointer) {
        // Edge case: If the pointer is still at index 0 after exactly "steps" steps then you've one valid way
        if(steps == 0)
            return (pointer == 0);

        // Edge case: If the steps becomes negative or the pointer is placed outside of the array at any time then you've no valid way
        if(steps < 0 || pointer < 0 || pointer >= arrLen)
            return 0;

        // There are always three posibilities to perform at each step
        int moveToLeft  = solveWithoutMemo(steps - 1, arrLen, pointer - 1); // Is to move 1 position to the left 
        int moveToRight = solveWithoutMemo(steps - 1, arrLen, pointer + 1); // Is to move 1 position to the right
        int stayAtSame  = solveWithoutMemo(steps - 1, arrLen, pointer);     // Is to stay at the same place      

        // Return the result value
        return ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the total number of ways using 2D tabulation - O((steps * min(arrLen, steps)) & O(steps * min(arrLen, steps))
    int numWays_A(int steps, int arrLen) {
        // Pointer movements are dependent on both steps and the array length hence it's better to chose the minimum one to fit in the memory 
        arrLen = min(arrLen, steps);

        // 2D table for tabulation: dp[currStep][pointer] stores the total number of ways such that the pointer is at the place after exactly "currStep" steps 
        vector<vector<int>> dp(steps + 1, vector<int>(arrLen, 0));

        // Edge case: If the pointer is at index 0 after exactly 0 steps then you've one valid way
        dp[0][0] = 1;

        // Fill the rest of the table
        for(int currStep = 1; currStep <= steps; ++currStep) {
            for(int pointer = 0; pointer < arrLen; ++pointer) {
                int stayAtSame       = dp[currStep - 1][pointer];                                  
                int moveToLeft       = (pointer - 1 >= 0) ? dp[currStep - 1][pointer - 1] : 0;     
                int moveToRight      = (pointer + 1 < arrLen) ? dp[currStep - 1][pointer + 1] : 0; 
                dp[currStep][pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
            }
        }

        // Return the total number of ways such that your pointer is still at index 0 after exactly "steps" steps
        return dp[steps][0];
    }

    // #2 Method to find the total number of ways using 1D tabulation - O((steps * min(arrLen, steps)) & O(min(arrLen, steps))
    int numWays_B(int steps, int arrLen) {
        // Pointer movements are dependent on both steps and the array length hence it's better to chose the minimum one to fit in the memory
        arrLen = min(arrLen, steps);

        // 1D table for tabulation: " prevRow[pointer] or currRow[pointer]" stores the total number of ways such that the pointer is at the place after exactly "currStep" steps 
        vector<int> prevRow(arrLen, 0), currRow(arrLen, 0);
        
        // Edge case: If the pointer is at index 0 after exactly 0 steps then you've one valid way
        prevRow[0] = 1;

        // Fill the rest of the table
        for(int currStep = 1; currStep <= steps; ++currStep) {
            for(int pointer = 0; pointer < arrLen; ++pointer) {
                int stayAtSame   = prevRow[pointer];
                int moveToLeft   = (pointer - 1 >= 0) ? prevRow[pointer - 1] : 0; 
                int moveToRight  = (pointer + 1 < arrLen) ? prevRow[pointer + 1] : 0; 
                currRow[pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
            }
            // Update the previous row of the upcoming row
            prevRow = currRow;
        }

        // Return the total number of ways such that your pointer is still at index 0 after exactly "steps" steps
        return prevRow[0];
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";

    // Input section to control the flow of iterations of the application
    int testCases;
    cout<<"Enter the total number of cases to test: ";
    cin>>testCases;

    while(testCases--) {
        int steps, arrLen;
        cout<<"\nEnter the total number of steps and array length: ";
        cin>>steps>>arrLen;

        // Check the given values are lying within the problem constraints or not
        if(steps < 1 || steps > 500) {
            cout<<"You must enter the steps which lies between 1 and 500!\n";
        }
        else if(arrLen < 1 || arrLen > 1e6) {
            cout<<"You must enter the array length which lies between 1 and 10^6!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The number of ways such that your pointer is still at index 0 after exactly "<<steps<<" steps is: "<<bottomUp.numWays_B(steps, arrLen)<<'\n';
        }
    }

    return 0;
}
/*
    Topics: Dynamic Programming | Matrix
    Link: https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/
*/
