// Code to check whether the string 's' is a subsequence of string 't' or not ~ coded by vHiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n, m;

    // O(2^M) & O(M)
    bool solveWithoutMemo(const string& s, const string& t, int i, int start) {
        if(i == n)
            return true;

        if(start == m)
            return false;

        bool flag = false;

        for(int j = start; j < m; ++j) {
            bool currTake = s[i] == t[j] 
                            ? solveWithoutMemo(s, t, i + 1, j + 1)
                            : false;
            flag |= currTake;
            if(flag) break; // Make faster
        }

        return flag;
    }

    // O(M*N*M) & O(N*M)
    bool solveWithMemo(vector<vector<int>>& dp, const string& s, const string& t, int i, int start) {
        if(i == n)
            return true;

        if(start == m)
            return false;

        if(dp[i][start] != -1)
            return dp[i][start];
        
        bool flag = false;

        for(int j = start; j < m; ++j) {
            bool currTake = s[i] == t[j] 
                            ? solveWithMemo(dp, s, t, i + 1, j + 1)
                            : false;
            flag |= currTake;
            if(flag) break; // Make faster
        }

        return dp[i][start] = flag;
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
    
    // O(N*M*M) & O(N*M)
    int solveBy2DTable(const string& s, const string& t) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int i = 0; i <= n; ++i) // Init second base case
            dp[i][m] = false;

        for(int start = 0; start <= m; ++start) // Init first base case
            dp[n][start] = true;

        for(int i = n - 1; i >= 0; --i) {
            for(int start = m - 1; start >= 0; --start) {
                bool flag = false;

                for(int j = start; j < m; ++j) {
                    bool currTake = s[i] == t[j] 
                                    ? dp[i + 1][j + 1]
                                    : false;
                    flag |= currTake;
                    if(flag) break; // Make faster
                }

                dp[i][start] = flag;    
            }
        }

        return dp[0][0];
    }

    // O(N*M*M) & O(N*M)
    int solveBy2DEnhanced(const string& s, const string& t) {
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        for(int start = 0; start <= m; ++start) // Init first base case
            dp[n][start] = true;

        for(int i = n - 1; i >= 0; --i) {
            for(int start = m - 1; start >= 0; --start) {
                bool flag = false;

                for(int j = start; j < m; ++j) {
                    bool currTake = s[i] == t[j] 
                                    ? dp[i + 1][j + 1]
                                    : false;
                    flag |= currTake;
                    if(flag) break; // Make faster
                }

                dp[i][start] = flag;    
            }
        }

        return dp[0][0];
    }

    // O(N*M*M) & O(M)
    bool solveBy1DTable(const string& s, const string& t) {
        vector<bool> nextRow(m + 1, false); // i + 1th row

        for(int j = 0; j <= m; ++j)
            nextRow[j] = true;

        for(int i = n - 1; i >= 0; --i) {
            vector<bool> idealRow(m + 1, false); // ith row

            for(int start = m - 1; start >= 0; --start) {
                bool flag = false;

                for(int j = start; j < m; ++j) {
                    bool currTake = s[i] == t[j]
                                    ? nextRow[j + 1]
                                    : false;
                    flag |= currTake;
                    if(flag) break; // Make faster
                }

                idealRow[start] = flag;
            }

            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }
    // Note: In this problem 1D space optimization of loop version is possible

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
