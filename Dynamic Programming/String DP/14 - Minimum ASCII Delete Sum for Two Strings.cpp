// Code to find the lowest ASCII sum of deleted characters to make two strings equal ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
public:
    // Method to find the lowest ASCII sum of deleted characters to make two strings equal, using recursion with memoization - O(N*M) & O(N*M)
    int minimumDeleteSum(string& s1, string& s2) {
        int n = s1.size(), m = s2.size();
        vector<vector<int>> memory(n, vector<int>(m, -1));
        return solveWithMemo(memory, s1, s2, n-1, m-1);
    }

private:
    // O(2*N*M) & O(N*M + N+M)
    int solveWithMemo(vector<vector<int>>& memory, string& s1, string& s2, int i, int j) {
        // Edge case: If s1 is exhausted then j+1 letters has to be removed in s2 to make it equal to s1 
        if(i < 0) {
            int asciiSum = 0;
            while(j >= 0) asciiSum += s2[j--];
            return asciiSum;
        }

        // Edge case: If s2 is exhausted then i+1 letters has to be removed in s1 to make it equal to s2
        if(j < 0) {
            int asciiSum = 0;
            while(i >= 0) asciiSum += s1[i--];
            return asciiSum;
        }

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[i][j] != -1)
            return memory[i][j];

        // If the both the letters match then no removal is needed that's why look for the other matches
        if(s1[i] == s2[j])
            return memory[i][j] = solveWithMemo(memory, s1, s2, i-1, j-1);

        // Else when the letters don't match then we've two possibilities to perform
        int removeIthLetter = s1[i] + solveWithMemo(memory, s1, s2, i-1, j); // Is to remove the ith letter of s1
        int removeJthLetter = s2[j] + solveWithMemo(memory, s1, s2, i, j-1); // Is to remove the jth letter of s2

        // Store the result value to the memoization table and then return it
        return memory[i][j] = min(removeIthLetter, removeJthLetter);
    }

    // O(2^(N+M)) & O(N+M)
    int solveWithoutMemo(string& s1, string& s2, int i, int j) {
        // Edge case: If s1 is exhausted then j+1 letters has to be removed in s2 to make it equal to s1 
        if(i < 0) {
            int asciiSum = 0;
            while(j >= 0) asciiSum += s2[j--];
            return asciiSum;
        }

        // Edge case: If s2 is exhausted then i+1 letters has to be removed in s1 to make it equal to s2
        if(j < 0) {
            int asciiSum = 0;
            while(i >= 0) asciiSum += s1[i--];
            return asciiSum;
        }

        // If the both the letters match then no removal is needed that's why look for the other matches
        if(s1[i] == s2[j])
            return solveWithoutMemo(s1, s2, i-1, j-1);

        // Else when the letters don't match then we've two possibilities to perform
        int removeIthLetter = s1[i] + solveWithoutMemo(s1, s2, i-1, j); // Is to remove the ith letter of s1
        int removeJthLetter = s2[j] + solveWithoutMemo(s1, s2, i, j-1); // Is to remove the jth letter of s2

        // As we're striving for lowest sum hence return the minimum value
        return min(removeIthLetter, removeJthLetter);
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
