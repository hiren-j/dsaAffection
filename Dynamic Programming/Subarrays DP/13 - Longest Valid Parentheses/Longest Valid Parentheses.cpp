// Code to find the the length of the longest valid (well-formed) parentheses substring ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int changeLen(char ch, int stackLen) {
        return ch == '(' ? stackLen + 1 : stackLen - 1;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int i, bool prevPick, int stackLen) {
        if(stackLen < 0)
            return INT_MIN;
        
        if(i == n)
            return (stackLen == 0) ? 0 : INT_MIN; 

        if(prevPick) {
            int pickInSubarr = solveWithoutMemo(s, i + 1, true, changeLen(s[i], stackLen));
            if(pickInSubarr != INT_MIN) pickInSubarr++; 
            int stopHere = (stackLen == 0) ? 0 : INT_MIN;
            return max(pickInSubarr, stopHere);
        }
        else {
            int startHere = solveWithoutMemo(s, i + 1, true, changeLen(s[i], stackLen));
            if(startHere != INT_MIN) startHere++; 
            int startNext = solveWithoutMemo(s, i + 1, false, stackLen);
            return max(startHere, startNext);
        }
    }
    // Note: This solution could lead to TLE

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const string& s, int i, bool prevPick, int stackLen) {
        if(stackLen < 0)
            return INT_MIN;
        
        if(i == n)
            return (stackLen == 0) ? 0 : INT_MIN; 
        
        if(dp[i][prevPick][stackLen] != -1)
            return dp[i][prevPick][stackLen];

        if(prevPick) {
            int pickInSubarr = solveWithMemo(dp, s, i + 1, true, changeLen(s[i], stackLen));
            if(pickInSubarr != INT_MIN) pickInSubarr++;
            int stopHere = (stackLen == 0) ? 0 : INT_MIN;
            return dp[i][prevPick][stackLen] = max(pickInSubarr, stopHere);
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

    // O(N*N) & O(N*N)
    int solveBy3DTable(const string& s) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(n, -1)));

        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int stackLen = 0; stackLen < n; ++stackLen)
                dp[n][prevPick][stackLen] = (prevPick == true && stackLen == 0) ? 0 : INT_MIN;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int stackLen = n - 1; stackLen >= 0; --stackLen) {
                    int newLen = changeLen(s[i], stackLen);

                    if(prevPick) {
                        int pickInSubarr = (newLen < 0 || newLen >= n) ? INT_MIN : dp[i + 1][true][newLen];
                        if(pickInSubarr != INT_MIN) pickInSubarr++;
                        int stopHere = (stackLen == 0) ? 0 : INT_MIN;
                        dp[i][prevPick][stackLen] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = (newLen < 0 || newLen >= n) ? INT_MIN : dp[i + 1][true][newLen];
                        if(startCurr != INT_MIN) startCurr++;
                        int startNext = dp[i + 1][false][0];
                        dp[i][prevPick][stackLen] = max(startCurr, startNext);
                    }
                }
            }
        }

        int res = dp[0][false][0];
        return (res == INT_MIN) ? 0 : res;
    }
    // Note: This solution will lead to MLE

    // O(N*N) & O(N)
    int solveBy2DTable(const string& s) {
        vector<vector<int>> next(2, vector<int>(n, -1)); // i + 1th table
        vector<vector<int>> curr(2, vector<int>(n, -1)); // ith table

        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int stackLen = 0; stackLen < n; ++stackLen)
                next[prevPick][stackLen] = (stackLen == 0) ? 0 : INT_MIN;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int stackLen = n - 1; stackLen >= 0; --stackLen) {
                    int newLen = changeLen(s[i], stackLen);

                    if(prevPick) {
                        int pickInSubarr = (newLen < 0 || newLen >= n) ? INT_MIN : next[true][newLen];
                        if(pickInSubarr != INT_MIN) pickInSubarr++;
                        int stopHere = (stackLen == 0) ? 0 : INT_MIN;
                        curr[prevPick][stackLen] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr = (newLen < 0 || newLen >= n) ? INT_MIN : next[true][newLen];
                        if(startCurr != INT_MIN) startCurr++;
                        int startNext = next[false][0];
                        curr[prevPick][stackLen] = max(startCurr, startNext);
                    }
                }
            }
            swap(next, curr);
        }

        int res = next[false][0];
        return (res == INT_MIN) ? 0 : res;
    }
    // Note: This solution will lead to TLE

public:
    int longestValidParentheses(string& s) {
        n = s.size();
        if(n == 0) return 0;
        return solveBy3DTable(s);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | String
Link  : https://leetcode.com/problems/longest-valid-parentheses/
