// Code to count the total number of subsequences in string "t" which are equal to string "s" ~ coded by vHiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(2^M) & O(M)
    int solveWithoutMemo(const string& s, const string& t, int i, int j) {
        if(i == n)
            return 1;

        if(j == m)
            return 0;

        int currSkip = solveWithoutMemo(s, t, i, j + 1);
        int currTake = s[i] == t[j] 
                        ? solveWithoutMemo(s, t, i + 1, j + 1)
                        : 0;

        return (currSkip + currTake);
    }

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s, const string& t, int i, int j) {
        if(i == n)
            return 1;

        if(j == m)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        int currSkip = solveWithMemo(dp, s, t, i, j + 1);
        int currTake = s[i] == t[j] 
                        ? solveWithMemo(dp, s, t, i + 1, j + 1)
                        : 0;

        return dp[i][j] = (currSkip + currTake);
    }


public:
    int numDistinct(string& t, string& s) {
        n = s.size(), m = t.size();
        if(m < n) return 0;
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s, t, 0, 0); 
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy2DTable(const string& s, const string& t) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int i = 0; i <= n; ++i)
            dp[i][m] = 0;

        for(int j = 0; j <= m; ++j)
            dp[n][j] = 1;        

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                unsigned int currSkip = dp[i][j + 1];
                unsigned int currTake = s[i] == t[j] 
                                ? dp[i + 1][j + 1]
                                : 0;
                dp[i][j] = (currSkip + currTake);  
            }
        }

        return dp[0][0];
    }
    
    // O(N*M) & O(N*M)
    int solveBy2DEnhanced(const string& s, const string& t) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = 1;        

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                unsigned int currSkip = dp[i][j + 1];
                unsigned int currTake = s[i] == t[j] 
                                ? dp[i + 1][j + 1]
                                : 0;
                dp[i][j] = (currSkip + currTake);  
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s, const string& t) {
        vector<int> nextRow(m + 1, 0); 

        for(int j = 0; j <= m; ++j)
            nextRow[j] = 1;        

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(m + 1, 0); 

            for(int j = m - 1; j >= 0; --j) {
                unsigned int currSkip = idealRow[j + 1];
                unsigned int currTake = s[i] == t[j] 
                                ? nextRow[j + 1]
                                : 0;
                idealRow[j] = (currSkip + currTake);  
            }
            
            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }

public:
    int numDistinct(string& t, string& s) {
        n = s.size(), m = t.size();
        if(m < n) return 0;
        return solveBy1DTable(s, t);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/discuss/interview-question/433901/Google-or-Phone-or-Distinct-subsequences
        https://leetcode.com/problems/distinct-subsequences/description/
        https://github.com/hiren-j/dsaAffection/tree/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/6%20-%20Is%20Subsequence
