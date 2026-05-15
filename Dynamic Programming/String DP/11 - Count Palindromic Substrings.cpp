// Code to count the total number of palindromic substrings of the given string ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    bool isPalindrome(vector<vector<int>>& dp, const string& s, int i, int j) {
        if(i >= j)
            return true;
        
        if(dp[i][j] != -1)
            return dp[i][j];

        if(s[i] == s[j])
            return dp[i][j] = isPalindrome(dp, s, i + 1, j - 1);
        else
            return dp[i][j] = false;
    }

public:
    // O(N*N) & O(N*N)
    int countSubstrings(string s) {
        const int n = s.size();
        int count = 0;

        vector<vector<int>> dp(n, vector<int>(n, -1));

        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                if(isPalindrome(dp, s, i, j))
                    count++;

        return count;
    }
};
// Note: Without Memoization The Time Complexity Is O(N^3)

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
