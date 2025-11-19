// Code to find the minimum possible total cost incurred before the Geek reaches the nth stone, the Geek can jump to any one of the following, stone + 1, stone + 2, ... stone + K stone and cost will be [hi - hj] is incurred, where jump is the stone to land on ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(K^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, const int k, int index) {
        if(index == n-1)
            return 0; // If reached last stone, return 0 as indication
        
        int minCost = INT_MAX;
        
        for(int jump = 1; (jump <= k && index + jump < n); ++jump) { // Try each possible jump from the index
            int jumpCost = abs(nums[index + jump] - nums[index]);
            int nextCost = solveWithoutMemo(nums, k, index + jump);
            int currPathCost = jumpCost + nextCost;
            minCost = min(minCost, currPathCost);
        }
        
        return minCost;
    }
    
    // O(K*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, const int k, int index) {
        if(index == n-1)
            return 0; // If reached last stone, return 0 as indication
            
        if(dp[index] != -1)
            return dp[index];
        
        int minCost = INT_MAX;
        
        for(int jump = 1; (jump <= k && index + jump < n); ++jump) { // Try each possible jump from the index
            int jumpCost = abs(nums[index + jump] - nums[index]);
            int nextCost = solveWithMemo(dp, nums, k, index + jump);
            int currPathCost = jumpCost + nextCost;
            minCost = min(minCost, currPathCost);
        }
        
        return dp[index] = minCost;
    }
    
public:
    int minimizeCost(int k, vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n-1, -1);
        return solveWithMemo(dp, nums, k, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*K) & O(N)
    int minimizeCost(const int k, const vector<int>& nums) {
        int n = nums.size();
        
        vector<int> dp(n, -1);
        dp[n - 1] = 0; // Initialize edge case
        
        for(int index = n-2; index >= 0; --index) {
            int minCost = INT_MAX;
            
            for(int jump = 1; (jump <= k && index + jump < n); ++jump) {
                int jumpCost = abs(nums[index + jump] - nums[index]);
                int nextCost = dp[index + jump];
                int currPathCost = jumpCost + nextCost;
                minCost = min(minCost, currPathCost);
            }
            
            dp[index] = minCost;
        }
        
        return dp[0];
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/minimal-cost/1
