// Code to find the maximum profit you can achieve from the specified transaction ~ coded by Hiren

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the maximum profit you can achieve - O(N) & O(1)
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
