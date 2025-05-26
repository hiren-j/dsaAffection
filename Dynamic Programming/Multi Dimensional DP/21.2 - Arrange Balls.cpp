// Code to find total number of possible arrangements. There are p balls of type P, q balls of type Q and r balls of type R. Using the balls we want to create a straight line such that no two balls of same type are adjacent ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*
    DON'T IGNORE MUST READ :-
        We'll use 1 to represent the ball of type P
        We'll use 2 to represent the ball of type Q
        We'll use 3 to represent the ball of type R

    NOTE: In the previous solution, we're using the same redundant code in all if blocks, here I just removed that redundancy, 
          so I could say approach remains the same.
*/
  -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, int P, int Q, int R, int prevBall) {
        if(P == 0 && Q == 0 && R == 0)
            return 1;
        
        if(P < 0 || Q < 0 || R < 0)
            return 0;
            
        if(dp[P][Q][R][prevBall] != -1)
            return dp[P][Q][R][prevBall];
            
        int count = 0;
        
        for(int ball = 1; ball < 4; ++ball)
            if(ball != prevBall)
                count = (count + solveWithMemo(dp, (ball == 1 ? P - 1 : P), 
                                                   (ball == 2 ? Q - 1 : Q), 
                                                   (ball == 3 ? R - 1 : R), ball)) % MOD;
                
        return dp[P][Q][R][prevBall] = count;
    }
    
public:
    int countTotalArrangements(int P, int Q, int R) {
        vector<vector<vector<vector<int>>>> dp(P + 1, vector<vector<vector<int>>>(Q + 1, vector<vector<int>>(R + 1, vector<int>(4, -1))));
        return solveWithMemo(dp, P, Q, R, 0);
    }
};
// Note: This solution will lead to TLE

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    
    int solveWith4DTable(int givenP, int givenQ, int givenR) {
        vector<vector<vector<vector<int>>>> dp(givenP + 2, vector<vector<vector<int>>>(givenQ + 2, vector<vector<int>>(givenR + 2, vector<int>(4, 0))));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)
            dp[1][1][1][prevBall] = 1;
        
        for(int P = 1; P <= givenP + 1; ++P) {
            for(int Q = 1; Q <= givenQ + 1; ++Q) {
                for(int R = 1; R <= givenR + 1; ++R) {
                    if(P == 1 && Q == 1 && R == 1)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;
                        for(int ball = 1; ball < 4; ++ball) {
                            if(ball != prevBall) {
                                count = (count + dp[ball == 1 ? P - 1 : P]
                                                   [ball == 2 ? Q - 1 : Q]
                                                   [ball == 3 ? R - 1 : R][ball]) % MOD;
                            }
                        }
                        dp[P][Q][R][prevBall] = count;
                    }
                }
            }
        }
            
        return dp[givenP + 1][givenQ + 1][givenR + 1][0];
    }
    // Note: This solution will lead to TLE
            
    int solveWith3DTable(int givenP, int givenQ, int givenR) {
        vector<vector<vector<int>>> prevRow(givenQ + 2, vector<vector<int>>(givenR + 2, vector<int>(4, 0)));
        vector<vector<vector<int>>> idealRow(givenQ + 2, vector<vector<int>>(givenR + 2, vector<int>(4, 0)));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)
            idealRow[1][1][prevBall] = 1;
        
        for(int P = 1; P <= givenP + 1; ++P) {
            for(int Q = 1; Q <= givenQ + 1; ++Q) {
                for(int R = 1; R <= givenR + 1; ++R) {
                    if(P == 1 && Q == 1 && R == 1)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;
                        for(int ball = 1; ball < 4; ++ball) {
                            if(ball != prevBall) {
                                if(ball == 1) {
                                    count = (count + prevRow[ball == 2 ? Q - 1 : Q]
                                                            [ball == 3 ? R - 1 : R][ball]) % MOD;
                                }
                                else {
                                    count = (count + idealRow[ball == 2 ? Q - 1 : Q]
                                                             [ball == 3 ? R - 1 : R][ball]) % MOD;
                                }
                            }
                        }
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
