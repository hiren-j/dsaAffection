// Code to find the minimal difference between angles of sectors that will go to Vasya and Petya ~ coded by vHiren
#include <iostream>
#include <vector>
using namespace std;

// O(N*AS) & O(N*AS) : Where AS = arrSum
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    int n, arrSum = 0;
    cin >> n;

    vector<int> nums(n);
    for(int& num : nums) {
        cin >> num;
        arrSum += num;
    }

    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(arrSum + 1, -1)));

    for(int prevPick = 0; prevPick < 2; ++prevPick)
        for(int k = 0; k <= arrSum; ++k)
            dp[n][prevPick][k] = (k == 0) ? true : false;    

    for(int i = n - 1; i >= 0; --i) {
        for(int prevPick = 1; prevPick >= 0; --prevPick) {
            for(int k = 0; k <= arrSum; ++k) {
                if(prevPick) {
                    bool pickInSubarr = (k - nums[i] < 0) ? false : dp[i + 1][true][k - nums[i]];
                    bool stopHere = (k == 0) ? true : false;
                    dp[i][prevPick][k] = (pickInSubarr || stopHere);
                }
                else {
                    bool startCurr = (k - nums[i] < 0) ? false : dp[i + 1][true][k - nums[i]];
                    bool startNext = dp[i + 1][false][k];
                    dp[i][prevPick][k] = (startCurr || startNext);
                }
            }
        }
    }        

    int result = INT_MAX;
    for(int subarr1Sum = 0; subarr1Sum <= arrSum; ++subarr1Sum) {
        if(dp[0][false][arrSum]) {
            int subarr2Sum = arrSum - subarr1Sum;
            result = min(result, abs(subarr1Sum - subarr2Sum));
        }
    }
    cout << result;

    return 0;
}
// Link: https://codeforces.com/contest/895/problem/A
