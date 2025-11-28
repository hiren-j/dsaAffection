class Solution {
    using LL = long long;
    const int MOD = 1e9 + 7;
    int n;

    bool star(const char ch) {
        return ch == '*';
    }

    bool digit(const char d) {
        return d >= '0' && d <= '9';
    }

    // O(4*N) & O(2*N)
    LL solveWithMemo(vector<int>& dp, const string& s, int i) {
        if(i == n)
            return 1;

        if(s[i] == '0')
            return 0;

        if(dp[i] != -1)
            return dp[i];

        // If you're here then the character could be within '1' to '9' or it could be a '*' which can be decoded hence consider it and move to the next character. Remember when it's a '*' then suppose we're considering it for the digit '1' only
        int count = solveWithMemo(dp, s, i + 1); 

        // If it's confirmly a '*' then consider it for the rest of the digits from '2' to '9'
        if(star(s[i])) {
            int nextCount = 8 * solveWithMemo(dp, s, i + 1) % MOD; // 2 - 9
            count = (count + nextCount) % MOD;
        }

        if(i + 1 < n) {
            // Case 1 : dd
            // If you're here then: When the first character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the first character is '2' then you can only decode when the next character lies within '0' to '6'
            if(digit(s[i + 1]) && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                count = (count + solveWithMemo(dp, s, i + 2)) % MOD; // 10 - 26
            }
            // Case 2 : *d
            // When the first character is a '*' and the second character is not, then consider the first character as '1' or to consider it as '2'
            else if(star(s[i]) && digit(s[i + 1])) {
                count = (count + solveWithMemo(dp, s, i + 2)) % MOD; // 10 - 19

                if(s[i + 1] <= '6') {
                    count = (count + solveWithMemo(dp, s, i + 2)) % MOD; // 20 - 26
                }
            }
            // Case 3 : d*
            // When the second character is a '*' and the first character is not, then if the first character is '1' then you can consider the second character to be within '1' to '9'. If the first character is '2' then you can consider the second character to be within '1' to '6' 
            else if(digit(s[i]) && star(s[i + 1])) {
                if(s[i] == '1') {
                    int nextCount = 9 * solveWithMemo(dp, s, i + 2) % MOD; // 11 - 19
                    count = (count + nextCount) % MOD; 
                }
                else if(s[i] == '2') {
                    int nextCount = 6 * solveWithMemo(dp, s, i + 2) % MOD; // 21 - 26
                    count = (count + nextCount) % MOD; 
                }
            }
            // Case 4 : **
            // When both the characters are '*' then consider the first character as '1' then for it consider the second character to be within '1' to '9'. If you consider the first character as '2' then for it consider the second character to be within '1' to '6'
            else if(star(s[i]) && star(s[i + 1])) {
                count = (count + 9 * solveWithMemo(dp, s, i + 2)) % MOD; // 11 - 19
                count = (count + 6 * solveWithMemo(dp, s, i + 2)) % MOD; // 21 - 26
            }
        }

        return dp[i] = count;
    }

    int solveWith1DTable(const string& s) {
        vector<LL> dp(n + 1, -1);
        dp[n] = 1;

        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == '0') {
                dp[i] = 0;
                continue;
            }

            int count = dp[i + 1]; // for specific s[i] or for 1 of below star loop

            if(star(s[i])) {
                int nextCount = 8 * dp[i + 1] % MOD; // 2 - 9
                count = (count + nextCount) % MOD;
            }

            if(i + 1 < n) {
                // Case 1 : dd
                if(digit(s[i + 1]) && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                    count = (count + dp[i + 2]) % MOD; // 10 - 26
                }
                // Case 2 : *d
                else if(star(s[i]) && digit(s[i + 1])) {
                    count = (count + dp[i + 2]) % MOD; // 10 - 19

                    if(s[i + 1] <= '6') {
                        count = (count + dp[i + 2]) % MOD; // 20 - 26
                    }
                }
                // Case 3 : d*
                else if(digit(s[i]) && star(s[i + 1])) {
                    if(s[i] == '1') {
                        int nextCount = 9 * dp[i + 2] % MOD; // 11 - 19
                        count = (count + nextCount) % MOD; 
                    }
                    else if(s[i] == '2') {
                        int nextCount = 6 * dp[i + 2] % MOD; // 21 - 26
                        count = (count + nextCount) % MOD; 
                    }
                }
                // Case 4 : **
                else if(star(s[i]) && star(s[i + 1])) {
                    count = (count + 9 * dp[i + 2]) % MOD; // 11 - 19
                    count = (count + 6 * dp[i + 2]) % MOD; // 21 - 26
                }
            }

            dp[i] = count;
        }

        return dp[0];
    }

    int solveWithoutTable(const string& s) {
        LL dp_i_1 = 1;
        LL dp_i_2 = 0;
        LL dp_i   = 0;

        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == '0') {
                dp_i   = 0;
                dp_i_2 = dp_i_1;
                dp_i_1 = dp_i;
                continue;
            }

            int count = dp_i_1; // for specific s[i] or for 1 of below star loop

            if(star(s[i])) {
                int nextCount = 8 * dp_i_1 % MOD; // 2 - 9
                count = (count + nextCount) % MOD;
            }

            if(i + 1 < n) {
                // Case 1 : dd
                if(digit(s[i + 1]) && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                    count = (count + dp_i_2) % MOD; // 10 - 26
                }
                // Case 2 : *d
                else if(star(s[i]) && digit(s[i + 1])) {
                    count = (count + dp_i_2) % MOD; // 10 - 19

                    if(s[i + 1] <= '6') {
                        count = (count + dp_i_2) % MOD; // 20 - 26
                    }
                }
                // Case 3 : d*
                else if(digit(s[i]) && star(s[i + 1])) {
                    if(s[i] == '1') {
                        int nextCount = 9 * dp_i_2 % MOD; // 11 - 19
                        count = (count + nextCount) % MOD; 
                    }
                    else if(s[i] == '2') {
                        int nextCount = 6 * dp_i_2 % MOD; // 21 - 26
                        count = (count + nextCount) % MOD; 
                    }
                }
                // Case 4 : **
                else if(star(s[i]) && star(s[i + 1])) {
                    count = (count + 9 * dp_i_2) % MOD; // 11 - 19
                    count = (count + 6 * dp_i_2) % MOD; // 21 - 26
                }
            }

            dp_i   = count;
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }

public:
    int numDecodings(string s) {
        n = s.size();
        // vector<int> dp(n, -1);
        // return solveWithMemo(dp, s, 0);
        return solveWithoutTable(s);
    }
};
