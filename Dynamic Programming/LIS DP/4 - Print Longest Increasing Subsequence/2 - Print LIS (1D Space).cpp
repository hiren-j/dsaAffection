// Code to find the longest increasing subsequence of the given array ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
public:
    // O(N*N) & O(N) 
    vector<int> getLIS(vector<int>& nums) {
        const int n = nums.size();

        vector<int> LIS(n, 1); 
        vector<int> prevIndex(n, -1);

        for(int i = 0; i < n; ++i) {   
            prevIndex[i] = i;

            for(int prev = 0; prev < i; ++prev) {
                if(nums[prev] < nums[i] && LIS[prev] + 1 > LIS[i]) {
                    LIS[i]       = max(LIS[i], LIS[prev] + 1);
                    prevIndex[i] = prev;
                }
            }
        }

        int arrayLIS = -1; 
        int curr = -1; 
        
        for(int i = 0; i < n; ++i) {
            if(LIS[i] > arrayLIS) {
                arrayLIS = LIS[i];
                curr = i;
            }
        }

        vector<int> answer;
        
        while(curr != prevIndex[curr]) {
            answer.push_back(nums[curr]);
            curr = prevIndex[curr];
        }
        answer.push_back(nums[curr]);
        reverse(begin(answer), end(answer));
        return answer;
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/printing-longest-increasing-subsequence/1
