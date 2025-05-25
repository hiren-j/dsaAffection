// Code to find the number of possible attendance records of length N that make a student eligible for an attendance award ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    const int MOD = 1e9+7;
    const int maxLate = 3, maxAbsences = 2;

    int solveWithoutMemo(int N, int consecutiveLate, int absences) {
        if(consecutiveLate == maxLate || absences == maxAbsences)
            return 0; // Edge case: If the student goes late for consecutively 3 days or absent for 2 days then its not valid

        if(N == 0)
            return 1; // Edge case: If it's possible to create a valid attendence record of length N then there's one way

        // There are three possibilities the student can perform each day
        int P = solveWithoutMemo(N - 1, 0, absences);                   // Is to present
        int A = solveWithoutMemo(N - 1, 0, absences + 1);               // Is to go absent
        int L = solveWithoutMemo(N - 1, consecutiveLate + 1, absences); // Is to go late

        return ((P + A) % MOD + L) % MOD;
    }

    int solveWithMemo(vector<vector<vector<int>>>& memory, int N, int consecutiveLate, int absences) {
        if(consecutiveLate == maxLate || absences == maxAbsences)
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
    int checkRecord(int N) {
        vector<vector<vector<int>>> memory(N + 1, vector<vector<int>>(maxLate, vector<int>(maxAbsences, -1)));
        return solveWithMemo(memory, N, 0, 0);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    const int MOD = 1e9+7;
    const int maxLate = 3, maxAbsences = 2;

    int solveWith3DTable(int N) {
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(maxLate, vector<int>(maxAbsences, -1)));
        
        for(int consecutiveLate = 0; consecutiveLate < maxLate; ++consecutiveLate) // Init second edge case
            for(int absences = 0; absences < maxAbsences; ++absences)
                dp[0][consecutiveLate][absences] = 1;
        
        for(int day = 1; day <= N; ++day) {
            for(int consecutiveLate = maxLate-1; consecutiveLate >= 0; --consecutiveLate) {
                for(int absences = maxAbsences-1; absences >= 0; --absences) {
                    int P = dp[day - 1][0][absences];
                    int A = (absences + 1 < maxAbsences) ? dp[day - 1][0][absences + 1] : 0;
                    int L = (consecutiveLate + 1 < maxLate) ? dp[day - 1][consecutiveLate + 1][absences] : 0;
                    dp[day][consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;
                }
            }
        }
        
        return dp[N][0][0];
    }

    int solveWith3DEnhanced(int N) {
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(maxLate + 1, vector<int>(maxAbsences + 1, 0)));
        
        for(int consecutiveLate = 0; consecutiveLate < maxLate; ++consecutiveLate)
            for(int absences = 0; absences < maxAbsences; ++absences)
                dp[0][consecutiveLate][absences] = 1;
        
        for(int day = 1; day <= N; ++day) {
            for(int consecutiveLate = maxLate-1; consecutiveLate >= 0; --consecutiveLate) {
                for(int absences = maxAbsences-1; absences >= 0; --absences) {
                    int P = dp[day - 1][0][absences];
                    int A = dp[day - 1][0][absences + 1];
                    int L = dp[day - 1][consecutiveLate + 1][absences];
                    dp[day][consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;
                }
            }
        }
        
        return dp[N][0][0];
    }

    int solveWith2DTable(int N) {
        vector<vector<int>> prevRow(maxLate + 1, vector<int>(maxAbsences + 1, 0)), idealRow(maxLate + 1, vector<int>(maxAbsences + 1, 0));

        for(int consecutiveLate = 0; consecutiveLate < maxLate; ++consecutiveLate)
            for(int absences = 0; absences < maxAbsences; ++absences)
                prevRow[consecutiveLate][absences] = 1;
        
        for(int day = 1; day <= N; ++day) {
            for(int consecutiveLate = maxLate-1; consecutiveLate >= 0; --consecutiveLate) {
                for(int absences = maxAbsences-1; absences >= 0; --absences) {
                    int P = prevRow[0][absences];
                    int A = prevRow[0][absences + 1];
                    int L = prevRow[consecutiveLate + 1][absences];
                    idealRow[consecutiveLate][absences] = ((P + A) % MOD + L) % MOD;
                }
            }
            prevRow = idealRow;
        }
        
        return prevRow[0][0];
    }

public:
    int checkRecord(int N) {
        return solveWith2DTable(N);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Combinatorics | Dynamic Programming
Link  : https://leetcode.com/problems/student-attendance-record-ii/description/?envType=daily-question&envId=2024-05-26
