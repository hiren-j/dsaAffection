// Code to find the cheapest price from source to destination with at most k stops. If there is no such route then return -1 ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class DynamicProgramming {
    vector<vector<pair<int, int>>> adjList;

    // O(K^N) & O(K) : Where N = total flights or total nodes, M = total edges.
    int solveWithoutMemo(int src, int dst, int k) {
        if(src == dst)
            return (k >= 0) ? 0 : INT_MAX; // If reached destination within k stops then return 0 as an indication

        if(k == 0)
            return INT_MAX;

        int minPrice = INT_MAX;
        
        for(auto& [neighbor, edgeWeight] : adjList[src]) {
            int nextPrice = solveWithoutMemo(neighbor, dst, k - 1);
            if(nextPrice != INT_MAX) {
                minPrice = min(minPrice, nextPrice + edgeWeight);
            }
        }

        return minPrice;
    }

    // O(N*N*K) & O(N*K) : Where N = total flights or total nodes, M = total edges.
    int solveWithMemo(vector<vector<int>>& dp, int src, int dst, int k) {
        if(src == dst)
            return (k >= 0) ? 0 : INT_MAX; // If reached destination within k stops then return 0 as an indication

        if(k == 0)
            return INT_MAX;

        if(dp[src][k] != -1)
            return dp[src][k];

        int minPrice = INT_MAX;
        
        for(auto& [neighbor, edgeWeight] : adjList[src]) {
            int nextPrice = solveWithMemo(dp, neighbor, dst, k - 1);
            if(nextPrice != INT_MAX) {
                minPrice = min(minPrice, nextPrice + edgeWeight);
            }
        }

        return dp[src][k] = minPrice;
    }

public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        adjList.resize(n);

        for(auto& f : flights) { // Construct the graph
            int from  = f[0];
            int to    = f[1];
            int price = f[2];
            adjList[from].push_back({to, price});
        }

        vector<vector<int>> dp(n, vector<int>(k + 2, -1));
        int minPrice = solveWithMemo(dp, src, dst, k + 1);

        return (minPrice == INT_MAX) ? -1 : minPrice;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Depth-First Search | Graph
Link  : https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
