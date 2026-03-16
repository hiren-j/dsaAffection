// Code to find the length of the longest common subsequence of the strings s1 and s2 ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(3^(N+M)) & O(N+M)
    int solveWithoutMemo(const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;

        int currSkip1 = solveWithoutMemo(s1, s2, i + 1, j);
        int currSkip2 = solveWithoutMemo(s1, s2, i, j + 1);
        int currTake  = s1[i] == s2[j] 
                        ? 1 + solveWithoutMemo(s1, s2, i + 1, j + 1)
                        : 0;

        return max({currTake, currSkip1, currSkip2});
    }
    
    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        int currSkip1 = solveWithMemo(dp, s1, s2, i + 1, j);
        int currSkip2 = solveWithMemo(dp, s1, s2, i, j + 1);
        int currTake  = s1[i] == s2[j] 
                        ? 1 + solveWithMemo(dp, s1, s2, i + 1, j + 1)
                        : 0;

        return dp[i][j] = max({currTake, currSkip1, currSkip2});
    }

public:
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s1, s2, 0, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy2DTable(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = 0;

        for(int i = 0; i <= n; ++i)
            dp[i][m] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                int currSkip1 = dp[i + 1][j];
                int currSkip2 = dp[i][j + 1];
                int currTake  = s1[i] == s2[j] 
                                ? 1 + dp[i + 1][j + 1]
                                : 0;
                dp[i][j] = max({currTake, currSkip1, currSkip2});
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(N*M)
    int solveBy2DEnhanced(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                int currSkip1 = dp[i + 1][j];
                int currSkip2 = dp[i][j + 1];
                int currTake  = s1[i] == s2[j] 
                                ? 1 + dp[i + 1][j + 1]
                                : 0;
                dp[i][j] = max({currTake, currSkip1, currSkip2});
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m + 1, 0); // i + 1th row

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(m + 1, 0); // ith row

            for(int j = m - 1; j >= 0; --j) {
                int currSkip1 = nextRow[j];
                int currSkip2 = idealRow[j + 1];
                int currTake  = s1[i] == s2[j] 
                                ? 1 + nextRow[j + 1]
                                : 0;
                idealRow[j] = max({currTake, currSkip1, currSkip2});
            }

            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }

public:
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        return solveBy1DTable(s1, s2);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/longest-common-subsequence/
