// Code to find the length of the longest possible word chain with words chosen from the given list of words ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*

    DON'T IGNORE MUST READ: In the previous LIS problems, we implemented loop conversion, and we could do the same here. However, the Lines of Code (LOC) for this solution are already quite large, 
                            so I’m not including the loop-based recursive solution this time. By now, you likely understand the concept, so you can try it on your own if needed.
                            
*/
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    static bool sortByLength(const string& wordA, const string& wordB) {
        return wordA.length() < wordB.length();
    }

    // O(32) Time
    bool isPredecessor(const string& wordA, const string& wordB) {
        if(wordA.length() != wordB.length() - 1)
            return false;
        
        int i = 0, j = 0;

        while(i < wordA.length() && j < wordB.length()) {
            if(wordA[i] == wordB[j])
                i++;
            j++;
        }

        return i == wordA.length() ? true : false;
    }

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<string>& words, int i, int prev) {
        if(i == n)
            return 0;

        if(dp[i][prev] != -1)
            return dp[i][prev];

        int currSkip = solveWithMemo(dp, words, i + 1, prev);
        int currTake = 0;

        if(prev == n || isPredecessor(words[prev], words[i]))
            currTake = solveWithMemo(dp, words, i + 1, i) + 1;

        return dp[i][prev] = max(currSkip, currTake);
    }

public:
    int longestStrChain(vector<string>& words) {
        n = words.size();
        sort(begin(words), end(words), sortByLength);
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, words, 0, n);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Two Pointers | String | Dynamic Programming | Sorting 
Link  : https://leetcode.com/problems/longest-string-chain/description/
