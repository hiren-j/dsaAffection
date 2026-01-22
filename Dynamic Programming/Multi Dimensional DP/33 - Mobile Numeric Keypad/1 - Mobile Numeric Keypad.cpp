// Code to find the number of possible unique sequences of len n that you can create by pressing buttons (You can start from any digit) ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {    
    const int rowLimit = 4, colLimit = 3;
    const vector<vector<int>> dirs   = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const vector<vector<int>> keypad = {{1, 2, 3}, 
                                        {4, 5, 6}, 
                                        {7, 8, 9}, 
                                        {-1, 0, -1}};

    // O(RL*CL * 5^N) & O(N) : Where RL = rowLimit, CL = colLimit
    int solveWithoutMemo(int N, int R, int C) {
        if(R < 0 || C < 0 || R == rowLimit || C == colLimit || keypad[R][C] == -1)
            return 0;
            
        if(N == 0)
            return 1;
        
        int count = 0;
        
        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];
            int nextCount = solveWithoutMemo(N - 1, newR, newC);
            count += nextCount;
        }
        
        return count;
    }
    
    // O(RL*CL + 5*N*RL*CL) & O(N*RL*CL + N) : Where RL = rowLimit, CL = colLimit
    int solveWithMemo(vector<vector<vector<int>>>& dp, int N, int R, int C) {
        if(R < 0 || C < 0 || R == rowLimit || C == colLimit || keypad[R][C] == -1)
            return 0;
            
        if(N == 0)
            return 1;
            
        if(dp[N][R][C] != -1)
            return dp[N][R][C];
        
        int count = 0;
        
        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];
            int nextCount = solveWithMemo(dp, N - 1, newR, newC);
            count += nextCount;
        }
        
        return dp[N][R][C] = count;
    }
    
public:
    // Method to count unique phone numbers of length N can dial, using recursion with memoization - O(N) & O(N)
    int countUniqueSeqsOfLen(int N) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));
        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(keypad[R][C] != -1)
                    result += solveWithMemo(dp, N - 1, R, C);
        
        return result;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int rowLimit = 4, colLimit = 3;
    const vector<vector<int>> dirs   = {{0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    const vector<vector<int>> keypad = {{1, 2, 3}, 
                                        {4, 5, 6}, 
                                        {7, 8, 9}, 
                                        {-1, 0, -1}};
    
    // O(GN*RL*CL*5) & O(GN*RL*CL) : Where GN = given_N, Where RL = rowLimit, CL = colLimit
    int solveBy3DTable(int given_N) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(rowLimit + 1, vector<int>(colLimit + 1, -1)));
    
        // N == 0
        for(int R = 0; R <= rowLimit; ++R)
            for(int C = 0; C <= colLimit; ++C)
                dp[0][R][C] = 1;
                
        for(int N = 1; N <= given_N - 1; ++N) {
            for(int R = rowLimit - 1; R >= 0; --R) {
                for(int C = colLimit - 1; C >= 0; --C) {
                    int count = 0;
                    
                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR == rowLimit || newC == colLimit || keypad[newR][newC] == -1) 
                                        ? 0 
                                        : dp[N - 1][newR][newC];
                        count += nextCount;
                    }
                    
                    dp[N][R][C] = count;
                }
            }
        }
        
        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(keypad[R][C] != -1)
                    result += dp[given_N - 1][R][C];
        
        return result;
    }
    
    // O(GN*RL*CL*5) & O(GN*RL*CL) : Where GN = given_N, Where RL = rowLimit, CL = colLimit
    int solveBy3DEnhanced(int given_N) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(rowLimit + 1, vector<int>(colLimit + 1, 1)));
                
        for(int N = 1; N <= given_N - 1; ++N) {
            for(int R = rowLimit - 1; R >= 0; --R) {
                for(int C = colLimit - 1; C >= 0; --C) {
                    int count = 0;
                    
                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR == rowLimit || newC == colLimit || keypad[newR][newC] == -1) 
                                        ? 0 
                                        : dp[N - 1][newR][newC];
                        count += nextCount;
                    }
                    
                    dp[N][R][C] = count;
                }
            }
        }
        
        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(keypad[R][C] != -1)
                    result += dp[given_N - 1][R][C];
        
        return result;
    }
    
    // O(GN*RL*CL*5) & O(2*RL*CL) : Where GN = given_N, Where RL = rowLimit, CL = colLimit
    int solveBy2DTable(int given_N) {
        vector<vector<int>> prev(rowLimit + 1, vector<int>(colLimit + 1, 1));  // N - 1th table
        vector<vector<int>> curr(rowLimit + 1, vector<int>(colLimit + 1, -1)); // Nth table
    
        for(int N = 1; N <= given_N - 1; ++N) {
            for(int R = rowLimit - 1; R >= 0; --R) {
                for(int C = colLimit - 1; C >= 0; --C) {
                    int count = 0;
                    
                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR == rowLimit || newC == colLimit || keypad[newR][newC] == -1) 
                                        ? 0 
                                        : prev[newR][newC];
                        count += nextCount;
                    }
                    
                    curr[R][C] = count;
                }
            }
            swap(prev, curr);
        }
        
        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(keypad[R][C] != -1)
                    result += prev[R][C];
        
        return result;
    }
    
public:
    int countUniqueSeqsOfLen(int N) {
        return solveBy2DTable(N);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/mobile-numeric-keypad5456/1
