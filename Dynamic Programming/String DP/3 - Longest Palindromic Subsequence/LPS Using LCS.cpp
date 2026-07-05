// Code to find the length of the longest palindromic subsequence of the given string ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int findLenOfLCS(const string& s1, const string& s2) {
        const int n = s1.size();
        const int m = s2.size();

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
    int longestPalindromeSubseq(string& s1) {
        string s2 = s1;
        reverse(begin(s2), end(s2));
        return findLenOfLCS(s1, s2);
    }
};
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/1%20-%20Longest%20Common%20Subsequence/Longest%20Common%20Subsequence.cpp
