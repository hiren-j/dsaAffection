// Code to find the maximum total value you can collect for the knapsack (each item can be taken any number of times) ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(2^K) & O(N)
    int solveWithoutMemo(const vector<int>& nums, const vector<int>& cost, int i, int k) {
        if(i == n || k == 0)
            return 0;
        
        int currSkip = solveWithoutMemo(nums, cost, i + 1, k);
        int currTake = cost[i] <= k 
                        ? nums[i] + solveWithoutMemo(nums, cost, i, k - cost[i])
                        : 0;
                       
        return max(currSkip, currTake);
    }
    
    // O(N*K) & O(N*K)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, const vector<int>& cost, int i, int k) {
        if(i == n || k == 0)
            return 0;
            
        if(dp[i][k] != -1)
            return dp[i][k];
        
        int currSkip = solveWithMemo(dp, nums, cost, i + 1, k);
        int currTake = cost[i] <= k 
                        ? nums[i] + solveWithMemo(dp, nums, cost, i, k - cost[i])
                        : 0;
                       
        return dp[i][k] = max(currSkip, currTake);
    }
    
    // O(N*N*K) & O(N*K)
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& nums, const vector<int>& cost, int start, int k) {
        if(start == n || k == 0)
            return 0;
            
        if(dp[start][k] != -1)
            return dp[start][k];
        
        int maxSum = 0;
        
        for(int i = start; i < n; ++i) {
            int currTake = cost[i] <= k 
                            ? nums[i] + solveWithMemoLoop(dp, nums, cost, i, k - cost[i])
                            : 0;
            maxSum = max(maxSum, currTake);
        }
            
        return dp[start][k] = maxSum;
    }
    
public:
    int unboundedKnapsack(vector<int>& nums, vector<int>& cost, int k) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return solveWithMemo(dp, nums, cost, 0, k);
    }
};
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N*GK) & O(N*GK) : Where GK = given_k
    int solveBy2DTable(const vector<int>& nums, const vector<int>& cost, int given_k) {
        vector<vector<int>> dp(n + 1, vector<int>(given_k + 1, -1));
        
        for(int k = 0; k <= given_k; ++k) 
            dp[n][k] = 0; // if(i == n) return 0
        
        for(int i = 0; i <= n; ++i) 
            dp[i][0] = 0; // if(k == 0) return 0
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 1; k <= given_k; ++k) {
                int currSkip = dp[i + 1][k];
                int currTake = cost[i] <= k 
                                ? nums[i] + dp[i][k - cost[i]]
                                : 0;
                dp[i][k] = max(currSkip, currTake);  
            }
        }
        
        return dp[0][given_k];
    }
    
    // O(N*GK) & O(N*GK) : Where GK = given_k
    int solveBy2DEnhanced(const vector<int>& nums, const vector<int>& cost, int given_k) {
        vector<vector<int>> dp(n + 1, vector<int>(given_k + 1, 0));
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 1; k <= given_k; ++k) {
                int currSkip = dp[i + 1][k];
                int currTake = cost[i] <= k 
                                ? nums[i] + dp[i][k - cost[i]]
                                : 0;
                dp[i][k] = max(currSkip, currTake);  
            }
        }
        
        return dp[0][given_k];
    }
    
    // O(N*GK) & O(GK) : Where GK = given_k
    int solveBy1DTable(const vector<int>& nums, const vector<int>& cost, int given_k) {
        vector<int> nextRow(given_k + 1, 0), idealRow(given_k + 1, 0); 
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 1; k <= given_k; ++k) {
                int currSkip = nextRow[k];
                int currTake = cost[i] <= k 
                                ? nums[i] + idealRow[k - cost[i]]
                                : 0;
                idealRow[k] = max(currSkip, currTake);  
            }
            swap(nextRow, idealRow);
        }
        
        return nextRow[given_k];
    }
    
public:
    int unboundedKnapsack(vector<int>& nums, vector<int>& cost, int k) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return solveBy1DTable(nums, cost, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.codingninjas.com/studio/problems/unbounded-unboundedKnapsack_1215029
        https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
