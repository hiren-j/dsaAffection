// Code to find the shortest string that has both str1 and str2 as subsequences. If there are multiple valid strings, return any of them ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*M) & O(N*M)
    string shortestCommonSupersequence(string& s1, string& s2) {
        const int n = s1.size(), m = s2.size();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Find length of LCS
        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                int currTake  = s1[i] == s2[j] 
                                ? 1 + dp[i + 1][j + 1]
                                : 0;
                int currSkip1 = dp[i + 1][j];
                int currSkip2 = dp[i][j + 1];
                dp[i][j] = max({currTake, currSkip1, currSkip2});
            }
        }

        string answer;

        int i = 0, j = 0;

        while(i < n && j < m) {
            // If both the letters match
            if(s1[i] == s2[j]) {
                // Take only 1 letter
                answer.push_back(s1[i]);
                i++;
                j++;
            }
            // Else when both the letters don't match
            else {
                // If it's maximum then string1 will shrink by size 1. So before shrink take that dropped letter of string1
                if(dp[i + 1][j] > dp[i][j + 1]) {
                    answer.push_back(s1[i]);
                    i++;
                }   
                // Else if it's maximum then string2 will shrink by size 1. So before shrink take that dropped letter of string2
                else {
                    answer.push_back(s2[j]);
                    j++;
                }
            }
        }

        // Store the remaining letters of string1 to the answer
        while(i < n) {
            answer.push_back(s1[i]);
            i++;
        }

        // Store the remaining letters of string2 to the answer
        while(j < m) {
            answer.push_back(s2[j]);
            j++;
        }

        return answer;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/shortest-common-supersequence/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Common%20Subsequence.cpp
