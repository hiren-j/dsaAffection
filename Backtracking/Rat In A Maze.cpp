// Program to find all the possible paths that the rat can take to reach from source (0, 0) to destination (n-1, n-1) ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

// Class to implement the Backtracking approach:
class Backtracking {
//                                         Up         Down         Left        Right
    vector<vector<int>> directions = {{-1, 0, 85}, {1, 0, 68}, {0, -1, 76}, {0, 1, 82}};
    vector<string> allPaths; // Result array to store all the paths
    string currPath;         // Tracks the directions of any path which is being explored
    
    // Method to find all the paths to reach the right-most-corner from the left-most-corner of the grid :-
    void getAllDestinationPaths(vector<vector<int>>& grid, int N, int R, int C) {
        // Edge case: If at any point you walk outside of the grid or walk into the cell not containing any gold then you can't find gold anymore
        if(R < 0 || C < 0 || R == N || C == N || grid[R][C] == 0)
            return;
            
        // Edge case: If reached the destination cell the store the current path to the result array 
        if(R == N-1 && C == N-1) {
            allPaths.push_back(currPath);
            return;
        }

        // Mark the current cell as visited
        grid[R][C] = 0;  

        // Explore all the 4 directions one by one from the current cell
        for(auto& dir : directions) {
            int reachRow   = dir[0]; // Tracks the final row you can reach from the current cell
            int reachCol   = dir[1]; // Tracks the final column you can reach from the current cell
            char direction = dir[2]; // Tracks the value of current direction
            
            currPath.push_back(direction);                               // Push the direction to ensure the correct order of the path
            getAllDestinationPaths(grid, N, R + reachRow, C + reachCol); // Traverse and find the source to destination path from the directions chosen from the current cell
            currPath.pop_back();                                         // Pop the previously visited direction to make sure the correct order of the upcoming direction
        }

        // Mark the current cell as unvisited
        grid[R][C] = 1; 
    }
    
public:
    // Method to find all the possible paths that the rat can take to reach the destination - O(4^(N*N) * M) & O(N*N) : Where M let be the maximum possible size of "currPath" array
    vector<string> findPath(vector<vector<int>>& grid, int N) {
        getAllDestinationPaths(grid, N, 0, 0);
        return allPaths;
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specified!\n";
        cout<<"Note: The application will consider square grid!\n\n";

        // Input the size of grid
        int N;
        cout<<"Enter the size of grid: ";
        cin>>N;

        // Check the given size is lying within the problem constraints or not
        if(N < 2 || N > 5) {
            cout<<"You must enter a size which lies between 2 and 5!\n";
        } 
        else {
            vector<vector<int>> grid(N, vector<int>(N, 0));

            // Input the grid values 
            for(int R = 0; R < N; ++R) {
                for(int C = 0; C < N;) {
                    cout<<"Enter value of the "<<C<<"th column of the "<<R<<"th row: ";
                    cin>>grid[R][C];
                    if(grid[R][C] < 0 || grid[R][C] > 1) {
                        cout<<"You must enter a value which should be 0 or 1!\n";
                    }
                    else {
                        ++C;
                    }
                }
            }

            // Call to get the list containing the all possible paths that the rat can take to reach the destination
            Backtracking backtracking;
            vector<string> allPaths = backtracking.findPath(grid, N);

            // Print each path one by one 
            cout<<"\nAll the possible paths that the rat can take to reach the destination are:\n";
            for(auto& currPath : allPaths) {
                int size = currPath.size();
                cout<<"[";
                for(int i = 0; i < size; ++i) {
                    cout<<currPath[i];
                    if(i < size - 1) {
                        cout<<", ";
                    }
                }
                cout<<"]\n";
            }
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application else it will exit: ";
        cin>>userChoice;
        userRunsApp = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Matrix | Backtracking
    Link: https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
*/
