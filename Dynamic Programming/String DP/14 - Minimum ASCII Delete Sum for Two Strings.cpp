// Code to find the lowest ASCII sum of deleted characters to make two strings equal ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    // O(2^(N+M)) & O(N+M)
    int solveWithoutMemo(const string& s1, const string& s2, int i, int j) {
        if(i == n) {
            int asciiSum = 0;
            while(j < m) asciiSum += s2[j++];
            return asciiSum;
        }

        if(j == m) {
            int asciiSum = 0;
            while(i < n) asciiSum += s1[i++];
            return asciiSum;
        }

        if(s1[i] == s2[j])
            return solveWithoutMemo(s1, s2, i + 1, j + 1);

        int removeIthLetter = s1[i] + solveWithoutMemo(s1, s2, i + 1, j); 
        int removeJthLetter = s2[j] + solveWithoutMemo(s1, s2, i, j + 1);
        
        return min(removeIthLetter, removeJthLetter);
    }

    // O(N*M) & O(N*M)
    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j) {
        if(i == n) {
            int asciiSum = 0;
            while(j < m) asciiSum += s2[j++];
            return asciiSum;
        }

        if(j == m) {
            int asciiSum = 0;
            while(i < n) asciiSum += s1[i++];
            return asciiSum;
        }

        if(dp[i][j] != -1)
            return dp[i][j];

        if(s1[i] == s2[j])
            return dp[i][j] = solveWithMemo(dp, s1, s2, i + 1, j + 1);

        int removeIthLetter = s1[i] + solveWithMemo(dp, s1, s2, i + 1, j); 
        int removeJthLetter = s2[j] + solveWithMemo(dp, s1, s2, i, j + 1);
        
        return dp[i][j] = min(removeIthLetter, removeJthLetter);
    }

public:
    int minimumDeleteSum(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return solveWithMemo(dp, s1, s2, 0, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // #1 Method to find the lowest ASCII sum of deleted characters to make two strings equal, using 2D tabulation - O(N*M) & O(N*M)
    int minimumDeleteSum_V1(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 2D DP table
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        // Initialize the first edge case
        int asciiSum = 0;
        for(int j = 1; j <= m; ++j) {
            asciiSum += s2[j-1];
            dp[0][j] = asciiSum;
        }

        // Initialize the second edge case
        asciiSum = 0;
        for(int i = 1; i <= n; ++i) {
            asciiSum += s1[i-1];
            dp[i][0] = asciiSum;
        }

        // Fill the rest of the table
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    int removeIthLetter = s1[i-1] + dp[i-1][j];
                    int removeJthLetter = s2[j-1] + dp[i][j-1];
                    dp[i][j] = min(removeIthLetter, removeJthLetter);
                }
            }
        }               

        // Return the result value
        return dp[n][m];
    }

    // #2 Method to find the lowest ASCII sum of deleted characters to make two strings equal, using 1D tabulation - O(N*M) & O(M)
    int minimumDeleteSum_V2(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 1D DP tables
        vector<int> prevRow(m+1, 0), currRow(m+1, 0);

        // Initialize the first edge case
        int asciiSum = 0;
        for(int j = 1; j <= m; ++j) {
            asciiSum += s2[j-1];
            prevRow[j] = asciiSum;
        }

        asciiSum = 0;

        for(int i = 1; i <= n; ++i) {
            // Initialize the second edge case
            asciiSum += s1[i-1];
            currRow[0] = asciiSum;

            for(int j = 1; j <= m; ++j) {
                if(s1[i-1] == s2[j-1]) {
                    currRow[j] = prevRow[j-1];
                }
                else {
                    int removeIthLetter = s1[i-1] + prevRow[j];
                    int removeJthLetter = s2[j-1] + currRow[j-1];
                    currRow[j] = min(removeIthLetter, removeJthLetter);
                }
            }

            prevRow = currRow;
        }        

        return prevRow[m];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description/
