// Code to find the maximum total energy boost you can gain in the next n hours by following the specified instructions ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long LL;
    int n;

    // O(2^N) & O(N)
    LL solveWithoutMemo(vector<int>& energyDrinkA, vector<int>& energyDrinkB, int i, bool pickDrinkA) {
        if(i >= n)
            return 0;

        if(pickDrinkA) {
            LL drinkAndMove   = solveWithoutMemo(energyDrinkA, energyDrinkB, i + 1, true);
            LL drinkAndSwitch = solveWithoutMemo(energyDrinkA, energyDrinkB, i + 2, false);
            return energyDrinkA[i] + max(drinkAndMove, drinkAndSwitch);
        }
        else {
            LL drinkAndMove   = solveWithoutMemo(energyDrinkA, energyDrinkB, i + 1, false); 
            LL drinkAndSwitch = solveWithoutMemo(energyDrinkA, energyDrinkB, i + 2, true); 
            return energyDrinkB[i] + max(drinkAndMove, drinkAndSwitch);
        }
    }

    // O(2*N*2) & O(N*2 + N)
    LL solveWithMemo(vector<vector<LL>>& dp, vector<int>& energyDrinkA, vector<int>& energyDrinkB, int i, bool pickDrinkA) {
        if(i >= n)
            return 0;

        if(dp[i][pickDrinkA] != -1)
            return dp[i][pickDrinkA];

        if(pickDrinkA) {
            LL drinkAndMove   = solveWithMemo(dp, energyDrinkA, energyDrinkB, i + 1, true);
            LL drinkAndSwitch = solveWithMemo(dp, energyDrinkA, energyDrinkB, i + 2, false);
            return dp[i][pickDrinkA] = energyDrinkA[i] + max(drinkAndMove, drinkAndSwitch);
        }
        else {
            LL drinkAndMove   = solveWithMemo(dp, energyDrinkA, energyDrinkB, i + 1, false); 
            LL drinkAndSwitch = solveWithMemo(dp, energyDrinkA, energyDrinkB, i + 2, true); 
            return dp[i][pickDrinkA] = energyDrinkB[i] + max(drinkAndMove, drinkAndSwitch);
        }
    }

public:
    LL maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        n = energyDrinkA.size();
        
        vector<vector<LL>> dp1(n, vector<LL>(2, -1)), dp2(n, vector<LL>(2, -1));

        LL maxEnergyA = solveWithMemo(dp1, energyDrinkA, energyDrinkB, 0, true);
        LL maxEnergyB = solveWithMemo(dp2, energyDrinkA, energyDrinkB, 0, false);

        return max(maxEnergyA, maxEnergyB);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long LL;
    int n;

    // O(N*2) & O(N*2)
    LL solveWith2DTable(vector<int>& energyDrinkA, vector<int>& energyDrinkB, bool startFromA) {
        vector<vector<LL>> dp(n + 1, vector<LL>(2, -1));
        dp[n][0] = 0;
        dp[n][1] = 0;

        for(int i = n-1; i >= 0; --i) {
            for(int pickDrinkA = !startFromA; (startFromA ? pickDrinkA <= 1 : pickDrinkA >= 0); (startFromA ? ++pickDrinkA : --pickDrinkA)) {
                if(pickDrinkA) {
                    LL drinkAndMove   = dp[i + 1][true];
                    LL drinkAndSwitch = (i + 2 <= n) ? dp[i + 2][false] : 0;
                    dp[i][pickDrinkA] = energyDrinkA[i] + max(drinkAndMove, drinkAndSwitch);
                }
                else {
                    LL drinkAndMove   = dp[i + 1][false]; 
                    LL drinkAndSwitch = (i + 2 <= n) ? dp[i + 2][true] : 0; 
                    dp[i][pickDrinkA] = energyDrinkB[i] + max(drinkAndMove, drinkAndSwitch);
                }
            }
        }

        return dp[0][startFromA];
    }

    // O(N*2) & O(2*2)
    LL solveWith1DTable(vector<int>& energyDrinkA, vector<int>& energyDrinkB, bool startFromA) {
        vector<LL> prevRow(2, -1), prevPrevRow(2, -1);
        prevRow[0] = 0;
        prevRow[0] = 0;

        for(int i = n-1; i >= 0; --i) {
            vector<LL> currRow(2, -1);

            for(int pickDrinkA = !startFromA; (startFromA ? pickDrinkA <= 1 : pickDrinkA >= 0); (startFromA ? ++pickDrinkA : --pickDrinkA)) {
                if(pickDrinkA) {
                    LL drinkAndMove   = prevRow[true];
                    LL drinkAndSwitch = (i + 2 <= n) ? prevPrevRow[false] : 0;
                    currRow[pickDrinkA] = energyDrinkA[i] + max(drinkAndMove, drinkAndSwitch);
                }
                else {
                    LL drinkAndMove   = prevRow[false]; 
                    LL drinkAndSwitch = (i + 2 <= n) ? prevPrevRow[true] : 0; 
                    currRow[pickDrinkA] = energyDrinkB[i] + max(drinkAndMove, drinkAndSwitch);
                }
            }

            prevPrevRow = prevRow;
            prevRow = currRow;
        }

        return prevRow[startFromA];
    }

    // O(N*2) & O(1)
    LL solveWithoutTable(vector<int>& energyDrinkA, vector<int>& energyDrinkB, bool startFromA) {
        LL prevRow_0 = 0;
        LL prevRow_1 = 0;
        LL prevPrevRow_0 = -1;
        LL prevPrevRow_1 = -1;

        for(int i = n-1; i >= 0; --i) {
            LL currRow_0 = -1;
            LL currRow_1 = -1;

            for(int pickDrinkA = !startFromA; (startFromA ? pickDrinkA <= 1 : pickDrinkA >= 0); (startFromA ? ++pickDrinkA : --pickDrinkA)) {
                if(pickDrinkA) {
                    LL drinkAndMove   = prevRow_1;
                    LL drinkAndSwitch = (i + 2 <= n) ? prevPrevRow_0 : 0;
                    currRow_1 = energyDrinkA[i] + max(drinkAndMove, drinkAndSwitch);
                }
                else {
                    LL drinkAndMove   = prevRow_0; 
                    LL drinkAndSwitch = (i + 2 <= n) ? prevPrevRow_1 : 0; 
                    currRow_0 = energyDrinkB[i] + max(drinkAndMove, drinkAndSwitch);
                }
            }

            prevPrevRow_0 = prevRow_0;
            prevPrevRow_1 = prevRow_1;
            prevRow_0 = currRow_0;
            prevRow_1 = currRow_1;
        }

        return (startFromA) ? prevRow_1 : prevRow_0;
    }

public:
    LL maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        n = energyDrinkA.size();
    
        LL maxEnergyA = solveWithoutTable(energyDrinkA, energyDrinkB, true);
        LL maxEnergyB = solveWithoutTable(energyDrinkA, energyDrinkB, false);

        return max(maxEnergyA, maxEnergyB);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/description/
