// Code to determine if you can partition the array into two subsets such that the sum of the elements in both the subsets is equal ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, arrSum;

    void precomputeSubsetSumK(vector<vector<int>>& dp, const vector<int>& nums) {
        dp.resize(n + 1, vector<int>(arrSum + 1, -1));

        for(int k = 0; k <= arrSum; ++k)
            dp[n][k] = (k == 0) ? true : false;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= arrSum; ++k) {
                bool currTake = (k - nums[i] < 0) ? false : dp[i + 1][k - nums[i]];
                bool currSkip = dp[i + 1][k];
                dp[i][k] = (currTake || currSkip);  
            }
        }
    }

public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    bool canPartition(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<int>> dp;
        precomputeSubsetSumK(dp, nums);

        for(int subset1Sum = 0; subset1Sum <= arrSum / 2; ++subset1Sum) {
            bool isPresent = dp[0][subset1Sum];
            
            if(isPresent) { // If subset1 is present is array 'nums'
                int subset2Sum = arrSum - subset1Sum;
                if(subset1Sum == subset2Sum) return true;
            }
        }

        return false;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/partition-equal-subset-sum/description/
