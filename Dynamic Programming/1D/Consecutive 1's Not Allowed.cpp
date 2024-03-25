// Program to count all the possible distinct binary strings of length N such that there are no consecutive 1’s ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#define ll long long
#define mod 1000000007
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using recursion with memoization - O(N) & O(N)
    ll countStrings(int N) {
	 vector<int> memory(N + 1, -1);
	 return solveWithMemo(memory, N);
    }

private:
    // O(N) & O(N)
    int solveWithMemo(vector<int>& memory, int N) {
	if(N < 2)
	    return N + 1;
	    
	if(memory[N] != -1)
	    return memory[N];

	int count1 = solveWithMemo(memory, N - 1);
	int count2 = solveWithMemo(memory, N - 2);
	        
	return memory[N] = (count1 + count2) % mod;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(int N) {
	if(N < 2)
	    return N + 1;

	int count1 = solveWithoutMemo(N - 1);
	int count2 = solveWithoutMemo(N - 2);
	        
	return (count1 + count2) % mod;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using 1D buffer for tabulation - O(N) & O(N)
    ll countStrings_V1(int N) {
	vector<int> dp(N + 1, -1);
	dp[0] = 1;
	dp[1] = 2;
	    
	for(int num = 2; num <= N; ++num) {
	    int count1 = dp[num - 1];
	    int count2 = dp[num - 2];
	    dp[num] = (count1 + count2) % mod;
	}
	    
	return dp[N];
    }

    // #2 Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using constant auxiliary space - O(N) & O(1)
    ll countStrings_V2(int N) {
	int count1 = 1;
	int count2 = 2;
	int overallCount = count2;
	    
	for(int num = 2; num <= N; ++num) {
	    overallCount = (count1 + count2) % mod;
	    count1 = count2;
	    count2 = overallCount;
	}
	    
	return overallCount;
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value!\n";
	
    int testCases;
    cout<<"Enter the number of cases to test: ";
    cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter a valid value, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        int N;
        cout<<"\nEnter the value of N: ";
        cin>>N;
	if(N <= 0 || N >= 1e5 + 1) {
	    cout<<"You must enter a value, which lies between 1 and 10^5!\n";
	}
	else {
	    BottomUp bottomUp;
	    int overallCount = bottomUp.countStrings_V2(N);
            cout<<"There are total "<<overallCount<<" possible distinct binary strings of length "<<N<<"\n";
	}
    }

    return 0;
}
/*
	Topics: Array | Dynamic Programming
	Link: https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1
*/
