// Code to find the maximum total energy boost you can gain in the next n hours by following the specified instructions ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    typedef long long ll;
    int n;

    // O(2^N) & O(N)
    ll solveWithoutMemo(vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // Edge case: If you've exhausted all the energy boosts then you can't gain more energy
        if(idx == n)
            return 0;

        ll maxEnergy = 0;
        
        // If its time to consume energyDrink A, then you've two options to perform on the energy boosts of it
        if(useArr1) {
            maxEnergy = arr1[idx] + solveWithoutMemo(arr1, arr2, idx + 1, 1);     // Is to drink it and then drink the next boost of energyDrink A
            maxEnergy = max(maxEnergy, solveWithoutMemo(arr1, arr2, idx + 1, 0)); // Is to make a switch to the next boost of energyDrink B
        }
        // Else, if its time to consume energyDrink B, then you've two options to perform on the energy boosts of it
        else {
            maxEnergy = arr2[idx] + solveWithoutMemo(arr1, arr2, idx + 1, 0);     // Is to drink it and then drink the next boost of energyDrink B
            maxEnergy = max(maxEnergy, solveWithoutMemo(arr1, arr2, idx + 1, 1)); // Is to make a switch to the next boost of energyDrink A
        }

        return maxEnergy;
    }

    // O(2 * N*2) & O(N*2 + N)
    ll solveWithMemo(vector<vector<ll>>& memory, vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // Edge case: If you've exhausted all the energy boosts then you can't gain more energy
        if(idx == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[idx][useArr1] != -1)
            return memory[idx][useArr1];

        ll maxEnergy = 0;
        
        // If its time to consume energyDrink A, then you've two options to perform on the energy boosts of it
        if(useArr1) {
            maxEnergy = arr1[idx] + solveWithMemo(memory, arr1, arr2, idx + 1, 1);     // Is to drink it and then drink the next boost of energyDrink A
            maxEnergy = max(maxEnergy, solveWithMemo(memory, arr1, arr2, idx + 1, 0)); // Is to make a switch to the next boost of energyDrink B
        }
        // Else, if its time to consume energyDrink B, then you've two options to perform on the energy boosts of it
        else {
            maxEnergy = arr2[idx] + solveWithMemo(memory, arr1, arr2, idx + 1, 0);     // Is to drink it and then drink the next boost of energyDrink B
            maxEnergy = max(maxEnergy, solveWithMemo(memory, arr1, arr2, idx + 1, 1)); // Is to make a switch to the next boost of energyDrink A
        }

        // Store the result value to the memoization table and then return it
        return memory[idx][useArr1] = maxEnergy;
    }

public:
    // Method to find the maximum total energy boost you can gain, using recursion with memoization - O(N) & O(N)
    ll maxEnergyBoost(vector<int>& arr1, vector<int>& arr2) {
        n = arr1.size();
        vector<vector<ll>> memory1(n, vector<ll>(2, -1)), memory2(n, vector<ll>(2, -1));
        ll maxEnergy1 = solveWithMemo(memory1, arr1, arr2, 0, 1);
        ll maxEnergy2 = solveWithMemo(memory2, arr1, arr2, 0, 0);
        return max(maxEnergy1, maxEnergy2);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    typedef long long ll;
    int n;

    // O(N*2) & O(N*2)
    ll solveUsing2DTable(vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // 2D DP table
        vector<vector<ll>> dp(n + 1, vector<ll>(2, 0));

        // Fill the table
        for(int idx = n-1; idx >= 0; --idx) {
            for(int col = (useArr1 == 1 ? 0 : 1); (useArr1 == 1 ? col <= 1 : col >= 0); (useArr1 == 1 ? col++ : col--)) {   
                ll maxEnergy = 0;

                if(col) {
                    maxEnergy = arr1[idx] + dp[idx + 1][1];
                    maxEnergy = max(maxEnergy, dp[idx + 1][0]);
                }
                else {
                    maxEnergy = arr2[idx] + dp[idx + 1][0];
                    maxEnergy = max(maxEnergy, dp[idx + 1][1]);
                }

                dp[idx][col] = maxEnergy;
            }   
        }

        // Return the result value
        return dp[0][useArr1];
    }

    // O(N*2) & O(1)
    ll solveUsing1DTable(vector<int>& arr1, vector<int>& arr2, int idx, int useArr1) {
        // 1D DP tables
        vector<ll> nextRow(2, 0), currRow(2, 0);

        // Fill the table
        for(int idx = n-1; idx >= 0; --idx) {
            for(int col = (useArr1 == 1 ? 0 : 1); (useArr1 == 1 ? col <= 1 : col >= 0); (useArr1 == 1 ? col++ : col--)) {   
                ll maxEnergy = 0;

                if(col) {
                    maxEnergy = arr1[idx] + nextRow[1];
                    maxEnergy = max(maxEnergy, nextRow[0]);
                }
                else {
                    maxEnergy = arr2[idx] + nextRow[0];
                    maxEnergy = max(maxEnergy, nextRow[1]);
                }

                currRow[col] = maxEnergy;
            }   
            nextRow = currRow;
        }

        // Return the result value
        return nextRow[useArr1];
    }

public:
    // Method to find the maximum total energy boost you can gain, using tabulation :-
    ll maxEnergyBoost(vector<int>& arr1, vector<int>& arr2) {
        n = arr1.size();
        ll maxEnergy1 = solveUsing1DTable(arr1, arr2, 0, 1);
        ll maxEnergy2 = solveUsing1DTable(arr1, arr2, 0, 0);
        return max(maxEnergy1, maxEnergy2);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Dynamic Programming
Link  : https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/description/
