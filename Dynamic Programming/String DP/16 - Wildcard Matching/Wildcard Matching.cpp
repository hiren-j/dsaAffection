// Code to implement wildcard pattern matching with support for '?' and '*' where: '?' Matches any single character. '*' Matches any sequence of characters (including the empty sequence). The matching should cover the entire input string (not partial) ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(N*N*M) & O(N*M)
    bool solveWithMemoLoop(vector<vector<int>>& dp, const string& s, const string& p, int i, int j) {
        if(i == n && j == m)
            return true;
        
        if(i == n) {
            while(j < m && p[j] == '*')
                j++;
            return j == m;
        }

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s[i] == p[j] || p[j] == '?')
            return dp[i][j] = solveWithMemoLoop(dp, s, p, i + 1, j + 1);
        
        if(p[j] != '*')
            return dp[i][j] = false;

        if(solveWithMemoLoop(dp, s, p, i, j + 1))
            return dp[i][j] = true;
        
        for(int k = i; k < n; ++k) 
            if(solveWithMemoLoop(dp, s, p, k + 1, j + 1))
                return dp[i][j] = true;
        
        return dp[i][j] = false;
    }

    // O(N*M) & O(N*M)
    bool solveWithMemo(vector<vector<int>>& dp, const string& s, const string& p, int i, int j) {
        if(i == n && j == m)
            return true;
        
        if(i == n) {
            while(j < m && p[j] == '*')
                j++;
            return j == m;
        }

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s[i] == p[j] || p[j] == '?')
            return dp[i][j] = solveWithMemo(dp, s, p, i + 1, j + 1);
        
        if(p[j] != '*')
            return dp[i][j] = false;

        if(solveWithMemo(dp, s, p, i, j + 1))
            return dp[i][j] = true;
        
        return dp[i][j] = solveWithMemo(dp, s, p, i + 1, j + 1) || solveWithMemo(dp, s, p, i + 1, j);
    }

public:
    bool isMatch(string& s, string& p) {
        n = s.size(), m = p.size();
        vector<vector<int>> dp(n, vector<int>(m + 1, -1));
        return solveWithMemo(dp, s, p, 0, 0);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    // O(N*M) & O(N*M)
    bool solveBy2DTable(const string& s, const string& p) {
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[n][m] = true;    

        for(int j = 0; j <= m; ++j) {
            int tmp = j;
            while(tmp < m && p[tmp] == '*')
                tmp++;
            dp[n][j] = tmp == m;
        }

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                if(s[i] == p[j] || p[j] == '?')
                    dp[i][j] = dp[i + 1][j + 1];
                else if(p[j] != '*')
                    dp[i][j] = false;
                else if(dp[i][j + 1])
                    dp[i][j] = true;
                else 
                    dp[i][j] = dp[i + 1][j + 1] || dp[i + 1][j];   
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(M)
    bool solveBy1DTable(const string& s, const string& p) {
        vector<bool> nextRow(m + 1, false);
        nextRow[m] = true;    

        for(int j = 0; j <= m; ++j) {
            int tmp = j;
            while(tmp < m && p[tmp] == '*')
                tmp++;
            nextRow[j] = tmp == m;
        }

        for(int i = n - 1; i >= 0; --i) {
            vector<bool> currRow(m + 1, false);
            
            for(int j = m - 1; j >= 0; --j) {
                if(s[i] == p[j] || p[j] == '?')
                    currRow[j] = nextRow[j + 1];
                else if(p[j] != '*')
                    currRow[j] = false;
                else if(currRow[j + 1])
                    currRow[j] = true;
                else 
                    currRow[j] = nextRow[j + 1] || nextRow[j];   
            }

            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

public:
    bool isMatch(string& s, string& p) {
        n = s.size(), m = p.size();
        return solveBy1DTable(s, p);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming | Greedy | Recursion
Link  : https://leetcode.com/problems/wildcard-matching/description/
