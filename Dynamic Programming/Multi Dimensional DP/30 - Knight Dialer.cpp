// Code to find how many distinct phone numbers of length N you can dial ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int rowLimit = 4, colLimit = 3;
    const int MOD = 1e9 + 7;

    vector<vector<int>> directions = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};
    vector<vector<int>> phonePad   = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < rowLimit && C < colLimit && phonePad[R][C] != -1; 
    }
    
    // O(10 * 8^N) & O(N)
    int solveWithoutMemo(int N, int R, int C) {
        // Edge case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0) 
            return 1; 

        int count = 0;

        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(isValid(newR, newC)) {
                count = (count + solveWithoutMemo(N - 1, newR, newC)) % MOD;
            }
        }

        return count;
    }
    
    // O(10 + 8*N*4*3) & O(N*4*3 + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int N, int R, int C) {
        // Edge case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0) 
            return 1; 

        if(dp[N][R][C] != -1)
            return dp[N][R][C];

        int count = 0;

        for(auto& dir : directions) {
            int newR = R + dir[0];
            int newC = C + dir[1];
            if(isValid(newR, newC)) {
                count = (count + solveWithMemo(dp, N - 1, newR, newC)) % MOD;
            }
        }

        return dp[N][R][C] = count;
    }

public:
    // Method to find how many distinct phone numbers of length N you can dial, using recursion with memoization - O(N) & O(N)
    int knightDialer(int N) {
        int result = 0;
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));

        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < rowLimit; ++R) 
            for(int C = 0; C < colLimit; ++C) 
                if(phonePad[R][C] != -1) 
                    result = (result + solveWithMemo(dp, N - 1, R, C)) % MOD;

        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int rowLimit = 4, colLimit = 3;
    const int MOD = 1e9 + 7;

    vector<vector<int>> directions = {{-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}};
    vector<vector<int>> phonePad   = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
    bool isValid(int R, int C) {
        return R >= 0 && C >= 0 && R < rowLimit && C < colLimit && phonePad[R][C] != -1; 
    }
    
public:
    // O(N*4*3*8) & O(N*4*3)
    int knightDialer(int N) {
        vector<vector<vector<int>>> dp(N, vector<vector<int>>(rowLimit, vector<int>(colLimit, -1)));

        for(int R = 0; R < rowLimit; ++R) // Init edge case
            for(int C = 0; C < colLimit; ++C)
                dp[0][R][C] = 1;

        for(int len = 1; len < N; ++len) {
            for(int R = rowLimit-1; R >= 0; --R) {
                for(int C = colLimit-1; C >= 0; --C) {
                    int count = 0;

                    for(auto& dir : directions) {
                        int newR = R + dir[0];
                        int newC = C + dir[1];
                        if(isValid(newR, newC)) {
                            count = (count + dp[len - 1][newR][newC]) % MOD;
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
                if(phonePad[R][C] != -1)
                    result = (result + dp[N - 1][R][C]) % MOD;

        return result;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/knight-dialer/description/
