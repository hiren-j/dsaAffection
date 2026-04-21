// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BinarySearch {
    // O(NLogN) & O(N)
    int solveWith1DTable(vector<int>& nums) {    
        vector<int> order; 

        for(const int val : nums) {
            if(order.empty() || order.back() < val) {
                order.push_back(val);
            }
            else {
                int pos    = lower_bound(begin(order), end(order), val) - begin(order);
                order[pos] = val;
            }
        }

        return order.size();
    }

    // O(NLogN) & O(1)
    int solveWithoutTable(vector<int>& nums) {
        int len = 0;

        for(const int val : nums) {
            if(len == 0 || nums[len - 1] < val) {
                nums[len] = val;
                len++;
            }
            else {
                int pos   = lower_bound(begin(nums), begin(nums) + len, val) - begin(nums);
                nums[pos] = val;
            }
        }

        return len;
    }

public:
    int lengthOfLIS(vector<int>& nums) {
        return solveWithoutTable(nums);
    }
};
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Binary Search | Dynamic Programming
Links : https://leetcode.com/problems/longest-increasing-subsequence/description/
        https://cses.fi/problemset/task/1145
