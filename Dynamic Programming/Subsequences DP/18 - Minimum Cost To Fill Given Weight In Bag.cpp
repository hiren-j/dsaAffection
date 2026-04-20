// Code to find the minimum cost to buy exactly W kg of oranges. The cost array has a 1-based indexing. If buying exactly W kg of oranges is impossible then return -1 ~ coded by vHiren

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;
    
    // O(2^(N+W)) & O(N+W)
    int solveWithoutMemo(const vector<int>& cost, int pos, int w) {
        if(w == 0)
            return 0;
            
        if(pos > n)
            return INT_MAX;
        
        int currSkip = solveWithoutMemo(cost, pos + 1, w);
        int currTake = INT_MAX;
    
        if(cost[pos - 1] != -1 && pos <= w) {
            currTake = solveWithoutMemo(cost, pos, w - pos);
            if(currTake != INT_MAX) currTake += cost[pos - 1];
        }
        
        return min(currSkip, currTake);
    }
    
    // O(N*W) & O(N*W)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& cost, int pos, int w) {
        if(w == 0)
            return 0;
            
        if(pos > n)
            return INT_MAX;

        if(dp[pos][w] != -1)
            return dp[pos][w];
        
        int currSkip = solveWithMemo(dp, cost, pos + 1, w);
        int currTake = INT_MAX;
    
        if(cost[pos - 1] != -1 && pos <= w) {
            currTake = solveWithMemo(dp, cost, pos, w - pos);
            if(currTake != INT_MAX) currTake += cost[pos - 1];
        }
        
        return dp[pos][w] = min(currSkip, currTake);
    }

    // O(N*N*W) & O(N*W)
    int solveWithMemoLoop(vector<vector<int>>& dp, const vector<int>& cost, int start, int w) {
        if(w == 0)
            return 0;
            
        if(start > n)
            return INT_MAX;

        if(dp[start][w] != -1)
            return dp[start][w];
        
        int minCost = INT_MAX;

        for(int pos = start; pos <= n; ++pos) {
            int currTake = INT_MAX;

            if(cost[pos - 1] != -1 && pos <= w) {
                currTake = solveWithMemoLoop(dp, cost, pos, w - pos);
                if(currTake != INT_MAX) currTake += cost[pos - 1];
            }

            minCost = min(minCost, currTake);
        }
        
        return dp[start][w] = minCost;
    }
    
public:
    int minimumCost(int size, int w, vector<int>& cost) {
        n = size;
        vector<vector<int>> dp(n + 1, vector<int>(w + 1, -1));
        int ans = solveWithMemo(dp, cost, 1, w);
        return (ans == INT_MAX) ? -1 : ans;
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;
    
    // O(N*GW) & O(N*GW) : Where GW = given_w
    int solveBy2DTable(const vector<int>& cost, int given_w) {
        vector<vector<int>> dp(n + 1, vector<int>(given_w + 1, -1));
        
        for(int pos = 0; pos <= n; ++pos)
            dp[pos][0] = 0;
        
        for(int pos = n; pos >= 1; --pos) {
            for(int w = 1; w <= given_w; ++w) {
                int currSkip = (pos + 1 > n) ? INT_MAX : dp[pos + 1][w];
                int currTake = INT_MAX;
            
                if(cost[pos - 1] != -1 && pos <= w) {
                    currTake = dp[pos][w - pos];
                    if(currTake != INT_MAX) currTake += cost[pos - 1];
                }
                
                dp[pos][w] = min(currSkip, currTake);
            }
        }
        
        int ans = dp[1][given_w];
        return (ans == INT_MAX) ? -1 : ans;
    }
    
    // O(N*GW) & O(N*GW) : Where GW = given_w
    int solveBy2DEnhanced(const vector<int>& cost, int given_w) {
        vector<vector<int>> dp(n + 1, vector<int>(given_w + 1, 0));
        
        for(int pos = n; pos >= 1; --pos) {
            for(int w = 1; w <= given_w; ++w) {
                int currSkip = (pos + 1 > n) ? INT_MAX : dp[pos + 1][w];
                int currTake = INT_MAX;
            
                if(cost[pos - 1] != -1 && pos <= w) {
                    currTake = dp[pos][w - pos];
                    if(currTake != INT_MAX) currTake += cost[pos - 1];
                }
                
                dp[pos][w] = min(currSkip, currTake);
            }
        }
        
        int ans = dp[1][given_w];
        return (ans == INT_MAX) ? -1 : ans;
    }
    
    // O(N*GW) & O(GW) : Where GW = given_w
    int solveBy1DTable(const vector<int>& cost, int given_w) {
        vector<int> nextRow(given_w + 1, 0); // pos + 1
        
        for(int pos = n; pos >= 1; --pos) {
            vector<int> idealRow(given_w + 1, 0); // pos
            
            for(int w = 1; w <= given_w; ++w) {
                int currSkip = (pos + 1 > n) ? INT_MAX : nextRow[w];
                int currTake = INT_MAX;
            
                if(cost[pos - 1] != -1 && pos <= w) {
                    currTake = idealRow[w - pos];
                    if(currTake != INT_MAX) currTake += cost[pos - 1];
                }
                
                idealRow[w] = min(currSkip, currTake);
            }
            
            swap(nextRow, idealRow);
        }
        
        int ans = nextRow[given_w];
        return (ans == INT_MAX) ? -1 : ans;
    }
    
public:
    int minimumCost(int size, int w, vector<int>& cost) {
        n = size;
        return solveBy1DTable(cost, w);
    }
};

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1?page=3&difficulty%5B%5D=1&category%5B%5D=Dynamic%2520Programming&sortBy=submissions*/
