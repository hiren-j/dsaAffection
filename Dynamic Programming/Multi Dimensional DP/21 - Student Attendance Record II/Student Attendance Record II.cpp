// Code to find the number of possible attendance records of length N that make a student eligible for an attendance award ~ coded by vHiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9 + 7;

    // O(3^N) & O(N)
    int solveWithoutMemo(int N, int consecutiveLate, int absences) {
        if(consecutiveLate == 3 || absences == 2)
            return 0;

        if(N == 0)
            return 1;

        int P = solveWithoutMemo(N - 1, 0, absences);
        int A = solveWithoutMemo(N - 1, 0, absences + 1);
        int L = solveWithoutMemo(N - 1, consecutiveLate + 1, absences);

        return ((P + A) % MOD + L) % MOD;
    }
    
    // O(3*N*3*2) & O(N*3*2 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int N, int consecutiveLate, int absences) {
        if(consecutiveLate == 3 || absences == 2)
            return 0;

        if(N == 0)
            return 1;

        if(memory[N][consecutiveLate][absences] != -1)
            return memory[N][consecutiveLate][absences];

        int P = solveWithMemo(memory, N - 1, 0, absences);
        int A = solveWithMemo(memory, N - 1, 0, absences + 1);
        int L = solveWithMemo(memory, N - 1, consecutiveLate + 1, absences);

        return memory[N][consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;
    }

public:
    int waysToBuildRecords(int N) {
        vector<vector<vector<int>>> memory(N + 1, vector<vector<int>>(3, vector<int>(2, -1)));
        return solveWithMemo(memory, N, 0, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9 + 7;
    
    // O(GN*3*2) & O(GN*4*3) : Where GN = given_N
    int solveBy3DTable(int given_N) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(4, vector<int>(3, -1)));

        for(int N = 0; N <= given_N; ++N)
            for(int absences = 0; absences < 3; ++absences)
                dp[N][3][absences] = 0;

        for(int N = 0; N <= given_N; ++N)
            for(int consecutiveLate = 0; consecutiveLate < 4; ++consecutiveLate)
                dp[N][consecutiveLate][2] = 0;

        for(int consecutiveLate = 0; consecutiveLate <= 2; ++consecutiveLate)
            for(int absences = 0; absences <= 1; ++absences)
                dp[0][consecutiveLate][absences] = 1;

        for(int N = 1; N <= given_N; ++N) {
            for(int consecutiveLate = 2; consecutiveLate >= 0; --consecutiveLate) {
                for(int absences = 1; absences >= 0; --absences) {
                    int P = dp[N - 1][0][absences];
                    int A = dp[N - 1][0][absences + 1];
                    int L = dp[N - 1][consecutiveLate + 1][absences];
                    dp[N][consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;   
                }
            }
        }

        return dp[given_N][0][0];
    }

    // O(GN*3*2) & O(GN*4*3) : Where GN = given_N
    int solveBy3DEnhanced(int given_N) {
        vector<vector<vector<int>>> dp(given_N + 1, vector<vector<int>>(4, vector<int>(3, 0)));

        for(int consecutiveLate = 0; consecutiveLate <= 2; ++consecutiveLate)
            for(int absences = 0; absences <= 1; ++absences)
                dp[0][consecutiveLate][absences] = 1;

        for(int N = 1; N <= given_N; ++N) {
            for(int consecutiveLate = 2; consecutiveLate >= 0; --consecutiveLate) {
                for(int absences = 1; absences >= 0; --absences) {
                    int P = dp[N - 1][0][absences];
                    int A = dp[N - 1][0][absences + 1];
                    int L = dp[N - 1][consecutiveLate + 1][absences];
                    dp[N][consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;   
                }
            }
        }

        return dp[given_N][0][0];
    }

    // O(GN*(4*3 + 3*2)) & O(2*4*3) : Where GN = given_N
    int solveBy2DTable(int given_N) {
        vector<vector<int>> prev(4, vector<int>(3, 0)), curr(4, vector<int>(3, 0));

        for(int consecutiveLate = 0; consecutiveLate <= 2; ++consecutiveLate)
            for(int absences = 0; absences <= 1; ++absences)
                prev[consecutiveLate][absences] = 1;

        for(int N = 1; N <= given_N; ++N) {
            for(int consecutiveLate = 2; consecutiveLate >= 0; --consecutiveLate) {
                for(int absences = 1; absences >= 0; --absences) {
                    int P = prev[0][absences];
                    int A = prev[0][absences + 1];
                    int L = prev[consecutiveLate + 1][absences];
                    curr[consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;   
                }
            }
            swap(prev, curr);
        }

        return prev[0][0];
    }

public:
    int waysToBuildRecords(int N) {
        return solveBy2DTable(N);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Combinatorics | Dynamic Programming
Link  : https://leetcode.com/problems/student-attendance-record-ii/description/?envType=daily-question&envId=2024-05-26
