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
    const vector<char> vowels = {'a', 'e', 'i', 'o', 'u'};
    const int MOD = 1e9 + 7;

    // O(GN) & O(GN) : Where GN = given_n
    int solveBy2DTable(int given_n) {
        vector<vector<int>> dp(given_n + 1, vector<int>(27, -1));

        for(int prev = 0; prev < 27; ++prev)
            dp[0][prev] = 1;

        for(int n = 1; n <= given_n; ++n) {
            for(char prev = 'a'; prev <= '{'; ++prev) {
                int count = 0;

                for(char curr : vowels) {
                    if(prev == '{' || (prev == 'a' && curr == 'e') 
                                   || (prev == 'e' && (curr == 'a' || curr == 'i'))
                                   || (prev == 'i' && curr != 'i')
                                   || (prev == 'o' && (curr == 'i' || curr == 'u'))
                                   || (prev == 'u' && curr == 'a')) {
                        int nextCount = dp[n - 1][curr - 'a'];
                        count = (count + nextCount) % MOD;
                    }
                }

                dp[n][prev - 'a'] = count;
            }
        }

        return dp[given_n]['{' - 'a'];
    }

    // O(GN) & O(1) : Where GN = given_n
    int solveBy1DTable(int given_n) {
        vector<int> prevRow(27, -1), currRow(27, -1);

        for(int prev = 0; prev < 27; ++prev)
            prevRow[prev] = 1;

        for(int n = 1; n <= given_n; ++n) {
            for(char prev = 'a'; prev <= '{'; ++prev) {
                int count = 0;

                for(char curr : vowels) {
                    if(prev == '{' || (prev == 'a' && curr == 'e') 
                                   || (prev == 'e' && (curr == 'a' || curr == 'i'))
                                   || (prev == 'i' && curr != 'i')
                                   || (prev == 'o' && (curr == 'i' || curr == 'u'))
                                   || (prev == 'u' && curr == 'a')) {
                        int nextCount = prevRow[curr - 'a'];
                        count = (count + nextCount) % MOD;
                    }
                }

                currRow[prev - 'a'] = count;
            }
            swap(prevRow, currRow);
        }

        return prevRow['{' - 'a'];
    }

public:
    int countVowelPermutation(int n) {
        return solveBy1DTable(n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming
Link  : https://leetcode.com/problems/count-vowels-permutation/
