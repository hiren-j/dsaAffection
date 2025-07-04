// Code to find the number of possible unique sequences of len n that you can create by pressing buttons (You can start from any digit) ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {    
    #define rowLimit 4
    #define colLimit 3

    vector<vector<int>> directions = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
    vector<vector<int>> keypad     = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
    // O(10 * 5^N) & O(N) 
    int solveWithoutMemo(int N, int R, int C) {
        // Edge case: No number exists outside of the keypad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R == rowLimit || C == colLimit || keypad[R][C] == -1)
            return 0;
            
        // Edge case: If you've correctly dialed a phone number of len N then you've one valid way
        if(N == 0)
            return 1;
                    
        int count = 0;
        
        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            count += solveWithoutMemo(N - 1, newR, newC);
        }

        return count;
    }

    // O(10 + 5*N*4*3) & O(N*4*3 + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int N, int R, int C) {
        // Edge case: No number exists outside of the keypad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R == rowLimit || C == colLimit || keypad[R][C] == -1)
            return 0;
            
        // Edge case: If you've correctly dialed a phone number of len N then you've one valid way
        if(N == 0)
            return 1;
        
        if(dp[N][R][C] != -1)
            return dp[N][R][C];
            
        int count = 0;
        
        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            count += solveWithMemo(dp, N - 1, newR, newC);
        }
        
        return dp[N][R][C] = count;
    }
    
public:
    // Method to count total distinct phone numbers of length N you can dial, using recursion with memoization - O(N) & O(N)
    int countUniqueSeqsOfLen(int N) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));
        int result = 0;        
        
        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < rowLimit; ++R) 
            for(int C = 0; C < colLimit; ++C) 
                if(keypad[R][C] != -1)
                    result += solveWithMemo(dp, N - 1, R, C);

        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    #define rowLimit 4
    #define colLimit 3

    vector<vector<int>> directions = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
    vector<vector<int>> keypad     = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
public:
    // O(N*4*3*5) & O(N*4*3)
    int getCount(int N) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));

        // Initialize second edge case
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                dp[0][R][C] = 1;

        for(int len = 1; len < N; ++len) {
            for(int R = rowLimit-1; R >= 0; --R) {
                for(int C = colLimit-1; C >= 0; --C) {
                    int count = 0;
                    
                    for(auto& dir : directions) {
                        int newR = R + dir[0];
                        int newC = C + dir[1];
                        if(newR >= 0 && newC >= 0 && newR < rowLimit && newC < colLimit && keypad[newR][newC] != -1) {
                            count += dp[len - 1][newR][newC];
                        }
                    }
                    
                    dp[len][R][C] = count; 
                }
            }
        }

        int result = 0;        

        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < rowLimit; ++R) 
            for(int C = 0; C < colLimit; ++C) 
                if(keypad[R][C] != -1)
                    result += dp[N - 1][R][C];

        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/mobile-numeric-keypad5456/1
