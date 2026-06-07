// Code to count how many strings of length n can be formed under the mentioned rules ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    const int MOD = 1e9 + 7;

    // O(5^N) & O(N)
    int solveWithoutMemo(int n, char prev) {
        if(n == 0)
            return 1;
        
        int count = 0;

        for(char curr : vowels) {
            if(prev == '{' || (prev == 'a' && curr == 'e') 
                           || (prev == 'e' && (curr == 'a' || curr == 'i'))
                           || (prev == 'i' && curr != 'i')
                           || (prev == 'o' && (curr == 'i' || curr == 'u'))
                           || (prev == 'u' && curr == 'a')) {
                int nextCount = solveWithoutMemo(n - 1, curr);
                count = (count + nextCount) % MOD;
            }
        }

        return count;
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, int n, char prev) {
        if(n == 0)
            return 1;

        if(dp[n][prev - 'a'] != -1)
            return dp[n][prev - 'a'];
        
        int count = 0;

        for(char curr : vowels) {
            if(prev == '{' || (prev == 'a' && curr == 'e') 
                           || (prev == 'e' && (curr == 'a' || curr == 'i'))
                           || (prev == 'i' && curr != 'i')
                           || (prev == 'o' && (curr == 'i' || curr == 'u'))
                           || (prev == 'u' && curr == 'a')) {
                int nextCount = solveWithMemo(dp, n - 1, curr);
                count = (count + nextCount) % MOD;
            }
        }

        return dp[n][prev - 'a'] = count;
    }

public:
    int countVowelPermutation(int n) {
        vector<vector<int>> dp(n + 1, vector<int>(27, -1));
        return solveWithMemo(dp, n, '{');     
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    vector<char> vowels = {'a','e','i','o','u'};
    const int MOD = 1e9+7;

public:
    // #1 Method to count how many such strings of length n that can be formed, using 2D tabulation - O(N*23*5) & O(N*26)
    int countVowelPermutation_V1(int n) {
        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(26, 0));

        // Intialize the edge case: If you've created such string of length n then return 1
        for(int ch = 0; ch < 26; ++ch)
            dp[0][ch] = 1;

        // Fill the rest of the table
        for(int length = 1; length <= n; ++length) {
            for(char prevLetter = 'a'; prevLetter <= 'w'; ++prevLetter) {
                int count = 0;
                for(char v : vowels) {
                    if(prevLetter == 'w' || (prevLetter == 'a' && v == 'e') || (prevLetter == 'e' && (v == 'a' || v == 'i')) || (prevLetter == 'i' && v != 'i') || (prevLetter == 'o' && (v == 'i' || v == 'u')) || (prevLetter == 'u' && v == 'a')) {
                        count = count % MOD + dp[length - 1][v - 'a'] % MOD;
                    }
                }
                dp[length][prevLetter - 'a'] = count % MOD;
            }
        }

        // Return the result value
        return dp[n]['w' - 'a'];
    }

    // #2 Method to count how many such strings of length n that can be formed, using 1D tabulation - O(N*23*5) & O(2*26)
    int countVowelPermutation_V2(int n) {
        // 1D DP tables
        vector<int> prevRow(26, 0), currRow(26, 0);

        // Intialize the edge case: If you've created such string of length n then return 1
        for(int ch = 0; ch < 26; ++ch)
            prevRow[ch] = 1;

        // Fill the rest of the table
        for(int length = 1; length <= n; ++length) {
            for(char prevLetter = 'a'; prevLetter <= 'w'; ++prevLetter) {
                int count = 0;
                for(char v : vowels) {
                    if(prevLetter == 'w' || (prevLetter == 'a' && v == 'e') || (prevLetter == 'e' && (v == 'a' || v == 'i')) || (prevLetter == 'i' && v != 'i') || (prevLetter == 'o' && (v == 'i' || v == 'u')) || (prevLetter == 'u' && v == 'a')) {
                        count = count % MOD + prevRow[v - 'a'] % MOD;
                    }
                }
                currRow[prevLetter - 'a'] = count % MOD;
            }
            prevRow = currRow;
        }

        // Return the result value
        return prevRow['w' - 'a'];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/count-vowels-permutation/
