// Code to find the length of the longest common subsequence of the given strings ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(2^(N+M)) & O(N+M)
    int solveWithoutMemo(const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;

        if(s1[i] == s2[j])
            return 1 + solveWithoutMemo(s1, s2, i+1, j+1);
        
        return max(solveWithoutMemo(s1, s2, i+1, j), solveWithoutMemo(s1, s2, i, j+1));
    }

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s1[i] == s2[j])
            return dp[i][j] = 1 + solveWithMemo(dp, s1, s2, i+1, j+1);
        
        return dp[i][j] = max(solveWithMemo(dp, s1, s2, i+1, j), solveWithMemo(dp, s1, s2, i, j+1));
    }

public:
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s1, s2, 0, 0); 
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy2DTable(const string& s1, const string& s2) {
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = 0;
        for(int i = 0; i <= n; ++i)
            dp[i][m] = 0;

        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    dp[i][j] = 1 + dp[i+1][j+1];
                else
                    dp[i][j] = max(dp[i+1][j], dp[i][j+1]);   
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(N*M)
    int solveBy2DEnhanced(const string& s1, const string& s2) {
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    dp[i][j] = 1 + dp[i+1][j+1];
                else
                    dp[i][j] = max(dp[i+1][j], dp[i][j+1]);   
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m+1, 0), currRow(m+1, 0);

        for(int i = n-1; i >= 0; --i) {
            for(int j = m-1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    currRow[j] = 1 + nextRow[j+1];
                else
                    currRow[j] = max(nextRow[j], currRow[j+1]);   
            }
            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

public:
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        return solveBy1DTable(s1, s2);
    }
};
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/1%20-%20Longest%20Common%20Subsequence.cpp
