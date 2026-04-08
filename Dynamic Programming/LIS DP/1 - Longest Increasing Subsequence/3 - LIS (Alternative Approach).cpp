// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren

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
