// Code to find the length of the longest palindromic subsequence of given string ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int i, int j) {
        if(i == j)
            return 1;
        
        if(i > j)
            return 0;
        
        if(s[i] == s[j]) 
            return 2 + solveWithoutMemo(s, i + 1, j - 1);

        int move_j = solveWithoutMemo(s, i, j - 1);
        int move_i = solveWithoutMemo(s, i + 1, j);
        return max(move_j, move_i);
    }

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& dp, const string& s, int i, int j) {
        if(i == j)
            return 1;
        
        if(i > j)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];
        
        if(s[i] == s[j]) 
            return dp[i][j] = 2 + solveWithMemo(dp, s, i + 1, j - 1);
        
        int move_j = solveWithMemo(dp, s, i, j - 1);
        int move_i = solveWithMemo(dp, s, i + 1, j);
        return dp[i][j] = max(move_j, move_i);
    }

public:
    int longestPalindromeSubseq(string& s) {
        const int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solveWithMemo(dp, s, 0, n - 1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*N) & O(N*N)
    int solveBy2DTable(const string& s) {
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for(int i = 0; i < n; ++i)
            dp[i][i] = 1;
            
        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j <= n - 1; ++j) {
                if(i == j || i > j)
                    continue;
                if(s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                }
                else {
                    int move_j = dp[i][j - 1];
                    int move_i = dp[i + 1][j];
                    dp[i][j] = max(move_j, move_i);
                }   
            }
        }

        return dp[0][n - 1];
    }

    // O(N*N) & O(N*N)
    int solveBy2DTEnhanced(const string& s) {
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = i; j <= n - 1; ++j) {
                if(i == j) {
                    dp[i][j] = 1;
                }
                else if(s[i] == s[j]) {
                    dp[i][j] = 2 + dp[i + 1][j - 1];
                }
                else {
                    int move_j = dp[i][j - 1];
                    int move_i = dp[i + 1][j];
                    dp[i][j] = max(move_j, move_i);
                }
            }
        }

        return dp[0][n - 1];
    }
 
    // O(N*N) & O(N)
    int solveBy1DTable(const string& s) {
        vector<int> nextRow(n, 0); // i + 1th row

        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(n, 0); // ith row

            for(int j = i; j <= n - 1; ++j) {
                if(i == j) {
                    currRow[j] = 1;
                }
                else if(s[i] == s[j]) {
                    currRow[j] = 2 + nextRow[j - 1];
                }
                else {
                    int move_j = currRow[j - 1];
                    int move_i = nextRow[j];
                    currRow[j] = max(move_j, move_i);
                }
            }

            swap(nextRow, currRow);
        }

        return nextRow[n - 1];
    }
 
public:
    int longestPalindromeSubseq(string& s) {
        n = s.size();
        return solveBy1DTable(s);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/ 
