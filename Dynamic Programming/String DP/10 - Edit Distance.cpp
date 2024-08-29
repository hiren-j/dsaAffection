// Code to find the minimum number of operations required to convert word1 to word2 (You have the following three operations permitted on a word: Insert a character, Delete a character, Replace a character) ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:    
class TopDown {
public:
    // Method to find minimum number of operations, using recursion with memoization - O(N*M) & O(N*M)
    int minDistance(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, n-1, m-1);
    }

private:
    // O(3*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If s2 is exhausted then i+1 letters has to be deleted in s1 to make it equal to s2
        if(j < 0)
            return i+1;

        // Edge case: If s1 is exhausted then j+1 letters has to be inserted in s1 to make it equal to s2 
        if(i < 0)
            return j+1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        // If the both the letters match then move to left in both the strings and look for other matches
        if(s1[i] == s2[j])
            return memory[i][j] = solveWithMemo(memory, s1, s2, i-1, j-1);

        // Else when the letters don't match then we've three possibilities to perform at the ith letter of s1
        int insertOp  = solveWithMemo(memory, s1, s2, i, j-1);   // Is to insert the jth letter 
        int deleteOp  = solveWithMemo(memory, s1, s2, i-1, j);   // Is to delete the ith letter 
        int replaceOp = solveWithMemo(memory, s1, s2, i-1, j-1); // Is to replace the ith letter by the jth letter

        // Store the result value to the memoization table and then return it
        return memory[i][j] = 1 + min({insertOp, deleteOp, replaceOp});
    }

    // O(3^(N+M)) & O(N+M)
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        // Edge case: If s2 is exhausted then i+1 letters has to be deleted in s1 to make it equal to s2
        if(j < 0)
            return i+1;

        // Edge case: If s1 is exhausted then j+1 letters has to be inserted in s1 to make it equal to s2 
        if(i < 0)
            return j+1;

        // If the both the letters match then move to left in both the strings and look for other matches
        if(s1[i] == s2[j])
            return solveWithoutMemo(s1, s2, i-1, j-1);

        // Else when the letters don't match then we've three possibilities to perform at the ith letter of s1
        int insertOp  = solveWithoutMemo(s1, s2, i, j-1);   // Is to insert the jth letter 
        int deleteOp  = solveWithoutMemo(s1, s2, i-1, j);   // Is to delete the ith letter 
        int replaceOp = solveWithoutMemo(s1, s2, i-1, j-1); // Is to replace the ith letter by the jth letter

        // As we're striving for minimum operations hence add the minimum value and then return the result
        return 1 + min({insertOp, deleteOp, replaceOp});
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:  
class BottomUp {
public:
    // #1 Method to find minimum number of operations, using 2D tabulation - O(N*M) & O(N*M)
    int minDistance_V1(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 2D DP table
        vector<vector<int>> dp(n+1, vector<int>(m+1, INT_MAX));

        // Initialize the first edge case: If s2 is exhausted then i+1 letters has to be deleted in s1 to make it equal to s2
        for(int i = 0; i <= n; ++i)
            dp[i][0] = i+1;

        // Initialize the second edge case: If s1 is exhausted then j+1 letters has to be inserted in s1 to make it equal to s2 
        for(int j = 0; j <= m; ++j)
            dp[0][j] = j+1;

        // Fill the rest of the table
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= m; ++j) {
                if(s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                }
                else {
                    int insertOp  = dp[i][j-1];
                    int deleteOp  = dp[i-1][j];
                    int replaceOp = dp[i-1][j-1];
                    dp[i][j]      = 1 + min({insertOp, deleteOp, replaceOp});
                }
            }
        }

        // Return the result value
        return dp[n][m] - 1;
    }

    // #2 Method to find minimum number of operations, using 1D tabulation - O(N*M) & O(M)
    int minDistance_V2(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();

        // 1D DP tables
        vector<int> prevRow(m+1, INT_MAX), currRow(m+1, INT_MAX);

        // Initialize the first edge case: If s2 is exhausted then i+1 letters has to be deleted in s1 to make it equal to s2
        currRow[0] = 1;

        // Initialize the second edge case: If s1 is exhausted then j+1 letters has to be inserted in s1 to make it equal to s2 
        for(int j = 0; j <= m; ++j)
            prevRow[j] = j+1;

        // Fill the rest of the table
        for(int i = 1; i <= n; ++i) {
            currRow[0] = i+1; // Initialize the first edge case
            for(int j = 1; j <= m; ++j) {
                if(s1[i-1] == s2[j-1]) {
                    currRow[j] = prevRow[j-1];
                }
                else {
                    int insertOp  = currRow[j-1];
                    int deleteOp  = prevRow[j];
                    int replaceOp = prevRow[j-1];
                    currRow[j]    = 1 + min({insertOp, deleteOp, replaceOp});
                }
            }
            prevRow = currRow;
        }

        // Return the result value
        return prevRow[m] - 1;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/edit-distance/description/
