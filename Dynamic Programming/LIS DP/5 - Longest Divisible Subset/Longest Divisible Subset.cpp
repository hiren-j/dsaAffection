// Code to find the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies: answer[i] % answer[j] == 0, or answer[j] % answer[i] == 0 ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*N) & O(N*N)
    vector<int> solveBy2DTable(vector<int>& nums) {
        const int n = nums.size();
        sort(begin(nums), end(nums));

        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j <= n; ++j) {
                int currSkip = dp[i + 1][j];
                int currTake = 0;

                if(j == n || (nums[i] % nums[j] == 0))
                    currTake = dp[i + 1][i] + 1;
                
                if(currSkip > currTake) {
                    dp[i][j] = currSkip;
                }   
                else {
                    dp[i][j] = currTake;
                }
            }
        }
        
        int i = 0, j = n;
        vector<int> answer;
        
        while(i <= n - 1 && j >= 0) {
            int currSkip = dp[i + 1][j];
            int currTake = 0;
            
            if(j == n || (nums[i] % nums[j] == 0))
                currTake = dp[i + 1][i] + 1;
            
            if(currSkip > currTake) {
                i = i + 1;
                j = j;
            }   
            else {
                if(j == n || (nums[i] % nums[j] == 0)) {
                    answer.push_back(nums[i]);
                    j = i;
                }
                i = i + 1;
            }
        }
        
        return answer;
    }

    // O(N*N) & O(N)
    vector<int> solveBy1DTable(const vector<int>& nums) {
        sort(begin(nums), end(nums));

        vector<int> LIS(n, 1);
        vector<int> jumpIndex(n);

        int maxElement = -1;
        int curr = -1;

        for(int i = 0; i < n; ++i) {
            jumpIndex[i] = i;

            for(int j = 0; j < i; ++j) {
                if(nums[i] % nums[j] == 0 && LIS[j] + 1 > LIS[i]) {
                    LIS[i] = LIS[j] + 1;
                    jumpIndex[i] = j;
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

public:
    vector<int> largestDivisibleSubset(vector<int>& nums) {
        n = nums.size();
        return solveBy1DTable(nums);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/largest-divisible-subset/description/
