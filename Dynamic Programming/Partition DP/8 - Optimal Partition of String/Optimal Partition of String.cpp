// Code to find the minimum number of substrings in a partition. You've to partition the string into one or more substrings such that the characters in each substring are unique. That is, no letter appears in a single substring more than once ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class TopDown {
    int n;

    // O(N^N) & O(N)
    int solveWithoutMemo(const string& s, int start) {
        if(start == n)
            return 0;
        
        vector<int> count(26);
        int res = INT_MAX;

        for(int i = start; i < n; ++i) {
            const int ch = s[i] - 'a';
            if(++count[ch] > 1) 
                break;
            const int next = solveWithoutMemo(s, i + 1);
            res = min(res, next + 1);
        }

        return res;
    }

    // O(N*N) & O(N)
    int solveWithMemo(vector<int>& dp, const string& s, int start) {
        if(start == n)
            return 0;

        if(dp[start] != -1)
            return dp[start];

        int res = INT_MAX;
        vector<int> count(26);

        for(int i = start; i < n; ++i) {
            const int ch = s[i] - 'a';
            if(++count[ch] > 1) 
                break;
            const int next = solveWithMemo(dp, s, i + 1);
            res = min(res, next + 1);
        }

        return dp[start] = res;
    }

public:
    int partitionString(string& s) {
        n = s.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, s, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N)
    int partitionString(string& s) {
        const int n = s.size();

        vector<int> dp(n + 1, -1);
        dp[n] = 0;

        for(int start = n - 1; start >= 0; --start) {
            vector<int> count(26);
            int res = INT_MAX;

            for(int i = start; i < n; ++i) {
                const int ch = s[i] - 'a';
                if(++count[ch] > 1) 
                    break;
                const int next = dp[i + 1];
                res = min(res, next + 1);
            }

            dp[start] = res;
        }

        return dp[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/optimal-partition-of-string/description/
