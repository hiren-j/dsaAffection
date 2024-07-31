// Program to count all the possible distinct binary strings of length N such that there are no consecutive 1’s ~ coded by Hiren
#define MOD 1000000007
#define ll long long
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using recursion with memoization - O(N) & O(N)
    ll countStrings(int N) {
	vector<ll> memory(N + 1, -1);
	return solveWithMemo(memory, N);
    }

private:
    // O(2*N) & O(N+N)
    ll solveWithMemo(vector<ll>& memory, int N) {
	if(N < 2)
	    return N + 1;
    
	if(memory[N] != -1)
	    return memory[N];

	ll count1 = solveWithMemo(memory, N - 1);
	ll count2 = solveWithMemo(memory, N - 2);
    
	return memory[N] = (count1 + count2) % MOD;
    }

    // O(2^N) & O(N)
    ll solveWithoutMemo(int N) {
	if(N < 2)
	    return N + 1;

	ll count1 = solveWithoutMemo(N - 1);
	ll count2 = solveWithoutMemo(N - 2);
    
	return (count1 + count2) % MOD;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // #1 Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using 1D tabulation - O(N) & O(N)
    ll countStrings_V1(int N) {
	vector<ll> dp(N + 1, -1);
	dp[0] = 1;
	dp[1] = 2;
    
	for(int num = 2; num <= N; ++num) {
	    ll count1 = dp[num - 1];
	    ll count2 = dp[num - 2];
	    dp[num]   = (count1 + count2) % MOD;
	}
    
	return dp[N];
    }

    // #2 Method to count all the possible distinct binary strings of length N such that there are no consecutive 1’s, using constant auxiliary space - O(N) & O(1)
    ll countStrings_V2(int N) {
	ll count1 = 1, count2 = 2;
	ll resultCount = count2;
    
	for(int num = 2; num <= N; ++num) {
	    resultCount = (count1 + count2) % MOD;
	    count1      = count2;
	    count2      = resultCount;
	} 
	    
	return resultCount;
    }
};

// Driver code
int main() {
    cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n\n";
	
    int testCases;
    cout<<"Enter the total number of testcases: ";
    cin>>testCases;

    while(testCases--) {
        int N;
        cout<<"\nEnter the value of N: ";
        cin>>N;

        // Check the given value is lying within the problem constraints or not
	if(N < 1 || N > 1e5) {
	    cout<<"You must enter a value which lies between 1 and 10^5!\n";
	}
	else {
	    BottomUp bottomUp;
	    int resultCount = bottomUp.countStrings_V2(N);
            cout<<"There are total "<<resultCount<<" possible distinct binary strings of length "<<N<<"\n";
	}
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link  : https://www.geeksforgeeks.org/problems/consecutive-1s-not-allowed1912/1
*/
