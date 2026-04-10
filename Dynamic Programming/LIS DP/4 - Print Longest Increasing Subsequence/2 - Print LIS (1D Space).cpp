// Code to find the longest increasing subsequence of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N) 
    vector<int> getLIS(vector<int>& nums) {
        const int n = nums.size();

        vector<int> LIS(n, 1); 
        vector<int> sequence(n, -1); // sequence[i] represents the index of the recently seen value which is considered as the part of the LIS ending at that index

        for(int i = 0; i < n; ++i) {   
            sequence[i] = i;

            for(int prev = 0; prev < i; ++prev) {
                if(nums[prev] < nums[i] && LIS[prev] + 1 > LIS[i]) {
                    LIS[i]      = max(LIS[i], LIS[prev] + 1);
                    sequence[i] = prev;
                }
            }
        }

        // Find index where length of LIS is stored
        int lengthOfLIS = -1; 
        int idx = -1; 

        for(int i = 0; i < n; ++i) {
            if(LIS[i] > lengthOfLIS) {
                lengthOfLIS = LIS[i];
                idx = i;
            }
        }

        vector<int> answer;

        while(idx != sequence[idx]) {
            answer.push_back(nums[idx]);
            idx = sequence[idx];
        }
        answer.push_back(nums[idx]);
        reverse(begin(answer), end(answer));
        return answer;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence/1
