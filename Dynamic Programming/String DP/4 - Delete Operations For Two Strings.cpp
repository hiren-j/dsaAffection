// Code to find the minimum number of steps required to make word1 and word2 the same. Note that in one step, you can delete exactly one character in either string ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the minimum number of steps required to make word1 and word2 the same :-
    int minDistance(string& word1, string& word2) {
        int n = word1.size(), m = word2.size();
        int lenLCS = longestCommonSubseq(word1, word2, n, m);
        return (n - lenLCS) + (m - lenLCS);
    }

private:
    // Method to find the length of the LCS, using recursion with memoization - O(N*M) & O(N*M)
    int longestCommonSubseq(string& word1, string& word2, int n, int m) {
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, word1, word2, n - 1, m - 1);
    }

    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, string& word1, string& word2, int i, int j) {
        // Edge case: If any of the string gets exhausted then we've found a common subsequence
        if(i < 0 || j < 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        // If the letters of both the string matches then we've got a common subsequence of length 1 
        if(word1[i] == word2[j])
            return 1 + solveWithMemo(memory, word1, word2, i - 1, j - 1);

        // Else when the letters doesn't match then it's possible that the jth letter could be found at the left side of the ith letter and vice versa. So, that's why explore both the possibilities and as we're striving for the LCS hence store the maximum value to the memoization table and then return it
        return memory[i][j] = max(solveWithMemo(memory, word1, word2, i, j - 1), solveWithMemo(memory, word1, word2, i - 1, j));
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the minimum number of steps required to make word1 and word2 the same :-
    int minDistance(string& word1, string& word2) {
        int n = word1.size(), m = word2.size();
        int lenLCS = longestCommonSubseq_V2(word1, word2, n, m);
        return (n - lenLCS) + (m - lenLCS);
    }

private:
    // #1 Method to find the length of the LCS, using 2D tabulation - O(N*M) & O(N*M)
    int longestCommonSubseq_V1(string& word1, string& word2, int n, int m) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else {
                    dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }

        return dp[n][m];
    }

    // #2 Method to find the length of the LCS, using 1D tabulation - O(N*M) & O(M)
    int longestCommonSubseq_V2(string& word1, string& word2, int n, int m) {
        vector<int> prevRow(m + 1, 0), currRow(m + 1, 0);

        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(word1[i - 1] == word2[j - 1]) {
                    currRow[j] = 1 + prevRow[j - 1];
                }
                else {
                    currRow[j] = max(currRow[j - 1], prevRow[j]);
                }
            }
            prevRow = currRow;
        }

        return prevRow[m];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/delete-operation-for-two-strings/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/Longest%20Common%20Subsequence.cpp
