// Program to find how many distinct phone numbers of length N you can dial ~ coded by Hiren
#define MOD 1000000007
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Top-down approach:
class TopDown {
    vector<vector<int>> directions = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {1, -2}, {2, 1}, {1, 2}};
    vector<vector<int>> dialpad    = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};

    // O(8^10) & O(N)
    int solveWithoutMemo(int N, int R, int C) {
        // Base case: No number exists outside of the dialpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R >= 4 || C >= 3 || dialpad[R][C] == -1)
            return 0;

        // Base case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;

        // Stores the result value
        int count = 0;

        // Explore all the 8 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            count = ((count % MOD) + solveWithoutMemo(N - 1, reachRow, reachCol)) % MOD;
        }

        // Return the result value
        return count % MOD;
    }

    // O(10*8*N*4*3) & O(N*4*3 + N)
    int solveWithMemo(vector<vector<vector<int>>>& memory, int N, int R, int C) {
        // Base case: No number exists outside of the dialpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R >= 4 || C >= 3 || dialpad[R][C] == -1)
            return 0;

        // Base case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N][R][C] != -1)
            return memory[N][R][C];

        // Stores the result value
        int count = 0;

        // Explore all the 8 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) {
            int reachRow = R + dir[0];
            int reachCol = C + dir[1];
            count = ((count % MOD) + solveWithMemo(memory, N - 1, reachRow, reachCol)) % MOD;
        }

        // Store the result value to the memoization table and then return it
        return memory[N][R][C] = count % MOD;
    }

public:
    // Method to find how many distinct phone numbers of length N you can dial, using recursion with memoization - O(N) & O(N)
    int knightDialer(int N) {
        int resCount = 0;
        
        // 3D Memoization table
        vector<vector<vector<int>>> memory(N, vector<vector<int>>(4, vector<int>(3, -1)));

        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(dialpad[R][C] != -1) 
                    resCount = ((resCount) % MOD + solveWithMemo(memory, N - 1, R, C)) % MOD;

        // Return the count of distinct phone numbers of length N you can dial
        return resCount % MOD;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
    vector<vector<int>> directions = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {2, -1}, {1, -2}, {2, 1}, {1, 2}};
    vector<vector<int>> dialpad    = {{1, 2, 3},
                                      {4, 5, 6},
                                      {7, 8, 9},
                                      {-1, 0, -1}};
public:
    // Method to find how many distinct phone numbers of length N you can dial, using 3D tabulation - O(N*4*3*4) & O(N*4*3)
    int knightDialer(int N) {
        // 3D Tabulation table
        vector<vector<vector<int>>> dp(N + 1, vector<vector<int>>(4, vector<int>(3, 0)));

        // Base case: If the length is 0 then there exists one valid way
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C)
                if(dialpad[R][C] != -1)
                    dp[0][R][C] = 1;

        // Fill the table for lengths from 1 to N
        for(int step = 1; step <= N; ++step) {
            for(int R = 3; R >= 0; --R) {
                for(int C = 2; C >= 0; --C) {
                    if(dialpad[R][C] != -1) {
                        int count = 0;
                        for(auto& dir : directions) {
                            int reachRow = R + dir[0];
                            int reachCol = C + dir[1];
                            if(reachRow >= 0 && reachCol >= 0 && reachRow < 4 && reachCol < 3 && dialpad[reachRow][reachCol] != -1) {
                                count = ((count % MOD) + dp[step - 1][reachRow][reachCol]) % MOD;
                            }
                        }
                        dp[step][R][C] = count % MOD;
                    }
                }
            }
        }
        
        int resCount = 0;

        // Sum up all the numbers of length N
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(dialpad[R][C] != -1) 
                    resCount = ((resCount) % MOD + dp[N - 1][R][C]) % MOD;

        // Return the count of distinct phone numbers of length N you can dial
        return resCount % MOD;
    }
};

// Driver code
int main() {
    cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

    // Input section to control the flow of iterations of the application
    int testCases;
    cout<<"Enter total number of cases to test: ";
    cin>>testCases;

    while(testCases--) {
        // Input a value
        int N;
        cout<<"\nEnter a value: ";
        cin>>N;
        
        // Check the given value is lying within the problem constraints or not
        if(N < 1 || N > 5000) {
            cout<<"You must enter a value which lies between 1 and 5000!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The total distinct phone numbers of length "<<N<<" you can dial is: "<<bottomUp.knightDialer(N)<<'\n';
        }
    }

    return 0;
}
/*
    Topics: Dynamic Programming
    Link: https://leetcode.com/problems/knight-dialer/description/
*/
