// Code to count total number of subsequences / subsets in an array ~ coded by vHiren
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i) {
        if(i == n)
            return 1;

        int currTake = solveWithoutMemo(nums, i + 1);
        int currSkip = solveWithoutMemo(nums, i + 1);

        return (currSkip + currTake);
    }

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int i) {
        if(i == n)
            return 1;

        if(dp[i] != -1)
            return dp[i];

        int currTake = solveWithMemo(dp, nums, i + 1);
        int currSkip = solveWithMemo(dp, nums, i + 1);

        return dp[i] = (currSkip + currTake);
    }

public:
    int countSubsequences(const vector<int>& nums) {
        n = nums.size();
        vector<int> dp(n, -1);
        return solveWithMemo(dp, nums, 0);
    }
};

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> dp(n + 1, -1);
        dp[n] = 1;

        for(int i = n - 1; i >= 0; --i) {
            int currTake = dp[i + 1];
            int currSkip = dp[i + 1];
            dp[i] = (currSkip + currTake);
        }

        return dp[0];
    }

    // O(N) & O(1)
    int solveWithoutTable(const vector<int>& nums) {
        int dp_i_plus_1 = 1; // dp[i + 1];
        int dp_i        = 1; // dp[i];

        for(int i = n - 1; i >= 0; --i) {
            int currTake = dp_i_plus_1;
            int currSkip = dp_i_plus_1;
            dp_i = (currSkip + currTake);
            dp_i_plus_1 = dp_i;
        }

        return dp_i;
    }

public:
    int countSubsequences(const vector<int>& nums) {
        n = nums.size();
        return solveWithoutTable(nums);
    }
};

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    vector<int> nums = {1, 2, 3};
    cout << "From Formula: " << pow(2, nums.size()) << '\n'; // calculate 2^N

    TopDown td;
    cout << "From Memoization: " << td.countSubsequences(nums) << '\n';

    BottomUp bu;
    cout << "From Bottom Up: " << bu.countSubsequences(nums) << '\n';

    return 0;
}
