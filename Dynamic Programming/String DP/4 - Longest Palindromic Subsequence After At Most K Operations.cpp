// Code to find the length of the longest palindromic subsequence of s that can be obtained after performing at most k operations. In one operation, you can replace the character at any position with the next or previous letter in the alphabet. For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y' ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // O(N^3) & O(N*N*K)
    int longestPalindromicSubsequence(string& s, int k) {
        int n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        return solveWithMemo(dp, s, 0, n-1, k);
    }

private:
    int solveWithMemo(vector<vector<vector<int>>>& dp, string& s, int i, int j, int k) {
        if(i == j) // Edge case: Any string of length 1 is palindrome 
            return 1;

        if(i > j) // Edge case: If no letters exist then no palindrome exist
            return 0;
        
        if(dp[i][j][k] != -1)
            return dp[i][j][k];
        
        // If both letters match then we have a palindrome of length 2 
        if(s[i] == s[j])
            return dp[i][j][k] = 2 + solveWithMemo(dp, s, i+1, j-1, k);
        
        // If both letters don't match then we have three possibilities
        int exclude_j = solveWithMemo(dp, s, i, j-1, k); // I. To find match for ith letter at left side of jth letter 
        int exclude_i = solveWithMemo(dp, s, i+1, j, k); // II. To find match for jth letter at right side of ith letter
        
        // III. To perform the replace operation
        int replaceOp = 0; 
        int transformCost = minTransformCost(s[i], s[j]);

        if(k - transformCost >= 0)
            replaceOp = 2 + solveWithMemo(dp, s, i+1, j-1, k - transformCost);
        
        return dp[i][j][k] = max({exclude_j, exclude_i, replaceOp});
    }

    int minTransformCost(char a, char b) {
        int nextOp = abs(b - a);    // Count operations needed to transform a to b using next operation
        int prevOp = 26 - nextOp;   // Count operations needed to transform a to b using previous operation
        return min(nextOp, prevOp); // Do minimum operations so that k remains and could find largest length in future
    }
};
// Without Memoization DP The Time Complexity Becomes O(3^(N+N)).

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    int longestPalindromicSubsequence(string& s, int k) {
        if(s.size() == 1) 
            return 1;
        return solveUsing3DTable(s, k);
    }

private:
    // O(N^3) & O(N*K)
    int solveUsing2DTable(string& s, int given_k) {
        int n = s.size();

        vector<vector<int>> nextRow(n, vector<int>(given_k + 1, 0));
        vector<vector<int>> idealRow(n, vector<int>(given_k + 1, 0));

        for(int i = n-1; i >= 0; --i) {
            for(int j = i+1; j <= n-1; ++j) { // Start j from i+1 to skip edge cases
                for(int k = 0; k <= given_k; ++k) {
                    idealRow[i][k] = 1; // Initialize the first edge case

                    if(s[i] == s[j]) {
                        idealRow[j][k] = 2 + (j-1 >= 0 ? nextRow[j-1][k] : 0);
                    }
                    else {
                        int exclude_j = (j-1 >= 0 ? idealRow[j-1][k] : 0);
                        int exclude_i = nextRow[j][k];
                        int replaceOp = 0;
                        int transformCost = minTransformCost(s[i], s[j]);
                        if(k - transformCost >= 0) {
                            replaceOp = 2 + (j-1 >= 0 ? nextRow[j-1][k - transformCost] : 0);
                        }
                        idealRow[j][k] = max({exclude_j, exclude_i, replaceOp});    
                    }
                }
            }
            nextRow = idealRow;
        }

        return nextRow[n-1][given_k];
    }

    // O(N^3) & O(N*N*K)
    int solveUsing3DTable(string& s, int given_k) {
        int n = s.size();

        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(n, vector<int>(given_k + 1, 0)));

        for(int i = 0; i < n; ++i) // Initialize the first edge case
            for(int k = 0; k <= given_k; ++k)
                dp[i][i][k] = 1;

        for(int i = n-1; i >= 0; --i) {
            for(int j = i+1; j <= n-1; ++j) { // Start j from i+1 to skip edge cases
                for(int k = 0; k <= given_k; ++k) {
                    if(s[i] == s[j]) {
                        dp[i][j][k] = 2 + (j-1 >= 0 ? dp[i+1][j-1][k] : 0);
                    }
                    else {
                        int exclude_j = (j-1 >= 0 ? dp[i][j-1][k] : 0);
                        int exclude_i = dp[i+1][j][k];
                        int replaceOp = 0;
                        int transformCost = minTransformCost(s[i], s[j]);
                        if(k - transformCost >= 0) {
                            replaceOp = 2 + (j-1 >= 0 ? dp[i+1][j-1][k - transformCost] : 0);
                        }
                        dp[i][j][k] = max({exclude_j, exclude_i, replaceOp});    
                    }
                }
            }
        }

        return dp[0][n-1][given_k];
    }

    int minTransformCost(char a, char b) {
        int nextOp = abs(b - a);
        int prevOp = 26 - nextOp;
        return min(nextOp, prevOp);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/description/  
