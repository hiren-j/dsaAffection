// Code to count the total number of palindromic substrings of the given string ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    bool isPalindrome(vector<vector<int>>& dp, string& s, int start, int end) {
        // Edge case: If no letters exists then string is palindrome
        if(start >= end)
            return true;
        
        // Edge case: If both letters don't match then string can't be palindrome
        if(s[start] != s[end])
            return false;

        if(dp[start][end] != -1)
            return dp[start][end];

        return dp[start][end] = isPalindrome(dp, s, start + 1, end - 1);
    }

public:
    // Method to count the number of palindromic substrings, using recursion with memoization - O(N^2) & O(N^2)
    int countSubstrings(string& s) {
        int n = s.size();
        int count = 0;

        vector<vector<int>> dp(n, vector<int>(n, -1));

        for(int i = 0; i < n; ++i) // Check all the substrings and count the palindromes
            for(int j = i; j < n; ++j)
                if(isPalindrome(dp, s, i, j))
                    count++;

        return count;
    }
};
// Note: Without Memoization DP The Time Complexity Is O(N^3).

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpBrute {
public:
    // Method to count the number of palindromic substrings, using 2D tabulation - O(N^2) & O(N^2)
    int countSubstrings(string& s) {
        int n = s.size();
        int count = 0;

        vector<vector<bool>> dp(n + 1, vector<bool>(n, false));

        for(int start = n-1; start >= 0; --start) // Initialize the first edge case
            for(int end = 0; end <= n-1; ++end)
                if(start >= end)
                    dp[start][end] = true;

        for(int start = n-1; start >= 0; --start) // Fill the rest of table
            for(int end = 0; end <= n-1; ++end)
                if(start < end && s[start] == s[end])
                    dp[start][end] = (end - 1 >= 0) ? dp[start + 1][end - 1] : false;

        for(int i = 0; i < n; ++i) // Check all the substrings and count the palindromes
            for(int j = i; j < n; ++j)
                if(dp[i][j])
                    count++;

        return count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpEnhanced {
public:
    // Method to count the number of palindromic substrings, using 2D tabulation - O(N^2) & O(N^2)
    int countSubstrings(string& s) {
        int n = s.size();
        int count = 0;

        vector<vector<bool>> dp(n + 1, vector<bool>(n, false));

        for(int start = n-1; start >= 0; --start) // Initiailze the first edge case
            for(int end = 0; end <= n-1; ++end)
                if(start >= end)
                    dp[start][end] = true;

        for(int start = n-1; start >= 0; --start) { // Fill rest of the table and count the palindromes
            for(int end = 0; end <= n-1; ++end) {
                if(start < end && s[start] == s[end])
                    dp[start][end] = (end - 1 >= 0) ? dp[start + 1][end - 1] : false;
                if(end >= start && dp[start][end])
                    count++;
            }
        }

        return count;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String | Dynamic Programming
Link  : https://leetcode.com/problems/palindromic-substrings/description/
