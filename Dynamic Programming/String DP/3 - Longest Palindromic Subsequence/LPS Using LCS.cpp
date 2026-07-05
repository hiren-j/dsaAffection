// Code to find the length of the longest palindromic subsequence of the given string ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

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

public:
    // O(N*M) & O(N*M)
    int longestCommonSubsequence(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        string s2 = s1;
        reverse(begin(s2), end(s2));
        int lenLCS = solveBy1DTable(s1, s2);
        return lenLCS;
    }
};
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/1%20-%20Longest%20Common%20Subsequence/Longest%20Common%20Subsequence.cpp
