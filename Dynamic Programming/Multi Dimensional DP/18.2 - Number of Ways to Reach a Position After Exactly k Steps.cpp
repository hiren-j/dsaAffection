// Code to find the number of different ways to reach the position "endPos" starting from "startPos", such that you perform exactly k steps. Initially, you are standing at position "startPos" on an infinite number line. With one steps, you can move either one position to the left, or one position to the right. Note that the number line includes negative integers ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
    DON'T IGNORE MUST READ: As you work on this problem, you'll notice that, in Top-Down approach I haven't provided this edge case:
                                if(k < endPos - startPos) 
                                    return 0; 
                            
*/
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    int MAX_POS, MIN_POS, TOTAL_POS;
    int OFFSET;

    // O(2^k) & O(k)
    int solveWithoutMemo(int k, int startPos, int endPos) {
        if(k == 0)
            return startPos == endPos;
            
        int moveLeft  = solveWithoutMemo(k - 1, startPos - 1, endPos);
        int moveRight = solveWithoutMemo(k - 1, startPos + 1, endPos);

        return (moveLeft + moveRight) % MOD;
    }

    // O(2*k*TOTAL_POS) & O(k*TOTAL_POS + k)
    int solveWithMemo(vector<vector<int>>& dp, int k, int startPos, int endPos) {
        if(k == 0)
            return startPos == endPos;

        if(dp[k][startPos + OFFSET] != -1)
            return dp[k][startPos + OFFSET];

        int moveLeft  = solveWithMemo(dp, k - 1, startPos - 1, endPos);
        int moveRight = solveWithMemo(dp, k - 1, startPos + 1, endPos);

        return dp[k][startPos + OFFSET] = (moveLeft + moveRight) % MOD;
    }

public:
    // Method to find number of ways to reach end position within k steps, using recursion with memoization - O(k*TOTAL_POS) & O(k*TOTAL_POS)
    int numberOfWays(int startPos, int endPos, int k) {
        MIN_POS   = startPos - k;
        MAX_POS   = max(startPos, endPos) + k;
        OFFSET    = abs(MIN_POS);
        TOTAL_POS = MAX_POS + OFFSET;

        vector<vector<int>> dp(k + 1, vector<int>(TOTAL_POS, -1));
        return solveWithMemo(dp, k, startPos, endPos);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    int MAX_POS, MIN_POS, TOTAL_POS;
    int OFFSET;

    // O(k*TOTAL_POS) & O(k*TOTAL_POS)
    int solveWith2DTable(int k, int startPos, int endPos) {
        vector<vector<int>> dp(k + 1, vector<int>(TOTAL_POS, 0));
        dp[0][endPos + OFFSET] = 1;

        for(int steps = 1; steps <= k; ++steps) {
            for(int start = MIN_POS; start <= MAX_POS; ++start) {
                int mainIdx = start + OFFSET;
                if(mainIdx >= TOTAL_POS) continue;
                int idx1 = start - 1 + OFFSET;
                int idx2 = start + 1 + OFFSET;
                int moveLeft  = (idx1 >= 0) ? dp[steps - 1][idx1] : 0;
                int moveRight = (idx2 < TOTAL_POS) ? dp[steps - 1][idx2] : 0;
                dp[steps][mainIdx] = (moveLeft + moveRight) % MOD;
            }
        }

        return dp[k][startPos + OFFSET];
    }

    // O(k*TOTAL_POS) & O(2*TOTAL_POS)
    int solveWith1DTable(int k, int startPos, int endPos) {
        vector<int> prevRow(TOTAL_POS, 0), idealRow(TOTAL_POS, 0);
        prevRow[endPos + OFFSET] = 1;

        for(int steps = 1; steps <= k; ++steps) {
            for(int start = MIN_POS; start <= MAX_POS; ++start) {
                int mainIdx = start + OFFSET;
                if(mainIdx >= TOTAL_POS) continue;
                int idx1 = start - 1 + OFFSET;
                int idx2 = start + 1 + OFFSET;
                int moveLeft  = (idx1 >= 0) ? prevRow[idx1] : 0;
                int moveRight = (idx2 < TOTAL_POS) ? prevRow[idx2] : 0;
                idealRow[mainIdx] = (moveLeft + moveRight) % MOD;
            }
            prevRow = idealRow;
        }

        return prevRow[startPos + OFFSET];
    }

public:
    int numberOfWays(int startPos, int endPos, int k) {
        MIN_POS   = startPos - k;
        MAX_POS   = max(startPos, endPos) + k;
        OFFSET    = abs(MIN_POS);
        TOTAL_POS = MAX_POS + OFFSET;
        
        vector<vector<int>> dp(k + 1, vector<int>(TOTAL_POS, -1));
        return solveWith1DTable(k, startPos, endPos);
    }
};
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Combinatorics
Link  : https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/description/
