// Code to find the maximum sum subsequence of the given array such that the integers in the subsequence are sorted in strictly increasing order (i.e. a strictly increasing subsequence) ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, int prev) {
        if(i == n)
            return 0;
        
        int currSkip = solveWithoutMemo(nums, i + 1, prev);
        int currTake = 0;

        if(prev == -1 || nums[prev] < nums[i])
            currTake = solveWithoutMemo(nums, i + 1, i) + nums[i];

        return max(currSkip, currTake);
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
            currTake = solveWithMemo(dp, nums, i + 1, i) + nums[i];

        return dp[i][prev] = max(currSkip, currTake);
    }
    
public:
    int maxSumIS(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        return solveWithMemo(dp, nums, 0, n);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
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
                    currTake = dp[i + 1][i] + nums[i];
        
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
                    currTake = dp[i + 1][i] + nums[i];
        
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
                    currTake = nextRow[i] + nums[i];
        
                currRow[prev] = max(currSkip, currTake);
            }
            
            swap(nextRow, currRow);
        }
        
        return nextRow[n];
    }
    
public:
    int maxSumIS(vector<int>& nums) {
        n = nums.size();
        return solveBy1DTable(nums);
    }
};
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpClean {
public:
    int maxSumIS(vector<int>& nums) {
        const int n = nums.size();
        vector<int> LIS(n);

        for(int i = 0; i < n; ++i) {
            LIS[i] = nums[i];
            
            for(int prev = 0; prev < i; ++prev) {
                if(nums[i] > nums[prev]) {
                    if(LIS[prev] + nums[i] > LIS[i]) {
                        LIS[i] = LIS[prev] + nums[i];
                    }
                }
            }
        }

        return *max_element(begin(LIS), end(LIS));
    }
};    
    
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/maximum-sum-increasing-subsequence4749/1
