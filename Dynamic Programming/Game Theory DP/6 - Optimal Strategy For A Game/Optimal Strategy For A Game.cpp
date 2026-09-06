// Code to find the maximum possible amount of money alice can win if she go first. Alice play against Bob in an alternating way. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the value of the coin. Note that both the players are playing optimally ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    // O(2^N) & O(N)
    int solveWithoutMemo(vector<int>& nums, int i, int j, bool myTurn) {
        if(i > j)
            return 0;

        if(myTurn) {
            int pickFirst = nums[i] + solveWithoutMemo(nums, i + 1, j, false);
            int pickLast  = nums[j] + solveWithoutMemo(nums, i, j - 1, false);
            return max(pickFirst, pickLast);
        }
        else {
            int pickFirst = solveWithoutMemo(nums, i + 1, j, true);
            int pickLast  = solveWithoutMemo(nums, i, j - 1, true);
            return min(pickFirst, pickLast);
        }
    }
    
    // O(N^2) & O(N^2)
    int solveWithMemo(int dp[][1000][2], vector<int>& nums, int i, int j, bool myTurn) {
        if(i > j)
            return 0;
            
        if(dp[i][j][myTurn] != -1)
            return dp[i][j][myTurn]; 

        if(myTurn) {
            int pickFirst = nums[i] + solveWithMemo(dp, nums, i + 1, j, false);
            int pickLast  = nums[j] + solveWithMemo(dp, nums, i, j - 1, false);
            return dp[i][j][myTurn] = max(pickFirst, pickLast);
        }
        else {
            int pickFirst = solveWithMemo(dp, nums, i + 1, j, true);
            int pickLast  = solveWithMemo(dp, nums, i, j - 1, true);
            return dp[i][j][myTurn] = min(pickFirst, pickLast);
        }
    }

public:
    int maximumAmount(vector<int>& nums) {
        int n = nums.size();
        int dp[1000][1000][2];
        memset(dp, -1, sizeof(dp));
        return solveWithMemo(dp, nums, 0, n - 1, true);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N^2) & O(N^2)
    int solveBy3DTable(const vector<int>& nums) {
        int dp[1001][1001][2];
        memset(dp, -1, sizeof(dp));
        
        for(int i = n - 1; i >= 0; --i) {
            for(int j = 0; j <= n - 1; ++j) {
                for(int myTurn = 0; myTurn <= 1; ++myTurn) {
                    if(myTurn) {
                        int pickFirst    = nums[i] + (i + 1 > j ? 0 : dp[i + 1][j][false]);
                        int pickLast     = nums[j] + (i > j - 1 ? 0 : dp[i][j - 1][false]);
                        dp[i][j][myTurn] = max(pickFirst, pickLast);
                    }
                    else {
                        int pickFirst    = (i + 1 > j ? 0 : dp[i + 1][j][true]);
                        int pickLast     = (i > j - 1 ? 0 : dp[i][j - 1][true]);
                        dp[i][j][myTurn] = min(pickFirst, pickLast);
                    }   
                }
            }
        }
        
        return dp[0][n - 1][true];
    }
    
    // O(N^2) & O(N^2)
    int solveBy3DEnhanced(const vector<int>& nums) {
        int dp[1001][1001][2];
        memset(dp, 0, sizeof(dp));
        
        for(int i = n - 1; i >= 0; --i) {
            for(int j = i; j <= n - 1; ++j) {
                for(int myTurn = 0; myTurn <= 1; ++myTurn) {
                    if(myTurn) {
                        int pickFirst    = nums[i] + dp[i + 1][j][false];
                        int pickLast     = nums[j] + (i > j - 1 ? 0 : dp[i][j - 1][false]);
                        dp[i][j][myTurn] = max(pickFirst, pickLast);
                    }
                    else {
                        int pickFirst    = dp[i + 1][j][true];
                        int pickLast     = (i > j - 1 ? 0 : dp[i][j - 1][true]);
                        dp[i][j][myTurn] = min(pickFirst, pickLast);
                    }   
                }
            }
        }
        
        return dp[0][n - 1][true];
    }
    
    // O(N^2) & O(N)
    int solveBy2DTable(const vector<int>& nums) {
        int next[1001][2], curr[1001][2];
        memset(next, 0, sizeof(next));
        memset(curr, 0, sizeof(curr));
        
        for(int i = n - 1; i >= 0; --i) {
            for(int j = i; j <= n - 1; ++j) {
                for(int myTurn = 0; myTurn <= 1; ++myTurn) {
                    if(myTurn) {
                        int pickFirst   = nums[i] + next[j][false];
                        int pickLast    = nums[j] + (i > j - 1 ? 0 : curr[j - 1][false]);
                        curr[j][myTurn] = max(pickFirst, pickLast);
                    }
                    else {
                        int pickFirst   = next[j][true];
                        int pickLast    = (i > j - 1 ? 0 : curr[j - 1][true]);
                        curr[j][myTurn] = min(pickFirst, pickLast);
                    }   
                }
            }
            swap(next, curr);
        }
        
        return next[n - 1][true];
    }
    
public:
    int maximumAmount(vector<int>& nums) {
        n = nums.size();
        return solveBy2DTable(nums);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming | Game Theory
Links : https://www.geeksforgeeks.org/problems/optimal-strategy-for-a-game-1587115620/1
        https://cses.fi/problemset/task/1097
