// Code to divide the array into two sets S1 and S2 such that the absolute difference between their sums is as minimum as possible. So, the task is to find the minimum absolute difference ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, arrSum;

    bool solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int k) {
        if(k < 0)
            return false;
        
        if(i == n)
            return (k == 0) ? true : false;
            
        if(dp[i][k] != -1)
            return dp[i][k];

        bool currSkip = solveWithMemo(dp, nums, i + 1, k);
        bool currTake = solveWithMemo(dp, nums, i + 1, k - nums[i]);
        
        return dp[i][k] = (currSkip || currTake);
    }
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int minDifference(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        
        vector<vector<int>> dp(n + 1, vector<int>(arrSum + 1, -1));
        int minAbsDiff = INT_MAX;

        for(int subset1Sum = arrSum / 2; subset1Sum >= 0; --subset1Sum) {
            if(solveWithMemo(dp, nums, 0, subset1Sum)) { // If subset1 is present is array 'nums'
                int subset2Sum = arrSum - subset1Sum;
                minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
            }
        }

        return minAbsDiff;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, arrSum;

    void precomputeSubsetSumK(vector<vector<int>>& dp, const vector<int>& nums) {
        dp.resize(n + 1, vector<int>(arrSum / 2 + 1, -1));

        for(int k = 0; k <= arrSum / 2; ++k)
            dp[n][k] = (k == 0) ? true : false;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= arrSum / 2; ++k) {
                bool currSkip = dp[i + 1][k];
                bool currTake = (k - nums[i] < 0) ? false : dp[i + 1][k - nums[i]];
                dp[i][k] = (currSkip || currTake);  
            }
        }
    }
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int minDifference(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<int>> dp;
        precomputeSubsetSumK(dp, nums);
        
        int minAbsDiff = INT_MAX;

        for(int subset1Sum = arrSum / 2; subset1Sum >= 0; --subset1Sum) {
            if(dp[0][subset1Sum]) { // If subset1 is present is array 'nums'
                int subset2Sum = arrSum - subset1Sum;
                minAbsDiff = min(minAbsDiff, abs(subset1Sum - subset2Sum));
            }
        }

        return minAbsDiff;
    }
};
// Note: To optimize bottom up then you could fetch solveBy1DTable() code from problem - Subset Sum Equal To K

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	
Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card
		https://www.naukri.com/code360/problems/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum_842494
