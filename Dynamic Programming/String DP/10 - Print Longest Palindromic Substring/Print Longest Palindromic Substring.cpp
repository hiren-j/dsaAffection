// Code to find the longest palindromic substring of a given string ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    bool isPalindrome(vector<vector<int>>& dp, const string& str, int i, int j) {
        if(i >= j)
            return true;

        if(dp[i][j] != -1)
            return dp[i][j];

        if(str[i] == str[j])
            return dp[i][j] = isPalindrome(dp, str, i + 1, j - 1);
        else
            return dp[i][j] = false;
    }

public:
    // O(N*N) & O(N*N)
    string longestPalindrome(string& s) {
        const int n = s.size();   
        int start = -1, end = -1;
        int maxLen = 0;

        vector<vector<int>> dp(n, vector<int>(n, -1));

        for(int i = 0; i < n; ++i) 
            for(int j = i; j < n; ++j) 
                if(isPalindrome(dp, s, i, j) && j - i + 1 > maxLen) 
                    maxLen = j - i + 1, start = i, end = j;

        return s.substr(start, end - start + 1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N)
    string longestPalindrome(string& s) {
        const int n = s.size();
        int start = -1, end = -1;
        int maxLen = 0;

        vector<int> nextRow(n, -1), currRow(n, -1);

        for(int i = n-1; i >= 0; --i) {
            for(int j = n-1; j >= i; --j) {
                if(s[i] == s[j])
                    currRow[j] = (i + 1 >= j || i >= j - 1) ? true : nextRow[j - 1];
                else
                    currRow[j] = false;  

                if(currRow[j] && j - i + 1 > maxLen)
                    maxLen = j - i + 1, start = i, end = j;
            }
            swap(nextRow, currRow);
        }

        return s.substr(start, end - start + 1);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String | Dynamic Programming 
Link  : https://leetcode.com/problems/longest-palindromic-substring/description/
        https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/String%20DP/11%20-%20Count%20Palindromic%20Substrings/Count%20Palindromic%20Substrings.cpp
