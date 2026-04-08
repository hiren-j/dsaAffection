// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpBruteForce {
public:
    int lengthOfLIS(vector<int>& nums) {
        const int n = nums.size();
        
        vector<int> dp(n, 1);

        for(int i = 0; i < n; ++i) {
            for(int prev = 0; prev < i; ++prev) {
                if(nums[i] > nums[prev]) {
                    dp[i] = max(dp[i], dp[prev] + 1);
                }
            }
        }

        return *max_element(begin(dp), end(dp));
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BinarySearch {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size();

        // This array doesn't necessarily store the values of the LIS in the correct order. This is due to updates made during the binary search. However, it will correctly provide the length of the actual LIS
        vector<int> LIS; 
        LIS.push_back(nums[0]);

        for(int num : nums) {
            // If the last element of the "LIS" array is lesser than the current element of the "nums" array then push the current element to the "LIS" array
            if(LIS.back() < num) {
                LIS.push_back(num);
            }
            // Else then find the index of the just greater element of the current element and then replace the value lying in the "LIS" array by the current element
            else {
                int i  = lower_bound(begin(LIS), end(LIS), num) - begin(LIS);
                LIS[i] = num;
            }
        }

        // Return the length of the LIS
        return LIS.size();
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
