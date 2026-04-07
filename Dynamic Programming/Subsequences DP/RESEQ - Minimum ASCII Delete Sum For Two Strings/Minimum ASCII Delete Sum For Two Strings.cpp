class TopDown {
    int n, m;

    int stringSum(const string& s) {
        int sum = 0;
        for(const char ch : s) sum += ch;
        return sum;
    }

    // O(N*M) & O(N*M)
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
