// Program to find the minimum cost of painting all the houses such that no adjacent houses are painted with the same colour ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the minimum cost, using recursion with memoization - O(N) & O(N)
    int paintHouse(vector<vector<int>>& cost) {
    	int N = cost.size();
    	vector<vector<int>> memory(N, vector<int>(4, -1));
    	return solveWithMemo(memory, cost, N, 0, 3);
    }

private:
    // O(2*N*4) & O(N+N*4)
    int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& cost, int N, int house, int skipColour) {
	// Edge case: If all the houses are exhausted then you can't paint anymore
    	if(house == N)
	    return 0;

	// Memoization table: If the current state is already computed then return the computed value
    	if(memory[house][skipColour] != -1)
	    return memory[house][skipColour];

	// Stores the minimum cost you can get by colouring the houses such that no adjacent houses are painted with the same colour
    	int paintGreen = INT_MAX, paintRed = INT_MAX, paintYellow = INT_MAX;

	// If the previous house is not painted with green colour then paint the current house with it
    	if(0 != skipColour) {
    	    int minCost = solveWithMemo(memory, cost, N, house + 1, 0);
            if(minCost != INT_MAX) {
                paintGreen = minCost + cost[house][0];
            }
    	}

	// If the previous house is not painted with red colour then paint the current house with it
    	if(1 != skipColour) {
	    int minCost = solveWithMemo(memory, cost, N, house + 1, 1);
            if(minCost != INT_MAX) {
                paintRed = minCost + cost[house][1];
            }	
        }

	// If the previous house is not painted with yellow colour then paint the current house with it
    	if(2 != skipColour) {
	    int minCost = solveWithMemo(memory, cost, N, house + 1, 2);
            if(minCost != INT_MAX) {
                paintYellow = minCost + cost[house][2];
            }
    	}

	// Store the result value to the memoization table and then return it
    	return memory[house][skipColour] = min({paintGreen, paintRed, paintYellow});
    }
	
	// O(2^N) & O(N)
    int solveWithoutMemo(vector<vector<int>>& cost, int N, int house, int skipColour) {
	// Edge case: If all the houses are exhausted then you can't paint anymore
    	if(house == N)
    	    return 0;
	
	// Stores the minimum cost you can get by colouring the houses such that no adjacent houses are painted with the same colour
    	int paintGreen = INT_MAX, paintRed = INT_MAX, paintYellow = INT_MAX;
    
	// If the previous house is not painted with green colour then paint the current house with it
    	if(0 != skipColour) {
    	    int minCost = solveWithoutMemo(cost, N, house + 1, 0);
            if(minCost != INT_MAX) {
                paintGreen = minCost + cost[house][0];
            }
    	}
    
	// If the previous house is not painted with red colour then paint the current house with it
    	if(1 != skipColour) {
    	    int minCost = solveWithoutMemo(cost, N, house + 1, 1);
            if(minCost != INT_MAX) {
                paintRed = minCost + cost[house][1];
            }	
        }
    
	// If the previous house is not painted with yellow colour then paint the current house with it
    	if(2 != skipColour) {
    	    int minCost = solveWithoutMemo(cost, N, house + 1, 2);
            if(minCost != INT_MAX) {
                paintYellow = minCost + cost[house][2];
            }
    	}

	// As we're striving for the minimum cost hence return the minimum value
    	return min({paintGreen, paintRed, paintYellow});
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to find the minimum cost, using 2D tabulation - O(N) & O(N)
    int paintHouse_A(vector<vector<int>>& cost) {
	int N = cost.size();

	// 2D table for tabulation: dp[house][skipColour] stores the overall minimum cost you can get by coloring the initial "house + 1" houses such that no adjacent houses are coloured with "skipColour" colour
	vector<vector<int>> dp(N, vector<int>(3, INT_MAX));

	// If there's only a single house then the minimum cost of painting each colour is the initial cost associated with them
	dp[0][0] = cost[0][0];
	dp[0][1] = cost[0][1];
	dp[0][2] = cost[0][2];

	// Iterate and fill the rest of the table
	for(int house = 1; house < N; ++house) {
	    for(int skipColour = 0; skipColour < 3; ++skipColour) {
		// Stores the minimum cost you can get by colouring the houses such that no adjacent houses are painted with the same colour
	    	int paintGreen = INT_MAX, paintRed = INT_MAX, paintYellow = INT_MAX;

		// If the previous house is not painted with green colour then paint the current house with it
	    	if(0 != skipColour) {
	    	    int minCost = dp[house - 1][0];
	            if(minCost != INT_MAX) {
	        	paintGreen = minCost + cost[house][skipColour];
		    }
		}

		// If the previous house is not painted with red colour then paint the current house with it
	    	if(1 != skipColour) {
	    	    int minCost = dp[house - 1][1];
	            if(minCost != INT_MAX) {
	        	paintRed = minCost + cost[house][skipColour];
		    }	
		}

		// If the previous house is not painted with yellow colour then paint the current house with it
	    	if(2 != skipColour) {
	    	    int minCost = dp[house - 1][2];
	            if(minCost != INT_MAX) {
	        	paintYellow = minCost + cost[house][skipColour];
		    }
	    	}

		// As we're striving for the minimum cost hence store the minimum value
	    	dp[house][skipColour] = min({paintGreen, paintRed, paintYellow});
	    }
	}

	// Return the result value
	return *min_element(begin(dp[N - 1]), end(dp[N - 1]));
    }

    // #2 Method to find the minimum cost, using constant auxiliary space - O(N) & O(1)
    int paintHouse_B(vector<vector<int>>& cost) {
	int N = cost.size();

	// Iterate and update the table 
	for(int house = 1; house < N; ++house) {
	    for(int skipColour = 0; skipColour < 3; ++skipColour) {
		// Stores the minimum cost you can get by colouring the houses such that no adjacent houses are painted with the same colour
	    	int paintGreen = INT_MAX, paintRed = INT_MAX, paintYellow = INT_MAX;

		// If the previous house is not painted with green colour then paint the current house with it
	    	if(0 != skipColour) {
	    	    int minCost = cost[house - 1][0];
	            if(minCost != INT_MAX) {
	        	paintGreen = minCost + cost[house][skipColour];
		    }
		}

		// If the previous house is not painted with red colour then paint the current house with it
	    	if(1 != skipColour) {
	    	    int minCost = cost[house - 1][1];
	            if(minCost != INT_MAX) {
	        	paintRed = minCost + cost[house][skipColour];
		    }	
		}

		// If the previous house is not painted with yellow colour then paint the current house with it
	    	if(2 != skipColour) {
	    	    int minCost = cost[house - 1][2];
	            if(minCost != INT_MAX) {
	        	paintYellow = minCost + cost[house][skipColour];
		    }
		}

		// As we're striving for the minimum cost hence store the minimum value
	    	cost[house][skipColour] = min({paintGreen, paintRed, paintYellow});
	    }
	}

	// Return the result value
	return *min_element(begin(cost[N - 1]), end(cost[N - 1]));
    }
};

