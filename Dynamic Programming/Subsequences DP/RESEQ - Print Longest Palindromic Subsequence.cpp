// Code to find the longest palindromic subsequence of given string ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*M) & O(N*M)
    string printLongestPalindromicSubseq(string& s1) {
        string s2 = s1;
        reverse(begin(s2), end(s2));

        const int n = s1.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Find length of LCS
        for(int i = n - 1; i >= 0; --i) {
            for(int j = n - 1; j >= 0; --j) {
                int currTake  = s1[i] == s2[j] 
                                ? 1 + dp[i + 1][j + 1]
                                : 0;
                int currSkip1 = dp[i + 1][j];
                int currSkip2 = dp[i][j + 1];
                dp[i][j] = max({currTake, currSkip1, currSkip2});
            }
        }
        
        string LPS;
        int i = 0, j = 0;

        while(i < n && j < n) {
            // If both the letters match
            if(s1[i] == s2[j]) {
                LPS.push_back(s1[i]);
                i = i + 1;
                j = j + 1;
            }
            // Else when both the letters don't match
            else {
                if(dp[i + 1][j] > dp[i][j + 1]) {
                    i = i + 1;
                }
                else {
                    j = j + 1;
                }
            }
        }

        return LPS;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/RESEQ%20-%20Longest%20Palindromic%20Subsequence.cpp
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/RESEQ%20-%20Longest%20Common%20Subsequence.cpp
