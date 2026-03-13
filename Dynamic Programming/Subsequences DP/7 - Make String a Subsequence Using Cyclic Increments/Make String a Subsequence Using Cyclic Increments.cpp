// Code to check is s2 can be a subsequence of s1 after performing the specifed operation at most once ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    char nextChar(char ch) {
        return ch == 'z' ? 'a' : ch + 1;
    }

    // O(2^M) & O(M)
    bool solveWithoutMemo(const string& s, const string& t, int i, int j) {
        if(i == n)
            return true;

        if(j == m)
            return false;

        bool currSkip = solveWithoutMemo(s, t, i, j + 1);
        bool currTake = s[i] == t[j] || s[i] == nextChar(t[j])
                        ? solveWithoutMemo(s, t, i + 1, j + 1)
                        : false;

        return (currSkip || currTake);
    }
    // Note: This solution will lead to TLE

    // O(N*M) & O(N*M)
    bool solveWithMemo(vector<vector<int>>& dp, const string& s, const string& t, int i, int j) {
        if(i == n)
            return true;

        if(j == m)
            return false;

        if(dp[i][j] != -1)
            return dp[i][j];

        bool currSkip = solveWithMemo(dp, s, t, i, j + 1);
        bool currTake = s[i] == t[j] || s[i] == nextChar(t[j])
                        ? solveWithMemo(dp, s, t, i + 1, j + 1)
                        : false;

        return dp[i][j] = (currSkip || currTake);
    }
    // Note: This solution will lead to MLE

public:
    bool canMakeSubsequence(string& t, string& s) {
        n = s.size(), m = t.size();
        if(m < n) return false;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s, t, 0, 0); 
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    char nextChar(char ch) {
        return ch == 'z' ? 'a' : ch + 1;
    }

    // O(N*M) & O(N*M)
    bool solveBy2DTable(const string& s, const string& t) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int i = 0; i <= n; ++i)
            dp[i][m] = false;

        for(int j = 0; j <= m; ++j)
            dp[n][j] = true;        

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                bool currSkip = dp[i][j + 1];
                bool currTake = s[i] == t[j] || s[i] == nextChar(t[j])
                                ? dp[i + 1][j + 1]
                                : false;
                dp[i][j] = (currSkip || currTake);  
            }
        }

        return dp[0][0];
    }
    // Note: This solution will lead to MLE
    
    // O(N*M) & O(N*M)
    bool solveBy2DEnhanced(const string& s, const string& t) {
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = true;        

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                bool currSkip = dp[i][j + 1];
                bool currTake = s[i] == t[j] || s[i] == nextChar(t[j])
                                ? dp[i + 1][j + 1]
                                : false;
                dp[i][j] = (currSkip || currTake);  
            }
        }

        return dp[0][0];
    }
    // Note: This solution will lead to MLE

    // O(N*M) & O(M)
    bool solveBy1DTable(const string& s, const string& t) {
        vector<bool> nextRow(m + 1, false); 

        for(int j = 0; j <= m; ++j)
            nextRow[j] = true;        

        for(int i = n - 1; i >= 0; --i) {
            vector<bool> idealRow(m + 1, false); 

            for(int j = m - 1; j >= 0; --j) {
                bool currSkip = idealRow[j + 1];
                bool currTake = s[i] == t[j] || s[i] == nextChar(t[j])
                                ? nextRow[j + 1]
                                : false;
                idealRow[j] = (currSkip || currTake);  
            }
            
            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }
    // Note: This solution will lead to TLE

public:
    bool canMakeSubsequence(string& t, string& s) {
        n = s.size(), m = t.size();
        if(m < n) return false;
        return solveBy1DTable(s, t);
    }
};
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TwoPointers {
public:
    // O(N+M) & O(1)
    bool canMakeSubsequence(string& s1, string& s2) {
        const int n = t.size(), m = s.size();
        int i = 0, j = 0;

        while(i < n && j < m) {
            char nextChar = (t[i] == 'z') ? 'a' : t[i] + 1;
            if(t[i] == s[j] || nextChar == s[j]) {
                j++;
            }
            i++;
        }

        return j == m;   
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String 
Link  : https://leetcode.com/problems/make-string-a-subsequence-using-cyclic-increments/?envType=daily-question&envId=2024-12-04
      : https://github.com/hiren-j/dsaAffection/tree/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/6%20-%20Is%20Subsequence
