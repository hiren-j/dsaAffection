// Code to find the number of ways such that your pointer is still at index 0 after exactly "steps" steps ~ coded by vHiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(3^S) & O(S) : Where S = steps
    int solveWithoutMemo(int steps, int arrLen, int pointer) {
        if(steps == 0)
            return (pointer == 0) ? 1 : 0;
        
        if(pointer < 0 || pointer == arrLen)
            return 0;
        
        int stayAtSame  = solveWithoutMemo(steps - 1, arrLen, pointer);   
        int moveToLeft  = solveWithoutMemo(steps - 1, arrLen, pointer - 1); 
        int moveToRight = solveWithoutMemo(steps - 1, arrLen, pointer + 1); 

        return ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
    }
    
    // O(3*S*AL) & O(S*AL + S) : Where S = steps, AL = arrLen
    int solveWithMemo(vector<vector<int>>& dp, int steps, int arrLen, int pointer) {
        if(steps == 0)
            return (pointer == 0) ? 1 : 0;
        
        if(pointer < 0 || pointer == arrLen)
            return 0;

        if(dp[steps][pointer] != -1)
            return dp[steps][pointer];
        
        int stayAtSame  = solveWithMemo(dp, steps - 1, arrLen, pointer);   
        int moveToLeft  = solveWithMemo(dp, steps - 1, arrLen, pointer - 1); 
        int moveToRight = solveWithMemo(dp, steps - 1, arrLen, pointer + 1); 

        return dp[steps][pointer] = ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
    }

public:
    // Method to find such number of ways, using recursion with memoization - O(S*AL) & O(S*AL) : Where S = steps, AL = arrLen
    int numWays(int steps, int arrLen) {
        arrLen = min(steps, arrLen);
        vector<vector<int>> dp(steps + 1, vector<int>(arrLen, -1));
        return solveWithMemo(dp, steps, arrLen, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;

    // O(GS*AL) & O(GS*AL) : Where GS = given_steps, AL = arrLen
    int solveBy2DShifting(int given_steps, int arrLen) {
        vector<vector<int>> dp(given_steps + 1, vector<int>(arrLen + 2, -1));

        dp[0][0+1] = 1;
        for(int pointer = 1; pointer < arrLen; ++pointer)
            dp[0][pointer + 1] = 0;

        for(int steps = 0; steps <= given_steps; ++steps)
            dp[steps][-1+1] = 0;
        for(int steps = 0; steps <= given_steps; ++steps)
            dp[steps][arrLen + 1] = 0;    

        for(int steps = 1; steps <= given_steps; ++steps) {
            for(int pointer = arrLen-1; pointer >= 0; --pointer) {
                int moveToLeft  = dp[steps - 1][pointer - 1+1]; 
                int moveToRight = dp[steps - 1][pointer + 1+1]; 
                int stayAtSame  = dp[steps - 1][pointer + 1];   
                dp[steps][pointer + 1] = ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
            }
        }

        return dp[given_steps][0+1];
    }

    // O(GS*AL) & O(GS*AL) : Where GS = given_steps, AL = arrLen
    int solveBy2DTable_V1(int given_steps, int arrLen) {
        vector<vector<int>> dp(given_steps + 1, vector<int>(arrLen + 1, -1));

        dp[0][0] = 1;
        for(int pointer = 1; pointer < arrLen; ++pointer)
            dp[0][pointer] = 0;

        for(int steps = 0; steps <= given_steps; ++steps)
            dp[steps][arrLen] = 0;    

        for(int steps = 1; steps <= given_steps; ++steps) {
            for(int pointer = arrLen-1; pointer >= 0; --pointer) {
                int moveToLeft  = (pointer - 1 < 0) ? 0 : dp[steps - 1][pointer - 1]; 
                int moveToRight = dp[steps - 1][pointer + 1]; 
                int stayAtSame  = dp[steps - 1][pointer];   
                dp[steps][pointer] = ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
            }
        }

        return dp[given_steps][0];
    }

    // O(GS*AL) & O(GS*AL) : Where GS = given_steps, AL = arrLen
    int solveBy2DTable_V2(int given_steps, int arrLen) {
        vector<vector<int>> dp(given_steps + 1, vector<int>(arrLen + 1, -1));

        dp[0][0] = 1;
        for(int pointer = 1; pointer < arrLen; ++pointer)
            dp[0][pointer] = 0;

        for(int steps = 1; steps <= given_steps; ++steps) {
            for(int pointer = arrLen-1; pointer >= 0; --pointer) {
                int moveToLeft  = (pointer - 1 < 0) ? 0 : dp[steps - 1][pointer - 1]; 
                int moveToRight = (pointer + 1 == arrLen) ? 0 : dp[steps - 1][pointer + 1]; 
                int stayAtSame  = dp[steps - 1][pointer];   
                dp[steps][pointer] = ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
            }
        }

        return dp[given_steps][0];
    }

    // O(GS*AL) & O(GS*AL) : Where GS = given_steps, AL = arrLen
    int solveBy2DEnhanced(int given_steps, int arrLen) {
        vector<vector<int>> dp(given_steps + 1, vector<int>(arrLen + 1, 0));
        dp[0][0] = 1;

        for(int steps = 1; steps <= given_steps; ++steps) {
            for(int pointer = arrLen-1; pointer >= 0; --pointer) {
                int moveToLeft  = (pointer - 1 < 0) ? 0 : dp[steps - 1][pointer - 1]; 
                int moveToRight = dp[steps - 1][pointer + 1]; 
                int stayAtSame  = dp[steps - 1][pointer];   
                dp[steps][pointer] = ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
            }
        }

        return dp[given_steps][0];
    }

    // O(GS*AL) & O(2*AL) : Where GS = given_steps, AL = arrLen
    int solveBy1DTable(int given_steps, int arrLen) {
        vector<int> prevRow(arrLen + 1, 0); // steps - 1th row
        prevRow[0] = 1;

        for(int steps = 1; steps <= given_steps; ++steps) {
            vector<int> currRow(arrLen + 1, 0); // steps row

            for(int pointer = arrLen-1; pointer >= 0; --pointer) {
                int moveToLeft  = (pointer - 1 < 0) ? 0 : prevRow[pointer - 1]; 
                int moveToRight = prevRow[pointer + 1]; 
                int stayAtSame  = prevRow[pointer];   
                currRow[pointer] = ((moveToRight + moveToLeft) % MOD + stayAtSame) % MOD;
            }

            swap(prevRow, currRow);
        }

        return prevRow[0];
    }

public:
    int numWays(int steps, int arrLen) {
        arrLen = min(steps, arrLen);
        return solveBy1DTable(steps, arrLen);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Combinatorics | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/description/
