// Code to find the number of ways to build the array under the mentioned conditions ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(M^N) & O(N)
    int solveWithoutMemo(int N, int M, int K, int maxElement) {
        if(N == 0)
            return K == 0;

        if(K < 0)
            return 0;

        int count = 0;

        for(int num = 1; num <= M; ++num) {
            int maxCopy = maxElement;
            int newK = K;
            if(num > maxCopy) {
                maxCopy = num;
                newK--;
            }
            int nextCount = solveWithoutMemo(N - 1, M, newK, maxCopy);
            count = (count + nextCount) % MOD;
        }

        return count;
    }

    // O(M*N*K*M) & O(N*K*M + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int N, int M, int K, int maxElement) {
        if(N == 0)
            return K == 0;

        if(K < 0)
            return 0;

        if(dp[N][K][maxElement] != -1)
            return dp[N][K][maxElement];

        int count = 0;

        for(int num = 1; num <= M; ++num) {
            int maxCopy = maxElement;
            int newK = K;
            if(num > maxCopy) {
                maxCopy = num;
                newK--;
            }
            int nextCount = solveWithMemo(dp, N - 1, M, newK, maxCopy);
            count = (count + nextCount) % MOD;
        }

        return dp[N][K][maxElement] = count;
    }

public:
    int numOfArrays(int N, int M, int K) {
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(K + 1, vector<int>(M + 1, -1)));
        return solveWithMemo(dp, N, M, K, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;

    // O(N*K*M*M) & O(N*K*M)
    int solveWith3DTable(int given_N, int given_M, int given_K) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(given_K + 1, vector<int>(given_M + 1, 0)));

        for(int maxElement = 0; maxElement <= given_M; ++maxElement)
            dp[0][0][maxElement] = 1;

        for(int N = 1; N <= given_N; ++N) {
            for(int K = 0; K <= given_K; ++K) {
                for(int maxElement = given_M; maxElement >= 0; --maxElement) {
                    int count = 0;

                    for(int num = 1; num <= given_M; ++num) {
                        int maxCopy = maxElement;
                        int newK = K;
                        if(num > maxCopy) {
                            maxCopy = num;
                            newK--;
                        }
                        int nextCount = (newK < 0) ? 0 : dp[N - 1][newK][maxCopy];
                        count = (count + nextCount) % MOD;
                    }

                    dp[N][K][maxElement] = count;
                }
            }
        }

        return dp[given_N][given_K][0];
    }

    // O(N*K*M*M) & O(2*K*M)
    int solveWith2DTable(int given_N, int given_M, int given_K) {
        vector<vector<int>> prevRow(given_K + 1, vector<int>(given_M + 1, 0));
        vector<vector<int>> idealRow(given_K + 1, vector<int>(given_M + 1, 0));

        for(int maxElement = 0; maxElement <= given_M; ++maxElement)
            prevRow[0][maxElement] = 1;

        for(int N = 1; N <= given_N; ++N) {
            for(int K = 0; K <= given_K; ++K) {
                for(int maxElement = given_M; maxElement >= 0; --maxElement) {
                    int count = 0;

                    for(int num = 1; num <= given_M; ++num) {
                        int maxCopy = maxElement;
                        int newK = K;
                        if(num > maxCopy) {
                            maxCopy = num;
                            newK--;
                        }
                        int nextCount = (newK < 0) ? 0 : prevRow[newK][maxCopy];
                        count = (count + nextCount) % MOD;
                    }

                    idealRow[K][maxElement] = count;
                }
            }
            swap(prevRow, idealRow);
        }

        return prevRow[given_K][0];
    }

public:
    int numOfArrays(int N, int M, int K) {
        return solveWith2DTable(N, M, K);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Prefix Sum | Weekly Contest 185
Link  : https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/description/
