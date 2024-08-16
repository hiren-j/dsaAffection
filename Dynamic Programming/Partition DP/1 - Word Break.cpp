// Code to check whether given string can be segmented into a space-separated sequence of one or more dictionary words ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    unordered_set<string> dictionary;
    int n;

    // O(N^N) & O(N+M)
    bool solveWithoutMemo(string& s, int startIndex) {
        // Edge case: If all the letters of the string are exhausted then return true
        if(startIndex == n)
            return true;

        string word;

        // Consider each letter into the word one by one and simultaneously check for it's existence in the dictionary. If it exists then consider a partition on that index and do the same from the next index
        for(int index = startIndex; index < n; ++index) {
            word += s[index];
            if(dictionary.count(word) && solveWithoutMemo(s, index + 1)) {
                return true;
            }
        }
        
        // If reached here then it's not possible for the string to become such sequence hence return false
        return false;
    }

    // O(N*N) & O(N+N+M)
    bool solveWithMemo(vector<int>& memory, string& s, int startIndex) {
        // Edge case: If all the letters of the string are exhausted then return true
        if(startIndex == n)
            return true;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[startIndex] != -1)
            return memory[startIndex];

        string word;

        // Consider each letter into the word one by one and simultaneously check for it's existence in the dictionary. If it exists then consider a partition on that index and do the same from the next index
        for(int index = startIndex; index < n; ++index) {
            word += s[index];
            if(dictionary.count(word) && solveWithMemo(memory, s, index + 1)) {
                return true;
            }
        }

        // Store the value to the memoization table and then return it
        return memory[startIndex] = false;
    }

public:
    // Method to check whether given string can be segmented into a space-separated sequence of one or more dictionary words, using recursion with memoization - O(N*N) & O(N+M) : Where M let be the size of "dictionary"
    bool wordBreak(string& s, vector<string>& wordDict) {
        n = s.size();
        for(auto& word : wordDict) dictionary.insert(word);
        vector<int> memory(n, -1);
        return solveWithMemo(memory, s, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to check whether given string can be segmented into a space-separated sequence of one or more dictionary words, using 1D tabulation - O(N*N) & O(N+M)
    bool wordBreak(string& s, vector<string>& wordDict) {
        int n = s.size();

        unordered_set<string> dictionary(begin(wordDict), end(wordDict));

        // 1D DP table
        vector<bool> dp(n + 1, false);

        // Initialize the edge case: If all the letters of the string are exhausted then return true
        dp[n] = true;

        // Fill the rest of the table
        for(int startIndex = n-1; startIndex >= 0; --startIndex) {
            string word;
            for(int index = startIndex; index < n; ++index) {
                word += s[index];
                if(dictionary.count(word) && dp[index + 1]) {
                    dp[startIndex] = true;
                }
            }
        }

        // Return the result value
        return dp[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Hash Table | String | Dynamic Programming | Memoization 
Link  : https://leetcode.com/problems/word-break/description/
