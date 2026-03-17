// Code to find the minimum number of steps required to make word1 and word2 the same. Note that in one step, you can delete exactly one character in either string ~ coded by Hiren

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

        return max({currSkip1, currSkip2, currTake});
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

        return dp[i][j] = max({currSkip1, currSkip2, currTake});
    }

public:
    int minDistance(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int lenLCS = solveWithMemo(dp, s1, s2, 0, 0);
        return (n - lenLCS) + (m - lenLCS);
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
                dp[i][j] = max({currSkip1, currSkip2, currTake});
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
                dp[i][j] = max({currSkip1, currSkip2, currTake});
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
                idealRow[j] = max({currSkip1, currSkip2, currTake});
            }

            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }

public:
    int minDistance(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        int lenLCS = solveBy1DTable(s1, s2);
        return (n - lenLCS) + (m - lenLCS);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/delete-operation-for-two-strings/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/RESEQ%20-%20Longest%20Common%20Subsequence.cpp
