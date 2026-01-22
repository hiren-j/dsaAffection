// Code to find how many distinct phone numbers of length N you can dial ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    const int rowLimit = 4, colLimit = 3;
    const vector<vector<int>> dirs   = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
    const vector<vector<int>> numpad = {{1, 2, 3}, 
                                        {4, 5, 6}, 
                                        {7, 8, 9}, 
                                        {-1, 0, -1}};

    // O(RL*CL * 8^N) & O(N)
    int solveWithoutMemo(int N, int R, int C) {
        if(R < 0 || C < 0 || R >= rowLimit || C >= colLimit || numpad[R][C] == -1)
            return 0;
            
        if(N == 0)
            return 1;
        
        int count = 0;
        
        for(const auto& D : dirs) {
            int newR = R + D[0];
            int newC = C + D[1];
            int nextCount = solveWithoutMemo(N - 1, newR, newC);
            count = (count + nextCount) % MOD;
        }
        
        return count;
    }

    // O(RL*CL + 8*N*RL*CL) & O(N*RL*CL)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int N, int R, int C) {
        if(R < 0 || C < 0 || R >= rowLimit || C >= colLimit || numpad[R][C] == -1)
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
            count = (count + nextCount) % MOD;
        }
        
        return dp[N][R][C] = count;
    }

public:
    // Method to find how many distinct phone numbers of length N can dial, using recursion with memoization - O(N) & O(N)
    int knightDialer(int N) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));
        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(numpad[R][C] != -1)
                    result = (result + solveWithMemo(dp, N - 1, R, C)) % MOD;
        
        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    const int rowLimit = 4, colLimit = 3;
    const vector<vector<int>> dirs   = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, -2}, {2, -1}, {1, 2}, {2, 1}};
    const vector<vector<int>> numpad = {{1, 2, 3}, 
                                        {4, 5, 6}, 
                                        {7, 8, 9}, 
                                        {-1, 0, -1}};

    // O(GN*RL*CL*8) & O(GN*RL*CL) : Where GN = given_N, RL = rowLimit, CL = colLimit
    int solveBy3DTable(int given_N) {
        vector<vector<vector<int>>> dp(given_N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));

        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                dp[0][R][C] = 1;

        for(int N = 1; N <= given_N - 1; ++N) {
            for(int R = rowLimit - 1; R >= 0; --R) {
                for(int C = colLimit - 1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR >= rowLimit || newC >= colLimit || numpad[newR][newC] == -1) 
                                        ? 0 
                                        : dp[N - 1][newR][newC];
                        count = (count + nextCount) % MOD;
                    }

                    dp[N][R][C] = count;       
                }
            }
        }

        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(numpad[R][C] != -1)
                    result = (result + dp[given_N - 1][R][C]) % MOD;
        
        return result;
    }

    // O(GN*RL*CL*8) & O(GN*RL*CL) : Where GN = given_N, RL = rowLimit, CL = colLimit
    int solveBy3DEnhanced(int given_N) {
        vector<vector<vector<int>>> dp(given_N, vector<vector<int>>(rowLimit, vector<int>(colLimit, 1)));

        for(int N = 1; N <= given_N - 1; ++N) {
            for(int R = rowLimit - 1; R >= 0; --R) {
                for(int C = colLimit - 1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR >= rowLimit || newC >= colLimit || numpad[newR][newC] == -1) 
                                        ? 0 
                                        : dp[N - 1][newR][newC];
                        count = (count + nextCount) % MOD;
                    }

                    dp[N][R][C] = count;       
                }
            }
        }

        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(numpad[R][C] != -1)
                    result = (result + dp[given_N - 1][R][C]) % MOD;
        
        return result;
    }

    // O(GN*RL*CL*8) & O(2*RL*CL) : Where GN = given_N, RL = rowLimit, CL = colLimit
    int solveBy2DTable(int given_N) {
        vector<vector<int>> prev(rowLimit, vector<int>(colLimit, 1)); // N - 1th table
        vector<vector<int>> curr(rowLimit, vector<int>(colLimit, 1)); // Nth table

        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                prev[R][C] = 1;

        for(int N = 1; N <= given_N - 1; ++N) {
            for(int R = rowLimit - 1; R >= 0; --R) {
                for(int C = colLimit - 1; C >= 0; --C) {
                    int count = 0;

                    for(const auto& D : dirs) {
                        int newR = R + D[0];
                        int newC = C + D[1];
                        int nextCount = (newR < 0 || newC < 0 || newR >= rowLimit || newC >= colLimit || numpad[newR][newC] == -1) 
                                        ? 0 
                                        : prev[newR][newC];
                        count = (count + nextCount) % MOD;
                    }

                    curr[R][C] = count;       
                }
            }

            swap(prev, curr);
        }

        int result = 0;
        
        for(int R = 0; R < rowLimit; ++R)
            for(int C = 0; C < colLimit; ++C)
                if(numpad[R][C] != -1)
                    result = (result + prev[R][C]) % MOD;
        
        return result;
    }

public:
    int knightDialer(int N) {
        return solveBy2DTable(N);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Combinatorics | Dynamic Programming
Link  : https://leetcode.com/problems/knight-dialer/description/
