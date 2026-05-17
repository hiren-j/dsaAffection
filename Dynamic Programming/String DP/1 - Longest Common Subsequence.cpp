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

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/1%20-%20Longest%20Common%20Subsequence.cpp
