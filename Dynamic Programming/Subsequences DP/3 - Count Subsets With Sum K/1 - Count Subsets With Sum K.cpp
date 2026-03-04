// Code to find the count of all the subsets of the given array with a sum equal to the given sum ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int i, int k) {
        // Edge case: If you reached the 0th index then compute the count of all the subsets according to their existence
        if(i == 0) {
            if(k == 0) 
                return (nums[i] == 0) ? 2 : 1;
            else
                return (nums[i] == k) ? 1 : 0;
        }
            
        int currSkip = solveWithoutMemo(nums, i - 1, k); 
        int currTake = 0;                                                    
        
        if(nums[i] <= k)
            currTake = solveWithoutMemo(nums, i - 1, k - nums[i]);

        return (currTake + currSkip);
    }
    
    // O(N*K) & O(N*K)
    int solveWithMemo(vector<vector<int>>& dp, vector<int>& nums, int i, int k) {
        if(i == 0) {
            if(k == 0) 
                return (nums[i] == 0) ? 2 : 1;
            else
                return (nums[i] == k) ? 1 : 0;
        }
        
        if(dp[i][k] != -1)
            return dp[i][k];
            
        int currSkip = solveWithMemo(dp, nums, i - 1, k); 
        int currTake = 0;                                                    
        
        if(nums[i] <= k)
            currTake = solveWithMemo(dp, nums, i - 1, k - nums[i]);

        return dp[i][k] = (currTake + currSkip);
    }
    
public:
    int perfectSum(vector<int>& nums, int sum) {
        const int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return solveWithMemo(dp, nums, n - 1, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N*GK) & O(N*GK) : Where GK = given_k
    int solveBy2DTable(const vector<int>& nums, int given_k) {
        vector<vector<int>> dp(n, vector<int>(given_k + 1, -1));
        
        for(int k = 0; k <= given_k; ++k) {
            if(k == 0) 
                dp[0][k] = (nums[0] == 0) ? 2 : 1;
            else
                dp[0][k] = (nums[0] == k) ? 1 : 0;
        }
        
        for(int i = 1; i < n; ++i) {
            for(int k = 0; k <= given_k; ++k) {
                int currSkip = dp[i - 1][k]; 
                int currTake = 0;                                                    
                
                if(nums[i] <= k)
                    currTake = dp[i - 1][k - nums[i]];
        
                dp[i][k] = (currTake + currSkip);
            }
        }
        
        return dp[n - 1][given_k];
    }
    
    // O(N*GK) & O(GK) : Where GK = given_k
    int solveBy1DTable(const vector<int>& nums, int given_k) {
         vector<int> prevRow(given_k + 1, -1); // i - th row
        
        for(int k = 0; k <= given_k; ++k) {
            if(k == 0) 
                prevRow[k] = (nums[0] == 0) ? 2 : 1;
            else
                prevRow[k] = (nums[0] == k) ? 1 : 0;
        }
        
        for(int i = 1; i < n; ++i) {
            vector<int> currRow(given_k + 1, -1); // ith row
            
            for(int k = 0; k <= given_k; ++k) {
                int currSkip = prevRow[k]; 
                int currTake = 0;                                                    
                
                if(nums[i] <= k)
                    currTake = prevRow[k - nums[i]];
        
                currRow[k] = (currTake + currSkip);
            }
            
            swap(prevRow, currRow);
        }
        
        return prevRow[given_k];
    }
    
public:
    int perfectSum(vector<int>& nums, int k) {
        n = nums.size();
        return solveBy1DTable(nums, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1
        https://www.naukri.com/code360/problems/count-subsets-with-sum-k_3952532
