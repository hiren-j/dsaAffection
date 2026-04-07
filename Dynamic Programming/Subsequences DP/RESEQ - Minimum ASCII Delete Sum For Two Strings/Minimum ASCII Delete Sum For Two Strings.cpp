// Code to find the lowest ASCII sum of deleted characters to make given two strings equal ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, m;

    int stringSum(const string& s) {
        int sum = 0;
        for(const char ch : s) sum += ch;
        return sum;
    }

    int solveWithMemo(vector<vector<int>>& dp, const string& s1, const string& s2, int i, int j) {
        if(i == n || j == m)
            return 0;

        if(dp[i][j] != -1)
            return dp[i][j];
        
        int currSkip1 = solveWithMemo(dp, s1, s2, i + 1, j);
        int currSkip2 = solveWithMemo(dp, s1, s2, i, j + 1);
        int currTake  = s1[i] == s2[j]
                        ? solveWithMemo(dp, s1, s2, i + 1, j + 1) + s1[i]
                        : 0;
        
        return dp[i][j] = max({currSkip1, currSkip2, currTake});
    } 

public:
    // O(N*M) & O(N*M)
    int minimumDeleteSum(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int sumOfLCS = solveWithMemo(dp, s1, s2, 0, 0);
        int res1 = stringSum(s1) - sumOfLCS;
        int res2 = stringSum(s2) - sumOfLCS;
        return res1 + res2;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, m;

    int stringSum(const string& s) {
        int sum = 0;
        for(const char ch : s) sum += ch;
        return sum;
    }

    int solveBy1DTable(const string& s1, const string& s2) {
        vector<int> nextRow(m + 1, 0); // i + 1th row

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(m + 1, 0); // ith row

            for(int j = m - 1; j >= 0; --j) {
                int currSkip1 = nextRow[j];
                int currSkip2 = idealRow[j + 1];
                int currTake  = s1[i] == s2[j] 
                                ? nextRow[j + 1] + s1[i]
                                : 0;
                idealRow[j] = max({currSkip1, currSkip2, currTake});
            }

            swap(nextRow, idealRow);
        }

        return nextRow[0];
    }
    
public:
    // O(N*M) & O(M)
    int minimumDeleteSum(string& s1, string& s2) {
        n = s1.size(), m = s2.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        int sumOfLCS = solveBy1DTable(s1, s2);
        int res1 = stringSum(s1) - sumOfLCS;
        int res2 = stringSum(s2) - sumOfLCS;
        return res1 + res2;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Senior Staff | String | Dynamic Programming
Link  : https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/description/
      : https://github.com/hiren-j/dsaAffection/blob/C%2B%2B/Dynamic%20Programming/Subsequences%20DP/RESEQ%20-%20Longest%20Common%20Subsequence/1%20-%20Longest%20Common%20Subsequence%20(Static%20Version).cpp
