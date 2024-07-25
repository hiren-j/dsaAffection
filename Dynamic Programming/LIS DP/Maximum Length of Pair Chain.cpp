// Code to find the length of the longest chain which can be formed under the mentioned instructions ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the length of the longest chain which can be formed, using recursion with memoization - O(N*N) & O(N*N)
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        sort(begin(pairs), end(pairs));
        vector<vector<int>> memory(n, vector<int>(n + 1, -1));
        return solveWithMemo(memory, pairs, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N*N + N)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& pairs, int n, int index, int prevIndex) {
        // Edge case: If all the elements are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // Memoizationt table: If the current state is already computed then return the computed value
        if(memory[index][prevIndex + 1] != -1)
            return memory[index][prevIndex + 1];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, pairs, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                     // Is to pick the index value                                       

        // If the previous value is strictly lesser than the current value then pick the current value
        if(prevIndex == -1 || pairs[prevIndex][1] < pairs[index][0])
            currTake = 1 + solveWithMemo(memory, pairs, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[index][prevIndex + 1] = max(currSkip, currTake);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& pairs, int n, int index, int prevIndex) {
        // Edge case: If all the elements are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each index
        int currSkip = solveWithoutMemo(pairs, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                // Is to pick the index value                                       

        // If the previous value is strictly lesser than the current value then pick the current value
        if(prevIndex == -1 || pairs[prevIndex][1] < pairs[index][0])
            currTake = 1 + solveWithoutMemo(pairs, n, index + 1, index);

        // As we're striving for the maximum length hence return the maximum value
        return max(currSkip, currTake);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the length of the longest chain which can be formed, using recursion with memoization - O(N*N) & O(N)
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        sort(begin(pairs), end(pairs));
        vector<int> memory(n + 1, -1);
        return solveWithMemo(memory, pairs, n, 0, -1);
    }

private:
    // O(2*N*N) & O(N+N)
    int solveWithMemo(vector<int>& memory, vector<vector<int>>& pairs, int n, int index, int prevIndex) {
        // Edge case: If all the elements are exhausted then you can't pick any more
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevIndex + 1] != -1)
            return memory[prevIndex + 1];

        // There are always two possibilities to perform at each index
        int currSkip = solveWithMemo(memory, pairs, n, index + 1, prevIndex); // Is to skip the index value
        int currTake = 0;                                                     // Is to pick the index value

        // If the previous value is strictly lesser than the current value then pick the current value
        if(prevIndex == -1 || pairs[prevIndex][1] < pairs[index][0])
            currTake = 1 + solveWithMemo(memory, pairs, n, index + 1, index);

        // Store the result value to the memoization table and then return it
        return memory[prevIndex + 1] = max(currSkip, currTake);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

// #1 Class to implement the Bottom-up approach:
class BottomUp_V1 {
public:
    // #1 Method to find the length of the longest chain which can be formed, using 2D tabulation - O(N*N) & O(N*N)
    int findLongestChain_V1(vector<vector<int>>& pairs) {
        int n = pairs.size();
        
        sort(begin(pairs), end(pairs));

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = index-1; prevIndex >= -1; --prevIndex) {
                int currSkip = dp[index + 1][prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || pairs[prevIndex][1] < pairs[index][0]) {
                    currTake = 1 + dp[index + 1][index + 1];
                }
                dp[index][prevIndex + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][0];
    }

    // #2 Method to find the length of the longest chain which can be formed, using 1D tabulation - O(N*N) & O(N)
    int findLongestChain_V2(vector<vector<int>>& pairs) {
        int n = pairs.size();

        sort(begin(pairs), end(pairs));

        vector<int> nextRow(n + 1, 0), idealRow(n + 1, 0);

        for(int index = n-1; index >= 0; --index) {
            for(int prevIndex = index-1; prevIndex >= -1; --prevIndex) {
                int currSkip = nextRow[prevIndex + 1];
                int currTake = 0;
                if(prevIndex == -1 || pairs[prevIndex][1] < pairs[index][0]) {
                    currTake = 1 + nextRow[index + 1];
                }
                idealRow[prevIndex + 1] = max(currSkip, currTake);
            }
            nextRow = idealRow;
        }

        return idealRow[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

// #2 Class to implement the Bottom-up approach:
class BottomUp_V2 {
public:
    // Method to find the length of the longest chain which can be formed, using 1D tabulation - O(N*N) & O(N)
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size(), maxLength = 0;

        sort(begin(pairs), end(pairs));

        vector<int> dp(n, 1);

        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(pairs[prevIndex][1] < pairs[index][0]) {
                    dp[index] = max(dp[index], 1 + dp[prevIndex]);
                }
            }
            maxLength = max(maxLength, dp[index]);
        }

        return maxLength;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Greedy | Sorting
Link  : https://leetcode.com/problems/maximum-length-of-pair-chain/description/
