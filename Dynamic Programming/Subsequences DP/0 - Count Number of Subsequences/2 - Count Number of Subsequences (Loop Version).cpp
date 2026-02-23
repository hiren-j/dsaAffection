// Code to count total number of subsequences / subsets in an array ~ coded by vHiren
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int start) {
        if(start == n)
            return 1;

        int count = 1;

        for(int i = start; i < n; ++i) {
            int currTake = solveWithoutMemo(nums, i + 1);
            count += currTake;
        }

        return count;
    }

    // O(N*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, const vector<int>& nums, int start) {
        if(start == n)
            return 1;

        if(dp[start] != -1)
            return dp[start];

        int count = 1;

        for(int i = start; i < n; ++i) {
            int currTake = solveWithMemo(dp, nums, i + 1);
            count += currTake;
        }

        return dp[start] = count;
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

    // O(N*N) & O(N)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> dp(n + 1, -1);
        dp[n] = 1;

        for(int start = n - 1; start >= 0; --start) {
            int count = 1;

            for(int i = start; i < n; ++i) {
                int currTake = dp[i + 1];
                count += currTake;
            }

            dp[start] = count;
        }

        return dp[0];
    }

public:
    int countSubsequences(const vector<int>& nums) {
        n = nums.size();
        return solveWith1DTable(nums);
    }
};

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    vector<int> nums = {1, 1, 2, 3};
    cout << "From Formula: " << pow(2, nums.size()) << '\n'; // calculate 2^N

    TopDown td;
    cout << "From Memoization: " << td.countSubsequences(nums) << '\n';

    BottomUp bu;
    cout << "From Bottom Up: " << bu.countSubsequences(nums) << '\n';

    return 0;
}
