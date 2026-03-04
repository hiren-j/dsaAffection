// Code to count the total number of partitions in which sum1 is greater than or equal to sum2 and the difference between sum1 and sum2 is equal to given difference ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int index, int target) {
        if(index == 0) {
            if(target == 0) 
                return (nums[0] == 0) ? 2 : 1;
            else
                return (nums[0] == target);
        }

        if(target < 0)
            return 0;

        if(dp[index][target] != -1)
            return dp[index][target];

        int currSkip = solveWithMemo(dp, nums, index - 1, target);
        int currTake = solveWithMemo(dp, nums, index - 1, target - nums[index]);

        return dp[index][target] = (currSkip + currTake);
    }

public:
    // O(N*TS) & O(N*TS) : Where TS = totalSum
    int countPartitions(vector<int>& nums, int difference) {
        int n = nums.size();
        int resCount = 0;
        int totalSum = accumulate(begin(nums), end(nums), 0);

        vector<vector<int>> dp(n, vector<int>(totalSum + 1, -1));

        for(int subset1Sum = totalSum/2; subset1Sum <= totalSum; ++subset1Sum) {
            int countSubsets = solveWithMemo(dp, nums, n-1, subset1Sum);
            int subset2Sum   = totalSum - subset1Sum;
            if(subset1Sum >= subset2Sum && subset1Sum - subset2Sum == difference) {
                resCount += countSubsets;
            }
        }

        return resCount;
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, arrSum;
    
    void precomputeCountOfSubsetsSumK(vector<vector<int>>& dp, const vector<int>& arr) {
        dp.resize(n + 1, vector<int>(arrSum + 1, -1));
        
        for(int k = 0; k <= arrSum; ++k)
            dp[n][k] = (k == 0) ? 1 : 0;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= arrSum; ++k) {
                int currTake = (k - arr[i] < 0) ? 0 : dp[i + 1][k - arr[i]];
                int currSkip = dp[i + 1][k];
                dp[i][k] = (currTake + currSkip);
            }
        }
    }
    
public:
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int countPartitions(vector<int>& arr, int D) {
        n = arr.size();
        arrSum = accumulate(begin(arr), end(arr), 0);
        
        vector<vector<int>> dp;
        precomputeCountOfSubsetsSumK(dp, arr);
        
        int result = 0;
        
        for(int subset1Sum = arrSum; subset1Sum >= arrSum / 2; --subset1Sum) {
            int countSubsets = dp[0][subset1Sum];
            int subset2Sum   = arrSum - subset1Sum;
            if(subset1Sum - subset2Sum == D) {
                result += countSubsets;
            }
        }
        
        return result;
    }
};
// Note: To optimize bottom up then you could fetch solveBy1DTable() code from problem - Subset Sum Equal To K

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/partitions-with-given-difference/1 
