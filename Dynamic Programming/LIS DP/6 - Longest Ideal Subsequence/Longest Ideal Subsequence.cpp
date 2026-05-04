// Code to find the length of the longest ideal string ~ coded by vHiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n, k;

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& str, int i, int prevLetter) {
        if(i == n)
            return 0;

        int currSkip = solveWithoutMemo(str, i + 1, prevLetter);
        int currTake = 0;

        if(prevLetter == '\0' || abs(prevLetter  - str[i]) <= k)
            currTake = solveWithoutMemo(str, i + 1, str[i]) + 1;

        return max(currSkip, currTake);
    }
    // Note: This solution will lead to TLE

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, const string& str, int i, int prevLetter) {
        if(i == n)
            return 0;

        if(dp[i][prevLetter - 'a'] != -1)
            return dp[i][prevLetter - 'a'];

        int currSkip = solveWithMemo(dp, str, i + 1, prevLetter);
        int currTake = 0;

        if(prevLetter == '{' || abs(prevLetter  - str[i]) <= k)
            currTake = solveWithMemo(dp, str, i + 1, str[i]) + 1;

        return dp[i][prevLetter - 'a'] = max(currSkip, currTake);
    }

    // O(N*N) & O(N)
    int solveWithMemoLoop(vector<vector<int>>& dp, const string& str, int start, int prevLetter) {
        if(start == n)
            return 0;

        if(dp[start][prevLetter - 'a'] != -1)
            return dp[start][prevLetter - 'a'];

        int maxLen = 0;

        for(int i = start; i < n; ++i) {
            int currTake = 0;

            if(prevLetter == '{' || abs(prevLetter  - str[i]) <= k)
                currTake = solveWithMemoLoop(dp, str, i + 1, str[i]) + 1;
            
            maxLen = max(maxLen, currTake);
        }

        return dp[start][prevLetter - 'a'] = maxLen;
    }
    // Note: This solution will lead to TLE

public:
    int longestIdealString(string& str, int K) {
        n = str.size(), k = K;
        vector<vector<int>> dp(n, vector<int>(27, -1));
        return solveWithMemo(dp, str, 0, '{');
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, k;

    // O(N) & O(N)
    int solveBy2DTable(const string& str) {
        vector<vector<int>> dp(n + 1, vector<int>(27, -1));

        for(char prevLetter = 'a'; prevLetter <= '{'; ++prevLetter) 
            dp[n][prevLetter - 'a'] = 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(char prevLetter = 'a'; prevLetter <= '{'; ++prevLetter) {
                int currSkip = dp[i + 1][prevLetter - 'a'];
                int currTake = 0;

                if(prevLetter == '{' || abs(prevLetter  - str[i]) <= k)
                    currTake = dp[i + 1][str[i] - 'a'] + 1;

                dp[i][prevLetter - 'a'] = max(currSkip, currTake);
            }
        }

        return dp[0]['{' - 'a'];
    }

    // O(N) & O(N)
    int solveBy2DEnhanced(const string& str) {
        vector<vector<int>> dp(n + 1, vector<int>(27, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(char prevLetter = 'a'; prevLetter <= '{'; ++prevLetter) {
                int currSkip = dp[i + 1][prevLetter - 'a'];
                int currTake = 0;

                if(prevLetter == '{' || abs(prevLetter  - str[i]) <= k)
                    currTake = dp[i + 1][str[i] - 'a'] + 1;

                dp[i][prevLetter - 'a'] = max(currSkip, currTake);
            }
        }

        return dp[0]['{' - 'a'];
    }

    // O(N) & O(1)
    int solveBy1DTable(const string& str) {
        vector<int> nextRow(27, 0), idealRow(27, 0);

        for(int i = n - 1; i >= 0; --i) {
            for(char prevLetter = 'a'; prevLetter <= '{'; ++prevLetter) {
                int currSkip = nextRow[prevLetter - 'a'];
                int currTake = 0;

                if(prevLetter == '{' || abs(prevLetter  - str[i]) <= k)
                    currTake = nextRow[str[i] - 'a'] + 1;

                idealRow[prevLetter - 'a'] = max(currSkip, currTake);
            }
            swap(nextRow, idealRow);
        }

        return nextRow['{' - 'a'];
    }

public:
    int longestIdealString(string& str, int K) {
        n = str.size(), k = K;
        return solveBy1DTable(str);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Hash Table | String | Dynamic Programming 
Link  : https://leetcode.com/problems/longest-ideal-subsequence/description/
