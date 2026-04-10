// Code to find the longest increasing subsequence of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N*N)
    vector<int> getLIS(vector<int>& nums) {
        const int n = nums.size();
  
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
    
        int i = 0, prev = n;
        vector<int> LIS;
        
        while(i < n) {
            if((prev == n || nums[prev] < nums[i])) {
                if(dp[i + 1][i] + 1 >= dp[i][prev]) {
                    LIS.push_back(nums[i]);
                    prev = i;
                }
            }
            i = i + 1;
        }
        
        return LIS;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence/1
