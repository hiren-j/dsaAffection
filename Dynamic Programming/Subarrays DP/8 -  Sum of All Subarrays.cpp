// Code to find the sum of all subarrays ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int arrSum;
    int n;
    
    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int subarrSum) {
        if(i == n)
            return subarrSum;
        
        if(prevPick) {
            int pickCurr = solveWithoutMemo(nums, i + 1, true, subarrSum + nums[i]);
            int stopHere = subarrSum;
            return pickCurr + stopHere;
        }
        else {
            int startHere = solveWithoutMemo(nums, i + 1, true, subarrSum + nums[i]);
            int startNext = solveWithoutMemo(nums, i + 1, false, subarrSum);
            return startHere + startNext;
        }
    }

    // O(2*N*2*AS) & O(N*2*AS + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int subarrSum) {
        if(i == n)
            return subarrSum;
            
        if(dp[i][prevPick][subarrSum] != -1)
            return dp[i][prevPick][subarrSum]; 
        
        if(prevPick) {
            int pickCurr = solveWithMemo(dp, nums, i + 1, true, subarrSum + nums[i]);
            int stopHere = subarrSum;
            return dp[i][prevPick][subarrSum] = pickCurr + stopHere;
        }
        else {
            int startHere = solveWithMemo(dp, nums, i + 1, true, subarrSum + nums[i]);
            int startNext = solveWithMemo(dp, nums, i + 1, false, subarrSum);
            return dp[i][prevPick][subarrSum] = startHere + startNext;
        }
    }
    
public:
    // Method to find sum of all subarrays, using recursion with memoization - O(N*AS) & O(N*AS) : Where AS = arrSum
    int subarraySum(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(arrSum + 1, -1)));
        return solveWithMemo(dp, nums, 0, false, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int arrSum;
    int n;

    // O(N*2*AS) & O(N*2*AS) : Where AS = arrSum
    int solveBy3DTable(const vector<int>& nums) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(arrSum + 1, -1)));
        
        for(int prevPick = 0; prevPick <= 1; ++prevPick) // Init edge case
            for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                dp[n][prevPick][subarrSum] = subarrSum;
            
        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                    if(prevPick) {
                        int newSum   = subarrSum + nums[i];
                        int pickCurr = (newSum <= arrSum) ? dp[i + 1][true][subarrSum + nums[i]] : 0;
                        int stopHere = subarrSum;
                        dp[i][prevPick][subarrSum] = pickCurr + stopHere;
                    }
                    else {
                        int newSum    = subarrSum + nums[i];
                        int startHere = (newSum <= arrSum) ? dp[i + 1][true][newSum] : 0;
                        int startNext = dp[i + 1][false][subarrSum];
                        dp[i][prevPick][subarrSum] = startHere + startNext;
                    }
                }
            }
        }
        
        return dp[0][false][0];
    }
    
    // O(N*2*AS) & O(2*2*AS) : Where AS = arrSum
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> nextRow(2, vector<int>(arrSum + 1, -1));
        
        for(int prevPick = 0; prevPick <= 1; ++prevPick) // Init edge case
            for(int subarrSum = 0; subarrSum <= arrSum; ++subarrSum)
                nextRow[prevPick][subarrSum] = subarrSum;
            
        for(int i = n - 1; i >= 0; --i) {
            vector<vector<int>> idealRow(2, vector<int>(arrSum + 1, -1));
            
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int subarrSum = arrSum; subarrSum >= 0; --subarrSum) {
                    if(prevPick) {
                        int newSum   = subarrSum + nums[i];
                        int pickCurr = (newSum <= arrSum) ? nextRow[true][subarrSum + nums[i]] : 0;
                        int stopHere = subarrSum;
                        idealRow[prevPick][subarrSum] = pickCurr + stopHere;
                    }
                    else {
                        int newSum    = subarrSum + nums[i];
                        int startHere = (newSum <= arrSum) ? nextRow[true][newSum] : 0;
                        int startNext = nextRow[false][subarrSum];
                        idealRow[prevPick][subarrSum] = startHere + startNext;
                    }
                }
            }
            
            swap(nextRow, idealRow);
        }
        
        return nextRow[false][0];
    }
    
public:
    int subarraySum(vector<int>& nums) {
        n = nums.size();
        arrSum = accumulate(begin(nums), end(nums), 0);
        return solveBy2DTable(nums);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/sum-of-subarrays2229/1
