// Code to find the the length of the longest valid (well-formed) parentheses substring ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int changeLen(char ch, int stackLen) {
        return ch == '(' ? stackLen + 1 : stackLen - 1;
    }

    int solveWithoutMemo(const string& s, int i, bool prevPick, int stackLen) {
        if(i == n)
            return (stackLen == 0) ? 0 : INT_MIN;

        if(stackLen < 0)
            return INT_MIN;

        if(prevPick) {
            int pickCurr = solveWithoutMemo(s, i + 1, true, changeLen(s[i], stackLen));
            if(pickCurr != INT_MIN) pickCurr++;
            int stopHere = (stackLen == 0) ? 0 : INT_MIN;
            return max(pickCurr, stopHere);
        }
        else {
            int startHere = solveWithoutMemo(s, i + 1, true, changeLen(s[i], stackLen));
            if(startHere != INT_MIN) startHere++; 
            int startNext = solveWithoutMemo(s, i + 1, false, stackLen);
            return max(startHere, startNext);
        }
    }
    // Note: This solution could lead to TLE

    int solveWithMemo(vector<vector<vector<int>>>& dp, const string& s, int i, bool prevPick, int stackLen) {
        if(i == n)
            return (stackLen == 0) ? 0 : INT_MIN;

        if(stackLen < 0)
            return INT_MIN;
        
        if(dp[i][prevPick][stackLen] != -1)
            return dp[i][prevPick][stackLen];

        if(prevPick) {
            int pickCurr = solveWithMemo(dp, s, i + 1, true, changeLen(s[i], stackLen));
            if(pickCurr != INT_MIN) pickCurr++;
            int stopHere = (stackLen == 0) ? 0 : INT_MIN;
            return dp[i][prevPick][stackLen] = max(pickCurr, stopHere);
        }
        else {
            int startHere = solveWithMemo(dp, s, i + 1, true, changeLen(s[i], stackLen));
            if(startHere != INT_MIN) startHere++; 
            int startNext = solveWithMemo(dp, s, i + 1, false, stackLen);
            return dp[i][prevPick][stackLen] = max(startHere, startNext);
        }
    }
    // Note: This solution could lead to MLE

public:
    int longestValidParentheses(string& s) {
        n = s.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(n + 1, -1)));
        return solveWithMemo(dp, s, 0, false, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int changeLen(char ch, int stackLen) {
        return ch == '(' ? stackLen + 1 : stackLen - 1;
    }

    int solveBy3DTable(const string& s) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n + 1, -1)));
        dp[n][0][0] = 0;
        dp[n][1][0] = 0;

        for(int i = 0; i <= n; ++i)
            for(int prevPick = 0; prevPick <= 1; ++prevPick)
                for(int stackLen = 0; stackLen <= n; ++stackLen)
                    if(!(i == n && stackLen == 0))
                        dp[i][prevPick][stackLen] = INT_MIN;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int stackLen = n; stackLen >= 0; --stackLen) {
                    if(prevPick) {
                        int newLen   = changeLen(s[i], stackLen);
                        int pickCurr = (newLen >= 0 && newLen <= n) ? dp[i + 1][true][newLen] : INT_MIN;
                        if(pickCurr != INT_MIN) pickCurr++;
                        int stopHere = (stackLen == 0) ? 0 : INT_MIN;
                        dp[i][prevPick][stackLen] = max(pickCurr, stopHere);
                    }
                    else {
                        int newLen    = changeLen(s[i], stackLen);
                        int startHere = (newLen >= 0 && newLen <= n) ? dp[i + 1][true][newLen] : INT_MIN;
                        if(startHere != INT_MIN) startHere++; 
                        int startNext = dp[i + 1][false][stackLen];
                        dp[i][prevPick][stackLen] = max(startHere, startNext);
                    }
                }
            }
        }

        return dp[0][false][0];
    }

    int solveBy3DEnhanced(const string& s) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n + 1, INT_MIN)));
        dp[n][0][0] = 0;
        dp[n][1][0] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int stackLen = n; stackLen >= 0; --stackLen) {
                    if(prevPick) {
                        int newLen   = changeLen(s[i], stackLen);
                        int pickCurr = (newLen >= 0 && newLen <= n) ? dp[i + 1][true][newLen] : INT_MIN;
                        if(pickCurr != INT_MIN) pickCurr++;
                        int stopHere = (stackLen == 0) ? 0 : INT_MIN;
                        dp[i][prevPick][stackLen] = max(pickCurr, stopHere);
                    }
                    else {
                        int newLen    = changeLen(s[i], stackLen);
                        int startHere = (newLen >= 0 && newLen <= n) ? dp[i + 1][true][newLen] : INT_MIN;
                        if(startHere != INT_MIN) startHere++; 
                        int startNext = dp[i + 1][false][stackLen];
                        dp[i][prevPick][stackLen] = max(startHere, startNext);
                    }
                }
            }
        }

        return dp[0][false][0];
    }

    int solveBy2DTable(const string& s) {
        vector<vector<int>> nextRow(2, vector<int>(n + 1, INT_MIN));
        nextRow[0][0] = 0;
        nextRow[1][0] = 0;

        for(int i = n - 1; i >= 0; --i) {
            vector<vector<int>> idealRow(2, vector<int>(n + 1, INT_MIN));
            
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int stackLen = n; stackLen >= 0; --stackLen) {
                    if(prevPick) {
                        int newLen   = changeLen(s[i], stackLen);
                        int pickCurr = (newLen >= 0 && newLen <= n) ? nextRow[true][newLen] : INT_MIN;
                        if(pickCurr != INT_MIN) pickCurr++;
                        int stopHere = (stackLen == 0) ? 0 : INT_MIN;
                        idealRow[prevPick][stackLen] = max(pickCurr, stopHere);
                    }
                    else {
                        int newLen    = changeLen(s[i], stackLen);
                        int startHere = (newLen >= 0 && newLen <= n) ? nextRow[true][newLen] : INT_MIN;
                        if(startHere != INT_MIN) startHere++; 
                        int startNext = nextRow[false][stackLen];
                        idealRow[prevPick][stackLen] = max(startHere, startNext);
                    }
                }
            }

            swap(nextRow, idealRow);
        }

        return nextRow[false][0];
    }

public:
    int longestValidParentheses(string& s) {
        n = s.size();
        return solveBy2DTable(s);
    }
};
// Note: This solution could lead to MLE

---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | String
Link  : https://leetcode.com/problems/longest-valid-parentheses/
