// Code to find the minimum number of extra characters left over if you break up the string "s" optimally ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Brute-force approach:
class DP_V1 {
public:
    class TopDown {
        unordered_set<string> dict;
        int n;

        // O(N^3) & O(N^2 + N+M) : Where N and M let be the size of "s" and "dict".
        int solveWithMemo(vector<vector<int>>& memory, const string& s, int startIndex, int partitionLength) {
            // Edge case: If all the letters are exhausted then you've created a partition hence calculate the number of extra characters in it and then return it
            if(startIndex == n)
                return n - partitionLength;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory[startIndex][partitionLength] != -1)
                return memory[startIndex][partitionLength];

            // It's possible that there are some words in dictionary which could be seen from the next index hence move to the next index and explore the partitions from that index 
            int minExtra = solveWithMemo(memory, s, startIndex + 1, partitionLength);

            string word;

            // Consider each letter into the word one by one and simultaneously check for it's existence in the dictionary. If it exists then consider a partition on that index and do the same from the next index
            for(int index = startIndex; index < n; ++index) {
                word += s[index];
                if(dict.count(word)) {
                    minExtra = min(minExtra, solveWithMemo(memory, s, index + 1, partitionLength + (index - startIndex + 1)));
                }
            }

            // Store the result value to the memoization table and then return it
            return memory[startIndex][partitionLength] = minExtra;
        }
        // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N+M) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code

    public:
        // Method to find the minimum number of extra characters, using recursion with 2D memoization :-
        int minExtraChar(string& s, vector<string>& dictionary) {
            n = s.size();
            for(auto& word : dictionary) dict.insert(word);
            vector<vector<int>> memory(n, vector<int>(n + 1, -1));
            return solveWithMemo(memory, s, 0, 0);
        }
    };

    class BottomUp {
    public:
        // Method to find the minimum number of extra characters, using 2D tabulation - O(N^3) & O(N^2 + M)
        int minExtraChar(string& s, vector<string>& dictionary) {
            int n = s.size();
    
            unordered_set<string> dict(begin(dictionary), end(dictionary));
    
            // 2D DP table
            vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));
    
            // Initialize the edge case
            for(int partitionLength = 0; partitionLength <= n; ++partitionLength)
                dp[n][partitionLength] = n - partitionLength;
    
            // Fill the rest of the table
            for(int startIndex = n-1; startIndex >= 0; --startIndex) {
                for(int partitionLength = n; partitionLength >= 0; --partitionLength) {
                    int minExtra = dp[startIndex + 1][partitionLength];
                    string word;
                    for(int index = startIndex; index < n; ++index) {
                        word += s[index];
                        if(dict.count(word)) {
                            int newIndex = partitionLength + (index - startIndex + 1);
                            if(newIndex >= 0 && newIndex <= n) {
                                minExtra = min(minExtra, dp[index + 1][newIndex]);
                            }
                        }
                    }
                    dp[startIndex][partitionLength] = minExtra;
                }
            }
    
            // Return the result value
            return dp[0][0];
        }
    };
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Optimized approach:
class DP_V2 {
public:
    class TopDown {
        unordered_set<string> dict;
        int n;

        // O(N*N) & O(N + N+M)
        int solveWithMemo(vector<int>& memory, const string& s, int startIndex) {
            // Edge case: If all the letters are exhausted then you've created a partition hence return 0
            if(startIndex == n)
                return 0;

            // Memoization table: If the current state is already computed then return the computed value
            if(memory[startIndex] != -1)
                return memory[startIndex];

            // It's possible that there are some words in dictionary which could be seen from the next index hence move to the next index and explore the partitions from that index 
            int maxValidLetters = solveWithMemo(memory, s, startIndex + 1);

            string word;

            // Consider each letter into the word one by one and simultaneously check for it's existence in the dictionary. If it exists then consider a partition on that index and do the same from the next index
            for(int index = startIndex; index < n; index++) {
                word += s[index];
                if(dict.count(word)) {
                    int currValid = (index - startIndex + 1) + solveWithMemo(memory, s, index + 1);
                    maxValidLetters = max(maxValidLetters, currValid);
                }
            }

            // Store the result value to the memoization table and then return it  
            return memory[startIndex] = maxValidLetters;
        }
        // Note: `solveWithoutMemo` function will have O(N^N) time complexity and O(N+M) auxiliary space. You can easily create it by removing the memoization from this `solveWithMemo`, which is straightforward to implement. The full function isn't provided here to avoid larger code

    public:
        // Method to find the minimum number of extra characters, using recursion with 1D memoization :-
        int minExtraChar(string& s, vector<string>& dictionary) {
            n = s.size();
            for(auto& word : dictionary) dict.insert(word);
            vector<int> memory(n, -1);
            return n - solveWithMemo(memory, s, 0);
        }
    };

    class BottomUp {
    public:
        // Method to find the minimum number of extra characters, using 1D tabulation - O(N*N) & O(N+M)
        int minExtraChar(string& s, vector<string>& dictionary) {
            int n = s.size();

            unordered_set<string> dict(begin(dictionary), end(dictionary));

            // 1D DP table
            vector<int> dp(n + 1, 0);

            // Fill the table   
            for(int startIndex = n-1; startIndex >= 0; --startIndex) {
                int maxValidLetters = dp[startIndex + 1];
                string word;

                for(int index = startIndex; index < n; index++) {
                    word += s[index];
                    if(dict.count(word)) {
                        int currValid = (index - startIndex + 1) + dp[index + 1];
                        maxValidLetters = max(maxValidLetters, currValid);
                    }
                }

                dp[startIndex] = maxValidLetters;
            }

            // Return the result value
            return n - dp[0];
        }
    };
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/extra-characters-in-a-string/description/
