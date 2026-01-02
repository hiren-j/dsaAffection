// Code to find total number of possible arrangements. There are p balls of type P, q balls of type Q and r balls of type R. Using the balls we want to create a straight line such that no two balls of same type are adjacent ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    
    // O(2^(P+Q+R)) & O(P+Q+R)
    int solveWithoutMemo(int P, int Q, int R, int prevBall) {
        if(P < 0 || Q < 0 || R < 0)
            return 0;
            
        if(P == 0 && Q == 0 && R == 0)
            return 1;
        
        int count = 0;
        
        for(int ball = 1; ball < 4; ++ball)
            if(ball != prevBall)
                count = (count + solveWithoutMemo((ball == 1 ? P - 1 : P), 
                                                  (ball == 2 ? Q - 1 : Q), 
                                                  (ball == 3 ? R - 1 : R), ball)) % MOD;
        return count;
    }
    
    // O(2*P*Q*R*4) & O(P*Q*R*4 + P+Q+R)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, int P, int Q, int R, int prevBall) {
        if(P < 0 || Q < 0 || R < 0)
            return 0;
            
        if(P == 0 && Q == 0 && R == 0)
            return 1;
            
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
    // Method to count total ways to make ball arrangements, using recursion with memoization - O(PQR) & O(PQR) 
    int countTotalArrangements(int P, int Q, int R) {
        return solveBy2DTable(P, Q, R);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;

    // O(GP*GQ*GR*4) & O(GP*GQ*GR*4) : Where GP = given_P, GQ = given_Q, GR = given_R
    int solveBy4DShifting(int given_P, int given_Q, int given_R) {
        vector<vector<vector<vector<int>>>> dp(given_P + 2, 
                vector<vector<vector<int>>>(given_Q + 2, 
                        vector<vector<int>>(given_R + 2, 
                                vector<int>(4, -1))));
        
        for(int Q = 0; Q <= given_Q; ++Q) 
            for(int R = 0; R <= given_R; ++R) 
                for(int prevBall = 3; prevBall >= 0; --prevBall) 
                    dp[-1+1][Q+1][R+1][prevBall] = 0;
                        
        for(int P = 0; P <= given_P; ++P)  
            for(int R = 0; R <= given_R; ++R) 
                for(int prevBall = 3; prevBall >= 0; --prevBall) 
                    dp[P+1][-1+1][R+1][prevBall] = 0;
                    
        for(int P = 0; P <= given_P; ++P)  
            for(int Q = 0; Q <= given_Q; ++Q) 
                for(int prevBall = 3; prevBall >= 0; --prevBall) 
                    dp[P+1][Q+1][-1+1][prevBall] = 0;
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)                         
            dp[0+1][0+1][0+1][prevBall] = 1;
            
        for(int P = 0; P <= given_P; ++P) {
            for(int Q = 0; Q <= given_Q; ++Q) {
                for(int R = 0; R <= given_R; ++R) {
                    if(P == 0 && Q == 0 && R == 0)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;

                        for(int ball = 1; ball < 4; ++ball)
                            if(ball != prevBall)
                                count = (count + dp[ball == 1 ? P-1+1 : P] 
                                                   [ball == 2 ? Q-1+1 : Q] 
                                                   [ball == 3 ? R-1+1 : R][ball]) % MOD;  

                        dp[P+1][Q+1][R+1][prevBall] = count;
                    }
                }
            }
        }
        
        return dp[given_P + 1][given_Q + 1][given_R + 1][0];
    }
    
    // O(GP*GQ*GR*4) & O(GP*GQ*GR*4) : Where GP = given_P, GQ = given_Q, GR = given_R
    int solveBy4DShiftEnhanced(int given_P, int given_Q, int given_R) {
        vector<vector<vector<vector<int>>>> dp(given_P + 2, 
                vector<vector<vector<int>>>(given_Q + 2, 
                        vector<vector<int>>(given_R + 2, 
                                vector<int>(4, 0))));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)                         
            dp[0+1][0+1][0+1][prevBall] = 1;
            
        for(int P = 0; P <= given_P; ++P) {
            for(int Q = 0; Q <= given_Q; ++Q) {
                for(int R = 0; R <= given_R; ++R) {
                    if(P == 0 && Q == 0 && R == 0)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        int count = 0;

                        for(int ball = 1; ball < 4; ++ball)
                            if(ball != prevBall)
                                count = (count + dp[ball == 1 ? P-1 : P] 
                                                   [ball == 2 ? Q-1 : Q] 
                                                   [ball == 3 ? R-1 : R][ball]) % MOD;  
                                                   
                        dp[P][Q][R][prevBall] = count;
                    }
                }
            }
        }
        
        return dp[given_P + 1][given_Q + 1][given_R + 1][0];
    }
    
    // O(GP*GQ*GR*4) & O(GP*GQ*GR*4) : Where GP = given_P, GQ = given_Q, GR = given_R
    int solveBy4DTable(int given_P, int given_Q, int given_R) {
        vector<vector<vector<vector<int>>>> dp(given_P + 1, 
                vector<vector<vector<int>>>(given_Q + 1, 
                        vector<vector<int>>(given_R + 1, 
                                vector<int>(4, -1))));
        
        for(int prevBall = 0; prevBall < 4; ++prevBall)                         
            dp[0][0][0][prevBall] = 1;
            
        for(int P = 0; P <= given_P; ++P) {
            for(int Q = 0; Q <= given_Q; ++Q) {
                for(int R = 0; R <= given_R; ++R) {
                    if(P == 0 && Q == 0 && R == 0)
                        continue;
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                       int count = 0;

                        for(int ball = 1; ball < 4; ++ball)
                            if(ball != prevBall)
                                count = (count + dp[ball == 1 ? P-1 : P] 
                                                   [ball == 2 ? Q-1 : Q] 
                                                   [ball == 3 ? R-1 : R][ball]) % MOD;  
                       
                        dp[P][Q][R][prevBall] = count;
                    }
                }
            }
        }
        
        return dp[given_P][given_Q][given_R][0];
    }
    
    // O(GQ*GR*4 + GP*(GQ*GR*4)) & O(2*GQ*GR*4) : Where GP = given_P, GQ = given_Q, GR = given_R
    int solveBy2DTable(int given_P, int given_Q, int given_R) {
        // P - 1th table
        vector<vector<vector<int>>> prev(given_Q + 1, 
                vector<vector<int>>(given_R + 1, 
                        vector<int>(4, -1)));
        // Pth table
        vector<vector<vector<int>>> curr(given_Q + 1, 
                vector<vector<int>>(given_R + 1, 
                        vector<int>(4, -1)));
        
        for(int P = 0; P <= given_P; ++P) {
            for(int Q = 0; Q <= given_Q; ++Q) {
                for(int R = 0; R <= given_R; ++R) {
                    for(int prevBall = 3; prevBall >= 0; --prevBall) {
                        if(P == 0 && Q == 0 && R == 0) {
                            curr[0][0][prevBall] = 1;
                        }
                        else {
                            int count = 0;

                            for(int ball = 1; ball < 4; ++ball) {
                                if(ball != prevBall) {
                                    if(ball == 1) {
                                        count = (count + prev[ball == 2 ? Q-1 : Q]
                                                             [ball == 3 ? R-1 : R][ball]) % MOD;  
                                    }
                                    else {
                                        count = (count + curr[ball == 2 ? Q-1 : Q]
                                                             [ball == 3 ? R-1 : R][ball]) % MOD;  
                                    }
                                }
                            }

                            curr[Q][R][prevBall] = count;
                        }
                    }
                }
            }
            swap(prev, curr);
        }
        
        return prev[given_Q][given_R][0];
    }
    
public:
    int countTotalArrangements(int P, int Q, int R) {
        return solveBy2DTable(P, Q, R);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
          
Topics: Combinatorics | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/arrange-balls0052/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
