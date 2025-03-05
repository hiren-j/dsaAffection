// Code to find the longest palindromic substring of a given string ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

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
    // Method to find the longset palindromic substring, using recursion with memoization - O(N^2) & O(N^2)
    string longestPalindrome(string& s) {
        int n = s.size();
        
        vector<vector<int>> dp(n, vector<int>(n, -1));
        
        int maxLength = 0;
        int start, end;
        
        // Find length of the longest palindromic substring
        for(int i = 0; i < n; ++i) 
            for(int j = i; j < n; ++j)
                if(isPalindrome(dp, s, i, j) && j-i+1 > maxLength) 
                    maxLength = j-i+1, start = i, end = j;
        
        // Get the longest palindromic substring using its start and end index and then return it
        return s.substr(start, end-start+1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpBrute {
public:
    // Method to find the longest palindromic substring, using 2D tabulation - O(N^2) & O(N^2)
    string longestPalindrome(string& s) {
        int n = s.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(n, false));

        // Initialize the first edge case
        for(int start = n-1; start >= 0; --start) 
            for(int end = 0; end < n; ++end)
                if(start >= end)
                    dp[start][end] = true;

        // Fill rest of the table
        for(int start = n-1; start >= 0; --start) 
            for(int end = 0; end <= n-1; ++end) 
                if(start < end && s[start] == s[end])
                    dp[start][end] = (end - 1 >= 0) ? dp[start + 1][end - 1] : false;

        int maxLength = 0;
        int start, end;

        // Find length of the longest palindromic substring
        for(int i = 0; i < n; ++i) 
            for(int j = i; j < n; ++j)
                if(dp[i][j] && j-i+1 > maxLength) 
                    maxLength = j-i+1, start = i, end = j;

        // Get the longest palindromic substring using its start and end index and then return it
        return s.substr(start, end-start+1); 
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpEnhanced {
public:
    // Method to find the longest palindromic substring, using 2D tabulation - O(N^2) & O(N^2)
    string longestPalindrome(string& s) {
        int n = s.size();

        vector<vector<bool>> dp(n + 1, vector<bool>(n, false));

        // Initialize the first edge case
        for(int start = n-1; start >= 0; --start)
            for(int end = 0; end <= start; ++end)
                dp[start][end] = true;

        int maxLength = 0;
        int i, j;

        // Fill rest of the table along with find length of the longest palindromic substring
        for(int start = n-1; start >= 0; --start) {
            for(int end = 0; end <= n-1; ++end) {
                if(start < end && s[start] == s[end]) {
                    dp[start][end] = (end - 1 >= 0) ? dp[start + 1][end - 1] : false;
                } 
                if(dp[start][end] && end-start+1 > maxLength) { 
                    maxLength = end-start+1;
                    i = start;
                    j = end;
                }
            }
        }

        // Get the longest palindromic substring using its start and end index and then return it
        return s.substr(i, j-i+1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String | Dynamic Programming 
Link  : https://leetcode.com/problems/longest-palindromic-substring/description/
