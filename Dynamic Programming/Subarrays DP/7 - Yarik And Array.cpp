// Code to find maximum sum of a subarray with adjacent elements having different parity ~ coded by vHiren
#include <iostream>
#include <vector>
using namespace std;

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int parity) {
        if(i == n)
            return (prevPick == true) ? 0 : INT_MIN;

        if(prevPick) {
            int pickInSubarr = parity != abs(nums[i] % 2)
                                ? solveWithoutMemo(nums, i + 1, true, abs(nums[i] % 2)) + nums[i]
                                : INT_MIN;
            int stopHere = 0;
            return max(pickInSubarr, stopHere);
        }
        else {
            int startCurr  = solveWithoutMemo(nums, i + 1, true, abs(nums[i] % 2)) + nums[i];
            int startNext  = solveWithoutMemo(nums, i + 1, false, 0);
            return max(startCurr, startNext);
        }
    }

    // O(8*N) & O(2*N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int parity) {
        if(i == n)
            return (prevPick == true) ? 0 : INT_MIN;

        if(dp[i][prevPick][parity] != INT_MIN)
            return dp[i][prevPick][parity];

        if(prevPick) {
            int pickInSubarr = parity != abs(nums[i] % 2)
                                ? solveWithMemo(dp, nums, i + 1, true, abs(nums[i] % 2)) + nums[i]
                                : INT_MIN;
            int stopHere = 0;
            return dp[i][prevPick][parity] = max(pickInSubarr, stopHere);
        }
        else {
            int startCurr  = solveWithMemo(dp, nums, i + 1, true, abs(nums[i] % 2)) + nums[i];
            int startNext  = solveWithMemo(dp, nums, i + 1, false, 0);
            return dp[i][prevPick][parity] = max(startCurr, startNext);
        }
    }

public:
    int maxSubarrSum(vector<int>& nums) {
        n = nums.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(2, INT_MIN)));
        return solveWithMemo(dp, nums, 0, false, 0);
    }
};

class BottomUp {
    int n;

    // O(N) & O(N)
    int solveBy3DTable(const vector<int>& nums) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(2, INT_MIN)));
        dp[n][true][0] = 0;
        dp[n][true][1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int parity = 1; parity >= 0; --parity) {
                    if(prevPick) {
                        int pickInSubarr = parity != abs(nums[i] % 2)
                                            ? dp[i + 1][true][abs(nums[i] % 2)] + nums[i]
                                            : INT_MIN;
                        int stopHere = 0;
                        dp[i][prevPick][parity] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr  = dp[i + 1][true][abs(nums[i] % 2)] + nums[i];
                        int startNext  = dp[i + 1][false][0];
                        dp[i][prevPick][parity] = max(startCurr, startNext);
                    }
                }
            }
        }

        return dp[0][false][0];
    }

    // O(N) & O(1)
    int solveBy2DTable(const vector<int>& nums) {
        vector<vector<int>> next(2, vector<int>(2, INT_MIN)); // i + 1th table
        vector<vector<int>> curr(2, vector<int>(2, INT_MIN)); // ith table
        next[true][0] = 0;
        next[true][1] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int parity = 1; parity >= 0; --parity) {
                    if(prevPick) {
                        int pickInSubarr = parity != abs(nums[i] % 2)
                                            ? next[true][abs(nums[i] % 2)] + nums[i]
                                            : INT_MIN;
                        int stopHere = 0;
                        curr[prevPick][parity] = max(pickInSubarr, stopHere);
                    }
                    else {
                        int startCurr  = next[true][abs(nums[i] % 2)] + nums[i];
                        int startNext  = next[false][0];
                        curr[prevPick][parity] = max(startCurr, startNext);
                    }
                }
            }
            swap(next, curr);
        }

        return next[false][0];
    }

public:
    int maxSubarrSum(vector<int>& nums) {
        n = nums.size();
        return solveBy2DTable(nums);
    }
};

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while(t--) {
        int n;
        cin >> n;

        vector<int> nums(n);
        for(int& num : nums)
            cin >> num;

        BottomUp bu;
        cout << bu.maxSubarrSum(nums) << '\n';
    }

    return 0;
}
// Link: https://codeforces.com/contest/1899/problem/C
