// Code to find the minimum number of extra characters left over if you break up the string "s" optimally ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    unordered_set<string> dict;
    int dp[51][51]; 
    int n;

    int solveWithMemo(const string& s, int start, int creatable) {
        if(start == n)
            return n - creatable; 

        if(dp[start][creatable] != -1)
            return dp[start][creatable];

        int result = solveWithMemo(s, start + 1, creatable);

        string substr;
        for(int i = start; i < n; ++i) {
            substr.push_back(s[i]);

            if(dict.count(substr)) {
                int next = solveWithMemo(s, i + 1, creatable + substr.size());
                result = min(result, next);
            }
        }

        return dp[start][creatable] = result;
    }

public:
    // O(N^3) & O(N^2)
    int minExtraChar(string& s, vector<string>& wordDict) {
        n = s.size();
        memset(dp, -1, sizeof(dp));
        for(const auto& w : wordDict) dict.insert(w);
        return solveWithMemo(s, 0, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N^3) & O(N^2)
    int minExtraChar(string& s, vector<string>& wordDict) {
        const int n = s.size();

        unordered_set<string> dict;
        for(const auto& w : wordDict) dict.insert(w);

        int dp[51][51*2]; 
        memset(dp, -1, sizeof(dp));
        
        for(int creatable = 0; creatable <= n; ++creatable) 
            dp[n][creatable] = n - creatable;

        for(int start = n - 1; start >= 0; --start) {
            for(int creatable = n; creatable >= 0; --creatable) {
                int result = dp[start + 1][creatable];

                string substr;
                for(int i = start; i < n; ++i) {
                    substr.push_back(s[i]);

                    if(dict.count(substr)) {
                        int next = dp[i + 1][creatable + substr.size()];
                        result = min(result, next);
                    }
                }

                dp[start][creatable] = result;
            }
        }

        return dp[0][0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/extra-characters-in-a-string/description/
