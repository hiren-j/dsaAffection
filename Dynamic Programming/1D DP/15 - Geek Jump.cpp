// Code to find the minimum energy that can be used by the Geek to jump from step 0 to step N-1 ~ coded by Hiren

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    int solveWithoutMemo(vector<int>& heights, int idx) {
        if(idx == n-1)
            return 0;
                    
        int jump1Step = abs(heights[idx + 1] - heights[idx]) + solveWithoutMemo(heights, idx + 1);
        int jump2Step = (idx + 2 < n)
                      ? abs(heights[idx + 2] - heights[idx]) + solveWithoutMemo(heights, idx + 2)
                      : INT_MAX;
        
        return min(jump1Step, jump2Step);
    }

    int solveWithMemo(vector<int>& dp, vector<int>& heights, int idx) {
        if(idx == n-1)
            return 0;
        
        if(dp[idx] != -1)
            return dp[idx];
            
        int jump1Step = abs(heights[idx + 1] - heights[idx]) + solveWithMemo(dp, heights, idx + 1);
        int jump2Step = (idx + 2 < n)
                      ? abs(heights[idx + 2] - heights[idx]) + solveWithMemo(dp, heights, idx + 2)
                      : INT_MAX;
        
        return dp[idx] = min(jump1Step, jump2Step);
    }
    
public:
    int minCostToReachTop(vector<int>& heights) {
        n = heights.size();
        vector<int> dp(n-1, -1);
        return solveWithMemo(dp, heights, 0);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    int solveWith1DTable(vector<int>& heights) {
        vector<int> dp(n, -1);
        dp[n - 1] = 0;
            
        for(int idx = n-2; idx >= 0; --idx) {
            int jump1Step = abs(heights[idx + 1] - heights[idx]) + dp[idx + 1];
            int jump2Step = (idx + 2 < n) 
                          ? abs(heights[idx + 2] - heights[idx]) + dp[idx + 2] 
                          : INT_MAX;
            
            dp[idx] = min(jump1Step, jump2Step);
        }
        
        return dp[0];
    }
    
    int solveWithoutTable(vector<int>& heights) {
        int dp_idx_1 = 0;
        int dp_idx_2 = 0;
        int minCost  = 0;
            
        for(int idx = n-2; idx >= 0; --idx) {
            int jump1Step = abs(heights[idx + 1] - heights[idx]) + dp_idx_1;
            int jump2Step = (idx + 2 < n) 
                          ? abs(heights[idx + 2] - heights[idx]) + dp_idx_2 
                          : INT_MAX;
            
            minCost  = min(jump1Step, jump2Step);
            dp_idx_2 = dp_idx_1;
            dp_idx_1 = minCost; 
        }
        
        return minCost;
    }
    
public:
    int minCostToReachTop(vector<int>& heights) {
        n = heights.size();
        return solveWithoutTable(heights);
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Topics: Array | Dynamic Programming
Links : https://www.geeksforgeeks.org/problems/geek-jump/1 
        https://www.codingninjas.com/studio/problems/frog-jump_3621012
