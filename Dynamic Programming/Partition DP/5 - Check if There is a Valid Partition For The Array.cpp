// Code to return true if the array has at least one valid partition. You have to partition the array into one or more contiguous subarrays. We call a partition of the array valid if each of the obtained subarrays satisfies one of the specified conditions ~ coded by Hiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
            
    bool isEqual(int a, int b, int c = -1) {
        return (c == -1 && a == b) || (a == b && b == c);
    }
    bool isConsecutive(int a, int b, int c) {
        return (a - b == 1 && b - c == 1);
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int start) {
        if(start == n)
            return true;

        int i = start + 1;
        if(i < n && isEqual(nums[i], nums[i - 1]) && solveWithoutMemo(nums, i + 1)) {
            return true;
        }

        i = start + 2;
        if(i < n && (isEqual(nums[i], nums[i - 1], nums[i - 2]) || 
                     isConsecutive(nums[i], nums[i - 1], nums[i - 2])) && 
                     solveWithoutMemo(nums, i + 1)) {
            return true;
        }
        
        return false;
    }

    // O(N) & O(N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int start) {
        if(start == n)
            return true;

        if(dp[start] != -1)
            return dp[start];

        int i = start + 1;
        if(i < n && isEqual(nums[i], nums[i - 1]) && solveWithMemo(dp, nums, i + 1)) {
            return dp[start] = true;
        }

        i = start + 2;
        if(i < n && (isEqual(nums[i], nums[i - 1], nums[i - 2]) || 
                     isConsecutive(nums[i], nums[i - 1], nums[i - 2])) && 
                     solveWithMemo(dp, nums, i + 1)) {
            return dp[start] = true;
        }

        return dp[start] = false;
    }

public:
    bool validPartition(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {   
    bool isEqual(int a, int b, int c = -1) {
        return (c == -1 && a == b) || (a == b && b == c);
    }
    bool isConsecutive(int a, int b, int c) {
        return (a - b == 1 && b - c == 1);
    }

public:
    // O(N) & O(N)
    bool validPartition(vector<int>& nums) {
        const int n = nums.size();

        vector<bool> dp(n + 1, false);
        dp[n] = true;
        
        for(int start = n - 1; start >= 0; --start) {
            int i = start + 1;
            if(i < n && isEqual(nums[i], nums[i - 1]) && dp[i + 1]) {
                dp[start] = true;
                continue;
            }

            i = start + 2;
            if(i < n && (isEqual(nums[i], nums[i - 1], nums[i - 2]) || 
                         isConsecutive(nums[i], nums[i - 1], nums[i - 2])) && dp[i + 1]) {
                dp[start] = true;
            }
        }

        return dp[0];
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming 
Link  : https://leetcode.com/problems/check-if-there-is-a-valid-partition-for-the-array/description/
