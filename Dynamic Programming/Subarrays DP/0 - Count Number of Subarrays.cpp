// Code to find the total number of non-empty subarrays ~ coded by vHiren
#include <iostream>
#include <vector>
using namespace std;

class TopDown {
    int n;

    // O(2^N) & O(N)
    int solveWithoutMemo(const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return prevPick;

        if(prevPick) {
            int pickCurrSubarr = solveWithoutMemo(nums, i + 1, true);
            int stopHere = prevPick;
            return (pickCurrSubarr + stopHere);
        }
        else {
            int startNewFromNext = solveWithoutMemo(nums, i + 1, false);
            int startNewFromCurr = solveWithoutMemo(nums, i + 1, true);
            return (startNewFromNext + startNewFromCurr);
        }
    }
    
    // O(2*N*2) & O(2*N)
    int solveWithMemo(vector<vector<int>>& dp, const vector<int>& nums, int i, bool prevPick) {
        if(i == n)
            return prevPick;

        if(dp[i][prevPick] != -1)
            return dp[i][prevPick];

        if(prevPick) {
            int pickCurrSubarr = solveWithMemo(dp, nums, i + 1, true);
            int stopHere = prevPick;
            return dp[i][prevPick] = (pickCurrSubarr + stopHere);
        }
        else {
            int startNewFromNext = solveWithMemo(dp, nums, i + 1, false);
            int startNewFromCurr = solveWithMemo(dp, nums, i + 1, true);
            return dp[i][prevPick] = (startNewFromNext + startNewFromCurr);
        }
    }

public:
    // Method to count total number of subarrays, using recursion with memoization - O(N) & O(N)
    int countSubarrays(vector<int>& nums) {
        n = nums.size();
        vector<vector<int>> dp(n, vector<int>(2, -1));
        return solveWithMemo(dp, nums, 0, false);
    }
};

class BottomUp {
    int n;

    // O(N*2) & O(N*2)
    int solveWith2DTable(const vector<int>& nums) {
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));
        dp[n][true]  = 1;
        dp[n][false] = 0;

        for(int i = n - 1; i >= 0; --i) {
            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = dp[i + 1][true];
                    int stopHere = prevPick;
                    dp[i][prevPick] = (pickCurrSubarr + stopHere);
                }
                else {
                    int startNewFromNext = dp[i + 1][false];
                    int startNewFromCurr = dp[i + 1][true];
                    dp[i][prevPick] = (startNewFromNext + startNewFromCurr);
                }     
            }
        }

        return dp[0][false];
    }

    // O(N*2) & O(2*2)
    int solveWith1DTable(const vector<int>& nums) {
        vector<int> nextRow(2, -1);
        nextRow[true]  = 1;
        nextRow[false] = 0;

        for(int i = n - 1; i >= 0; --i) {
            vector<int> currRow(2, -1);

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nextRow[true];
                    int stopHere = prevPick;
                    currRow[prevPick] = (pickCurrSubarr + stopHere);
                }
                else {
                    int startNewFromNext = nextRow[false];
                    int startNewFromCurr = nextRow[true];
                    currRow[prevPick] = (startNewFromNext + startNewFromCurr);
                }     
            }

            swap(nextRow, currRow);
        }

        return nextRow[false];
    }

    // O(N*2) & O(1)
    int solveWithoutTable(const vector<int>& nums) {;
        int nextRow_1 = 1;
        int nextRow_0 = 0;

        for(int i = n - 1; i >= 0; --i) {
            int currRow_1  = -1;
            int currRow_0 = -1;

            for(int prevPick = 1; prevPick >= 0; --prevPick) {
                if(prevPick) {
                    int pickCurrSubarr = nextRow_1;
                    int stopHere = prevPick;
                    currRow_1 = (pickCurrSubarr + stopHere);
                }
                else {
                    int startNewFromNext = nextRow_0;
                    int startNewFromCurr = nextRow_1;
                    currRow_0 = (startNewFromNext + startNewFromCurr);
                }     
            }

            swap(nextRow_0, currRow_0);
            swap(nextRow_1, currRow_1);
        }

        return nextRow_0;
    }

public:
    int countSubarrays(vector<int>& nums) {
        n = nums.size();
        return solveWithoutTable(nums);
    }
};

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "From Formula: " << nums.size() * (nums.size() + 1) / 2 << '\n';

    TopDown td;
    cout << "From Memoization: " << td.countSubarrays(nums) << '\n';

    BottomUp bu;
    cout << "From Bottom Up: " << bu.countSubarrays(nums);

    return 0;
}
