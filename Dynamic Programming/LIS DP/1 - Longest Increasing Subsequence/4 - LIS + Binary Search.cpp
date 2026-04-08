// Code to find the length of the longest strictly increasing subsequence ~ coded by vHiren
    
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BinarySearch {
    // O(NLogN) & O(N)
    int solveWith1DTable(vector<int>& nums) {
        const int n = nums.size();

        // This array doesn't necessarily store the values of the LIS in the correct temp. 
        // This is due to updates made during the binary search. 
        // However, it will correctly provide the length of the actual LIS
        vector<int> temp; 

        for(const int val : nums) {
            if(temp.empty() || temp.back() < val) {
                temp.push_back(val);
            }
            else {
                int i  = lower_bound(begin(temp), end(temp), val) - begin(temp);
                temp[i] = val;
            }
        }

        return temp.size();
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
                int i   = lower_bound(begin(nums), begin(nums) + len, val) - begin(nums);
                nums[i] = val;
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
