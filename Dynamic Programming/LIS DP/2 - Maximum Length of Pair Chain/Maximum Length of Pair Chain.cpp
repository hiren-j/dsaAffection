// Code to find the length of the longest chain which can be formed under the mentioned instructions ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/*

    DON'T IGNORE MUST READ: In the previous LIS problem, we implemented loop conversion, and we could do the same here. However, the Lines of Code (LOC) for this solution are already quite large, 
                            so I’m not including the loop-based recursive solution this time. By now, you likely understand the concept, so you can try it on your own if needed.
                            
*/
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<vector<int>>& pairs, int i, int prev) {
        if(i == n)
            return 0;

        int currSkip = solveWithoutMemo(pairs, i + 1, prev);
        int currTake = 0;

        if(prev == n || pairs[prev][1] < pairs[i][0])
            currTake = solveWithoutMemo(pairs, i + 1, i) + 1;

        return max(currSkip, currTake);
    }

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<vector<int>>& pairs, int i, int prev) {
        if(i == n)
            return 0;

        if(dp[i][prev] != -1)
            return dp[i][prev];

        int currSkip = solveWithMemo(dp, pairs, i + 1, prev);
        int currTake = 0;

        if(prev == n || pairs[prev][1] < pairs[i][0])
            currTake = solveWithMemo(dp, pairs, i + 1, i) + 1;

        return dp[i][prev] = max(currSkip, currTake);
    }

public:
    int findLongestChain(vector<vector<int>>& pairs) {
        n = pairs.size();
        sort(begin(pairs), end(pairs));
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, pairs, 0, n);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*N) & O(N*N)
    int solveBy2DTable(const vector<vector<int>>& pairs) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = dp[i + 1][prev];
                int currTake = 0;
        
                if(prev == n || pairs[prev][1] < pairs[i][0])
                    currTake = dp[i + 1][i] + 1;
        
                dp[i][prev] = max(currSkip, currTake);
            }
        }

        return dp[0][n];
    }

    // O(N*N) & O(N)
    int solveBy1DTable(const vector<vector<int>>& pairs) {
        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = nextRow[prev];
                int currTake = 0;
        
                if(prev == n || pairs[prev][1] < pairs[i][0])
                    currTake = nextRow[i] + 1;
        
                idealRow[prev] = max(currSkip, currTake);
            }
            swap(nextRow, idealRow);
        }

        return nextRow[n];
    }

public:
    int findLongestChain(vector<vector<int>>& pairs) {
        n = pairs.size();
        sort(begin(pairs), end(pairs));
        return solveBy1DTable(pairs);
    }
};    
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUpClean {
public:
    // O(N*N) & O(N)
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size(), maxLen = 0;
        sort(begin(pairs), end(pairs));

        vector<int> dp(n, 1);

        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(pairs[prevIndex][1] < pairs[index][0]) {
                    dp[index] = max(dp[index], 1 + dp[prevIndex]);
                }
            }
            maxLen = max(maxLen, dp[index]);
        }

        return maxLen;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Topics: Array | Dynamic Programming | Greedy | Sorting
Link  : https://leetcode.com/problems/maximum-length-of-pair-chain/description/
