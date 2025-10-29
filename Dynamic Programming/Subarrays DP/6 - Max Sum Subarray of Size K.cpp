// Code to find the maximum sum of a subarray among all the subarrays of size k ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
        
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int k) {
        if(k == 0 || i == n)
            return 0;
                        
        if(prevPick) {
            int pickCurr = nums[i] + solveWithoutMemo(dp, nums, i + 1, true, k - 1);
            int stopHere = 0;
            return max(pickCurr, stopHere);
        }
        else {
            int startHere = nums[i] + solveWithoutMemo(dp, nums, i + 1, true, k - 1);
            int startNext = solveWithoutMemo(dp, nums, i + 1, false, k);
            return max(startHere, startNext);
        }
    }
    
    // O(2*N*2*K) & O(N*2*K + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int k) {
        if(k == 0 || i == n)
            return 0;
            
        if(dp[i][prevPick][k] != -1)
            return dp[i][prevPick][k]; 
            
        if(prevPick) {
            int pickCurr = nums[i] + solveWithMemo(dp, nums, i + 1, true, k - 1);
            int stopHere = 0;
            return dp[i][prevPick][k] = max(pickCurr, stopHere);
        }
        else {
            int startHere = nums[i] + solveWithMemo(dp, nums, i + 1, true, k - 1);
            int startNext = solveWithMemo(dp, nums, i + 1, false, k);
            return dp[i][prevPick][k] = max(startHere, startNext);
        }
    }

public:
    // Method to find maximum sum of a subarray of size k, using recursion with memoization - O(N*K) & O(N*K)
    int maxSumSubarrSizeK(vector<int>& nums, int k) {
        n = nums.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solveWithMemo(dp, nums, 0, false, k);
    }
};
// Note: This solution will lead to time limit exceed

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(N*2*K) & O(N*2*K) : Where K = given_K
    int solveBy3DTable(const vector<int>& nums, int given_k) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(given_k + 1, -1)));
        
        // Init edge case (k == 0)
        for(int i = 0; i <= n; ++i) 
            for(int prevPick = 0; prevPick <= 1; ++prevPick)
                dp[i][prevPick][0] = 0;
        
        // Init edge case (i == n)
        for(int prevPick = 0; prevPick <= 1; ++prevPick) 
            for(int k = 0; k <= given_k; ++k)
                dp[n][prevPick][k] = 0;
                
        for(int i = n-1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int k = 1; k <= given_k; ++k) {
                    if(prevPick) {
                        int pickCurr = nums[i] + dp[i + 1][true][k - 1];
                        int stopHere = 0;
                        dp[i][prevPick][k] = max(pickCurr, stopHere);
                    }
                    else {
                        int startHere = nums[i] + dp[i + 1][true][k - 1];
                        int startNext = dp[i + 1][false][k];
                        dp[i][prevPick][k] = max(startHere, startNext);
                    }
                }
            }
        }
        
        return dp[0][false][given_k];
    }
    
    // O(N*2*K) & O(N*2*K) : Where K = given_K
    int solveBy3DEnhanced(const vector<int>& nums, int given_k) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(given_k + 1, 0)));
        
        for(int i = n-1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int k = 1; k <= given_k; ++k) {
                    if(prevPick) {
                        int pickCurr = nums[i] + dp[i + 1][true][k - 1];
                        int stopHere = 0;
                        dp[i][prevPick][k] = max(pickCurr, stopHere);
                    }
                    else {
                        int startHere = nums[i] + dp[i + 1][true][k - 1];
                        int startNext = dp[i + 1][false][k];
                        dp[i][prevPick][k] = max(startHere, startNext);
                    }
                }
            }
        }
        
        return dp[0][false][given_k];
    }
    
    // O(N*2*K) & O(2*2*K) : Where K = given_K
    int solveBy2DTable(const vector<int>& nums, int given_k) {
        vector<vector<int>> nextRow(2, vector<int>(given_k + 1, 0));
        
        for(int i = n-1; i >= 0; --i) {
            vector<vector<int>> idealRow(2, vector<int>(given_k + 1, 0));
            
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int k = 1; k <= given_k; ++k) {
                    if(prevPick) {
                        int pickCurr = nums[i] + nextRow[true][k - 1];
                        int stopHere = 0;
                        idealRow[prevPick][k] = max(pickCurr, stopHere);
                    }
                    else {
                        int startHere = nums[i] + nextRow[true][k - 1];
                        int startNext = nextRow[false][k];
                        idealRow[prevPick][k] = max(startHere, startNext);
                    }
                }
            }
            
            swap(nextRow, idealRow);
        }
        
        return nextRow[false][given_k];
    }
        
public:
    int maxSumSubarrSizeK(vector<int>& nums, int k) {
        n = nums.size();
        return solveBy2DTable(nums, k);
    }
};
// Note: This solution will lead to time limit exceed

--------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BruteForce {
public:
    // Method to find maximum sum of a subarray of size k, using brute force approach - O(N*K) & O(1)
    int maxSumSubarrSizeK(vector<int>& nums, int k) {
        int n = nums.size();
        int subarrSum, maxSum = 0;
        
        for(int i = 0; i <= n-k; ++i) {
            subarrSum = 0;
            for(int j = i; j < i+k; ++j) {
                subarrSum += nums[j];
            }
            maxSum = max(maxSum, subarrSum);
        }
        
        return maxSum;
    }
};
// Note: This approach is taking less than 10^6 iterations in the worst case and that's the reason its getting accepted, else it's not possible. However still looking at the majors we must consider the time complexity to be O(N*K)

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class SlidingWindow {
public:
    // Method to find maximum sum of a subarray of size k, using sliding window technique - O(N) & O(1)
    int maxSumSubarrSizeK(vector<int>& nums, int k) {
        int n = nums.size();
        int i = 0, j = 0;
        int subarrSum = 0, maxSum = 0;
        
        while(j < n) {
            subarrSum += nums[j];
            
            // If window size is equal to k then update result and shrink window from left
            if(j-i+1 == k) { 
                maxSum = max(maxSum, subarrSum);
                subarrSum -= nums[i]; 
                i++;
            }
            
            j++;
        }
        
        return maxSum;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Sliding Window
Link  : https://www.geeksforgeeks.org/problems/max-sum-subarray-of-size-k5313/1
