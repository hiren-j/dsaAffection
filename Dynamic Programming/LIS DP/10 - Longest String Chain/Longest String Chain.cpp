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

class BottomUp {
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
    int solveBy2DTable(const vector<string>& words) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        for(int prev = 0; prev <= n; ++prev)
            dp[n][prev] = 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = dp[i + 1][prev];
                int currTake = 0;

                if(prev == n || isPredecessor(words[prev], words[i]))
                    currTake = dp[i + 1][i] + 1;

                dp[i][prev] = max(currSkip, currTake);
            }
        }

        return dp[0][n];
    }
    
    // O(N*N) & O(N*N)
    int solveBy2DEnhanced(const vector<string>& words) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = dp[i + 1][prev];
                int currTake = 0;

                if(prev == n || isPredecessor(words[prev], words[i]))
                    currTake = dp[i + 1][i] + 1;

                dp[i][prev] = max(currSkip, currTake);
            }
        }

        return dp[0][n];
    }

    // O(N*N) & O(N)
    int solveBy1DTable(const vector<string>& words) {
        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = nextRow[prev];
                int currTake = 0;

                if(prev == n || isPredecessor(words[prev], words[i]))
                    currTake = nextRow[i] + 1;

                idealRow[prev] = max(currSkip, currTake);
            }
            swap(nextRow, idealRow);
        }

        return nextRow[n];
    }

public:
    int longestStrChain(vector<string>& words) {
        n = words.size();
        sort(begin(words), end(words), sortByLength);
        return solveBy1DTable(words);
    }
};
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpClean {
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

public:
    // O(N*N) & O(N)
    int longestStrChain(vector<string>& words) {
        const int n = words.size();
        sort(begin(words), end(words), sortByLength);
        
        vector<int> LIS(n, 1);

        for(int idx = 0; idx < n; ++idx)
            for(int prevIdx = 0; prevIdx < idx; ++prevIdx)
                if(isPredecessor(words[prevIdx], words[idx]))
                    LIS[idx] = max(LIS[idx], LIS[prevIdx] + 1);

        return *max_element(begin(LIS), end(LIS));
    }
};
    
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | Two Pointers | String | Dynamic Programming | Sorting 
Link  : https://leetcode.com/problems/longest-string-chain/description/
