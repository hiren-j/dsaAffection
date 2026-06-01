// Code to find the length of the longest palindromic subsequence of given string ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(string& s, int i, int j) {
        if(i == j) // Edge case: Any string of length 1 is always a palindrome
            return 1;

        if(i > j) // Edge case: If no letters anymore then palindrome can't exist
            return 0;

        // If letters match then we got palindrome of length 2 and then check for other matchings
        if(s[i] == s[j]) { 
            return 2 + solveWithoutMemo(s, i+1, j-1);
        }
        else { 
            int exclude_j = solveWithoutMemo(s, i, j-1); // Its possible ith letter could exist at left side of jth letter 
            int exclude_i = solveWithoutMemo(s, i+1, j); // Its possible jth letter could exist at right side of ith letter
            return max(exclude_i, exclude_j); 
        }
    }

    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& dp, string& s, int i, int j) {
        if(i == j) // Edge case: Any string of length 1 is always a palindrome
            return 1;

        if(i > j) // Edge case: If no letters anymore then palindrome can't exist
            return 0;

        if(dp[i][j] != -1) 
            return dp[i][j];

        // If letters match then we got palindrome of length 2 and then check for other matchings
        if(s[i] == s[j]) { 
            return dp[i][j] = 2 + solveWithMemo(dp, s, i+1, j-1);
        }
        else { 
            int exclude_j = solveWithMemo(dp, s, i, j-1); // Its possible ith letter could exist at left side of jth letter 
            int exclude_i = solveWithMemo(dp, s, i+1, j); // Its possible jth letter could exist at right side of ith letter
            return dp[i][j] = max(exclude_i, exclude_j); 
        }
    }

public:
    // Method to find the length of longest palindromic subsequence, using recursion with memoization - O(N^2) & O(N^2)
    int longestPalindromeSubseq(string& s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return solveWithMemo(dp, s, 0, n-1);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    // O(N^2) & O(N^2)
    int solveBy2DTableBrute(string& s) {
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int>(n, 0));
        
        for(int i = 0; i < n; ++i) // Initialize the first edge case
            dp[i][i] = 1;
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = 0; j <= n-1; ++j) {
                if(i >= j)
                    continue; // Skip the edge cases
                
                if(s[i] == s[j]) {
                    dp[i][j] = 2 + (j-1 >= 0 ? dp[i+1][j-1] : 0);
                }
                else {
                    int exclude_j = (j-1 >= 0 ? dp[i][j-1] : 0);
                    int exclude_i = dp[i+1][j];   
                    dp[i][j] = max(exclude_i, exclude_j);
                }
            }
        }
        
        return dp[0][n-1];
    }
    
    // O(N^2) & O(N^2)
    int solveBy2DTableOptimized(string& s) {
        int n = s.size();

        vector<vector<int>> dp(n+1, vector<int>(n, 0));
        
        for(int i = 0; i < n; ++i) // Initialize the first edge case
            dp[i][i] = 1;
        
        for(int i = n-1; i >= 0; --i) {
            for(int j = i+1; j <= n-1; ++j) {
                if(s[i] == s[j]) {
                    dp[i][j] = 2 + (j-1 >= 0 ? dp[i+1][j-1] : 0);
                }
                else {
                    int exclude_j = (j-1 >= 0 ? dp[i][j-1] : 0);
                    int exclude_i = dp[i+1][j];   
                    dp[i][j] = max(exclude_i, exclude_j);
                }
            }
        }
        
        return dp[0][n-1];
    }
        
    // O(N^2) & O(N)
    int solveBy1DTable(string& s) {
        int n = s.size();
        
        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);
        
        for(int i = n-1; i >= 0; --i) {
            idealRow[i] = 1; // Initialize the first edge case
             for(int j = i+1; j <= n-1; ++j) {
                if(s[i] == s[j]) {
                    idealRow[j] = 2 + (j-1 >= 0 ? nextRow[j-1] : 0);
                }
                else {
                    int exclude_j = (j-1 >= 0 ? idealRow[j-1] : 0);
                    int exclude_i = nextRow[j];   
                    idealRow[j] = max(exclude_i, exclude_j);
                }
            }
            nextRow = idealRow;
        }
        return idealRow[n-1];
    }

public:
    // Method to find the length of longest palindromic subsequence, using tabulation :-
    int longestPalindromeSubseq(string& s) {
        return solveBy1DTable(s);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Links : https://leetcode.com/problems/longest-palindromic-subsequence/description/ 
