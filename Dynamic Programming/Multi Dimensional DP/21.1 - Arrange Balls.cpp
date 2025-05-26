// Code to find total number of possible arrangements. There are p balls of type P, q balls of type Q and r balls of type R. Using the balls we want to create a straight line such that no two balls of same type are adjacent ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    DON'T IGNORE MUST READ :-
        We'll use 1 to represent the ball of type P
        We'll use 2 to represent the ball of type Q
        We'll use 3 to represent the ball of type R
*/
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    
    // O(2^(P*Q*R)) & O(P+Q+R)
    int solveWithoutMemo(int P, int Q, int R, int prevBall) {
        // Edge case: If you've created a valid arrangement by picking all type of balls then return 1
        if(P == 0 && Q == 0 && R == 0)
            return 1; 

        // Edge case: If its not possible to pick all type of balls then return 0
        if(P < 0 || Q < 0 || R < 0)
            return 0; 
                        
        int count = 0;

        if(prevBall != 1) count = solveWithoutMemo(P-1, Q, R, 1);                 // If previously not picked then pick a ball of type P
        if(prevBall != 2) count = (count + solveWithoutMemo(P, Q-1, R, 2)) % MOD; // If previously not picked then pick a ball of type Q
        if(prevBall != 3) count = (count + solveWithoutMemo(P, Q, R-1, 3)) % MOD; // If previously not picked then pick a ball of type R
        
        return count;
    }

    // O(2*P*Q*R*4) & O(P*Q*R*4 + P+Q+R)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, int P, int Q, int R, int prevBall) {
        // Edge case: If you've created a valid arrangement by picking all type of balls then return 1
        if(P == 0 && Q == 0 && R == 0)
            return 1; 

        // Edge case: If its not possible to pick all type of balls then return 0
        if(P < 0 || Q < 0 || R < 0)
            return 0; 
            
        if(dp[P][Q][R][prevBall] != -1)
            return dp[P][Q][R][prevBall];
            
        int count = 0;

        if(prevBall != 1) count = solveWithMemo(dp, P-1, Q, R, 1);                 // If previously not picked then pick a ball of type P
        if(prevBall != 2) count = (count + solveWithMemo(dp, P, Q-1, R, 2)) % MOD; // If previously not picked then pick a ball of type Q
        if(prevBall != 3) count = (count + solveWithMemo(dp, P, Q, R-1, 3)) % MOD; // If previously not picked then pick a ball of type R
        
        return dp[P][Q][R][prevBall] = count;
    }
    
public:
    // Method to count total ways to make ball arrangements, using recursion with memoization - O(PQR) & O(PQR) 
    int countTotalArrangements(int P, int Q, int R) {
        vector<vector<vector<vector<int>>>> dp(P+1, vector<vector<vector<int>>>(Q+1, vector<vector<int>>(R+1, vector<int>(4, -1))));
        return solveWithMemo(dp, P, Q, R, 0);
    }
};
// Note: This solution will lead to TLE

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
    // O(PQR) & O(PQR) : Where P = givenP, Q = givenQ, R = givenR
    int solveWith4DTable(int givenP, int givenQ, int givenR) {
        vector<vector<vector<vector<int>>>> dp(givenP + 1, 
                vector<vector<vector<int>>>(givenQ + 1, 
                        vector<vector<int>>(givenR + 1, 
                                vector<int>(4, -1))));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall) // Init first edge case
            dp[0][0][0][prevBall] = 1;
        
        for(int P = 0; P <= givenP; ++P) {
            for(int Q = 0; Q <= givenQ; ++Q) {
                for(int R = 0; R <= givenR; ++R) {
                    if(P == 0 && Q == 0 && R == 0)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;
                        if(prevBall != 1) count = (P-1 >= 0 ? dp[P-1][Q][R][1] : 0);
                        if(prevBall != 2) count = (count + (Q-1 >= 0 ? dp[P][Q-1][R][2] : 0)) % MOD;
                        if(prevBall != 3) count = (count + (R-1 >= 0 ? dp[P][Q][R-1][3] : 0)) % MOD;
                        dp[P][Q][R][prevBall] = count;
                    }
                }
            }
        }
            
        return dp[givenP][givenQ][givenR][0];
    }
    
    // O(PQR) & O(PQR) : Where P = givenP, Q = givenQ, R = givenR
    int solveWith4DEnhanced(int givenP, int givenQ, int givenR) {
        vector<vector<vector<vector<int>>>> dp(givenP + 2, 
                vector<vector<vector<int>>>(givenQ + 2, 
                        vector<vector<int>>(givenR + 2, 
                                vector<int>(4, 0))));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)
            dp[1][1][1][prevBall] = 1;
        
        for(int P = 1; P <= givenP + 1; ++P) {
            for(int Q = 1; Q <= givenQ + 1; ++Q) {
                for(int R = 1; R <= givenR + 1; ++R) {
                    if(P == 1 && Q == 1 && R == 1)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;
                        if(prevBall != 1) count = dp[P-1][Q][R][1];
                        if(prevBall != 2) count = (count + dp[P][Q-1][R][2]) % MOD;
                        if(prevBall != 3) count = (count + dp[P][Q][R-1][3]) % MOD;
                        dp[P][Q][R][prevBall] = count;
                    }
                }
            }
        }
            
        return dp[givenP + 1][givenQ + 1][givenR + 1][0];
    }
    // Note: This solution will lead to TLE
    
    // O(PQR) & O(2*QR) : Where P = givenP, Q = givenQ, R = givenR
    int solveWith3DTable(int givenP, int givenQ, int givenR) {
        vector<vector<vector<int>>> prevRow(givenQ + 2, 
                vector<vector<int>>(givenR + 2, 
                        vector<int>(4, 0)));
        
        vector<vector<vector<int>>> idealRow(givenQ + 2, 
                vector<vector<int>>(givenR + 2, 
                        vector<int>(4, 0)));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)
            idealRow[1][1][prevBall] = 1;
        
        for(int P = 1; P <= givenP + 1; ++P) {
            for(int Q = 1; Q <= givenQ + 1; ++Q) {
                for(int R = 1; R <= givenR + 1; ++R) {
                    if(P == 1 && Q == 1 && R == 1)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;
                        if(prevBall != 1) count = prevRow[Q][R][1];
                        if(prevBall != 2) count = (count + idealRow[Q-1][R][2]) % MOD;
                        if(prevBall != 3) count = (count + idealRow[Q][R-1][3]) % MOD;
                        idealRow[Q][R][prevBall] = count;
                    }
                }
            }
            prevRow = idealRow;
        }
            
        return idealRow[givenQ + 1][givenR + 1][0];
    }
    
public:
    int countTotalArrangements(int P, int Q, int R) {
        return solveWith3DTable(P, Q, R);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          
Topics: Combinatorics | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/arrange-balls0052/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
