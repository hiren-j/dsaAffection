// Code to find the total number of ways to decode the given string in the specified way ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const string& s, int i) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've 1 way
        if(i == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it any way
        if(s[i] == '0')
            return 0;

        // If you're here then it's guaranteed that the character lies within '1' to '9' which can be decoded hence consider it and move to the next character
        int numWays = solveWithoutMemo(s, i + 1);

        // If you're here then there are two possible ways of decoding: When the current character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the current character is '2' then you can only decode when the next character lies within '0' to '6'
        if(i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')))
            numWays += solveWithoutMemo(s, i + 2);

        return numWays;
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const string& s, int i) {
        // Edge case: If all the characters are exhausted then you've decoded the whole string hence you've 1 way
        if(i == n)
            return 1;

        // Edge case: If the character is '0' then you've can't decode it in any way
        if(s[i] == '0')
            return 0;

        if(dp[i] != -1)
            return dp[i];

        // If you're here then it's guaranteed that the character lies within '1' to '9' which can be decoded hence consider it and move to the next character
        int numWays = solveWithMemo(dp, s, i + 1);

        // If you're here then there are two possible ways of decoding: When the current character is '1' then it's guaranteed that the next character will be within '0' to '9'. If the current character is '2' then you can only decode when the next character lies within '0' to '6'
        if(i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6')))
            numWays += solveWithMemo(dp, s, i + 2);
        
        return dp[i] = numWays;
    }

public:
    int numDecodings(string& s) {
        n = s.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, s, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(1*N) & O(1*N)
    int solveWith1DTable(const string& s) {
        vector<int> dp(n + 1, -1);
        dp[n] = 1; // Init first edge case

        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == '0') { // Handle second edge case
                dp[i] = 0;
            }
            else {
                int numWays = dp[i + 1];

                if(i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                    numWays += dp[i + 2];
                }

                dp[i] = numWays;
            }
        }

        return dp[0];
    }

    // O(1*N) & O(1)
    int solveWithoutTable(const string& s) {
        int dp_i_1 = 1; // Init first edge case
        int dp_i_2 = 0; 
        int dp_i   = 0;

        for(int i = n - 1; i >= 0; --i) {
            if(s[i] == '0') { // Handle second edge case
                dp_i = 0;
            }
            else {
                int numWays = dp_i_1;

                if(i + 1 < n && (s[i] == '1' || (s[i] == '2' && s[i + 1] <= '6'))) {
                    numWays += dp_i_2;
                }

                dp_i = numWays;
            }
            dp_i_2 = dp_i_1;
            dp_i_1 = dp_i;
        }

        return dp_i;
    }

public:
    int numDecodings(string& s) {
        n = s.size();
        return solveWithoutTable(s);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming
Link  : https://leetcode.com/problems/decode-ways/description/
