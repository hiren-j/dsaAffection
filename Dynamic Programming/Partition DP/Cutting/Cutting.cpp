// Author: vHiren
#include <iostream>
#include <cstdint>
#include <cstring>
#include <vector>
#define input 0
#define LL long long
#define P pair<int, int>
using namespace std;

void solve() {
    int n, target;
    cin >> n >> target;
    
    vector<int> nums(n);
    for(int& num : nums) 
        cin >> num;

    int dp[101][101];
    memset(dp, 0, sizeof(dp));

    for(int start = n - 1; start >= 0; --start) {
        for(int k = 0; k <= target; ++k) {
            int evens = 0, odds = 0;
            int maxCuts = 0;

            for(int i = start; i < n; ++i) {
                (nums[i] & 1) == 0 ? evens++ : odds++;
                if(evens != odds) continue;
                const int delta = (i < n - 1) ? abs(nums[i + 1] - nums[i]) : 0;
                const int next  = (k - delta < 0) ? INT_MIN : dp[i + 1][k - delta];
                if(next != INT_MIN) maxCuts = max(maxCuts, next + 1);
            }

            dp[start][k] = maxCuts;
        }
    }

    cout << dp[0][target] - 1;
}

// Driver code
__int32 main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    uint32_t t = 1;
    if(input) cin >> t;
    while(t--) solve();

    return 0;
}
// Link: https://codeforces.com/contest/998/problem/B
