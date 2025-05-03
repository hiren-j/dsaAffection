// Code to find the total number of ways to decode the given string in the specified way ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int index) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        if(index == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in the valid way
        if(s[index] == '0')
            return 0;

        // If you're here then it's guaranteed that the character lies within '1' to '9' which can be decoded hence consider it and move to the next character
        int numWays = solveWithoutMemo(s, index + 1);

        // If you're here then there are two possible ways of decoding: When the current character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the current character is '2' then you can only decode when the next character lies within '0' to '6'
        if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6')))
            numWays += solveWithoutMemo(s, index + 2);

        return numWays;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const string& s, int index) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've one valid way
        if(index == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in the valid way
        if(s[index] == '0')
            return 0;

        if(dp[index] != -1)
            return dp[index];

        // If you're here then it's guaranteed that the character lies within '1' to '9' which can be decoded hence consider it and move to the next character
        int numWays = solveWithMemo(dp, s, index + 1);

        // If you're here then there are two possible ways of decoding: When the current character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the current character is '2' then you can only decode when the next character lies within '0' to '6'
        if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6')))
            numWays += solveWithMemo(dp, s, index + 2);
        
        return dp[index] = numWays;
    }

public:
    int numDecodings(string& s) {
        n = s.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, s, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int solveWith1DTable(const string& s) {
        vector<int> dp(n + 1, -1);
        dp[n] = 1; // Init first edge case

        for(int index = n-1; index >= 0; --index) {
            if(s[index] == '0') { // Handle second edge case
                dp[index] = 0;
            }
            else {
                int numWays = dp[index + 1];
                if(index + 1< n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays += dp[index + 2];
                }
                dp[index] = numWays;
            }
        }

        return dp[0];
    }

    int solveWithoutTable(const string& s) {
        int dp_index_1 = 1; // Init first edge case
        int dp_index_2 = 0; 
        int result = 0;

        for(int index = n-1; index >= 0; --index) {
            if(s[index] == '0') { // Handle second edge case
                result = 0;
            }
            else {
                int numWays = dp_index_1;
                if(index + 1 < n && (s[index] == '1' || (s[index] == '2' && s[index + 1] <= '6'))) {
                    numWays += dp_index_2;
                }
                result = numWays;
            }
            dp_index_2 = dp_index_1;
            dp_index_1 = result;
        }

        return result;
    }

public:
    int numDecodings(string& s) {
        n = s.size();
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/decode-ways/description/
