// Code to check whether there exists a subarray with sum k ~ coded by vHiren
#include <iostream>
#include <vector>
using namespace std;

class TopDown {
    int n;

    // O(2^N) & O(N)
    bool solveWithoutMemo(const vector<int>& nums, int i, bool prevPick, int k) {
        if(k == 0)
            return true;

        if(k < 0 || i == n)
            return false;

        if(prevPick) {
            bool pickInSubarr = solveWithoutMemo(nums, i + 1, true, k - nums[i]);
            bool stopHere = (k == 0) ? true : false;
            return (pickInSubarr || stopHere);
        }
        else {
            bool startNewFromCurr = solveWithoutMemo(nums, i + 1, true, k - nums[i]);
            bool startNewFromNext = solveWithoutMemo(nums, i + 1, false, k);
            return (startNewFromNext || startNewFromCurr);
        }
    }

    // O(N*K) & O(N*K)
    bool solveWithMemo(vector<vector<vector<int>>>& dp, const vector<int>& nums, int i, bool prevPick, int k) {
        if(k == 0)
            return true;

        if(k < 0 || i == n)
            return false;

        if(dp[i][prevPick][k] != -1)
            return dp[i][prevPick][k];

        if(prevPick) {
            bool pickInSubarr = solveWithMemo(dp, nums, i + 1, true, k - nums[i]);
            bool stopHere = (k == 0) ? true : false;
            return dp[i][prevPick][k] = (pickInSubarr || stopHere);
        }
        else {
            bool startNewFromCurr = solveWithMemo(dp, nums, i + 1, true, k - nums[i]);
            bool startNewFromNext = solveWithMemo(dp, nums, i + 1, false, k);
            return dp[i][prevPick][k] = (startNewFromNext || startNewFromCurr);
        }
    }

public:
    bool isSubarraySumK(vector<int>& nums, int k) {
        n = nums.size();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k + 1, -1)));
        return solveWithMemo(dp, nums, 0, false, k);
    }
};

class BottomUp {
    int n;

    // O(N*GK) & O(N*GK) : Where GK = given_k
    bool solveBy3DTable(const vector<int>& nums, int given_k) {
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(given_k + 1, -1)));
        
        // k == 0
        for(int i = 0; i <= n; ++i)
            for(int prevPick = 0; prevPick < 2; ++prevPick)
                dp[i][prevPick][0] = true;

        // i == n
        for(int prevPick = 0; prevPick < 2; ++prevPick)
            for(int k = 0; k <= given_k; ++k)
                dp[n][prevPick][k] = false;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int k = 1; k <= given_k; ++k) {
                    if(prevPick) {
                        bool pickInSubarr = (k - nums[i] < 0) ? false : dp[i + 1][true][k - nums[i]];
                        bool stopHere = (k == 0) ? true : false;
                        dp[i][prevPick][k] = (pickInSubarr || stopHere);
                    }
                    else {
                        bool startNewFromCurr = (k - nums[i] < 0) ? false : dp[i + 1][true][k - nums[i]];
                        bool startNewFromNext = dp[i + 1][false][k];
                        dp[i][prevPick][k] = (startNewFromNext || startNewFromCurr);
                    }
                }
            }
        }

        return dp[0][false][given_k];
    }

    // O(N*GK) & O(N*GK) : Where GK = given_k
    bool solveBy3DEnhanced(const vector<int>& nums, int given_k) {
        vector<vector<vector<bool>>> dp(n + 1, vector<vector<bool>>(2, vector<bool>(given_k + 1, false)));
        
        // k == 0
        for(int i = 0; i <= n; ++i)
            for(int prevPick = 0; prevPick < 2; ++prevPick)
                dp[i][prevPick][0] = true;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                for(int k = 1; k <= given_k; ++k) {
                    if(prevPick) {
                        bool pickInSubarr = (k - nums[i] < 0) ? false : dp[i + 1][true][k - nums[i]];
                        bool stopHere = (k == 0) ? true : false;
                        dp[i][prevPick][k] = (pickInSubarr || stopHere);
                    }
                    else {
                        bool startNewFromCurr = (k - nums[i] < 0) ? false : dp[i + 1][true][k - nums[i]];
                        bool startNewFromNext = dp[i + 1][false][k];
                        dp[i][prevPick][k] = (startNewFromNext || startNewFromCurr);
                    }
                }
            }
        }

        return dp[0][false][given_k];
    }

    // O(N*K) & O(GK) : Where GK = given_k
    bool solveBy2DTable(const vector<int>& nums, int given_k) {
        vector<vector<bool>> next(2, vector<bool>(given_k + 1, false));
        vector<vector<bool>> curr(2, vector<bool>(given_k + 1, false));
        
        for(int prevPick = 0; prevPick < 2; ++prevPick) // Base case k == 0 for (i == n)
            next[prevPick][0] = true;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                curr[prevPick][0] = true; // Base case k == 0 for (i >= 0 && i <= n - 1)

                for(int k = 1; k <= given_k; ++k) {
                    if(prevPick) {
                        bool pickInSubarr = (k - nums[i] < 0) ? false : next[true][k - nums[i]];
                        bool stopHere = (k == 0) ? true : false;
                        curr[prevPick][k] = (pickInSubarr || stopHere);
                    }
                    else {
                        bool startNewFromCurr =(k - nums[i] < 0) ? false : next[true][k - nums[i]];
                        bool startNewFromNext = next[false][k];
                        curr[prevPick][k] = (startNewFromNext || startNewFromCurr);
                    }
                }
            }

            swap(next, curr);
        }

        return next[false][given_k];
    }

public:
    int isSubarraySumK(vector<int>& nums, int k) {
        n = nums.size();
        return solveBy2DTable(nums, k);
    }
};

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    vector<int> nums = {1, 4, 3, 7, 2};
    const int k = 9;

    TopDown td;
    if(td.isSubarraySumK(nums, k)) {
        cout << "From Memoization: YES" << '\n';
    } 
    else {
        cout << "From Memoization: NO" << '\n';
    }

    BottomUp bu;
    if(bu.isSubarraySumK(nums, k)) {
        cout << "From Bottom up: YES" << '\n';
    } 
    else {
        cout << "From Bottom up: NO" << '\n';
    }

    return 0;
}
