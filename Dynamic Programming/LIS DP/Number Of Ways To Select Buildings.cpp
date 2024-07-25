// Code to find the number of valid ways to select 3 buildings ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Top-down approach:
class TopDown {
    typedef long long ll;

public:
    // Method to find the number of valid ways to select 3 buildings, using recursion with memoizatin - O(N) & O(N)
    ll numberOfWays(string& s) {
        int n = s.size();
        vector<vector<vector<ll>>> memory(n, vector<vector<ll>>(3, vector<ll>(4, -1)));
        return solveWithMemo(memory, s, n, 0, '2', 3);
    }

private:
    // O(2*N*3*4) & O(N*3*4 + N)
    ll solveWithMemo(vector<vector<vector<ll>>>& memory, const string& s, int n, int index, char prevBuilding, int k) {
        // Edge case: If you've selected 3 buildings then you've got one valid way
        if(k == 0)
            return 1;

        // Edge case: If all the buildings are exhausted then you've no valid way
        if(index == n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[index][prevBuilding - '0'][k] != -1)
            return memory[index][prevBuilding - '0'][k];

        // There are always two possibilities to perform at each building
        ll currSkip   = solveWithMemo(memory, s, n, index + 1, prevBuilding, k); // Is to skip it
        ll currSelect = 0;                                                       // Is to select it 

        // If the previous and current building is not same then select the current building
        if(prevBuilding == '2' || prevBuilding != s[index])
            currSelect = solveWithMemo(memory, s, n, index + 1, s[index], k - 1);

        // Store the result value to the memoization table and then return it
        return memory[index][prevBuilding - '0'][k] = (currSkip + currSelect);
    }

    // O(2^N) & O(N)
    ll solveWithoutMemo(const string& s, int n, int index, char prevBuilding, int k) {
        // Edge case: If you've selected 3 buildings then you've got one valid way
        if(k == 0)
            return 1;

        // Edge case: If all the buildings are exhausted then you've no valid way
        if(index == n)
            return 0;

        // There are always two possibilities to perform at each building
        ll currSkip   = solveWithoutMemo(s, n, index + 1, prevBuilding, k); // Is to skip it
        ll currSelect = 0;                                                  // Is to select it

        // If the previous and current building is not same then select the current building
        if(prevBuilding == '2' || prevBuilding != s[index])
            currSelect = solveWithoutMemo(s, n, index + 1, s[index], k - 1);

        // Return the result value
        return (currSkip + currSelect);
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------

// Class to implement the Bottom-up approach:
class BottomUp {
    typedef long long ll;

public:
    // #1 Method to find the number of valid ways to select 3 buildings, using 2D tabulation - O(N*3*3) & O(N*3*4)
    ll numberOfWays_V1(const string& s) {
        int n = s.size();

        vector<vector<vector<ll>>> dp(n + 1, vector<vector<ll>>(3, vector<ll>(4, 0)));

        for(int index = 0; index <= n; ++index)
            for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding)
                dp[index][prevBuilding - '0'][0] = 1;

        for(int index = n-1; index >= 0; --index) {
            for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding) {
                for(int k = 1; k <= 3; ++k) {
                    ll currSkip   = dp[index + 1][prevBuilding - '0'][k];
                    ll currSelect = 0;
                    if(prevBuilding == '2' || prevBuilding != s[index]) {
                        currSelect = dp[index + 1][s[index] - '0'][k - 1];
                    }
                    dp[index][prevBuilding - '0'][k] = (currSkip + currSelect);
                }
            }
        }

        return dp[0]['2' - '0'][3];
    }

    // #2 Method to find the number of valid ways to select 3 buildings, using 1D tabulation - O(N*3*3) & O(2*3*4)
    ll numberOfWays_V2(const string& s) {
        int n = s.size();

        vector<vector<ll>> nextRow(3, vector<ll>(4, 0)), idealRow(3, vector<ll>(4, 0));

        for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding)
            nextRow[prevBuilding - '0'][0] = 1;

        for(int index = n-1; index >= 0; --index) {
            for(char prevBuilding = '0'; prevBuilding <= '2'; ++prevBuilding) {
                idealRow[prevBuilding - '0'][0] = 1;
                for(int k = 1; k <= 3; ++k) {
                    ll currSkip   = nextRow[prevBuilding - '0'][k];
                    ll currSelect = 0;
                    if(prevBuilding == '2' || prevBuilding != s[index]) {
                        currSelect = nextRow[s[index] - '0'][k - 1];
                    }
                    idealRow[prevBuilding - '0'][k] = (currSkip + currSelect);
                }
            }
            nextRow = idealRow;
        }

        return idealRow['2' - '0'][3];
    }
};

---------------------------------------------------------------------------------------------------------------------------------------------

Topics: String | Dynamic Programming | Prefix Sum
Link  : https://leetcode.com/problems/number-of-ways-to-select-buildings/description/
