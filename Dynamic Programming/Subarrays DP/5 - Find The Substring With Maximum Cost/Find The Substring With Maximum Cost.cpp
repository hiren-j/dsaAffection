// Code to find the maximum cost among all substrings of the string `s` ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    vector<int> values;
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int i, bool prevPick) {
        if(i == n)
            return 0;
        
        if(prevPick) {
            const int ch = s[i] - 'a';
            int pickInSubarr = values[ch] + solveWithoutMemo(s, i + 1, true);
            int stopHere = 0;
            return max(pickInSubarr, stopHere);
        }
        else {
            const int ch = s[i] - 'a';
            int startHere = values[ch] + solveWithoutMemo(s, i + 1, true);
            int startNext = solveWithoutMemo(s, i + 1, false);
            return max(startHere, startNext);
        }
    }

    // O(2*N*2) & O(N*2 + N)
    int solveWithMemo(vector<vector<int>>& dp, const string& s, int i, bool prevPick) {
        if(i == n)
            return 0;

        if(dp[i][prevPick] != -1)
            return dp[i][prevPick];

        if(prevPick) {
            const int ch = s[i] - 'a';
            int pickInSubarr = values[ch] + solveWithMemo(dp, s, i + 1, true);
            int stopHere = 0;
            return dp[i][prevPick] = max(pickInSubarr, stopHere);
        }
        else {
            const int ch = s[i] - 'a';
            int startHere = values[ch] + solveWithMemo(dp, s, i + 1, true);
            int startNext = solveWithMemo(dp, s, i + 1, false);
            return dp[i][prevPick] = max(startHere, startNext);
        }
    }

public:
    // Method to find the maximum cost among all substrings, using recursion with memoization - O(N) & O(N) 
    int maximumCostSubstring(string& s, string& chars, vector<int>& vals) {
        n = s.size();
        values.resize(26);

        for(int i = 0; i < 26; ++i) {
            values[i] = i + 1;
        }
        for(int i = 0; i < chars.size(); ++i) {
            const int ch = chars[i] - 'a';
            values[ch] = vals[i];
        }
        
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, s, 0, false);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<int> values;
    int n;

    // O(N*2) & O(N*2)
    int solveBy2DTable(const string& s) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][0] = 0;
        dp[n][1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    const int ch = s[i] - 'a';
                    int pickInSubarr = values[ch] + dp[i + 1][true];
                    int stopHere = 0;
                    dp[i][prevPick] = max(pickInSubarr, stopHere);
                }
                else {
                    const int ch = s[i] - 'a';
                    int startHere = values[ch] + dp[i + 1][true];
                    int startNext = dp[i + 1][false];
                    dp[i][prevPick] = max(startHere, startNext);
                } 
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveBy1DTable(const string& s) {
        vector<int> nextRow(2, -1);
        nextRow[0] = 0;
        nextRow[1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> idealRow(2, -1);
            
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    const int ch = s[i] - 'a';
                    int pickInSubarr = values[ch] + nextRow[true];
                    int stopHere = 0;
                    idealRow[prevPick] = max(pickInSubarr, stopHere);
                }
                else {
                    const int ch = s[i] - 'a';
                    int startHere = values[ch] + nextRow[true];
                    int startNext = nextRow[false];
                    idealRow[prevPick] = max(startHere, startNext);
                } 
            }
            
            swap(nextRow, idealRow);
        }

        return nextRow[false];
    }

    // O(N*2) & O(1)
    int solveInPlace(const string& s) {
        int nextRow_0 = 0;
        int nextRow_1 = 0;

        for(int i = n - 1; i >= 0; --i) {
            int idealRow_0 = -1;
            int idealRow_1 = -1;

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    const int ch = s[i] - 'a';
                    int pickInSubarr = values[ch] + nextRow_1;
                    int stopHere = 0;
                    idealRow_1 = max(pickInSubarr, stopHere);
                }
                else {
                    const int ch = s[i] - 'a';
                    int startHere = values[ch] + nextRow_1;
                    int startNext = nextRow_0;
                    idealRow_0 = max(startHere, startNext);
                } 
            }

            swap(nextRow_0, idealRow_0);
            swap(nextRow_1, idealRow_1);
        }

        return nextRow_0;
    }

public:
    int maximumCostSubstring(string& s, string& chars, vector<int>& vals) {
        n = s.size();
        values.resize(26);

        for(int i = 0; i < 26; ++i) {
            values[i] = i + 1;
        }
        for(int i = 0; i < chars.size(); ++i) {
            const int ch = chars[i] - 'a';
            values[ch] = vals[i];
        }
        
        return solveInPlace(s);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/find-the-substring-with-maximum-cost/description/?envType=problem-list-v2&envId=dynamic-programming
