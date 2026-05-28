// Code to find the maximum possible sum of an increasing subsequence of length k. Note that it's not necessary for the subsequence to be strictly increasing ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, int prev, int k) {
        if(k < 0)
            return INT_MIN;
        
        if(i == n)
            return (k == 0) ? 0 : INT_MIN;
        
        int currSkip = solveWithoutMemo(nums, i + 1, prev, k);
        int currTake = INT_MIN;

        if(prev == -1 || nums[prev] <= nums[i]) {
            currTake = solveWithoutMemo(nums, i + 1, i, k - 1);
            if(currTake != INT_MIN) currTake += nums[i];
        }

        return max(currSkip, currTake);
    }
    
    // O(N*N*K) & O(N*N*K)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, int prev, int k) {
        if(k < 0)
            return INT_MIN;
        
        if(i == n)
            return (k == 0) ? 0 : INT_MIN;
        
        if(dp[i][prev][k] != -1)
            return dp[i][prev][k];
        
        int currSkip = solveWithMemo(dp, nums, i + 1, prev, k);
        int currTake = INT_MIN;

        if(prev == n || nums[prev] <= nums[i]) {
            currTake = solveWithMemo(dp, nums, i + 1, i, k - 1);
            if(currTake != INT_MIN) currTake += nums[i];
        }

        return dp[i][prev][k] = max(currSkip, currTake);
    }
    
public:
    int max_sum(vector<int>& nums, int k) {
        n = nums.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n + 1, vector<int>(k + 1, -1)));
        int res = solveWithMemo(dp, nums, 0, n, k);
        return (res == INT_MIN) ? -1 : res;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N*N*GK) & O(N*N*GK) : Where GK = given_k
    int solveBy3DTable(const vector<int>& nums, int given_k) {
        vector<vector<vector<int>>> dp(n + 1, 
                vector<vector<int>>(n + 1, 
                        vector<int>(given_k + 1, -1)));
        
        for(int prev = 0; prev <= n; ++prev)
            for(int k = 0; k <= given_k; ++k)
                dp[n][prev][k] = (k == 0) ? 0 : INT_MIN;
            
        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                for(int k = 0; k <= given_k; ++k) {
                    int currSkip = dp[i + 1][prev][k];
                    int currTake = INT_MIN;
            
                    if(prev == n || nums[prev] <= nums[i]) {
                        currTake = (k - 1 < 0) ? INT_MIN : dp[i + 1][i][k - 1];
                        if(currTake != INT_MIN) currTake += nums[i];
                    }
            
                    dp[i][prev][k] = max(currSkip, currTake);   
                }
            }
        }
        
        return dp[0][n][given_k];
    }
    
    // O(N*N*GK) & O(N*GK) : Where GK = given_k
    int solveBy2DTable(const vector<int>& nums, int given_k) {
        vector<vector<int>> next(n + 1, vector<int>(given_k + 1, -1)); // i + 1th table
        vector<vector<int>> ideal(n + 1, vector<int>(given_k + 1, -1)); // ith table
        
        for(int prev = 0; prev <= n; ++prev)
            for(int k = 0; k <= given_k; ++k)
                next[prev][k] = (k == 0) ? 0 : INT_MIN;
            
        for(int i = n - 1; i >= 0; --i) {
            for(int prev = 0; prev <= n; ++prev) {
                for(int k = 0; k <= given_k; ++k) {
                    int currSkip = next[prev][k];
                    int currTake = INT_MIN;
            
                    if(prev == n || nums[prev] <= nums[i]) {
                        currTake = (k - 1 < 0) ? INT_MIN : next[i][k - 1];
                        if(currTake != INT_MIN) currTake += nums[i];
                    }
            
                    ideal[prev][k] = max(currSkip, currTake);   
                }
            }
            
            swap(next, ideal);
        }
        
        return next[n][given_k];
    }
    
public:
    int max_sum(vector<int>& nums, int k) {
        n = nums.size();
        int res = solveBy2DTable(nums, k);
        return (res == INT_MIN) ? -1 : res;
    }
};
	
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming  
Link  : https://www.geeksforgeeks.org/problems/maximum-sum-subsequence-of-length-k3053/1?page=6&difficulty%5B%5D=1&category%5B%5D=Dynamic%2520Programming&sortBy=submissions
