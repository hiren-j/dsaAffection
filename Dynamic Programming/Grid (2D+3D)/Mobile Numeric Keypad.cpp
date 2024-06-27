// Program to find the number of possible unique sequences of length n that you can create by pressing buttons (You can start from any digit) ~ coded by Hiren
#define ll long long
#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> directions = {{0,0}, {-1,0}, {1,0}, {0,-1}, {0,1}};
vector<vector<int>> numpad     = {{1, 2, 3},
                                  {4, 5, 6},
                                  {7, 8, 9},
                                  {-1, 0, -1}};

// Class to implement the Top-down approach:
class TopDown {    
    // O(5^10) & O(N)
    ll solveWithoutMemo(int R, int C, int N) {
        // Base case: No number exists outside of the numpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R == 4 || C == 3 || numpad[R][C] == -1)
            return 0;
            
        // Base case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;
        
        // Stores the result value
        ll count = 0;
        
        // Explore all the 5 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) 
            count += solveWithoutMemo(R + dir[0], C + dir[1], N - 1);
        
        // Return the result value
        return count;
    }
    
    // O(10*5*N*4*3) & O(N*4*3 + N)
    ll solveWithMemo(vector<vector<vector<ll>>>& memory, int R, int C, int N) {
        // Base case: No number exists outside of the numpad and if you try to look for it or you've pressed '*' or '#' then you've no valid way
        if(R < 0 || C < 0 || R == 4 || C == 3 || numpad[R][C] == -1)
            return 0;
            
        // Base case: If you've correctly dialed a phone number of length N then you've one valid way
        if(N == 0)
            return 1;
        
        // Memoization table: If the current state is already computed then return the computed value
        if(memory[N][R][C] != -1)
            return memory[N][R][C];
            
        // Stores the result value
        ll count = 0;
        
        // Explore all the 5 directions one by one from the cell (R, C) and dial the phone numbers 
        for(auto& dir : directions) 
            count += solveWithMemo(memory, R + dir[0], C + dir[1], N - 1);
        
        // Store the result value to the memoization table and then return it
        return memory[N][R][C] = count;
    }
    
public:
    // Method to find how many distinct phone numbers of length N you can dial, using recursion with memoization - O(N) & O(N)
    ll getCount(int N) {
        ll resCount = 0;
        
        // 3D Memoization table
        vector<vector<vector<ll>>> memory(N, vector<vector<ll>>(4, vector<ll>(3, -1)));
        
        // Start dialing from the cells which doesn't starts from '*' or '#'
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(numpad[R][C] != -1)
                    resCount += solveWithMemo(memory, R, C, N - 1);
        
        // Return the count of distinct phone numbers of length N you can dial
        return resCount;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {    
public:
    // Method to find how many distinct phone numbers of length N you can dial, using 3D tabulation - O(N*4*3*5) & O(N*4*3)
    ll getCount(int N) {
        // 3D Tabulation table
        vector<vector<vector<ll>>> dp(N + 1, vector<vector<ll>>(4, vector<ll>(3, 0)));
        
        // Base case: If the length is 0 then there exists one valid way
        for(int R = 0; R < 4; ++R)
            for(int C = 0; C < 3; ++C)
                if(numpad[R][C] != -1)
                    dp[0][R][C] = 1;
        
        // Fill the table for lengths from 1 to N
        for(int n = 1; n <= N; ++n) {
            for(int R = 3; R >= 0; --R) {
                for(int C = 2; C >= 0; --C) {
                    if(numpad[R][C] != -1) {
                        ll count = 0;
                        for(auto& dir : directions) {
                            int reachRow = R + dir[0];
                            int reachCol = C + dir[1];
                            if(reachRow >= 0 && reachCol >= 0 && reachRow < 4 && reachCol < 3 && numpad[reachRow][reachCol] != -1) {
                                count += dp[n - 1][reachRow][reachCol];
                            }
                        }
                        dp[n][R][C] = count;      
                    }
                }
            }
        }
        
        ll resCount = 0;
        
        // Sum up all the numbers of length N
        for(int R = 0; R < 4; ++R) 
            for(int C = 0; C < 3; ++C) 
                if(numpad[R][C] != -1)
                    resCount += dp[N - 1][R][C];
        
        // Return the count of distinct phone numbers of length N you can dial  
        return resCount;
    }
};

// Driver code
int main() {
   cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

    int testCases;
    cout<<"Enter total number of cases to test: ";
    cin>>testCases;

    while(testCases--) {
        // Input a value
        int N;
        cout<<"\nEnter a value: ";
        cin>>N;
        
        // Check the given value is lying within the problem constraints or not
        if(N < 1 || N > 25) {
            cout<<"You must enter a value which lies between 1 and 25!\n";
        }
        else {
            BottomUp bottomUp;
            cout<<"The total distinct phone numbers of length "<<N<<" you can dial is: "<<bottomUp.getCount(N)<<'\n';
        }
    }

    return 0;
}
/*
    Topics: Dynamic Programming
    Link: https://www.geeksforgeeks.org/problems/mobile-numeric-keypad5456/1
*/
