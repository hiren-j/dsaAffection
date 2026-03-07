// Code to find the number of different expressions that you can build using specified way such that they evaluates to target ~ coded by vHiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n, arrSum;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, int sum, int target) {
        if(i == n)
            return (sum == target) ? 1 : 0;

        int add = solveWithoutMemo(nums, i + 1, sum + nums[i], target);
        int sub = solveWithoutMemo(nums, i + 1, sum - nums[i], target);

        return add + sub;
    }

    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int sum, int target) {
        if(i == n)
            return (sum == target) ? 1 : 0;

        if(dp[i][sum + arrSum] != c)
            return dp[i][sum + arrSum];

        int add = solveWithMemo(dp, nums, i + 1, sum + nums[i], target);
        int sub = solveWithMemo(dp, nums, i + 1, sum - nums[i], target);

        return dp[i][sum + arrSum] = add + sub;
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        vector<vector<int>> dp(n, vector<int>(arrSum * 2 + 1, -1));
        return solveWithMemo(dp, nums, 0, 0, target);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n, arrSum;
    
    // O(N*AS) & O(N*AS) : Where AS = arrSum
    int solveBy2DTable(const vector<int>& nums, int target) {
        vector<vector<int>> dp(n + 1, vector<int>(arrSum * 2 + 1, INT_MAX));

        for(int sum = -arrSum; sum <= arrSum; ++sum)
            dp[n][sum + arrSum] = (sum == target) ? 1 : 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int sum = -arrSum; sum <= arrSum; ++sum) {
                int newIdx1 = sum + nums[i] + arrSum;
                int newIdx2 = sum - nums[i] + arrSum;
                int add = (newIdx1 >= 0 && newIdx1 <= arrSum * 2) ? dp[i + 1][newIdx1] : 0;
                int sub = (newIdx2 >= 0 && newIdx2 <= arrSum * 2) ? dp[i + 1][newIdx2] : 0;
                dp[i][sum + arrSum] = add + sub;
            }
        }

        return dp[0][0 + arrSum];
    }

    // O(N*AS) & O(AS) : Where AS = arrSum
    int solveBy1DTable(const vector<int>& nums, int target) {
        vector<int> nextRow(arrSum * 2 + 1, INT_MAX); // i + 1th row

        for(int sum = -arrSum; sum <= arrSum; ++sum)
            nextRow[sum + arrSum] = (sum == target) ? 1 : 0;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(arrSum * 2 + 1, INT_MAX); // ith row

            for(int sum = -arrSum; sum <= arrSum; ++sum) {
                int newIdx1 = sum + nums[i] + arrSum;
                int newIdx2 = sum - nums[i] + arrSum;
                int add = (newIdx1 >= 0 && newIdx1 <= arrSum * 2) ? nextRow[newIdx1] : 0;
                int sub = (newIdx2 >= 0 && newIdx2 <= arrSum * 2) ? nextRow[newIdx2] : 0;
                currRow[sum + arrSum] = add + sub;
            }

            swap(nextRow, currRow);
        }

        return nextRow[0 + arrSum];
    }

public:
    int findTargetSumWays(vector<int>& nums, int target) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        return solveBy1DTable(nums, target);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Backtracking 
Link  : https://leetcode.com/problems/target-sum/description/?envType=list&envId=50vif4uc