// Driver code
int main() {
    bool userRunsApp = true;

    while(userRunsApp) {
	system("cls || clear");

	cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

	// Input the array size
	int N;
	cout<<"Enter the total number of houses (size): ";
	cin>>N;

	// Check the given size is lying within the problem constraints or not
	if(N < 1 || N > 10000) {
	    cout<<"You must enter a size which lies between 1 and 10^4!";
	}
	else {
	    vector<vector<int>> cost(N, vector<int>(3));

	    // Input the array values
	    cout<<"\nNote: Each house will be associated with 3 colours. The colour code is as follows: green - 0, red - 1 and yellow - 2\n";
	    for(int house = 0; house < N; ++house) {
		cout<<"\nEnter the cost of colours of the "<<house + 1<<"th house:-\n";
		for(int colour = 0; colour < 3;) {
		    cout<<"Enter the cost of "<<colour<<"th colour: ";
		    cin>>cost[house][colour];
			
		    // Check the given values are lying within the problem constraints or not
		    if(cost[house][colour] < 0 || cost[house][colour] > 100) {
			cout<<"You must enter a cost which lies between 0 and 100!\n";
		    }
		    else {
			++colour;
		    }
		}
	    }
			
		// Call to find the minimum cost
		BottomUp bottomUp;
		int minCost = bottomUp.paintHouse_B(cost);
		cout<<"\nThe minimum cost of painting all the houses such that no adjacent houses are painted with the same colour is: "<<minCost;
	}

	// Input section to control the flow of iterations of the application
	char userChoice;
	cout<<"\n\nPress \'R\' to restart the application else it will exit: ";
	cin>>userChoice;
	userRunsApp = (userChoice == 'R');
    }

    return 0;
}
/*
	Topics: Array | Dynamic Programming
	Links: https://www.naukri.com/code360/problems/paint-house_1460385
	       https://leetcode.com/problems/paint-house/description/
*/
