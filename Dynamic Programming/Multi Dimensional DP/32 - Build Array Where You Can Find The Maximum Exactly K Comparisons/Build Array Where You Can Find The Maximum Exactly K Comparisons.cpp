// Code to find the number of ways to build the array under the mentioned conditions ~ coded by Hiren

-----------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;
    int M;

    // O(M^N) & O(N)
    int solveWithoutMemo(int N, int K, int maxElement) {
        if(K < 0)
            return 0;

        if(N == 0)
            return (K == 0) ? 1 : 0;

        int count = 0;

        for(int val = 1; val <= M; ++val) {
            int new_max = maxElement;
            int new_K   = K;
            if(val > maxElement) {
                new_max = val;
                new_K--;
            }
            int nextCount = solveWithoutMemo(N - 1, new_K, new_max);
            count = (count + nextCount) % MOD;
        }

        return count;
    }

    // O(M*N*K*M) & O(N*K*M + N)
    int solveWithMemo(vector<vector<vector<int>>>& dp, int N, int K, int maxElement) {
        if(K < 0)
            return 0;

        if(N == 0)
            return (K == 0) ? 1 : 0;

        if(dp[N][K][maxElement] != -1)
            return dp[N][K][maxElement];

        int count = 0;

        for(int val = 1; val <= M; ++val) {
            int new_max = maxElement;
            int new_K   = K;
            if(val > maxElement) {
                new_max = val;
                new_K--;
            }
            int nextCount = solveWithMemo(dp, N - 1, new_K, new_max);
            count = (count + nextCount) % MOD;
        }

        return dp[N][K][maxElement] = count;
    }

public:
    int numOfArrays(int N, int m, int K) {
        M = m;
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(K + 1, vector<int>(M + 1, -1)));
        return solveWithMemo(dp, N, K, 0);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    int M;

    // O(GN*GK*M*M) & O(GN*GK*M) : Where GN = given_N, GK = given_K
    int solveBy3DShifting(int given_N, int given_K) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(given_K + 2, vector<int>(M + 1, -1)));

        for(int N = 0; N <= given_N; ++N) 
            for(int maxElement = 0; maxElement <= M; ++maxElement)
                dp[N][-1+1][maxElement] = 0;

        for(int maxElement = 0; maxElement <= M; ++maxElement)
            dp[0][0+1][maxElement] = 1;
        
        for(int K = 1; K <= given_K; ++K)
            for(int maxElement = 0; maxElement <= M; ++maxElement)
                dp[0][K+1][maxElement] = 0;

        for(int N = 1; N <= given_N; ++N) {
            for(int K = 0; K <= given_K; ++K) {
                for(int maxElement = M; maxElement >= 0; --maxElement) {
                    int count = 0;
            
                    for(int val = 1; val <= M; ++val) {
                        int new_max = maxElement;
                        int new_K   = K;
                        if(val > maxElement) {
                            new_max = val;
                            new_K--;
                        }
                        int nextCount = dp[N - 1][new_K + 1][new_max];
                        count = (count + nextCount) % MOD;
                    }
            
                    dp[N][K+1][maxElement] = count;
                }
            }
        }

        return dp[given_N][given_K + 1][0];
    }

    // O(GN*GK*M*M) & O(GN*GK*M) : Where GN = given_N, GK = given_K
    int solveBy3DTable(int given_N, int given_K) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(given_K + 1, vector<int>(M + 1, -1)));

        for(int maxElement = 0; maxElement <= M; ++maxElement)
            dp[0][0][maxElement] = 1;
        
        for(int K = 1; K <= given_K; ++K)
            for(int maxElement = 0; maxElement <= M; ++maxElement)
                dp[0][K][maxElement] = 0;

        for(int N = 1; N <= given_N; ++N) {
            for(int K = 0; K <= given_K; ++K) {
                for(int maxElement = M; maxElement >= 0; --maxElement) {
                    int count = 0;
            
                    for(int val = 1; val <= M; ++val) {
                        int new_max = maxElement;
                        int new_K   = K;
                        if(val > maxElement) {
                            new_max = val;
                            new_K--;
                        }
                        int nextCount = (new_K < 0) ? 0 : dp[N - 1][new_K][new_max];
                        count = (count + nextCount) % MOD;
                    }
            
                    dp[N][K][maxElement] = count;
                }
            }
        }

        return dp[given_N][given_K][0];
    }

    // O(GN*GK*M*M) & O(GN*GK*M) : Where GN = given_N, GK = given_K
    int solveBy3DEnhanced(int given_N, int given_K) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(given_K + 1, vector<int>(M + 1, 0)));

        for(int maxElement = 0; maxElement <= M; ++maxElement)
            dp[0][0][maxElement] = 1;
        
        for(int N = 1; N <= given_N; ++N) {
            for(int K = 0; K <= given_K; ++K) {
                for(int maxElement = M; maxElement >= 0; --maxElement) {
                    int count = 0;
            
                    for(int val = 1; val <= M; ++val) {
                        int new_max = maxElement;
                        int new_K   = K;
                        if(val > maxElement) {
                            new_max = val;
                            new_K--;
                        }
                        int nextCount = (new_K < 0) ? 0 : dp[N - 1][new_K][new_max];
                        count = (count + nextCount) % MOD;
                    }
            
                    dp[N][K][maxElement] = count;
                }
            }
        }

        return dp[given_N][given_K][0];
    }

    // O(GN*(GK*M + K*M*M)) & O(2*GK*M) : Where GN = given_N, GK = given_K
    int solveBy2DTable(int given_N, int given_K) {
        vector<vector<int>> prev(given_K + 1, vector<int>(M + 1, 0)); // N - 1th table
        vector<vector<int>> curr(given_K + 1, vector<int>(M + 1, 0)); // Nth table

        for(int maxElement = 0; maxElement <= M; ++maxElement)
            prev[0][maxElement] = 1;
        
        for(int N = 1; N <= given_N; ++N) {
            for(int K = 0; K <= given_K; ++K) {
                for(int maxElement = M; maxElement >= 0; --maxElement) {
                    int count = 0;
            
                    for(int val = 1; val <= M; ++val) {
                        int new_max = maxElement;
                        int new_K   = K;
                        if(val > maxElement) {
                            new_max = val;
                            new_K--;
                        }
                        int nextCount = (new_K < 0) ? 0 : prev[new_K][new_max];
                        count = (count + nextCount) % MOD;
                    }
            
                    curr[K][maxElement] = count;
                }
            }
            swap(prev, curr);
        }

        return prev[given_K][0];
    }

public:
    int numOfArrays(int N, int m, int K) {
        M = m;
        return solveBy2DTable(N, K);
    }
};

-----------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Dynamic Programming | Prefix Sum | Weekly Contest 185
Link  : https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/description/
