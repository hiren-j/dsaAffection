// Code to find the minimum number of steps to make string "s" palindrome ~ coded by vHiren 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];

        int currSkip1 = solveWithMemo(dp, s1, s2, i + 1, j);
        int currSkip2 = solveWithMemo(dp, s1, s2, i, j + 1);
        int currTake  = s1[i] == s2[j] 
                        ? 1 + solveWithMemo(dp, s1, s2, i + 1, j + 1)
                        : 0;

        return dp[i][j] = max({currSkip1, currSkip2, currTake});
    }

    int longestPalindromeSubseq(string& s1) {
        string s2 = s1;
        reverse(begin(s2), end(s2));
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s1, s2, 0, 0); // Find length of LCS
    }
    
public:
    int minInsertions(string& s) {
        return s.size() - longestPalindromeSubseq(s);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m + 1, 0); // i + 1th row

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(m + 1, 0); // ith row

            for(int j = m - 1; j >= 0; --j) {
                int currSkip1 = nextRow[j];
                int currSkip2 = idealRow[j + 1];
                int currTake  = s1[i] == s2[j] 
                                ? 1 + nextRow[j + 1]
                                : 0;
                idealRow[j] = max({currSkip1, currSkip2, currTake});
            }

            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }

    int longestPalindromeSubseq(string& s1) {
        string s2 = s1;
        reverse(begin(s2), end(s2));
        n = s1.size(), m = s2.size();
        return solveBy1DTable(s1, s2); // Find length of LCS
    }
    
public:
    int minInsertions(string& s) {
        return s.size() - longestPalindromeSubseq(s);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/RESEQ%20-%20Longest%20Palindromic%20Subsequence.cpp
