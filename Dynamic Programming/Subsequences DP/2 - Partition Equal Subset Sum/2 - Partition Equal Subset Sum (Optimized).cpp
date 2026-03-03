// Code to determine if you can partition the array into two subsets such that the sum of the elements in both the subsets is equal ~ coded by vHiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

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
        int arrSum = accumulate(begin(nums), end(nums), 0);
        
        if(arrSum % 2 != 0)
            return false; 

        int subset1Sum = arrSum / 2;
        vector<vector<int>> dp(n, vector<int>(subset1Sum + 1, -1));
        return solveWithMemo(dp, nums, 0, subset1Sum);
    }
};
    
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    bool canPartition(vector<int>& nums) {
        const int n = nums.size();
        int arrSum = accumulate(begin(nums), end(nums), 0);
        
        if(arrSum % 2 != 0)
            return false; 

        int subset1Sum = arrSum / 2;
        vector<vector<int>> dp(n + 1, vector<int>(subset1Sum + 1, -1));
        
        for(int k = 0; k <= subset1Sum; ++k)
            dp[n][k] = (k == 0) ? true : false;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= subset1Sum; ++k) {
                bool currTake = (k - nums[i] < 0) ? false : dp[i + 1][k - nums[i]];
                bool currSkip = dp[i + 1][k];
                dp[i][k] = (currTake || currSkip);  
            }
        }

        return (dp[0][subset1Sum] == true);
    }
};
// Note: To optimize bottom up then you could fetch solveBy1DTable() code from problem - Subset Sum Equal To K

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://leetcode.com/problems/partition-equal-subset-sum/description/
        https://www.geeksforgeeks.org/problems/subset-sum-problem2014/1
