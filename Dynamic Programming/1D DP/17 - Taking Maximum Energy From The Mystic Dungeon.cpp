// Code to find the maximum possible energy you can gain by performing the specified teleportation ~ coded by Hiren

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    int solveWithoutMemo(vector<int>& energy, int k, int magician) {
        if(magician >= n)
            return 0;

        return energy[magician] + solveWithoutMemo(energy, k, magician + k);
    }

    int solveWithMemo(vector<int>& dp, vector<int>& energy, int k, int magician) {
        if(magician >= n)
            return 0;

        if(dp[magician] != -1)
            return dp[magician];

        return dp[magician] = energy[magician] + solveWithMemo(dp, energy, k, magician + k);
    }

public:
    int maximumEnergy(vector<int>& energy, int k) {
        n = energy.size();
        
        vector<int> dp(n, -1);

        int maxEnergy = INT_MIN;
        for(int start = 0; start < n; ++start) 
            maxEnergy = max(maxEnergy, solveWithMemo(dp, energy, k, start));

        return maxEnergy;
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    int solveWith1DTable(vector<int>& energy, int k) {
        vector<int> dp(n, -1);
        for(int magician = n-1; magician >= 0; --magician) {
            int nextAbsorptions = (magician + k < n) ? dp[magician + k] : 0;
            dp[magician] = energy[magician] + nextAbsorptions;
        }

        int maxEnergy = INT_MIN;
        for(int start = 0; start < n; ++start) 
            maxEnergy = max(maxEnergy, dp[start]);

        return maxEnergy;
    }

    int solveWith1DEnhanced(vector<int>& energy, int k) {
        int n = energy.size();
        int maxEnergy = INT_MIN;

        vector<int> dp(n, -1);

        for(int magician = n-1; magician >= 0; --magician) {
            int nextAbsorptions = (magician + k < n) ? dp[magician + k] : 0;
            dp[magician] = energy[magician] + nextAbsorptions;
            maxEnergy = max(maxEnergy, dp[magician]);
        }

        return maxEnergy;
    }

public:
    int maximumEnergy(vector<int>& energy, int k) {
        n = energy.size();
        return solveWith1DEnhanced(energy, k);
    }
};

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Topics: Array | Prefix Sum | Dynamic Programming
Link  : https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/
