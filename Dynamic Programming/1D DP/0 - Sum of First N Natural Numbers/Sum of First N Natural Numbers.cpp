#include <iostream>
#include <vector>
#define LL long long
using namespace std;

/*   
    DON'T IGNORE MUST READ: Hey! Welcome to my series. I am assuming you know the basic theory of DP, like there are two ways to do DP (TopDown and BottomUp), meaning of memoization, meaning of tabulation, why DP is required? I know you want this so I'll be adding this theory soon. 
                            Now, For the Top-Down DP approach in the series, each problem will feature two solutions: `solveWithoutMemo` and `solveWithMemo`. 
                            You must start with `solveWithoutMemo`, which demonstrates the recursive solution without memoization (without DP) and which is expected to run into TLE (Time Limit Exceeded, but its not necessary its because acceptance is dependent on the constraints, haven't got it? its okay). 
                            After understanding the non-optimized approach, move to `solveWithMemo` for the memoized solution (DP in recursion), and after understanding the Top-Down DP (memoization approach), 
                            now you could move to the Bottom-Up DP (tabulation approach) and in this always follow this order, Start from the space consuming tabulation then move to the optimized one as ordered. 
                            So, Follow this order of solving problems for all the questions of the DP series.
*/

/*
    DON'T IGNORE MUST READ: The bottom-up solution is the direct conversions of the memoized solution (recursive DP). 
                            This conversion technique helps to create Bottom-up solution very easily and fast, this helps to reduce time and avoid the need for pen and paper as it takes in intuitive bottom-up, This makes the process more efficient, as we will be avoiding the recursive stack space in bottom-up, and also bottom-up is more time optimized compared to the time of memoized solution.
                            Sometimes you'll see that memoization is giving TLE, but the bottom-up is getting accepted, so you see bottom-up is totally efficient than memoized solution, and I'm telling you because I've solved tons of DP problems and saw those things happening with my own eyes!
                            As you work through the bottom-up solutions, switch tabs to view the memoized solution side-by-side, now give your time and try to observe that what's happening, how things are relating in the memoized and bottom-up solution. 
                            This will help you see how the values passed as parameters in the memoized solution correspond to what we calculate and store in the bottom-up approach. 
                            With practice, you’ll be able to create bottom-up solutions within minutes or even seconds, as I have developed the habit of doing. 
                            This conversion technique will be applied to the all the Bottom-up solutions of the remaining problems across all DP patterns.

    FINAL NOTE: The problem link and topic tags are provided at the end of the page.
*/  

/*
    DON'T IGNORE MUST READ (NOTE ON TIME COMPLEXITY CALCULATION):
    
    As you’ve noticed, for this problem, the time complexity of the solveWithMemo function is O(LIMIT * 1) I want to clarify that the LIMIT comes from the loop that calls the recursive function, it's not from the function's auxiliary time. Specifically:

        For solveWithMemo, in O(LIMIT * 1), the term 1 represents the auxiliary time of the function itself, while LIMIT reflects the time from the loop that invokes the function.
        For solveWithoutMemo, in O(LIMIT * N), the term N represents the auxiliary time of the function itself, while LIMIT indicates the number of times the loop calls the function.
    
    So for future problems, be sure to identify any loops from which the function is called. This is crucial for providing a complete time complexity analysis, so I can’t ignore these terms.
*/  

class TopDown {
    // O(LIMIT*N) & O(1*N)
    LL solveWithoutMemo(LL n) {
        if(n == 1)
            return 1;

        LL sum = n + solveWithoutMemo(n - 1);

        return sum; 
    }
    
    // O(LIMIT*1) & O(1)
    LL solveWithMemo(vector<LL>& dp, LL n) {
        if(n == 1)
            return 1;

        LL sum = n + solveWithMemo(dp, n - 1);

        return dp[n] = sum; // Store sum to memoization table and then return it
    }

public:
    vector<LL> findSumFirstNaturalNums(LL LIMIT) {
        vector<LL> dp(LIMIT + 1, -1);
        vector<LL> answer;

        for(LL n = 1; n <= LIMIT; ++n) { 
            LL sum = solveWithMemo(dp, n);
            answer.push_back(sum);
        }

        return answer;
    }
};

class BottomUp {
    // O(1*LIMIT) & O(1*LIMIT)
    vector<LL> solveBy1DTable(LL LIMIT) {
        vector<LL> dp(LIMIT + 1, -1);
        dp[1] = 1; // Init base case

        vector<LL> answer;
        answer.push_back(1);

        for(LL n = 2; n <= LIMIT; ++n) { // In recursion we are moving from n to base case, in Bottom-up just move the reverse way, move from base case to n
            LL sum = n + dp[n - 1];
            dp[n]  = sum;
            answer.push_back(dp[n]);
        }

        return answer;
    }
    // Note: For calculating the result of any n we are dependent on the previous value, which is constant, so we could simply maintain one variable instead of using the dp array  


    // O(1*LIMIT) & O(1)
    vector<LL> solveWithoutTable(LL LIMIT) {
        int dp_n_1 = 1; // dp[n - 1]
        int dp_n   = 1; // dp[n]

        vector<LL> answer;
        answer.push_back(1);

        for(LL n = 2; n <= LIMIT; ++n) {
            LL sum = n + dp_n_1;
            dp_n   = sum;
            answer.push_back(dp_n);
            dp_n_1 = dp_n;
        }

        return answer;
    }

public:
    vector<LL> findSumFirstNaturalNums(LL LIMIT) {
        return solveWithoutTable(LIMIT);
    }
};

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    LL LIMIT = 10;

    BottomUp bottomUp;
    vector<LL> answer = bottomUp.findSumFirstNaturalNums(LIMIT);

    LL n = 1;
    for(const LL sum : answer) {
        cout << "Sum of [1, " << n << "] is " << sum << '\n';
        n++;
    }

    return 0;
}
// Topics: Math | Dynamic Programming
