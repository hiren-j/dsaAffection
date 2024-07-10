// Program to find the minimum cost of painting all the houses such that no adjacent houses are painted with the same color ~ coded by Hiren
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
	// Method to find the minimum cost, using recursion with memoization - O(N) & O(N)
	int minCost(vector<vector<int>>& cost) {
		int n = cost.size();
		vector<vector<int>> memory(n, vector<int>(4, -1));
		return solveWithMemo(memory, cost, n, 0, 3);
	}

private:
	// O(2*N*4) & O(N*4 + N)
	int solveWithMemo(vector<vector<int>>& memory, vector<vector<int>>& cost, int n, int house, int prevColor) {
		// Base case: If all the houses are exhausted then there's no more house to paint
		if(house == n)
			return 0;
		
		// Memoization table: If the current state is already computed then return the computed value 
		if(memory[house][prevColor] != -1)
			return memory[house][prevColor];

		// Stores the result value
		int minCost = INT_MAX;
		
		// Explore the colors and if the previous house is not painted with the current color then paint the current house with it
		for(int color = 0; color < 3; ++color) {
			if(color != prevColor) {
				minCost = min(minCost, cost[house][color] + solveWithMemo(memory, cost, n, house + 1, color));
			}
		}

		// Store the result value to the memoization table and then return it
		return memory[house][prevColor] = minCost;
	}

	// O(2^N) & O(N)
	int solveWithoutMemo(vector<vector<int>>& cost, int n, int house, int prevColor) {
		// Base case: If all the houses are exhausted then there's no more house to paint
		if(house == n)
			return 0;

		// Stores the result value
		int minCost = INT_MAX;
		
		// Explore the colors and if the previous house is not painted with the current color then paint the current house with it
		for(int color = 0; color < 3; ++color) {
			if(color != prevColor) {
				minCost = min(minCost, cost[house][color] + solveWithoutMemo(cost, n, house + 1, color));
			}
		}
		
		// Return the result value
		return minCost;
	}
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
	// #1 Method to find the minimum cost, using 2D tabulation - O(N*4*3) & O(N*4)
	int minCost_V1(vector<vector<int>>& cost) {
		int n = cost.size();

		vector<vector<int>> dp(n + 1, vector<int>(4, 0));

		for(int house = n-1; house >= 0; --house) {
			for(int prevColor = 0; prevColor <= 3; ++prevColor) {
				int minCost = INT_MAX;
				for(int color = 0; color < 3; ++color) {
					if(color != prevColor) {
						minCost = min(minCost, cost[house][color] + dp[house + 1][color]);
					}
				}
				dp[house][prevColor] = minCost;
			}
		}

		return dp[0][3];
	}

	// #2 Method to find the minimum cost, using 1D tabulation - O(N*4*3) & O(2*4)
	int minCost_V2(vector<vector<int>>& cost) {
		int n = cost.size();

		vector<int> nextRow(4, 0), currRow(4, 0);

		for(int house = n-1; house >= 0; --house) {
			for(int prevColor = 0; prevColor <= 3; ++prevColor) {
				int minCost = INT_MAX;
				for(int color = 0; color < 3; ++color) {
					if(color != prevColor) {
						minCost = min(minCost, cost[house][color] + nextRow[color]);
					}
				}
				currRow[prevColor] = minCost;
			}
			nextRow = currRow;
		}

		return currRow[3];
	}	
};

// Driver code
int main() {
    bool userRunsApp = true;

    while(userRunsApp) {
		// Controls console clearance for both "windows" and "linux" user
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
	    	cout<<"\nNote: Each house will be associated with 3 colours. The color code is as follows: green - 0, red - 1 and yellow - 2\n";
	    	for(int house = 0; house < N; ++house) {
				cout<<"\nEnter the cost of colours of the "<<house<<"th house:-\n";
				for(int color = 0; color < 3;) {
				    cout<<"Enter the cost of "<<color<<"th color: ";
				    cin>>cost[house][color];

				    // Check the given values are lying within the problem constraints or not
				    if(cost[house][color] < 0 || cost[house][color] > 100) {
						cout<<"You must enter a cost which lies between 0 and 100!\n";
				    }
				    else {
						++color;
				    }
				}
	    	}
			
	    	// Call to find the minimum cost
	    	BottomUp bottomUp;
	    	int minCost = bottomUp.minCost_V2(cost);
	    	cout<<"\nThe minimum cost of painting all the houses such that no adjacent houses are painted with the same color is: "<<minCost;
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
