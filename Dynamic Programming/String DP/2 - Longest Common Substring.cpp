// Code to find the length of the longest common substring of given strings ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;
    
    // O(N+M) & O(min(N,M))
    int solveWithoutMemo(const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;
        
        if(s1[i] == s2[j])
            return 1 + solveWithoutMemo(s1, s2, i + 1, j + 1);
            
        return 0;
    }
    // This function will be called N*M times, look below from the loop, hence overall Time considering this O(N*M * (N+M))
    
    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;
        
        if(dp[i][j] != -1)
            return dp[i][j];
        
        if(s1[i] == s2[j])
            return dp[i][j] = 1 + solveWithMemo(dp, s1, s2, i + 1, j + 1);
            
        return dp[i][j] = 0;
    }
    // This function will be called N*M times, look below from the loop, hence overall Time considering this O(N*M + N*M) = O(2*N*M) = O(N*M)
    
public:
    int longCommSubstr(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int maxLen = 0;
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                maxLen = max(maxLen, solveWithMemo(dp, s1, s2, i, j));
        
        return maxLen;
    }
};
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the length of the longest common substring, using 2D tabulation - O(N*M) & O(N*M)
    int longestCommonSubstring_V1(string& s1, string& s2, int n, int m) {
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));
        
        int maxLength = 0;
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                // If both the letters match
                if(s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                // Else when both the letters don't match
                else {
                    dp[i][j] = 0;
                }
                maxLength = max(maxLength, dp[i][j]);
            }
        }
        
        return maxLength;
    }

    // #2 Method to find the length of the longest common substring, using 1D tabulation - O(N*M) & O(M)
    int longestCommonSubstring_V2(string& s1, string& s2, int n, int m) {
        // 1D DP tables
        vector<int> prevRow(m + 1), currRow(m + 1);
        
        int maxLength = 0;
        
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                // If both the letters match
                if(s1[i - 1] == s2[j - 1]) {
                    currRow[j] = 1 + prevRow[j - 1];
                }
                // Else when both the letters don't match
                else {
                    currRow[j] = 0;
                }
                maxLength = max(maxLength, currRow[j]);
            }
            prevRow = currRow;
        }
        
        return maxLength;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
