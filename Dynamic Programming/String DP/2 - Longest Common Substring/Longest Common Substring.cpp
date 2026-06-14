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
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy2DTable(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); // Fill dp table with 0 so don't have to initialize both base cases seperately
         
        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                else
                    dp[i][j] = 0;
            }
        }
        
        int maxLen = 0;
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < m; ++j)
                maxLen = max(maxLen, dp[i][j]);
        
        return maxLen;
    }
    
    // O(N*M) & O(N*M)
    int solveBy2DEnhanced(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); 
        int maxLen = 0;
         
        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    dp[i][j] = 1 + dp[i + 1][j + 1];
                else
                    dp[i][j] = 0;
                
                maxLen = max(maxLen, dp[i][j]);
            }
        }
    
        return maxLen;
    }

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m + 1, 0); // i + 1th row
        int maxLen = 0;
         
        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(m + 1, 0); // ith row
            
            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j])
                    currRow[j] = 1 + nextRow[j + 1];
                else
                    currRow[j] = 0;
                
                maxLen = max(maxLen, currRow[j]);
            }
            
            swap(nextRow, currRow);
        }
    
        return maxLen;
    }

public:
    int longCommSubstr(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        return solveBy1DTable(s1, s2);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
