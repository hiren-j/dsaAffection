// Code to find the number of ways such that your pointer is still at index 0 after exactly "steps" steps ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {  
    #define MOD 1000000007

    // O(3^steps) & O(steps)
    int solveWithoutMemo(int steps, int pointer, int arrLen) {
        if(pointer < 0 || pointer == arrLen)
            return 0;

        if(steps == 0)
            return pointer == 0;
        
        int stayAtSame  = solveWithoutMemo(steps - 1, pointer, arrLen); 
        int moveToLeft  = solveWithoutMemo(steps - 1, pointer - 1, arrLen);
        int moveToRight = solveWithoutMemo(steps - 1, pointer + 1, arrLen);

        return ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
    }

    // O(3*steps*arrLen) & O(steps*arrLen + steps)
    int solveWithMemo(vector<vector<int>>& memory, int steps, int pointer, int arrLen) {
        if(pointer < 0 || pointer == arrLen)
            return 0;

        if(steps == 0)
            return pointer == 0;

        if(memory[steps][pointer] != -1)
            return memory[steps][pointer];
        
        int stayAtSame  = solveWithMemo(memory, steps - 1, pointer, arrLen); 
        int moveToLeft  = solveWithMemo(memory, steps - 1, pointer - 1, arrLen);
        int moveToRight = solveWithMemo(memory, steps - 1, pointer + 1, arrLen);

        return memory[steps][pointer] = ((moveToLeft + moveToRight) % MOD + stayAtSame) % MOD;
    }

public:
    int numWays(int steps, int arrLen) {
        arrLen = min(steps, arrLen); 
        vector<vector<int>> memory(steps + 1, vector<int>(arrLen, -1));
        return solveWithMemo(memory, steps, 0, arrLen);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    #define MOD 1000000007

    // O(steps*arrLen) & O(steps*arrLen)
    int solveWith2DTable(int steps, int arrLen) {
        vector<vector<int>> dp(steps + 1, vector<int>(arrLen, -1));
        dp[0][0] = 1;

        for(int pointer = 1; pointer < arrLen; ++pointer)
            dp[0][pointer] = 0;

        for(int moves = 1; moves <= steps; ++moves) {
            for(int pointer = arrLen - 1; pointer >= 0; --pointer) {
                int stayAtSame  = dp[moves - 1][pointer]; 
                int moveToLeft  = (pointer - 1 >= 0) ? dp[moves - 1][pointer - 1] : 0;
                int moveToRight = (pointer + 1 < arrLen) ? dp[moves - 1][pointer + 1] : 0;
                dp[moves][pointer] = (stayAtSame + (moveToLeft + moveToRight) % MOD) % MOD;  
            }
        }

        return dp[steps][0];
    }

    // O(steps*arrLen) & O(steps*arrLen)
    int solveWith2DEnhanced(int steps, int arrLen) {
        vector<vector<int>> dp(steps + 1, vector<int>(arrLen + 2, 0));
        dp[0][1] = 1;

        for(int moves = 1; moves <= steps; ++moves) {
            for(int pointer = arrLen; pointer >= 1; --pointer) {
                int stayAtSame  = dp[moves - 1][pointer]; 
                int moveToLeft  = dp[moves - 1][pointer - 1];
                int moveToRight = dp[moves - 1][pointer + 1];
                dp[moves][pointer] = (stayAtSame + (moveToLeft + moveToRight) % MOD) % MOD;  
            }
        }

        return dp[steps][1];
    }

    // O(steps*arrLen) & O(2*arrLen)
    int solveWith1DTable(int steps, int arrLen) {
        vector<int> prevRow(arrLen + 2, 0), idealRow(arrLen + 2, 0);
        prevRow[1] = 1;

        for(int moves = 1; moves <= steps; ++moves) {
            for(int pointer = arrLen; pointer >= 1; --pointer) {
                int stayAtSame  = prevRow[pointer]; 
                int moveToLeft  = prevRow[pointer - 1];
                int moveToRight = prevRow[pointer + 1];
                idealRow[pointer] = (stayAtSame + (moveToLeft + moveToRight) % MOD) % MOD;  
            }
            prevRow = idealRow;
        }

        return prevRow[1];
    }

public:
    int numWays(int steps, int arrLen) {
        arrLen = min(steps, arrLen); ;
        return solveWith1DTable(steps, arrLen);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Combinatorics | Dynamic Programming | Matrix
Link  : https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/description/
