// Code to find the maximum total energy boost you can gain in the next n hours by following the specified instructions ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*
  NOTE: In the previous solution, we're using the same redundant code in both if and else block, here I just removed that redundancy, 
        so I could say approach remains the same but the code looks more shorter now.
*/  
  
---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    using LL = long long;
    int n;

    // O(2^N) & O(N)
    LL solveWithoutMemo(vector<int>& energyDrinkA, vector<int>& energyDrinkB, int i, bool pickA) {
        if(i >= n)
            return 0;

        LL drinkAndMove   = solveWithoutMemo(energyDrinkA, energyDrinkB, i + 1, (pickA ? true : false));
        LL drinkAndSwitch = solveWithoutMemo(energyDrinkA, energyDrinkB, i + 2, (pickA ? false : true));

        return (pickA ? energyDrinkA[i] : energyDrinkB[i]) + max(drinkAndMove, drinkAndSwitch);
    }

    // O(2*N*2) & O(N*2+N)
    LL solveWithMemo(vector<vector<LL>>& dp, vector<int>& energyDrinkA, vector<int>& energyDrinkB, int i, bool pickA) {
        if(i >= n)
            return 0;

        if(dp[i][pickA] != -1)
            return dp[i][pickA];

        LL drinkAndMove   = solveWithMemo(dp, energyDrinkA, energyDrinkB, i + 1, (pickA ? true : false));
        LL drinkAndSwitch = solveWithMemo(dp, energyDrinkA, energyDrinkB, i + 2, (pickA ? false : true));

        return dp[i][pickA] = (pickA ? energyDrinkA[i] : energyDrinkB[i]) + max(drinkAndMove, drinkAndSwitch);
    }

public:
    // Method to find maximum energy boost, using recursion with memoization - O(N) & O(N)
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
    using LL = long long;
    int n;

    // O(N*2) & O(N*2)
    LL solveWith2DTable(vector<int>& energyDrinkA, vector<int>& energyDrinkB, bool startFromA) {
        vector<vector<LL>> dp(n + 1, vector<LL>(2, -1));
        dp[n][0] = 0;
        dp[n][1] = 0;

        for(int i = n-1; i >= 0; --i) {
            for(int pickA = !startFromA; (startFromA ? pickA <= 1 : pickA >= 0); (startFromA ? ++pickA : --pickA)) {
                LL drinkAndMove   = dp[i + 1][pickA ? true : false];
                LL drinkAndSwitch = (i + 2 <= n) ? dp[i + 2][pickA ? false : true] : 0;
                dp[i][pickA] = (pickA ? energyDrinkA[i] : energyDrinkB[i]) + max(drinkAndMove, drinkAndSwitch);
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

            for(int pickA = !startFromA; (startFromA ? pickA <= 1 : pickA >= 0); (startFromA ? ++pickA : --pickA)) {
                LL drinkAndMove   = prevRow[pickA ? true : false];
                LL drinkAndSwitch = (i + 2 <= n) ? prevPrevRow[pickA ? false : true] : 0;
                currRow[pickA] = (pickA ? energyDrinkA[i] : energyDrinkB[i]) + max(drinkAndMove, drinkAndSwitch);
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

            for(int pickA = !startFromA; (startFromA ? pickA <= 1 : pickA >= 0); (startFromA ? ++pickA : --pickA)) {
                LL drinkAndMove   = (pickA ? prevRow_1 : prevRow_0);
                LL drinkAndSwitch = (i + 2 <= n ? (pickA ? prevPrevRow_0 : prevPrevRow_1) : 0);
                LL maxEnergy = (pickA ? energyDrinkA[i] : energyDrinkB[i]) + max(drinkAndMove, drinkAndSwitch);
                (pickA) ? currRow_1 = maxEnergy : currRow_0 = maxEnergy;
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
