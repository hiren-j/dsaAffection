// Code to find the minimum number of extra characters left over if you break up the string "s" optimally ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    unordered_set<string> dict;
    int dp[51]; 
    int n;

    // O(N^2) & O(N)
    int solveWithMemo(const string& s, int start) {
        if(start == n)
            return 0;

        if(dp[start] != -1)
            return dp[start];

        int result = solveWithMemo(s, start + 1);

        string substr;
        for(int i = start; i < n; ++i) {
            substr.push_back(s[i]);

            if(dict.count(substr)) {
                int next = solveWithMemo(s, i + 1);
                result = max(result, next + (int)substr.size());
            }
        }

        return dp[start] = result;
    }

public:
    int minExtraChar(string& s, vector<string>& wordDict) {
        n = s.size();
        memset(dp, -1, sizeof(dp));
        for(const auto& w : wordDict) dict.insert(w);
        return n - solveWithMemo(s, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N^2) & O(N)
    int minExtraChar(string& s, vector<string>& wordDict) {
        const int n = s.size();

        unordered_set<string> dict;
        for(const auto& w : wordDict) dict.insert(w);

        int dp[51]; 
        memset(dp, 0, sizeof(dp));

        for(int start = n - 1; start >= 0; --start) {
            int result = dp[start + 1];

            string substr;
            for(int i = start; i < n; ++i) {
                substr.push_back(s[i]);

                if(dict.count(substr)) {
                    int next = dp[i + 1];
                    result = max(result, next + (int)substr.size());
                }
            }

            dp[start] = result;
        }

        return n - dp[0];
    }
};
    
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/extra-characters-in-a-string/description/
