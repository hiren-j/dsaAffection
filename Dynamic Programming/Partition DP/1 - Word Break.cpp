// Code to check whether given string can be segmented into a space-separated sequence of one or more dictionary words ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    unordered_set<string> dict;
    int n;

    // O(N^N) & O(N+M) : Where M = dict.size
    bool solveWithoutMemo(const string& s, int start) {
        if(start == n)
            return true;
        
        string word;

        for(int i = start; i < n; ++i) {
            word.push_back(s[i]);
            if(dict.count(word) && solveWithoutMemo(s, i + 1)) {
                return true;
            }
        }

        return false;
    }

    // O(N*N) & O(N+M) : Where M = dict.size
    bool solveWithMemo(vector<int>& dp, const string& s, int start) {
        if(start == n)
            return true;

        if(dp[start] != -1)
            return dp[start];

        string word;

        for(int i = start; i < n; ++i) {
            word.push_back(s[i]);
            if(dict.count(word) && solveWithMemo(dp, s, i + 1)) {
                return dp[start] = true;
            }
        }

        return dp[start] = false;
    }

public:
    bool wordBreak(string& s, vector<string>& wordDict) {
        n = s.size();
        for(const auto& w : wordDict) dict.insert(w);
        vector<int> dp(n, -1);
        return solveWithMemo(dp, s, 0);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N+M) : Where M = dict.size
    bool wordBreak(string& s, vector<string>& wordDict) {
        const int n = s.size();
        unordered_set<string> dict(begin(wordDict), end(wordDict));

        vector<bool> dp(n + 1, false);
        dp[n] = true;

        for(int start = n - 1; start >= 0; --start) {
            string word;

            for(int i = start; i < n; ++i) {
                word.push_back(s[i]);
                if(dict.count(word) && dp[i + 1]) {
                    dp[start] = true;
                    break;
                }
            }
        }

        return dp[0];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Hash Table | String | Dynamic Programming | Memoization 
Link  : https://leetcode.com/problems/word-break/description/
