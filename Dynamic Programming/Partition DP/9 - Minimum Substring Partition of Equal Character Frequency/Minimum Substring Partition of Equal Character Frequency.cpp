// Code to find the minimum number of substrings such that you can partition the string "s" into one or more balanced substrings ~ coded by Hiren
 
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    bool isBalanced(const vector<int>& count) {
        int prev = -1;

        for(const int c : count) {
            if(c == 0) continue;
            if(prev == -1) prev = c;
            if(c != prev) return false;
        }

        return true;
    }

    // O(N^N) & O(N)
    int solveWithoutMemo(const string& s, int start) {
        if(start == n)
            return 0;
        
        vector<int> count(26);
        int res = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int ch = s[i] - 'a';
            count[ch]++;

            if(isBalanced(count)) {
                const int next = solveWithoutMemo(s, i + 1);
                res = min(res, next + 1);
            }
        }

        return res;
    }

    // O(N*N) & O(N)
    int solveWithMemo(vector<int>& dp, const string& s, int start) {
        if(start == n)
            return 0;

        if(dp[start] != -1)
            return dp[start];
        
        vector<int> count(26);
        int res = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int ch = s[i] - 'a';
            count[ch]++;

            if(isBalanced(count)) {
                const int next = solveWithMemo(dp, s, i + 1);
                res = min(res, next + 1);
            }
        }

        return dp[start] = res;
    }

public:
    int minimumSubstringsInPartition(string s) {
        n = s.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, s, 0);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    bool isBalanced(const vector<int>& count) {
        int prev = -1;

        for(const int c : count) {
            if(c == 0) continue;
            if(prev == -1) prev = c;
            if(c != prev) return false;
        }

        return true;
    }

public:
    // O(N*N) & O(N)
    int minimumSubstringsInPartition(string s) {
        const int n = s.size();

        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int start = n - 1; start >= 0; --start) {
            vector<int> count(26);
            int res = INT_MAX;
    
            for(int i = start; i < n; ++i) {
                const int ch = s[i] - 'a';
                count[ch]++;
    
                if(isBalanced(count)) {
                    const int next = dp[i + 1];
                    res = min(res, next + 1);
                }
            }
    
            dp[start] = res;
        }

        return dp[0];
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Hash Table | String | Dynamic Programming | Counting
Link  : https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/description/
