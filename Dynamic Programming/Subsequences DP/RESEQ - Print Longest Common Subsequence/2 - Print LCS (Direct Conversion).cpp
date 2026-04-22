// Code to find the longest common subsequence of s1 and s2 ~ coded by vHiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*M) & O(N*M)
    string findLCS(int n, int m, string& s1, string& s2){
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Find length of LCS
        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                int currSkip1 = dp[i + 1][j];
                int currSkip2 = dp[i][j + 1];
                int currTake  = s1[i] == s2[j] 
                                ? 1 + dp[i + 1][j + 1]
                                : 0;
                dp[i][j] = max({currSkip1, currSkip2, currTake});
            }
        }

        int i = 0, j = 0;
        string LCS;

        while(i <= n - 1 && j <= m - 1) {
            int currSkip1 = dp[i + 1][j];
            int currSkip2 = dp[i][j + 1];
            int currTake  = s1[i] == s2[j] 
                            ? 1 + dp[i + 1][j + 1]
                            : 0;
            if(currSkip1 >= max(currSkip2, currTake)) {
                i = i + 1;
            }
            else if(currSkip2 >= max(currSkip1, currTake)) {
                j = j + 1;
            }
            else {
                if(s1[i] == s2[j]) {
                    LCS.push_back(s1[i]);
                    j = j + 1;
                }
                i = i + 1;
            }
        }

        return LCS;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383?leftPanelTabValue=PROBLEM
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Common%20Subsequence.cpp
        https://cses.fi/problemset/task/3403
