// Code to find the maximum profit you can achieve by making only one transaction ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N) 
    int solveWithoutMemo(const vector<int>& prices, int day, bool canBuy) {
        if(day == n)
            return 0;

        if(canBuy) {
            int currBuy  = solveWithoutMemo(prices, day + 1, false) - prices[day]; 
            int currSell = solveWithoutMemo(prices, day + 1, true);                
            return max(currBuy, currSell);                                            
        }
        else {
            int currSell = max(prices[day], solveWithoutMemo(prices, day + 1, true)); 
            int currSkip = solveWithoutMemo(prices, day + 1, false);                  
            return max(currSell, currSkip);                                              
        }
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& prices, int day, bool canBuy) {
        if(day == n)
            return 0;

        if(dp[day][canBuy] != -1)
            return dp[day][canBuy];

        if(canBuy) {
            int currBuy  = solveWithMemo(dp, prices, day + 1, false) - prices[day]; 
            int currSkip = solveWithMemo(dp, prices, day + 1, true);                
            return dp[day][canBuy] = max(currBuy, currSkip);                           
        }
        else {
            int currSell = max(prices[day], solveWithMemo(dp, prices, day + 1, true)); 
            int currSkip = solveWithMemo(dp, prices, day + 1, false);                  
            return dp[day][canBuy] = max(currSell, currSkip);                             
        }
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, prices, 0, true);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
class BottomUp_V1 {
public:
    // #1 Method to find the maximum profit you can achieve, using 2D tabulation - O(N*2) & O(N*2)
    int maxProfit_V1(vector<int>& prices) {
        int n = prices.size();

        // 2D DP table
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        // Fill the table
        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int currBuy  = dp[day + 1][false] - prices[day];
                    int currSkip = dp[day + 1][true];
                    dp[day][canBuy] = max(currBuy, currSkip);
                }
                else {
                    int currSell = max(prices[day], dp[day + 1][true]);
                    int currSkip = dp[day + 1][false];
                    dp[day][canBuy] = max(currSell, currSkip);
                }
            }
        }

        // Return the result value
        return dp[0][true];
    }

    // #2 Method to find the maximum profit you can achieve, using 1D tabulation - O(N*2) & O(1)
    int maxProfit_V2(vector<int>& prices) {
        int n = prices.size();

        // 1D DP tables
        vector<int> nextRow(2, 0), idealRow(2, 0);

        // Fill the table
        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int currBuy  = nextRow[false] - prices[day];
                    int currSkip = nextRow[true];
                    idealRow[canBuy] = max(currBuy, currSkip);
                }
                else {
                    int currSell = max(prices[day], nextRow[true]);
                    int currSkip = nextRow[false];
                    idealRow[canBuy] = max(currSell, currSkip);
                }
            }
            nextRow = idealRow;
        }

        // Return the result value
        return idealRow[true];
    }

    // #3 Method to find the maximum profit you can achieve, using constant auxiliary space - O(N*2) & O(1)
    int maxProfit_V3(vector<int>& prices) {
        int n = prices.size();

        int nextSell = 0, nextBuy   = 0;
        int idealBuy = 0, idealSell = 0;

        for(int day = n-1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int currBuy  = nextSell - prices[day];
                    int currSkip = nextBuy;
                    idealBuy = max(currBuy, currSkip);
                }
                else {
                    int currSell = max(prices[day], nextBuy);
                    int currSkip = nextSell;
                    idealSell = max(currSell, currSkip);
                }
            }
            nextBuy  = idealBuy;
            nextSell = idealSell;
        }

        return idealBuy;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp_V2 {
public:
    // Method to find the maximum profit you can achieve, using constant auxiliary space - O(N) & O(1)
    int maxProfit(vector<int>& prices) {
        int profit = 0, minPrice = INT_MAX;

        for(int price : prices) {
            profit   = max(profit, price - minPrice);
            minPrice = min(minPrice, price);
        }

        return profit;
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description
