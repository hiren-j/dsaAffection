// Code to implement wildcard pattern matching with support for '?' and '*' where: '?' Matches any single character. '*' Matches any sequence of characters (including the empty sequence). The matching should cover the entire input string (not partial) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the brute force approach:
class BruteForce_DP {
public:
    // Subclass to implement the Top-down approach:
    class TopDown {
    public:
        // Method to check whether the string "p" matches the string "s" after implementing the wildcard matching, using recursion with memoization :-
        bool isMatch(string& s, string& p) {
            int n = s.size(), m = p.size();
            vector<vector<int>> memory(n, vector<int>(m, -1));
            return solveWithMemo(memory, s, p, n-1, m-1);
        }

    private:
        // O(K*N*M) & O(N*M + N+M)
        bool solveWithMemo(vector<vector<int>>& memory, string& s, string& p, int i, int j) {
            // If the string "s" is exhausted and all the remaining letters of the string "p" are '*' then consider all those letters as an empty sequence 
            if(i < 0) {
                while(j >= 0 && p[j] == '*') {
                    j--;
                }
            }
            
            // Base case: If both the string completely matches each other then return true
            if(i < 0 && j < 0)
                return true;

            // Base case: If any of the string gets exhausted then they can't match hence return false
            if(i < 0 || j < 0)
                return false;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory[i][j] != -1)
                return memory[i][j];

            // If both the letters match or the jth letter is a '?' then still consider it to be a valid match and then check for other matches
            if(s[i] == p[j] || p[j] == '?')
                return memory[i][j] = solveWithMemo(memory, s, p, i-1, j-1);

            // If the ith and jth letter don't match and the jth letter is not a '*' then it's guaranteed that it's a other lowercase letter hence return false
            if(p[j] != '*')
                return memory[i][j] = false;

            // If you reached here then it's guaranteed that the jth letter is a '*' hence explore the possiblity of considering the jth letter as an empty sequence
            if(solveWithMemo(memory, s, p, i, j-1))
                return memory[i][j] = true;

            // Now consider the jth letter as a match of sequence of letters and explore the possibility
            for(int k = i; k >= 0; --k) {
                if(solveWithMemo(memory, s, p, k-1, j-1)) {
                    return memory[i][j] = true;
                }
            }

            // Store the value to the memoization table and then return it
            return memory[i][j] = false;
        }
    };

    // Subclass to implement the Bottom-up approach:
    class BottomUp {
    public:
        // Method to check whether the string "p" matches the string "s" after implementing the wildcard matching, using 2D tabulation - O(N*M*N) & O(N*M)
        bool isMatch(string& s, string& p) {
            int n = s.size(), m = p.size();

            // 2D DP table
            vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));

            // Set the first base case: If both the string completely matches each other then return true
            dp[0][0] = true;

            // Suppose if the string "s" is exhausted then consider all the beginning '*' of the string "p" as an empty sequence and as it's an empty sequence so we could say that both the strings completely matches each other hence set true for these states in table
            int j = 1;
            while(j <= m && p[j-1] == '*') {
                dp[0][j] = true;
                j++;
            }

            // Fill the rest of the table
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= m; ++j) {
                    if(s[i-1] == p[j-1]) {
                        dp[i][j] = dp[i-1][j-1];
                    }
                    if(p[j-1] != '?' && p[j-1] != '*') {
                        continue;
                    }
                    else if(p[j-1] == '?') {
                        dp[i][j] = dp[i-1][j-1];
                    }
                    else if(dp[i][j-1]) {
                        dp[i][j] = true;
                    }
                    else {
                        for(int k = i; k >= 0; --k) {
                            if(k-1 >= 0 && dp[k-1][j-1]) {
                                dp[i][j] = true;
                                break;
                            }
                        }
                    }
                }
            }

            // Return the result value
            return dp[n][m];
        }
    };
};

----------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the optimized approach:
class Optimized_DP {
public:
    // Subclass to implement the Top-down approach:
    class TopDown {
    public:
        // Method to check whether the string "p" matches the string "s" after implementing the wildcard matching, using recursion with memoization :-
        bool isMatch(string& s, string& p) {
            int n = s.size(), m = p.size();
            vector<vector<int>> memory(n, vector<int>(m, -1));
            return solveWithMemo(memory, s, p, n-1, m-1);
        }

    private:
        // O(2*N*M) & O(N*M + N+M)
        bool solveWithMemo(vector<vector<int>>& memory, string& s, string& p, int i, int j) {
            // If the string "s" is exhausted and all the remaining letters of the string "p" are '*' then consider all those letters as an empty sequence 
            if(i < 0) {
                while(j >= 0 && p[j] == '*') {
                    j--;
                }
            }
            
            // Base case: If both the string completely matches each other then return true
            if(i < 0 && j < 0)
                return true;

            // Base case: If any of the string gets exhausted then they can't match hence return false
            if(i < 0 || j < 0)
                return false;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory[i][j] != -1)
                return memory[i][j];

            // If both the letters match or the jth letter is a '?' then still consider it to be a valid match and then check for other matches
            if(s[i] == p[j] || p[j] == '?')
                return memory[i][j] = solveWithMemo(memory, s, p, i-1, j-1);

            // If the ith and jth letter don't match and the jth letter is not a '*' then it's guaranteed that it's a other lowercase letter hence return false
            if(p[j] != '*')
                return memory[i][j] = false;

            // If you reached here then it's guaranteed that the jth letter is a '*' hence explore the possiblity of considering the jth letter as an empty sequence and also explore the possibility of considering the jth letter as a match of sequence of letters 
            return memory[i][j] = solveWithMemo(memory, s, p, i, j-1) || solveWithMemo(memory, s, p, i-1, j);
        }
    };
    
    // Class to implement the Bottom-up approach:
    class BottomUp {
    public:
        // O(N*M) & O(N*M)
        bool isMatch(string& s, string& p) {
            int n = s.size(), m = p.size();
            
            // 2D DP table
            vector<vector<bool>> dp(n+1, vector<bool>(m+1, false));

            // Set the first base case: If both the string completely matches each other then return true
            dp[0][0] = true;

            // Suppose if the string "s" is exhausted then consider all the beginning '*' of the string "p" as an empty sequence and as it's an empty sequence so we could say that both the strings completely matches each other hence set true for these states in table
            for(int j = 1; j <= m; ++j) {
                if(p[j-1] == '*') {
                    dp[0][j] = true;
                } 
                else {
                    break;
                }
            }
            
            // Fill the rest of the table
            for(int i = 1; i <= n; ++i) {
                for(int j = 1; j <= m; ++j) {
                    if(s[i-1] == p[j-1] || p[j-1] == '?')
                        dp[i][j] = dp[i-1][j-1];

                    else if(p[j-1] != '*')
                        dp[i][j] = false;

                    else
                        dp[i][j] = dp[i][j-1] || dp[i-1][j];
                }
            }

            // Return the result value
            return dp[n][m];
        }
    };
};

----------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming | Greedy | Recursion
Link  : https://leetcode.com/problems/wildcard-matching/description/
