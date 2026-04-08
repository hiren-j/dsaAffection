// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpBrute {
public:
    // O(N*N) & O(N)
    int lengthOfLIS(vector<int>& nums) {
        const int n = nums.size();
        int maxLen = 0;
        
        vector<int> dp(n, 1);

        for(int i = 0; i < n; ++i) {
            for(int prev = 0; prev < i; ++prev) {
                if(nums[i] > nums[prev]) {
                    dp[i] = max(dp[i], dp[prev] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        return maxLen;
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BinarySearch {
public:
    // O(NLogN) & O(N)
    int lengthOfLIS(vector<int>& nums) {
        const int n = nums.size();

        // This array doesn't necessarily store the values of the LIS in the correct ans. 
        // This is due to updates made during the binary search. 
        // However, it will correctly provide the length of the actual LIS
        vector<int> ans; 
        ans.push_back(nums[0]);

        for(const int val : nums) {
            if(ans.back() < val) {
                ans.push_back(val);
            }
            else {
                int i  = lower_bound(begin(ans), end(ans), val) - begin(ans);
                ans[i] = val;
            }
        }

        return ans.size();
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
