// Code to count the total number of partitions in which sum1 is greater than or equal to sum2 and the difference between sum1 and sum2 is equal to given difference ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, arrSum;
    
    // O(N*K) & O(N*K)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int k) {
        if(k < 0)
            return 0;
        
        if(i == n)
            return (k == 0) ? 1 : 0;
            
        if(dp[i][k] != -1)
            return dp[i][k];
            
        int currTake = solveWithMemo(dp, nums, i + 1, k - nums[i]);
        int currSkip = solveWithMemo(dp, nums, i + 1, k);
        
        return dp[i][k] = (currTake + currSkip);
    }
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int countPartitions(vector<int>& nums, int D) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        
        if(D > arrSum || (arrSum + D) % 2 != 0)
            return 0;
        
        vector<vector<int>> dp(n, vector<int>(arrSum + 1, -1));
        
        int subset1Sum   = (arrSum + D) / 2;
        int countSubsets = solveWithMemo(dp, nums, 0, subset1Sum);
        return countSubsets;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, arrSum;
    
    void precomputeCountOfSubsetsSumK(vector<vector<int>>& dp, const vector<int>& nums) {
        dp.resize(n + 1, vector<int>(arrSum + 1, -1));
        
        for(int k = 0; k <= arrSum; ++k)
            dp[n][k] = (k == 0) ? 1 : 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= arrSum; ++k) {
                int currTake = (k - nums[i] < 0) ? 0 : dp[i + 1][k - nums[i]];
                int currSkip = dp[i + 1][k];
                dp[i][k] = (currTake + currSkip);
            }
        }
    }
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int countPartitions(vector<int>& nums, int D) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        
        if(D > arrSum || (arrSum + D) % 2 != 0)
            return 0;
        
        vector<vector<int>> dp;
        precomputeCountOfSubsetsSumK(dp, nums);
        
        int subset1Sum   = (arrSum + D) / 2;
        int countSubsets = dp[0][subset1Sum];
        return countSubsets;
    }
};
// Note: To optimize bottom up then you could fetch solveBy1DTable() code from problem - Count Subsets With Sum K

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1 
