// Code to find the minimum number of jumps to reach the last index of the array ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class TopDown {
    int n;    

    // O(M^N) & O(N) : Where M = maximum element of array
    int solveWithoutMemo(vector<int>& nums, int index) {
        if(index == n-1)
            return 0;
        
        int minJumps = INT_MAX;

        for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
            int nextJumps = solveWithoutMemo(nums, index + jump);
            
            if(nextJumps != INT_MAX) { 
                minJumps = min(minJumps, nextJumps + 1); // Update result if you reached the last index
            }
        }

        return minJumps;
    }

    // O(M*N) & O(2*N) : Where M = maximum element of array
    int solveWithMemo(vector<int>& dp, vector<int>& nums, int index) {
        if(index == n-1)
            return 0;

        if(dp[index] != -1)
            return dp[index];
        
        int minJumps = INT_MAX;

        for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
            int nextJumps = solveWithMemo(dp, nums, index + jump);
            
            if(nextJumps != INT_MAX) {
                minJumps = min(minJumps, nextJumps + 1); // Update result if you reached the last index
            }
        }

        return dp[index] = minJumps;
    }

public:
    int minJumpsToLastIndex(vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n-1, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp {
public:
    // O(N*M) & O(1*N) : Where M = maximum element of array
    int minJumpsToLastIndex(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> dp(n, -1);
        dp[n - 1] = 0;

        for(int index = n-2; index >= 0; --index) {
            int minJumps = INT_MAX;

            for(int jump = 1; (jump <= nums[index] && index + jump < n); ++jump) {
                int nextJumps = dp[index + jump];
                
                if(nextJumps != INT_MAX) {
                    minJumps = min(minJumps, nextJumps + 1);
                }
            }

            dp[index] = minJumps; 
        }

        return dp[0];
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Greedy
Link  : https://leetcode.com/problems/jump-game-ii/description/
