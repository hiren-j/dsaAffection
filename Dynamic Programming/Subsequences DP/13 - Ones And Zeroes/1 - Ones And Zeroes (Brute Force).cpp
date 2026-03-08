// Code to find the size of the largest subset of strs such that there are at most m 0's and n 1's in the subset (A set x is a subset of a set y if all elements of x are also elements of y) ~ coded by vHiren

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int arrSize;

    // O(2^AS * K) & O(AS) : Where AS = arrSize, K = maximum size among all arr[i]
    int solveWithoutMemo(const vector<string>& arr, int i, int n, int m) {
        if(n < 0 || m < 0)
            return INT_MIN;

        if(i == arrSize)
            return (n >= 0 && m >= 0) ? 0 : INT_MIN;

        int currSkip = solveWithoutMemo(arr, i + 1, n, m);

        int cnt1 = 0, cnt0 = 0;
        for(const char ch : arr[i]) ch == '1' ? cnt1++ : cnt0++;
        int currTake = solveWithoutMemo(arr, i + 1, n - cnt1, m - cnt0);
        if(currTake != INT_MIN) currTake += 1;

        return max(currTake, currSkip);
    }

    // O(AS*N*M*K) & O(AS*N*M) : Where AS = arrSize, K = maximum size among all arr[i]
    int solveWithMemo(vector<vector<vector<int>>>& dp, const vector<string>& arr, int i, int n, int m) {
        if(n < 0 || m < 0)
            return INT_MIN;

        if(i == arrSize)
            return (n >= 0 && m >= 0) ? 0 : INT_MIN;

        if(dp[i][n][m] != -1)
            return dp[i][n][m];

        int currSkip = solveWithMemo(dp, arr, i + 1, n, m);

        int cnt1 = 0, cnt0 = 0;
        for(const char ch : arr[i]) ch == '1' ? cnt1++ : cnt0++;
        int currTake = solveWithMemo(dp, arr, i + 1, n - cnt1, m - cnt0);
        if(currTake != INT_MIN) currTake += 1;

        return dp[i][n][m] = max(currTake, currSkip);
    }

    // O(AS*AS*N*M*K) & O(AS*N*M) : Where AS = arrSize, K = maximum size among all arr[i]
    int solveWithMemoLoop(vector<vector<vector<int>>>& dp, const vector<string>& arr, int start, int n, int m) {
        if(n < 0 || m < 0)
            return INT_MIN;

        if(start == arrSize)
            return (n >= 0 && m >= 0) ? 0 : INT_MIN;

        if(dp[start][n][m] != -1)
            return dp[start][n][m];

        int maxLen = (n >= 0 && m >= 0) ? 0 : INT_MIN;

        for(int i = start; i < arrSize; ++i) {
            int cnt1 = 0, cnt0 = 0;
            for(const char ch : arr[i]) ch == '1' ? cnt1++ : cnt0++;
            int currTake = solveWithMemoLoop(dp, arr, i + 1, n - cnt1, m - cnt0);
            if(currTake != INT_MIN) currTake += 1;
            maxLen = max(maxLen, currTake);
        }

        return dp[start][n][m] = maxLen;
    }

public:
    int findMaxForm(vector<string>& arr, int m, int n) {
        arrSize = arr.size();
        vector<vector<vector<int>>> dp(arrSize, vector<vector<int>>(n + 1, vector<int>(m + 1, -1)));
        return solveWithMemo(dp, arr, 0, n, m);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
class BottomUp {
    int arrSize;

    // O(AS*GN*GM*K) & O(AS*GN*GM) : Where AS = arrSize, GN = given_n, GM = given_m, K = maximum size among all arr[i]
    int solveBy3DTable(const vector<string>& arr, int given_n, int given_m) {
        vector<vector<vector<int>>> dp(arrSize + 1, vector<vector<int>>(given_n + 1, vector<int>(given_m + 1, -1)));

        for(int n = 0; n <= given_n; ++n)
            for(int m = 0; m <= given_m; ++m)
                dp[arrSize][n][m] = (n >= 0 && m >= 0) ? 0 : INT_MIN;

        for(int i = arrSize - 1; i >= 0; --i) {
            for(int n = 0; n <= given_n; ++n) {
                for(int m = 0; m <= given_m; ++m) {
                    int currSkip = dp[i + 1][n][m];

                    int cnt1 = 0, cnt0 = 0;
                    for(const char ch : arr[i]) ch == '1' ? cnt1++ : cnt0++;
                    int currTake = (n - cnt1 < 0 || m - cnt0 < 0) ? INT_MIN : dp[i + 1][n - cnt1][m - cnt0];
                    if(currTake != INT_MIN) currTake += 1;

                    dp[i][n][m] = max(currTake, currSkip);
                }
            }
        }

        return dp[0][given_n][given_m];
    }

    // O(AS*GN*GM*K) & O(GN*GM) : Where AS = arrSize, GN = given_n, GM = given_m, K = maximum size among all arr[i]
    int solveBy2DTable(const vector<string>& arr, int given_n, int given_m) {
        vector<vector<int>> next(given_n + 1, vector<int>(given_m + 1, -1)); // i + 1th table
        vector<vector<int>> curr(given_n + 1, vector<int>(given_m + 1, -1)); // i + 1th table

        for(int n = 0; n <= given_n; ++n)
            for(int m = 0; m <= given_m; ++m)
                next[n][m] = (n >= 0 && m >= 0) ? 0 : INT_MIN;

        for(int i = arrSize - 1; i >= 0; --i) {
            for(int n = 0; n <= given_n; ++n) {
                for(int m = 0; m <= given_m; ++m) {
                    int currSkip = next[n][m];

                    int cnt1 = 0, cnt0 = 0;
                    for(const char ch : arr[i]) ch == '1' ? cnt1++ : cnt0++;
                    int currTake = (n - cnt1 < 0 || m - cnt0 < 0) ? INT_MIN : next[n - cnt1][m - cnt0];
                    if(currTake != INT_MIN) currTake += 1;

                    curr[n][m] = max(currTake, currSkip);
                }
            }
            swap(next, curr);
        }

        return next[given_n][given_m];
    }

public:
    int findMaxForm(vector<string>& arr, int m, int n) {
        arrSize = arr.size();
        return solveBy2DTable(arr, n, m);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  
Topics: Array | String | Dynamic Programming
Link  : https://leetcode.com/problems/ones-and-zeroes/description/
