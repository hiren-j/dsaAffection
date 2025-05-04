// Code to find the total number of ways to decode the given string in the specified way. In addition to the specified mapping, an encoded message may contain the '*' character, which can represent any digit from '1' to '9' ('0' is excluded) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    int n;

    int getEndLimit(char digit) {
        if(digit == '1')
            return 9;
        if(digit == '2')
            return 6;
        return 0;
    }

    // O(24*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const string& s, int index) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        if(index == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in the valid way
        if(s[index] == '0')
            return 0;

        if(dp[index] != -1)
            return dp[index];

        // If you're here then the character could be within '1' to '9' or it could be a '*' which can be decoded hence consider it and move to the next character. Remember when it's a '*' then suppose we're considering it for the digit '1' only
        int numWays = solveWithMemo(dp, s, index + 1);

        // If it's confirmly a '*' then consider it for the rest of the digits from '2' to '9'
        if(s[index] == '*') {
            for(int digit = 2; digit <= 9; ++digit) {
                numWays = (numWays + solveWithMemo(dp, s, index + 1)) % MOD;
            }
        }

        // At this point now we will look for the cases when we've to consider both the characters together
        if(index + 1 < n) {
            // When both the characters are '*' then there are two possible ways of decoding: Consider the first character as '1' then for it consider the second character to be within '1' to '9'. If you consider the first character as '2' then for it consider the second character to be within '1' to '6'
            if(s[index] == '*' && s[index + 1] == '*') {
                for(int digit = 1; digit <= 9; ++digit) {
                    numWays = (numWays + solveWithMemo(dp, s, index + 2)) % MOD;
                    if(digit <= 6) {
                        numWays = (numWays + solveWithMemo(dp, s, index + 2)) % MOD;
                    }
                }
            }
            // When the first character is a '*' and the second character is not, then you've two ways to decode, which means is to consider the first character as '1' or to consider it as '2'
            else if(s[index] == '*') {
                numWays = (numWays + solveWithMemo(dp, s, index + 2)) % MOD;
                if(s[index + 1] <= '6') {
                    numWays = (numWays + solveWithMemo(dp, s, index + 2)) % MOD;
                }
            }
            // When the second character is a '*' and the first character is not, then you've two ways to decode, in which if the first character is '1' then you can consider the second character to be within '1' to '9'. If the first character is '2' then you can consider the second character to be within '1' to '6' 
            else if(s[index + 1] == '*') {
                for(int digit = 1; (digit <= getEndLimit(s[index])); ++digit) {
                    numWays = (numWays + solveWithMemo(dp, s, index + 2)) % MOD;
                }
            }
            // If you're here then there are two possible ways of decoding: When the first character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the first character is '2' then you can only decode when the next character lies within '0' to '6'
            else if((s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                numWays = (numWays + solveWithMemo(dp, s, index + 2)) % MOD;
            }
        }

        return dp[index] = numWays;
    }
    // Note: Creating the `solveWithoutMemo()` is easy, simply remove the dp part, I haven't included because it will increase the line of code

public: 
    // Method to find the total number of ways to decode the string, using recursion with memoization - O(N) & O(N)
    int numDecodings(string& s) {
        n = s.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, s, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    int n;

    int getEndLimit(char digit) {
        if(digit == '1')
            return 9;
        if(digit == '2')
            return 6;
        return 0;
    }

    // O(1*N) & O(1*N)
    int solveWith1DTable(const string& s) {
        vector<int> dp(n + 1, 0);
        dp[n] = 1; // Init first edge case

        for(int index = n-1; index >= 0; --index) {
            if(s[index] == '0') // Handle second edge case
                continue;

            int numWays = dp[index + 1];

            if(s[index] == '*') {
                for(int digit = 2; digit <= 9; ++digit) {
                    numWays = (numWays + dp[index + 1]) % MOD;
                }
            }

            if(index + 1 < n) {
                if(s[index] == '*' && s[index + 1] == '*') {
                    for(int digit = 1; digit <= 9; ++digit) {
                        numWays = (numWays + dp[index + 2]) % MOD;
                        if(digit <= 6) {
                            numWays = (numWays + dp[index + 2]) % MOD;
                        }
                    }
                }
                else if(s[index] == '*') {
                    numWays = (numWays + dp[index + 2]) % MOD;
                    if(s[index + 1] <= '6') {
                        numWays = (numWays + dp[index + 2]) % MOD;
                    }
                }
                else if(s[index + 1] == '*') {
                    for(int digit = 1; (digit <= getEndLimit(s[index])); ++digit) {
                        numWays = (numWays + dp[index + 2]) % MOD;
                    }
                }
                else if((s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays = (numWays + dp[index + 2]) % MOD;
                }
            }
    
            dp[index] = numWays;
        }

        return dp[0];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(const string& s) {
        int dpIndex1 = 1; // Init first edge case
        int dpIndex2 = 0;
        int result = 0;

        for(int index = n-1; index >= 0; --index) {
            if(s[index] == '0') { // Handle second edge case
                result   = 0;
                dpIndex2 = dpIndex1;
                dpIndex1 = result;
                continue;
            }

            int numWays = dpIndex1;

            if(s[index] == '*') {
                for(int digit = 2; digit <= 9; ++digit) {
                    numWays = (numWays + dpIndex1) % MOD;
                }
            }

            if(index + 1 < n) {
                if(s[index] == '*' && s[index + 1] == '*') {
                    for(int digit = 1; digit <= 9; ++digit) {
                        numWays = (numWays + dpIndex2) % MOD;
                        if(digit <= 6) {
                            numWays = (numWays + dpIndex2) % MOD;
                        }
                    }
                }
                else if(s[index] == '*') {
                    numWays = (numWays + dpIndex2) % MOD;
                    if(s[index + 1] <= '6') {
                        numWays = (numWays + dpIndex2) % MOD;
                    }
                }
                else if(s[index + 1] == '*') {
                    for(int digit = 1; (digit <= getEndLimit(s[index])); ++digit) {
                        numWays = (numWays + dpIndex2) % MOD;
                    }
                }
                else if((s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays = (numWays + dpIndex2) % MOD;
                }
            }
            result   = numWays;
            dpIndex2 = dpIndex1;
            dpIndex1 = result;
        }

        return result;        
    }

public: 
    // Method to find the total number of ways to decode the string, using tabulation :-
    int numDecodings(string& s) {
        n = s.size();
        return solveWithoutTable(s);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/decode-ways-ii/description/
