// Code to find the length of the longest common subsequence of the strings s1 and s2 ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(3^(N+M)) & O(N+M)
    int solveWithoutMemo(const string& s1, const string& s2, int start, int j) {
        if(start == n || j == m)
            return 0;

        int maxLen = 0;

        for(int i = start; i < n; ++i) {
            int currSkip2 = solveWithoutMemo(s1, s2, i, j + 1);
            int currTake  = s1[i] == s2[j] 
                            ? 1 + solveWithoutMemo(s1, s2, i + 1, j + 1)
                            : 0;
            maxLen = max({maxLen, currSkip2, currTake});
        }

        return maxLen;
    }

    // O(N*N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int start, int j) {
        if(start == n || j == m)
            return 0;

        if(dp[start][j] != -1)
            return dp[start][j];

        int maxLen = 0;

        for(int i = start; i < n; ++i) {
            int currSkip2 = solveWithMemo(dp, s1, s2, i, j + 1);
            int currTake  = s1[i] == s2[j] 
                            ? 1 + solveWithMemo(dp, s1, s2, i + 1, j + 1)
                            : 0;
            maxLen = max({maxLen, currSkip2, currTake});
        }

        return dp[start][j] = maxLen;
    }

public:
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return solveWithMemo(dp, s1, s2, 0, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    // O(N*M*N) & O(N*M)
    int solveBy2DTable(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = 0;

        for(int i = 0; i <= n; ++i)
            dp[i][m] = 0;

        for(int start = n - 1; start >= 0; --start) {
            for(int j = m - 1; j >= 0; --j) {
                int maxLen = 0;

                for(int i = start; i < n; ++i) {
                    int currSkip2 = dp[i][j + 1];
                    int currTake  = s1[i] == s2[j] 
                                    ? 1 + dp[i + 1][j + 1]
                                    : 0;
                    maxLen = max({maxLen, currSkip2, currTake});
                }

                dp[start][j] = maxLen;
            }
        }

        return dp[0][0];
    }

    // O(N*M*N) & O(N*M)
    int solveBy2DEnhanced(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int start = n - 1; start >= 0; --start) {
            for(int j = m - 1; j >= 0; --j) {
                int maxLen = 0;

                for(int i = start; i < n; ++i) {
                    int currSkip2 = dp[i][j + 1];
                    int currTake  = s1[i] == s2[j] 
                                    ? 1 + dp[i + 1][j + 1]
                                    : 0;
                    maxLen = max({maxLen, currSkip2, currTake});
                }

                dp[start][j] = maxLen;
            }
        }

        return dp[0][0];
    }

public:
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        return solveBy2DEnhanced(s1, s2);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/longest-common-subsequence/
