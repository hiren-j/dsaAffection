// Code to find the maximum possible energy you can gain by performing the specified teleportation ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class TopDown {
    int n;

    // O(N*N) & O(N)
    int solveWithoutMemo(vector<int>& energy, int k, int magician) {
        if(magician >= n)
            return 0;

        return energy[magician] + solveWithoutMemo(energy, k, magician + k);
    }
    // Note: In the time complexity of `solveWithoutMemo()`, the first term in O(N*N) is O(N) and this time is considered for the loop through which we're calling this function

    // O(2*N) & O(2*N)
    int solveWithMemo(vector<int>& dp, vector<int>& energy, int k, int magician) {
        if(magician >= n)
            return 0;

        if(dp[magician] != -1)
            return dp[magician];

        return dp[magician] = energy[magician] + solveWithMemo(dp, energy, k, magician + k);
    }
    // Note: In the time complexity of `solveWithMemo()`, a term in O(2*N) is O(1*N) and this time is considered for the loop through which we're calling this function
    
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

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class BottomUp {
    int n;

    // O(2*N) & O(1*N)
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

    // O(1*N) & O(1*N)
    int solveWith1DEnhanced(vector<int>& energy, int k) {
        vector<int> dp(n, -1);

        int maxEnergy = INT_MIN;
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

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
Topics: Array | Prefix Sum | Dynamic Programming
Link  : https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/
