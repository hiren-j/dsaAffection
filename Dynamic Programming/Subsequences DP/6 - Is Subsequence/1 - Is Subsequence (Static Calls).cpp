// Code to check whether the string 's' is a subsequence of string 't' or not ~ coded by vHiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n, m;

    // O(2^M) & O(M)
    bool solveWithoutMemo(const string& s, const string& t, int i, int j) {
        if(i == n)
            return true;

        if(j == m)
            return false;

        bool currSkip = solveWithoutMemo(s, t, i, j + 1);
        bool currTake = s[i] == t[j] 
                        ? solveWithoutMemo(s, t, i + 1, j + 1)
                        : false;

        return (currSkip || currTake);
    }

    // O(N*M) & O(N*M)
    bool solveWithMemo(vector<vector<int>>& dp, const string& s, const string& t, int i, int j) {
        if(i == n)
            return true;

        if(j == m)
            return false;

        if(dp[i][j] != -1)
            return dp[i][j];

        bool currSkip = solveWithMemo(dp, s, t, i, j + 1);
        bool currTake = s[i] == t[j] 
                        ? solveWithMemo(dp, s, t, i + 1, j + 1)
                        : false;

        return dp[i][j] = (currSkip || currTake);
    }

public:
    bool isSubsequence(string& s, string& t) {
        n = s.size(), m = t.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s, t, 0, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

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
                bool currTake = s[i] == t[j] 
                                ? dp[i + 1][j + 1]
                                : false;
                dp[i][j] = (currSkip || currTake);  
            }
        }

        return dp[0][0];
    }
    
    // O(N*M) & O(N*M)
    bool solveBy2DEnhanced(const string& s, const string& t) {
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = true;        

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                bool currSkip = dp[i][j + 1];
                bool currTake = s[i] == t[j] 
                                ? dp[i + 1][j + 1]
                                : false;
                dp[i][j] = (currSkip || currTake);  
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(N*M)
    bool solveBy1DTable(const string& s, const string& t) {
        vector<bool> nextRow(m + 1, false); 

        for(int j = 0; j <= m; ++j)
            nextRow[j] = true;        

        for(int i = n - 1; i >= 0; --i) {
            vector<bool> idealRow(m + 1, false); 

            for(int j = m - 1; j >= 0; --j) {
                bool currSkip = idealRow[j + 1];
                bool currTake = s[i] == t[j] 
                                ? nextRow[j + 1]
                                : false;
                idealRow[j] = (currSkip || currTake);  
            }
            
            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }

public:
    bool isSubsequence(string& s, string& t) {
        n = s.size(), m = t.size();
        return solveBy1DTable(s, t);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TwoPointers {
public:
    // O(N+M) & O(1)
    bool isSubsequence(const string& s, const string& t) {
        const int n = s.size(), m = t.size();
        int i = 0, j = 0;
        
        while(i < n && j < m) {
            if(s[i] == t[j]) {
                i++;
            }
            j++;
        }

        return i == n; // If string 's' is present then return true
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String | Dynamic Programming
Link  : https://leetcode.com/problems/is-subsequence/description/
