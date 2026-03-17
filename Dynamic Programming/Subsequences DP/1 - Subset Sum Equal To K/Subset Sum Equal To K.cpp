// Code to check whether there exists a subset in the array whose sum is equal to k ~ coded by vHiren
  
--------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {   
    int n;

    // O(2^N) & O(N)
    bool solveWithoutMemo(const vector<int>& nums, int i, int k) {
        if(k < 0)
            return false;
        
        if(i == n)
            return (k == 0) ? true : false;
            
        bool currSkip = solveWithoutMemo(nums, i + 1, k);
        bool currTake = solveWithoutMemo(nums, i + 1, k - nums[i]);
        
        return (currSkip || currTake);
    }
    
    // O(N*K) & O(N*K)
    bool solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, int k) {
        if(k < 0)
            return false;
        
        if(i == n)
            return (k == 0) ? true : false;
            
        if(dp[i][k] != -1)
            return dp[i][k];
            
        bool currSkip = solveWithMemo(dp, nums, i + 1, k);
        bool currTake = solveWithMemo(dp, nums, i + 1, k - nums[i]);
        
        return dp[i][k] = (currSkip || currTake);
    }

    // O(N*N*K) & O(N*K)
    bool solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& nums, int start, int k) {
        if(k < 0)
            return false;
        
        if(start == n)
            return (k == 0) ? true : false;
            
        if(dp[start][k] != -1)
            return dp[start][k];
            
        bool currTake = (k == 0) ? true : false;
            
        for(int i = start; i < n; ++i) {
            currTake = currTake || solveWithMemoLoop(dp, nums, i + 1, k - nums[i]);
        }
            
        return dp[start][k] = currTake;
    }

public:
    bool isSubsetSum(vector<int>& nums, int k) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(k + 1, -1));
        return solveWithMemo(dp, nums, 0, k);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {   
    int n;

    // O(N*GK) & O(N*GK) : Where GK = given_k
    bool solveBy2DTable(const vector<int>& nums, int given_k) {
        vector<vector<int>> dp(n + 1, vector<int>(given_k + 1, -1));
        
        for(int k = 0; k <= given_k; ++k)
            dp[n][k] = (k == 0) ? true : false;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= given_k; ++k) {
                bool currSkip = dp[i + 1][k];
                bool currTake = (k - nums[i] < 0) ? false : dp[i + 1][k - nums[i]];
                dp[i][k] = (currSkip || currTake); 
            }
        }
        
        return dp[0][given_k];
    }
    
    // O(N*GK) & O(GK) : Where GK = given_k
    bool solveBy1DTable(const vector<int>& nums, int given_k) {
        vector<int> nextRow(given_k + 1, -1), idealRow(given_k + 1, -1);
        
        for(int k = 0; k <= given_k; ++k)
            nextRow[k] = (k == 0) ? true : false;
        
        for(int i = n - 1; i >= 0; --i) {
            for(int k = 0; k <= given_k; ++k) {
                bool currSkip = nextRow[k];
                bool currTake = (k - nums[i] < 0) ? false : nextRow[k - nums[i]];
                idealRow[k] = (currSkip || currTake);
            }
            swap(nextRow, idealRow);
        }
        
        return nextRow[given_k];
    }

public:
    bool isSubsetSum(vector<int>& nums, int k) {
        n = nums.size();
        return solveBy1DTable(nums, k);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
        https://www.codingninjas.com/studio/problems/subset-sum-equal-to-k_1550954?leftPanelTabValue=PROBLEM
