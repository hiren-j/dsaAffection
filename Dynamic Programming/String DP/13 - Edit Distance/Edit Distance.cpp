// Code to find the minimum number of operations required to convert word1 to word2 (You have the following three operations permitted on a word: Insert a character, Delete a character, Replace a character) ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(3^(N+M)) & O(N+M)
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        if(i == n)
            return m - j;

        if(j == m)
            return n - i;

        if(s1[i] == s2[j])
            return solveWithoutMemo(s1, s2, i + 1, j + 1);

        int insertOp  = solveWithoutMemo(s1, s2, i, j + 1);  
        int deleteOp  = solveWithoutMemo(s1, s2, i + 1, j);   
        int replaceOp = solveWithoutMemo(s1, s2, i + 1, j + 1); 

        return 1 + min({insertOp, deleteOp, replaceOp});
    }

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, string& s1, string& s2, int i, int j) {
        if(i == n)
            return m - j;

        if(j == m)
            return n - i;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s1[i] == s2[j])
            return dp[i][j] = solveWithMemo(dp, s1, s2, i + 1, j + 1);

        int insertOp  = solveWithMemo(dp, s1, s2, i, j + 1);  
        int deleteOp  = solveWithMemo(dp, s1, s2, i + 1, j);   
        int replaceOp = solveWithMemo(dp, s1, s2, i + 1, j + 1); 

        return dp[i][j] = 1 + min({insertOp, deleteOp, replaceOp});
    }

public:
    int minDistance(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s1, s2, 0, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class BottomUp {
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy2DTable(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int j = 0; j <= m; ++j)
            dp[n][j] = m - j;

        for(int i = 0; i <= n; ++i)
            dp[i][m] = n - i;

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                }
                else {
                    int insertOp  = dp[i][j + 1];  
                    int deleteOp  = dp[i + 1][j];   
                    int replaceOp = dp[i + 1][j + 1]; 
                    dp[i][j] = 1 + min({insertOp, deleteOp, replaceOp});     
                }
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m + 1, -1), currRow(m + 1, -1); 

        for(int j = 0; j <= m; ++j)
            nextRow[j] = m - j;
            nextRow[m] = n - n;

        for(int i = n - 1; i >= 0; --i) {
            currRow[m] = n - i;

            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j]) {
                    currRow[j] = nextRow[j + 1];
                }
                else {
                    int insertOp  = currRow[j + 1];  
                    int deleteOp  = nextRow[j];   
                    int replaceOp = nextRow[j + 1]; 
                    currRow[j] = 1 + min({insertOp, deleteOp, replaceOp});     
                }
            }
            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

public:
    int minDistance(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        return solveBy1DTable(s1, s2);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/edit-distance/description/
        https://cses.fi/problemset/task/1639 
