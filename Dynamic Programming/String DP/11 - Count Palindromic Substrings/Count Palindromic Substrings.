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
    // O(N^2) & O(N^2)
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

class BottomUp {
    int n;

    // O(N^2) & O(N^2)
    int solveBy2DTable(const string& s) {
        vector<vector<int>> dp(n, vector<int>(n, -1));

        for(int i = n-1; i >= 0; --i) {
            for(int j = n-1; j >= i; --j) {
                if(s[i] == s[j])
                    dp[i][j] = (i + 1 >= j || i >= j - 1) ? true : dp[i + 1][j - 1];
                else
                    dp[i][j] = false;  
            }
        }

        int count = 0;
        
        for(int i = 0; i < n; ++i)
            for(int j = i; j < n; ++j)
                if(dp[i][j])
                    count++;

        return count;
    }

    // O(N^2) & O(N^2)
    int solveBy2DEnhanced(const string& s) {
        vector<vector<int>> dp(n, vector<int>(n, -1));
        int count = 0;

        for(int i = n-1; i >= 0; --i) {
            for(int j = n-1; j >= i; --j) {
                if(s[i] == s[j])
                    dp[i][j] = (i + 1 >= j || i >= j - 1) ? true : dp[i + 1][j - 1];
                else
                    dp[i][j] = false;  

                if(dp[i][j])
                    count++;
            }
        }

        return count;
    }

    // O(N^2) & O(N)
    int solveBy1DTable(const string& s) {
        vector<int> nextRow(n, -1), currRow(n, -1);
        int count = 0;

        for(int i = n-1; i >= 0; --i) {
            for(int j = n-1; j >= i; --j) {
                if(s[i] == s[j])
                    currRow[j] = (i + 1 >= j || i >= j - 1) ? true : nextRow[j - 1];
                else
                    currRow[j] = false;  

                if(currRow[j])
                    count++;
            }
            swap(nextRow, currRow);
        }

        return count;
    }

public:
    int countSubstrings(string s) {
        n = s.size();
        return solveBy1DTable(s);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Two Pointers | String | Dynamic Programming
Link  : https://leetcode.com/problems/palindromic-substrings/description/
