// Code to find the minimum number of extra characters left over if you break up the string "s" optimally ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------

class TopDown {
    unordered_set<string> dict;
    int n;

    // O(N^N) & O(N+M) : Where N and M let be the size of "s" and "dict".
    int solveWithoutMemo(const string& s, int startIndex, int partitionLength) {
        if(startIndex == n)
            return n - partitionLength;

        int minExtra = solveWithoutMemo(s, startIndex + 1, partitionLength);

        string word;

        for(int index = startIndex; index < n; ++index) {
            word += s[index];
            if(dict.count(word)) {
                minExtra = min(minExtra, solveWithoutMemo(s, index + 1, partitionLength + (index - startIndex + 1)));
            }
        }

        return minExtra;
    }

    // O(N^3) & O(N^2)
    int solveWithMemo(vector<vector<int>>& memory, const string& s, int startIndex, int partitionLength) {
        if(startIndex == n)
            return n - partitionLength;

        if(memory[startIndex][partitionLength] != -1)
            return memory[startIndex][partitionLength];

        int minExtra = solveWithMemo(memory, s, startIndex + 1, partitionLength);

        string word;

        for(int index = startIndex; index < n; ++index) {
            word += s[index];
            if(dict.count(word)) {
                minExtra = min(minExtra, solveWithMemo(memory, s, index + 1, partitionLength + (index - startIndex + 1)));
            }
        }

        return memory[startIndex][partitionLength] = minExtra;
    }

public:
    // Method to find the minimum number of extra characters, using recursion with memoization :-
    int minExtraChar(string& s, vector<string>& dictionary) {
        n = s.size();
        for(auto& word : dictionary) dict.insert(word);
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, s, 0, 0);
    }
};

----------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // Method to find the minimum number of extra characters, using 2D tabulation - O(N^3) & O(N^2)
    int minExtraChar(string& s, vector<string>& dictionary) {
        int n = s.size();

        unordered_set<string> dict(begin(dictionary), end(dictionary));
        
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, INT_MAX));

        for(int partitionLength = 0; partitionLength <= n; ++partitionLength)
            dp[n][partitionLength] = n - partitionLength;

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

        return dp[0][0];
    }
};

----------------------------------------------------------------------------------------------------------------


Topics: Array | Hash Table | String | Dynamic Programming
Link  : https://leetcode.com/problems/extra-characters-in-a-string/description/
