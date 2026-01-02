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
        
        int pickP = (prevBall != 1) ? solveWithoutMemo(P-1, Q, R, 1) : 0;
        int pickQ = (prevBall != 2) ? solveWithoutMemo(P, Q-1, R, 2) : 0; 
        int pickR = (prevBall != 3) ? solveWithoutMemo(P, Q, R-1, 3) : 0;
        
        return ((pickP + pickQ) % MOD + pickR) % MOD;
    }
    
    // O(2*P*Q*R*4) & O(P*Q*R*4 + P+Q+R)
    int solveWithMemo(vector<vector<vector<vector<int>>>>& dp, int P, int Q, int R, int prevBall) {
        if(P < 0 || Q < 0 || R < 0)
            return 0;
            
        if(P == 0 && Q == 0 && R == 0)
            return 1;
            
        if(dp[P][Q][R][prevBall] != -1)
            return dp[P][Q][R][prevBall]; 
        
        int pickP = (prevBall != 1) ? solveWithMemo(dp, P-1, Q, R, 1) : 0;
        int pickQ = (prevBall != 2) ? solveWithMemo(dp, P, Q-1, R, 2) : 0; 
        int pickR = (prevBall != 3) ? solveWithMemo(dp, P, Q, R-1, 3) : 0;
        
        return dp[P][Q][R][prevBall] = ((pickP + pickQ) % MOD + pickR) % MOD;
    }
    
public:
    // Method to count total ways to make ball arrangements, using recursion with memoization - O(PQR) & O(PQR) 
    int countTotalArrangements(int P, int Q, int R) {
        vector<vector<vector<vector<int>>>> dp(P + 1, 
                vector<vector<vector<int>>>(Q + 1, 
                        vector<vector<int>>(R + 1, 
                                vector<int>(4, -1))));
                                
        return solveWithMemo(dp, P, Q, R, 0);
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
                        int pickP = (prevBall != 1) ? dp[P-1+1][Q+1][R+1][1] : 0;
                        int pickQ = (prevBall != 2) ? dp[P+1][Q-1+1][R+1][2] : 0; 
                        int pickR = (prevBall != 3) ? dp[P+1][Q+1][R-1+1][3] : 0;
                        dp[P+1][Q+1][R+1][prevBall] = ((pickP + pickQ) % MOD + pickR) % MOD;
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
                        int pickP = (prevBall != 1) ? dp[P-1+1][Q+1][R+1][1] : 0;
                        int pickQ = (prevBall != 2) ? dp[P+1][Q-1+1][R+1][2] : 0; 
                        int pickR = (prevBall != 3) ? dp[P+1][Q+1][R-1+1][3] : 0;
                        dp[P+1][Q+1][R+1][prevBall] = ((pickP + pickQ) % MOD + pickR) % MOD;
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
                        int pickP = (prevBall != 1) ? (P-1 < 0 ? 0 : dp[P-1][Q][R][1]) : 0;
                        int pickQ = (prevBall != 2) ? (Q-1 < 0 ? 0 : dp[P][Q-1][R][2]) : 0; 
                        int pickR = (prevBall != 3) ? (R-1 < 0 ? 0 : dp[P][Q][R-1][3]) : 0;
                        dp[P][Q][R][prevBall] = ((pickP + pickQ) % MOD + pickR) % MOD;
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
                            int pickP = (prevBall != 1) ? (P-1 < 0 ? 0 : prev[Q][R][1]) : 0;
                            int pickQ = (prevBall != 2) ? (Q-1 < 0 ? 0 : curr[Q-1][R][2]) : 0; 
                            int pickR = (prevBall != 3) ? (R-1 < 0 ? 0 : curr[Q][R-1][3]) : 0;
                            curr[Q][R][prevBall] = ((pickP + pickQ) % MOD + pickR) % MOD;
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
