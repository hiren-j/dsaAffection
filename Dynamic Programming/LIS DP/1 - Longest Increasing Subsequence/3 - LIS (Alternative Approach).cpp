// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(N*N) & O(N)
    int solveWithMemo(vector<int>& LIS, const vector<int>& nums, int i) {
        if(LIS[i] != -1)
            return LIS[i];

        int maxLen = 1;

        for(int prev = 0; prev < i; ++prev) {
            if(nums[i] > nums[prev]) {
                int lisLenPrevSide = solveWithMemo(LIS, nums, prev) + 1;
                maxLen = max(maxLen, lisLenPrevSide);
            }
        }

        return LIS[i] = maxLen;
    }

public:
    int lengthOfLIS(vector<int>& nums) { 
        int n = nums.size(), res = 0;
        
        vector<int> LIS(n, -1); // dp array

        for(int i = n - 1; i >= 0; --i) {
            res = max(res, solveWithMemo(LIS, nums, i));
        }

        return res;
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*N) & O(N)
    int solveBy1DTable(const vector<int>& nums) {
        vector<int> LIS(n, -1);

        for(int i = 0; i < n; ++i) {
            int maxLen = 1;

            for(int prev = 0; prev < i; ++prev) {
                if(nums[i] > nums[prev]) {
                    int lisLenPrevSide = LIS[prev] + 1;
                    maxLen = max(maxLen, lisLenPrevSide);
                }
            }

            LIS[i] = maxLen;
        }

        int res = 0;
        for(int i = n - 1; i >= 0; --i) {
            res = max(res, LIS[i]);
        }
        return res;
    }

    // O(N*N) & O(N)
    int solveBy1DEnhanced(const vector<int>& nums) {
        vector<int> LIS(n, -1);
        int res = 0;

        for(int i = 0; i < n; ++i) {
            int maxLen = 1;

            for(int prev = 0; prev < i; ++prev) {
                if(nums[i] > nums[prev]) {
                    int lisLenPrevSide = LIS[prev] + 1;
                    maxLen = max(maxLen, lisLenPrevSide);
                }
            }

            LIS[i] = maxLen;
            res = max(res, LIS[i]);
        }

        return res;
    }

public:
    int lengthOfLIS(vector<int>& nums) { 
        n = nums.size();
        return solveBy1DEnhanced(nums);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpCleanVersion {
public:
    // O(N*N) & O(N)
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), maxLen = 0;

        vector<int> LIS(n, 1);

        for(int index = 0; index < n; ++index) {
            for(int prevIndex = 0; prevIndex < index; ++prevIndex) {
                if(nums[index] > nums[prevIndex]) {
                    LIS[index] = max(LIS[index], LIS[prevIndex] + 1);
                }
            }
            maxLen = max(maxLen, LIS[index]);
        }

        return maxLen;
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
