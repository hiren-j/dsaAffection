// Program to find the minimum cost to buy "weight" kgs of oranges. If it is not possible to buy exactly "weight" kgs of oranges then output -1 ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
using namespace std;

// #1 Class to implement the Top-down approach:
class TopDown_V1 {
public:
    // Method to find the minimum cost to buy weight kgs of oranges, using recursion with memoization - O(N*W) & O(N*W) : Where N let be the array size and W let be the weight
	int minimumCost(vector<int>& cost, int N, int weight) {
	    vector<vector<int>> memory(N, vector<int>(weight + 1, -1));
	    int minCost = solveWithMemo(memory, cost, N, 1, weight);
	    return (minCost == INT_MAX) ? -1 : minCost;
	}
	
private:
    // O(N*W) & O(N*W)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& cost, int N, int KG, int weight) {
        // Edge case: If all the kgs are exhausted, then you can't buy any more kgs of oranges
        if(KG - 1 == N)
            return (weight == 0) ? 0 : INT_MAX;
        
        // Edge case: If the weight becomes zero, then you have bought weight kgs of oranges, hence return 0 as a valid indication of it
        if(weight == 0)
            return 0;   
            
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[KG - 1][weight] != -1)
            return memory[KG - 1][weight];
        
        // There are always two possibilities to perform at each kg
        int currSkip = INT_MAX; // Is to skip the weight buy in current kg
        int currTake = INT_MAX; // Is to buy the weight in current kg
        
        // If possible, then skip the weight buy in current kg and move to the next kg
        if(KG <= weight)    
            currSkip = solveWithMemo(memory, cost, N, KG + 1, weight);
        
        // If possible and the kg is available, then buy the weight in current kg and stay on the same kg
        if(cost[KG - 1] != -1 && KG <= weight) {
            int currCost = solveWithMemo(memory, cost, N, KG, weight - KG);
            currTake = (currCost != INT_MAX) ? currCost + cost[KG - 1] : currTake;
        }
        
        // Store the minimum cost value to the memoization table and then return it
        return memory[KG - 1][weight] = min(currTake, currSkip);
    }

    // O(2^W) & O(W)
    int solveWithoutMemo(vector<int>& cost, int N, int KG, int weight) {
        // Edge case: If all the kgs are exhausted, then you can't buy any more kgs of oranges
        if(KG - 1 == N)
            return (weight == 0) ? 0 : INT_MAX;
            
        // Edge case: If the weight becomes zero, then you have bought weights kgs of oranges, hence return 0 as a valid indication of it
        if(weight == 0)
            return 0;
        
        // There are always two possibilities to perform at each kg
        int currSkip = solveWithoutMemo(cost, N, KG + 1, weight); // Is to skip the weight buy in current kg
        int currTake = INT_MAX;                                   // Is to buy the weight in current kg
        
        // If possible and the kg is available, then buy the weight in current kg and stay on the same kg
        if(cost[KG - 1] != -1 && KG <= weight) {
            int currCost = solveWithoutMemo(cost, N, KG, weight - KG);
            currTake = (currCost != INT_MAX) ? currCost + cost[KG - 1] : currTake;
        }
        
        // Return the minimum cost value
        return min(currTake, currSkip);
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_V2 {
public:
    // Method to find the minimum cost to buy weight kgs of oranges, using recursion with memoization - O(N*W) & O(N*W) : Where N let be the array size and W let be the weight
	int minimumCost(vector<int>& cost, int N, int weight) {
	    vector<vector<int>> memory(N, vector<int>(weight + 1, -1));
	    int minCost = solveWithMemo(memory, cost, N, 1, weight);
	    return (minCost == INT_MAX) ? -1 : minCost;
	}
	
private:
    // O(N*W) & O(N*W)
    int solveWithMemo(vector<vector<int>>& memory, vector<int>& cost, int N, int KG, int weight) {
        // Edge case: If the weight becomes zero, then you have bought weights kgs of oranges, hence return 0 as a valid indication of it
        if(weight == 0)
            return 0;
            
        // Memoization table: If the current state is already computed, then return the computed value
        if(memory[KG - 1][weight] != -1)
            return memory[KG - 1][weight];
        
        // Stores the "minimum cost value / result value"
        int minCost = INT_MAX;
        
        // Iterate and if the kg is available then buy the weight kgs of oranges and update the result value by the minimum cost
        for(int currKG = KG; (currKG <= N && currKG <= weight); ++currKG) {
            if(cost[currKG - 1] != -1) {
                int currCost = solveWithMemo(memory, cost, N, currKG, weight - currKG);
                if(currCost != INT_MAX) {
                    minCost = min(minCost, currCost + cost[currKG - 1]);
                }
            }
        }
        
        // Store the minimum cost value to the memoization table and then return it
        return memory[KG - 1][weight] = minCost;
    }

    // O(2^W) & O(W)
    int solveWithoutMemo(vector<int>& cost, int N, int KG, int weight) {
        // Edge case: If the weight becomes zero, then you have bought weights kgs of oranges, hence return 0 as a valid indication of it
        if(weight == 0)
            return 0;
        
        // Stores the "minimum cost value / result value"
        int minCost = INT_MAX;
        
        // Iterate and if the kg is available then buy the weight kgs of oranges and update the result value by the minimum cost
        for(int currKG = KG; (currKG <= N && currKG <= weight); ++currKG) {
            if(cost[currKG - 1] != -1) {
                int currCost = solveWithoutMemo(cost, N, currKG, weight - currKG);
                if(currCost != INT_MAX) {
                    minCost = min(minCost, currCost + cost[currKG - 1]);
                }
            }
        }
        
        // Return the minimum cost value
        return minCost;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the minimum cost to buy weight kgs of oranges, using 2D buffer for tabulation - O(N*W) & O(N*W) : Where N let be the array size and W let be the weight
	int minimumCost_V1(vector<int>& cost, int N, int weight) {
        // Tabulation buffer: dp[KG][currWeight] represents the minimum cost you can get by buying "currWeight" kgs of oranges such that by taking "KG" kgs 
	    vector<vector<int>> dp(N + 1, vector<int>(weight + 1, INT_MAX));

        // Edge case: If there is no kg and no weight, then you don't need any cost
	    dp[0][0] = 0;

        // Treat each "KG" as the total kgs you can take and find the minimum cost you can get by buying "currWeight" kgs of oranges
	    for(int KG = 1; KG <= N; ++KG) {
	        for(int currWeight = 0; currWeight <= weight; ++currWeight) {
	            int currSkip = dp[KG - 1][currWeight];
	            int currTake = INT_MAX;
	            if(cost[KG - 1] != -1 && KG <= currWeight) {
	                currTake = dp[KG][currWeight - KG];
	                currTake = (currTake != INT_MAX) ? currTake + cost[KG - 1] : currTake;
	            }
	            dp[KG][currWeight] = min(currTake, currSkip);
	        }
	    }
	    
        // Return the minimum cost you can get to buy weight kgs of oranges
	    return (dp[N][weight] == INT_MAX) ? -1 : dp[N][weight];
	}

    // #2 Method to find the minimum cost to buy weight kgs of oranges, using 1D buffer for tabulation - O(N*W) & O(W) : Where N let be the array size and W let be the weight
	int minimumCost_V2(vector<int>& cost, int N, int weight) {
        // Tabulation buffer: "prevRow[currWeight] / currRow[currWeight]" represents the minimum cost you can get by buying "currWeight" kgs of oranges such that by taking "KG" kgs 
	    vector<int> prevRow(weight + 1, INT_MAX), currRow(weight + 1, INT_MAX);

        // Edge case: If there is no kg and no weight, then you don't need any cost
	    prevRow[0] = 0;
	    
        // Treat each "KG" as the total kgs you can take and find the minimum cost you can get by buying "currWeight" kgs of oranges
	    for(int KG = 1; KG <= N; ++KG) {
	        for(int currWeight = 0; currWeight <= weight; ++currWeight) {
	            int currSkip = prevRow[currWeight];
	            int currTake = INT_MAX;
	            if(cost[KG - 1] != -1 && KG <= currWeight) {
	                currTake = currRow[currWeight - KG];
	                currTake = (currTake != INT_MAX) ? currTake + cost[KG - 1] : currTake;
	            }
	            currRow[currWeight] = min(currTake, currSkip);
	        }
	        prevRow = currRow;
	    }
	    
        // Return the minimum cost you can get to buy weight kgs of oranges
	    return (prevRow[weight] == INT_MAX) ? -1 : prevRow[weight];
	}
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int N;
        cout<<"Enter the total number of orange packets: ";
        cin>>N;

        // Input the weight value
        int weight;
        cout<<"Enter the weight value: ";
        cin>>weight;

        // Check the given values are lying within the problem constraints or not
        if(N <= 0 || N >= 201 || weight <= 0 || weight >= 201) {
            cout<<"You must enter the size and weight, which lies between 1 and 200!";
        }
        else {
            // Stores the array values
            vector<int> cost(N, 0);

            // Input the array values
            cout<<"\nNote: -1 will be considered as the unavailability of any kg (kilogram) packet of oranges!\n";
            for(int index = 0; index < N;) {
                cout<<"Enter the cost of "<<index<<"th packet: ";
                cin>>cost[index];
                if(cost[index] == 0)
                    cout<<"You must enter a cost, which should be -1 or greater than 0!\n";
                else if(cost[index] <= -2 || cost[index] >= 1e5 + 1)
                    cout<<"You must enter a cost, which lies between -1 and 10^5!\n";
                else 
                    index++;
            }

            // Call to find the minimum cost to buy weight kgs of oranges
            BottomUp bottomUp;
            int minCost = bottomUp.minimumCost_V2(cost, N, weight);
            cout<<"\nThe minimum cost to buy "<<weight<<" kgs (kilograms) of oranges is: "<<minCost;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://www.geeksforgeeks.org/problems/minimum-cost-to-fill-given-weight-in-a-bag1956/1?page=3&difficulty%5B%5D=1&category%5B%5D=Dynamic%2520Programming&sortBy=submissions
*/
