// Code to find the longest increasing subsequence of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N)
    vector<int> getLIS(vector<int>& nums) {
        const int n = nums.size();

        vector<int> LIS(n, 1);
        vector<int> jumpIndex(n);

        int maxElement = -1;
        int curr = -1;

        for(int i = 0; i < n; ++i) {
            jumpIndex[i] = i;

            for(int prev = 0; prev < i; ++prev) {
                if(nums[i] > nums[prev] && LIS[prev] + 1 > LIS[i]) {
                    LIS[i]       = LIS[prev] + 1;
                    jumpIndex[i] = prev;
                }
            }
            
            if(LIS[i] > maxElement) { // Find index of maxElement
                maxElement = LIS[i];
                curr = i;
            }
        }
        
        vector<int> answer;
        
        while(curr != jumpIndex[curr]) {
            answer.push_back(nums[curr]);
            curr = jumpIndex[curr];
        }
        
        answer.push_back(nums[curr]);
        reverse(begin(answer), end(answer));
        return answer;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence/1
