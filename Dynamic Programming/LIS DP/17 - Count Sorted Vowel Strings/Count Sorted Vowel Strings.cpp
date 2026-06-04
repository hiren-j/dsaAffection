// Code to find the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted. A string "s" is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    // O(5^N) & O(N)
    int solveWithoutMemo(int n, char prev) {
        if(n == 0)
            return 1;
        
        int count = 0;

        for(const char ch : vowels) 
            if(prev <= ch)
                count += solveWithoutMemo(n - 1, ch);

        return count;
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, int n, char prev) {
        if(n == 0)
            return 1;
        
        if(dp[n][prev - 'a'] != -1)
            return dp[n][prev - 'a'];

        int count = 0;

        for(const char ch : vowels) 
            if(prev <= ch)
                count += solveWithMemo(dp, n - 1, ch);

        return dp[n][prev - 'a'] = count;
    }

public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(26, -1));
        return solveWithMemo(dp, n, 'a');  
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    // O(GN) & O(GN) : Where GN = given_n
    int solveBy2DTable(int given_n) {
        vector<vector<int>> dp(given_n + 1, vector<int>(26, -1));

        for(char prev = 'a'; prev <= 'z'; ++prev)
            dp[0][prev - 'a'] = 1;
        
        for(int n = 1; n <= given_n; ++n) {
            for(char prev = 'z'; prev >= 'a'; --prev) {
                int count = 0;

                for(const char ch : vowels) 
                    if(prev <= ch)
                        count += dp[n - 1][ch - 'a'];

                dp[n][prev - 'a'] = count;
            }
        }

        return dp[given_n]['a' - 'a'];
    }

    // O(GN) & O(1) : Where GN = given_n
    int solveBy1DTable(int given_n) {
        vector<int> prevRow(26, -1), currRow(26, -1);

        for(char prev = 'a'; prev <= 'z'; ++prev)
            prevRow[prev - 'a'] = 1;
        
        for(int n = 1; n <= given_n; ++n) {
            for(char prev = 'z'; prev >= 'a'; --prev) {
                int count = 0;

                for(const char ch : vowels) 
                    if(prev <= ch)
                        count += prevRow[ch - 'a'];

                currRow[prev - 'a'] = count;
            }
            swap(prevRow, currRow);
        }

        return prevRow['a' - 'a'];
    }

public:
    int countVowelStrings(int n) {
        return solveBy1DTable(n);        
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Math | Dynamic Programming | Combinatorics
Link  : https://leetcode.com/problems/count-sorted-vowel-strings/description/
