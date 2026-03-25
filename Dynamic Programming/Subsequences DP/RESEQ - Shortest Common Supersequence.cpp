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
            // If both letters match, then take any of the letter in move in both strings
            if(s1[i] == s2[j]) {
                answer.push_back(s1[i]);
                i++;
                j++;
            }
            // Else when both letters don't match
            else {
                // If it's maximum then move in string1. So before moving take the ith letter
                if(dp[i + 1][j] > dp[i][j + 1]) {
                    answer.push_back(s1[i]);
                    i++;
                }   
                // Else if it's maximum then move in string2. So before moving take the jth letter
                else {
                    answer.push_back(s2[j]);
                    j++;
                }
            }
        }

        // Store the remaining letters of string1 to answer
        while(i < n) {
            answer.push_back(s1[i]);
            i++;
        }

        // Store the remaining letters of string2 to answer
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
