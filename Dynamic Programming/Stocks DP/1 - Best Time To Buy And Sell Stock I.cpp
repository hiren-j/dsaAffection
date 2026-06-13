// Code to find the maximum profit you can achieve by making only one transaction ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(2^N) & O(N) 
    int solveWithoutMemo(const vector<int>& prices, int day, bool canBuy) {
        if(day == n)
            return 0;

        if(canBuy) {
            int buy  = solveWithoutMemo(prices, day + 1, false) - prices[day]; 
            int skip = solveWithoutMemo(prices, day + 1, true);                
            return max(buy, skip);                                            
        }
        else {
            int sell = max(prices[day], solveWithoutMemo(prices, day + 1, true)); 
            int skip = solveWithoutMemo(prices, day + 1, false);                  
            return max(sell, skip);                                              
        }
    }

    // O(N) & O(N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& prices, int day, bool canBuy) {
        if(day == n)
            return 0;

        if(dp[day][canBuy] != -1)
            return dp[day][canBuy];

        if(canBuy) {
            int buy  = solveWithMemo(dp, prices, day + 1, false) - prices[day]; 
            int skip = solveWithMemo(dp, prices, day + 1, true);                
            return dp[day][canBuy] = max(buy, skip);                           
        }
        else {
            int sell = max(prices[day], solveWithMemo(dp, prices, day + 1, true)); 
            int skip = solveWithMemo(dp, prices, day + 1, false);                  
            return dp[day][canBuy] = max(sell, skip);                             
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
    
class Solution {
    int n;

    // O(N) & O(N)
    int solveBy2DTable(const vector<int>& prices) {
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for(int day = n - 1; day >= 0; --day) {
            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = dp[day + 1][false] - prices[day]; 
                    int skip = dp[day + 1][true];                
                    dp[day][canBuy] = max(buy, skip);                           
                }
                else {
                    int sell = max(prices[day], dp[day + 1][true]); 
                    int skip = dp[day + 1][false];                  
                    dp[day][canBuy] = max(sell, skip);                             
                }
            }
        }

        return dp[0][true];
    }

    // O(N) & O(1)
    int solveBy1DTable(const vector<int>& prices) {
        vector<int> nextRow(2, 0);

        for(int day = n - 1; day >= 0; --day) {
            vector<int> currRow(2, 0);

            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = nextRow[false] - prices[day]; 
                    int skip = nextRow[true];                
                    currRow[canBuy] = max(buy, skip);                           
                }
                else {
                    int sell = max(prices[day], nextRow[true]); 
                    int skip = nextRow[false];                  
                    currRow[canBuy] = max(sell, skip);                             
                }
            }

            swap(nextRow, currRow);
        }

        return nextRow[true];
    }
    
    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& prices) {
        int nextRow_0 = 0;
        int nextRow_1 = 0;

        for(int day = n - 1; day >= 0; --day) {
            int currRow_0 = 0;
            int currRow_1 = 0;

            for(int canBuy = 0; canBuy <= 1; ++canBuy) {
                if(canBuy) {
                    int buy  = nextRow_0 - prices[day]; 
                    int skip = nextRow_1;                
                    currRow_1 = max(buy, skip);                           
                }
                else {
                    int sell = max(prices[day], nextRow_1); 
                    int skip = nextRow_0;                  
                    currRow_0 = max(sell, skip);                             
                }
            }

            swap(nextRow_0, currRow_0);
            swap(nextRow_1, currRow_1);
        }

        return nextRow_1;
    }

public:
    int maxProfit(vector<int>& prices) {
        n = prices.size();
        return solveWithoutTable(prices);
    }
};

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUpPrecise {
public:
    // O(N) & O(1)
    int maxProfit(const vector<int>& prices) {
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
