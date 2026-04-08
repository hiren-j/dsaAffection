// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, int prev) {
        if(i == n)
            return 0;
        
        int currSkip = solveWithoutMemo(nums, i + 1, prev);
        int currTake = 0;

        if(prev == -1 || nums[prev] < nums[i])
            currTake = solveWithoutMemo(nums, i + 1, i) + 1;

        return max(currSkip, currTake);
    }

    // O(N*N) & O(N*N)
    int solveWithMemoShifting(vector<vector<int>>& dp, const vector<int>& nums, int i, int prev) {
        if(i == n)
            return 0;

        if(dp[i][prev + 1] != -1)
            return dp[i][prev + 1];

        int currSkip = solveWithMemoShifting(dp, nums, i + 1, prev);
        int currTake = 0;

        if(prev == -1 || nums[prev] < nums[i])
            currTake = solveWithMemoShifting(dp, nums, i + 1, i) + 1;

        return dp[i][prev + 1] = max(currSkip, currTake);
    }

    // O(N*N) & O(N*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int prev) {
        if(i == n)
            return 0;

        if(dp[i][prev] != -1)
            return dp[i][prev];

        int currSkip = solveWithMemo(dp, nums, i + 1, prev);
        int currTake = 0;

        if(prev == n || nums[prev] < nums[i])
            currTake = solveWithMemo(dp, nums, i + 1, i) + 1;

        return dp[i][prev] = max(currSkip, currTake);
    }

    // O(N*N) & O(N)
    int solveWithMemoSpaceReduce(vector<int>& dp, const vector<int>& nums, int i, int prev) {
        if(i == n)
            return 0;

        if(dp[prev] != -1)
            return dp[prev];

        int currSkip = solveWithMemoSpaceReduce(dp, nums, i + 1, prev);
        int currTake = 0;

        if(prev == n || nums[prev] < nums[i]) {
            currTake = solveWithMemoSpaceReduce(dp, nums, i + 1, i) + 1;
        }

        return dp[prev] = max(currSkip, currTake);
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, nums, 0, n);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N*N) & O(N*N)
    int solveBy2DShifting(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 2, -1));

        for(int prev = 0; prev <= n; ++prev)
            dp[n][prev + 1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prev = n - 1; prev >= -1; --prev) {
                int currSkip = dp[i + 1][prev + 1];
                int currTake = 0;

                if(prev == -1 || nums[prev] < nums[i])
                    currTake = dp[i + 1][i + 1] + 1;

                dp[i][prev + 1] = max(currSkip, currTake);
            }
        }

        return dp[0][-1+1];
    }

    // O(N*N) & O(N*N)
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        for(int prev = 0; prev <= n; ++prev)
            dp[n][prev] = 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = dp[i + 1][prev];
                int currTake = 0;

                if(prev == n || nums[prev] < nums[i])
                    currTake = dp[i + 1][i] + 1;

                dp[i][prev] = max(currSkip, currTake);
            }
        }

        return dp[0][n];
    }

    // O(N*N) & O(N*N)
    int solveBy2DEnhanced(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = dp[i + 1][prev];
                int currTake = 0;

                if(prev == n || nums[prev] < nums[i])
                    currTake = dp[i + 1][i] + 1;

                dp[i][prev] = max(currSkip, currTake);
            }
        }

        return dp[0][n];
    }

    // O(N*N) & O(N)
    int solveBy1DTable(const vector<int>& nums) {
        vector<int> nextRow(n + 1, 0); // i + 1th row
        
        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(n + 1, 0); // ith row

            for(int prev = 0; prev <= n; ++prev) {
                int currSkip = nextRow[prev];
                int currTake = 0;

                if(prev == n || nums[prev] < nums[i])
                    currTake = nextRow[i] + 1;

                currRow[prev] = max(currSkip, currTake);
            }

            swap(nextRow, currRow);
        }

        return nextRow[n];
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        n = nums.size();
        return solveBy1DTable(nums);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
