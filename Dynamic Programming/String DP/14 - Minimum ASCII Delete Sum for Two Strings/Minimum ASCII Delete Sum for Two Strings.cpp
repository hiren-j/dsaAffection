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
    int n, m;

    // O(N*M) & O(N*M)
    int solveBy2DTable(const string& s1, const string& s2) {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        for(int j = 0; j <= m; ++j) {
            int tmp = j;
            int asciiSum = 0;
            while(tmp < m) asciiSum += s2[tmp++];
            dp[n][j] = asciiSum;
        }
            
        for(int i = 0; i <= n; ++i) {
            int tmp = i;
            int asciiSum = 0;
            while(tmp < n) asciiSum += s1[tmp++];
            dp[i][m] = asciiSum;
        }

        for(int i = n - 1; i >= 0; --i) {
            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j]) {
                    dp[i][j] = dp[i + 1][j + 1];
                }
                else {
                    int removeIthLetter = s1[i] + dp[i + 1][j]; 
                    int removeJthLetter = s2[j] + dp[i][j + 1];
                    dp[i][j] = min(removeIthLetter, removeJthLetter);
                }
            }
        }

        return dp[0][0];
    }

    // O(N*M) & O(M)
    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m + 1, -1), currRow(m + 1, -1);

        for(int j = 0; j <= m; ++j) {
            int tmp = j;
            int asciiSum = 0;
            while(tmp < m) asciiSum += s2[tmp++];
            nextRow[j] = asciiSum;
        }    
        int tmp = n;
        int asciiSum = 0;
        while(tmp < n) asciiSum += s1[tmp++];
        nextRow[m] = asciiSum;

        for(int i = n - 1; i >= 0; --i) {
            int tmp = i;
            int asciiSum = 0;
            while(tmp < n) asciiSum += s1[tmp++];
            currRow[m] = asciiSum;

            for(int j = m - 1; j >= 0; --j) {
                if(s1[i] == s2[j]) {
                    currRow[j] = nextRow[j + 1];
                }
                else {
                    int removeIthLetter = s1[i] + nextRow[j]; 
                    int removeJthLetter = s2[j] + currRow[j + 1];
                    currRow[j] = min(removeIthLetter, removeJthLetter);
                }
            }
            swap(nextRow, currRow);
        }

        return nextRow[0];
    }

public:
    int minimumDeleteSum(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        return solveBy1DTable(s1, s2);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description/
