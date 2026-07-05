// Code to find the length of the longest palindromic subsequence of s that can be obtained after performing at most k operations. In one operation, you can replace the character at any position with the next or previous letter in the alphabet. For example, replacing 'a' with the next letter results in 'b', and replacing 'a' with the previous letter results in 'z'. Similarly, replacing 'z' with the next letter results in 'a', and replacing 'z' with the previous letter results in 'y' ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int dp[201][201][201];
    int n;

    int minTransformCost(char a, char b) {
        int nextOp = abs(b - a);    // Count operations needed to transform a to b using next operation
        int prevOp = 26 - nextOp;   // Count operations needed to transform a to b using previous operation
        return min(nextOp, prevOp); // Do minimum operations so that k remains and could find largest length in future
    }

    int solveWithMemo(const string& s, int i, int j, int k) {
        if(i == j) // Edge case: Any string of length 1 is palindrome 
            return 1;

        if(i > j) // Edge case: If no letters exist then no palindrome exist
            return 0;
        
        if(dp[i][j][k] != -1)
            return dp[i][j][k];
        
        // If both letters match then we have a palindrome of length 2 
        if(s[i] == s[j])
            return dp[i][j][k] = 2 + solveWithMemo(s, i+1, j-1, k);
        
        // If both letters don't match then we have three possibilities
        int move_j = solveWithMemo(s, i, j-1, k); // I.  To find match for ith letter at left side of jth letter 
        int move_i = solveWithMemo(s, i+1, j, k); // II. To find match for jth letter at right side of ith letter
        
        // III. To perform the replace operation
        int replaceOp = 0; 
        int transformCost = minTransformCost(s[i], s[j]);

        if(k - transformCost >= 0)
            replaceOp = 2 + solveWithMemo(s, i+1, j-1, k - transformCost);
        
        return dp[i][j][k] = max({move_j, move_i, replaceOp});
    }

public:
    // O(NNK) & O(NNK)
    int longestPalindromicSubsequence(string& s, int k) {
        n = s.size();
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(s, 0, n-1, k);
    }
};
// Without Memoization DP the Time Complexity is O(3^N)

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int minTransformCost(char a, char b) {
        int nextOp = abs(b - a);  
        int prevOp = 26 - nextOp;   
        return min(nextOp, prevOp); 
    }

    // O(N*N*GK) & O(N*N*GK) : Where GK = given_k
    int solveBy2DTable(const string& s, int given_k) {
        int dp[201][201][201];
        memset(dp, 0, sizeof(dp));

        for(int i = n-1; i >= 0; --i) {
            for(int j = i; j <= n-1; ++j) {
                for(int k = 0; k <= given_k; ++k) {
                    if(i == j) {
                        dp[i][j][k] = 1;
                    }
                    else if(s[i] == s[j]) {
                        dp[i][j][k] = 2 + dp[i+1][j-1][k];
                    }
                    else {
                        int move_j = dp[i][j-1][k];
                        int move_i = dp[i+1][j][k]; 

                        int replaceOp = 0; 
                        int transformCost = minTransformCost(s[i], s[j]);
                        if(k - transformCost >= 0) replaceOp = 2 + dp[i+1][j-1][k - transformCost];

                        dp[i][j][k] = max({move_j, move_i, replaceOp});
                    }
                }
            }
        }

        return dp[0][n-1][given_k];
    }

    // O(N*N*GK) & O(N*GK) : Where GK = given_k
    int solveBy1DTable(const string& s, int given_k) {
        int next[201][201], curr[201][201];
        memset(next, 0, sizeof(next));
        memset(curr, 0, sizeof(curr));

        for(int i = n-1; i >= 0; --i) {
            for(int j = i; j <= n-1; ++j) {
                for(int k = 0; k <= given_k; ++k) {
                    if(i == j) {
                        curr[j][k] = 1;
                    }
                    else if(s[i] == s[j]) {
                        curr[j][k] = 2 + next[j-1][k];
                    }
                    else {
                        int move_j = curr[j-1][k];
                        int move_i = next[j][k]; 

                        int replaceOp = 0; 
                        int transformCost = minTransformCost(s[i], s[j]);
                        if(k - transformCost >= 0) replaceOp = 2 + next[j-1][k - transformCost];

                        curr[j][k] = max({move_j, move_i, replaceOp});
                    }
                }
            }

            swap(next, curr);
        }

        return next[n-1][given_k];
    }

public:
    int longestPalindromicSubsequence(string& s, int k) {
        n = s.size();
        return solveBy1DTable(s, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/longest-palindromic-subsequence-after-at-most-k-operations/description/  
