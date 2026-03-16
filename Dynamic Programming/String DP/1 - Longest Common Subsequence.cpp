// Code to find the length of the longest common subsequence of the given strings ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the length of the longest common subsequence, using recursion with memoization - O(N*M) & O(N*M)
    int longestCommonSubsequence(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, n-1, m-1); 
    }

private:
    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If any of the string gets exhausted then we've found a common subsequence
        if(i < 0 || j < 0)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        // If the letters of both the string matches then we've got a common subsequence of length 1 
        if(s1[i] == s2[j])
            return memory[i][j] = 1 + solveWithMemo(memory, s1, s2, i-1, j-1);
        
        // Else when the letters doesn't match then it's possible that the jth letter could be found at the left side of the ith letter and vice versa. So, that's why explore both the possibilities and as we're striving for the LCS hence store the maximum value to the memoization table and then return it
        return memory[i][j] = max(solveWithMemo(memory, s1, s2, i-1, j), solveWithMemo(memory, s1, s2, i, j-1));
    }

    // O(2^(N+M)) & O(N+M)
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        // Edge case: If any of the string gets exhausted then we've found a common subsequence
        if(i < 0 || j < 0)
            return 0;

        // If the letters of both the string matches then we've got a subsequence of length 1 
        if(s1[i] == s2[j])
            return 1 + solveWithoutMemo(s1, s2, i-1, j-1);
        
        // Else when the letters doesn't match then it's possible that the jth letter could be found at the left side of the ith letter and vice versa. So, that's why explore both the possibilities and as we're striving for the LCS hence return the maximum value
        return max(solveWithoutMemo(s1, s2, i-1, j), solveWithoutMemo(s1, s2, i, j-1));
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

WRITE BOTTOM UP TOO

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/1%20-%20Longest%20Common%20Subsequence.cpp
