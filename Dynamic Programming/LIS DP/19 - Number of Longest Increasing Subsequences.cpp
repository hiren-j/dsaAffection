// Code to find the number of longest increasing subsequences. Notice that the sequence has to be strictly increasing ~ coded by vHiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N)
    int findNumberOfLIS(vector<int>& nums) {
        const int n = nums.size();

        vector<int> LIS(n, 1), count(n, 1); 

        for(int i = 0; i < n; ++i) {
            for(int prev = 0; prev < i; ++prev) {
                if(nums[prev] < nums[i]) {
                    if(LIS[prev] + 1 > LIS[i]) {
                        LIS[i]   = LIS[prev] + 1; 
                        count[i] = count[prev];
                    }
                    else if(LIS[prev] + 1 == LIS[i]) {
                        count[i] += count[prev];
                    }
                }
            }
        }

        int maxElement = *max_element(begin(LIS), end(LIS));
        int countOfLIS  = 0;

        for(int i = 0; i < n; ++i) 
            if(LIS[i] == maxElement) 
                countOfLIS += count[i];

        return countOfLIS;   
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming 
Link  : https://leetcode.com/problems/number-of-longest-increasing-subsequence/description/
