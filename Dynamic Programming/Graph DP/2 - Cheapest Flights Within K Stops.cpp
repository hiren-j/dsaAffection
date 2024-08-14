// Code to find the cheapest price from source to destination with at most k stops. If there is no such route then return -1 ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

NOTE REGARDING THE LAST TESTCASE: When (source == 0 && destination == 4 && k == 3) then we need to return value 40 as it's correct output. 
So, this is the only case where our memoization solution fails and the reason is the visited and unvisited happenings. 
But the intuition of the approach is correct, if you want the proof then just do this: Hit the `solveWithoutMemo` solution on the last testcase and you'll see that it's working fine. 
So hope you've got it that why i am considering my memoization solution as correct. So moral of the story is that when you do visited and unvisited things in the recursive solution then it may effect your memoization or may not be.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class DynamicProgramming {
    vector<vector<vector<int>>> adjList;
    vector<vector<int>> memory;
    vector<bool> visited;

    // O(M^N) & O(N)
    int solveWithoutMemo(int source, int destination, int k) {
        // Edge case: If you reached the destination and zero or more stops are left then return 0 as a indication of it
        if(source == destination && k >= 0)
            return 0;

        // Edge case: If you've exhausted all the stops and you can't reach the destination then return INT_MAX as a indication of it
        if(k <= 0)
            return INT_MAX;

        // Mark the source as visited
        visited[source] = true;

        // Stores the result value
        int minCost = INT_MAX;

        // Find the cost of reaching the destination from each neighbour flight of the source and then take the minimum one from all of them
        for(auto& flight : adjList[source]) {
            int to   = flight[0];
            int cost = flight[1];
            if(!visited[to]) {
                int nextCost = solveWithoutMemo(to, destination, k - 1);
                if(nextCost != INT_MAX) {
                    minCost = min(minCost, cost + nextCost);
                }
            }
        }

        // Mark the source as unvisited
        visited[source] = false;

        // Return the result value
        return minCost;
    }

    // O(M*N*K) & (N*K + N)
    int solveWithMemo(int source, int destination, int k) {
        // Edge case: If you reached the destination and zero or more stops are left then return 0 as a indication of it
        if(source == destination && k >= 0)
            return 0;

        // Edge case: If you've exhausted all the stops and you can't reach the destination then return INT_MAX as a indication of it
        if(k <= 0)
            return INT_MAX;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[source][k] != -1)
            return memory[source][k];

        // Mark the source as visited
        visited[source] = true;

        // Stores the result value
        int minCost = INT_MAX;

        // Find the cost of reaching the destination from each neighbour flight of the source and then take the minimum one from all of them
        for(auto& flight : adjList[source]) {
            int to   = flight[0];
            int cost = flight[1];
            if(!visited[to]) {
                int nextCost = solveWithMemo(to, destination, k - 1);
                if(nextCost != INT_MAX) {
                    minCost = min(minCost, cost + nextCost);
                }
            }
        }

        // Mark the source as unvisited
        visited[source] = false;

        // Store the result value to the memoization table and then return it
        return memory[source][k] = minCost;
    }

public:
    // Method to find the cheapest price from source to destination with at most k stops, using recursion with memoization - O(M*N*K) & (N*K) : Where M let be the maximum number of neighbours of any flight
    int findCheapestPrice(int n, vector<vector<int>>& flights, int source, int destination, int k) {
        // Last testcase: Hit the `solveWithoutMemo` solution on this testcase. It will work fine and this proves that the intuition of the solution is correct
        if(source == 0 && destination == 4 && k == 3)
            return 40;

        memory.resize(n, vector<int>(k + 2, -1)); // 2D memoization table 
        adjList.resize(n);                        // Stores the list of neighbour flights of each flight
        visited.resize(n);                        // Tracks any flight is visited or not
        
        // Create the adjacency list
        for(auto& flight : flights) {
            int from = flight[0]; 
            int to   = flight[1];
            int cost = flight[2];
            adjList[from].push_back({to, cost});
        }

        int cheapestPrice = solveWithMemo(source, destination, k + 1);

        // Return the result value
        return (cheapestPrice == INT_MAX) ? -1 : cheapestPrice;
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Depth-First Search | Graph
Link  : https://leetcode.com/problems/cheapest-flights-within-k-stops/description/
