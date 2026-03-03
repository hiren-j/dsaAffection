// Code to determine if you can partition the array into two subsets such that the sum of the elements in both the subsets is equal ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, arrSum;

    bool solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int k) {
        if(k < 0)
            return false;
        
        if(i == n)
            return (k == 0) ? true : false;
            
        if(dp[i][k] != -1)
            return dp[i][k];

        bool currTake = solveWithMemo(dp, nums, i + 1, k - nums[i]);
        bool currSkip = solveWithMemo(dp, nums, i + 1, k);
        
        return dp[i][k] = (currTake || currSkip);
    }

public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    bool canPartition(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<int>> dp(n, vector<int>(arrSum / 2 + 1, -1));

        for(int subset1Sum = arrSum / 2; subset1Sum >= 0; --subset1Sum) {
            if(solveWithMemo(dp, nums, 0, subset1Sum)) { // If subset1 is present is array 'nums'
                int subset2Sum = arrSum - subset1Sum;
                if(subset1Sum == subset2Sum) return true;
            }
        }

        return false;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
    int n, arrSum;

    void precomputeSubsetSumK(vector<vector<int>>& dp, const vector<int>& nums) {
        dp.resize(n + 1, vector<int>(arrSum / 2 + 1, -1));

        for(int k = 0; k <= arrSum / 2; ++k)
            dp[n][k] = (k == 0) ? true : false;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= arrSum / 2; ++k) {
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

        for(int subset1Sum = arrSum / 2; subset1Sum >= 0; --subset1Sum) {
            if(dp[0][subset1Sum]) { // If subset1 is present is array 'nums'
                int subset2Sum = arrSum - subset1Sum;
                if(subset1Sum == subset2Sum) return true;
            }
        }

        return false;
    }
};
// Note: To optimize bottom up then you could fetch solveBy1DTable() code from problem - Subset Sum Equal To K

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/partition-equal-subset-sum/description/
