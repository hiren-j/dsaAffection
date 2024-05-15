// Program to find the maximum possible energy you can gain by performing the aforementioned teleportation ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>

// Class to implement the Top-down approach:
class TopDown {
public:
    // Method to find the maximum possible energy you can gain, using recursion with memoization - O(N) & O(N) : Where N let be the size of "energy" array
    int maximumEnergy(std::vector<int>& energy, int k) {
        int n = energy.size(), maxEnergy = INT_MIN;

        // 1D buffer for memoization
        std::vector<int> memory(n, -1);
        
        // Gain the total energy you can get from each magician and update the result by the maximum value each time
        for(int magician = 0; magician < n; ++magician)
            maxEnergy = std::max(maxEnergy, energy[magician] + solveWithMemo(memory, energy, k, n, magician));
        
        // Return the maximum possible energy you can gain
        return maxEnergy;
    }
    
private:
    // O(N) & O(N)
    int solveWithMemo(std::vector<int>& memory, std::vector<int>& energy, int k, int n, int magician) {    
        // Edge case: If all the magicians are visited then you can't gain any more energy
        if(magician >= n)
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[magician] != -1)
            return memory[magician];
        
        // Stores the energy you can gain from the current magician along with the energies of the kth magicians
        int currEnergy = 0;
        
        // If it's possible to teleport to the kth magician then take the energy of the current magician and teleport to the kth magician
        if(magician + k < n)
            currEnergy += energy[magician + k] + solveWithMemo(memory, energy, k, n, magician + k);
        
        // Stores the result value to the memoization table and then return it
        return memory[magician] = currEnergy;
    }
    
    // O(N*N) & O(N)
    int solveWithoutMemo(std::vector<int>& energy, int k, int n, int magician) {    
        // Edge case: If all the magicians are visited then you can't gain any more energy
        if(magician >= n)
            return 0;
        
        // Stores the energy you can gain from the current magician along with the energies of the kth magicians
        int currEnergy = 0;
        
        // If it's possible to teleport to the kth magician then take the energy of the current magician and teleport to the kth magician
        if(magician + k < n)
            currEnergy += energy[magician + k] + solveWithoutMemo(energy, k, n, magician + k);
        
        // Return the result value
        return currEnergy;
    }
};

// Class to implement the Bottom-up approach:
class BottomUp {
public:
    // Method to find the maximum possible energy you can gain, using constant auxiliary space - O(N) & O(1) : Where N let be the size of "energy" array
    int maximumEnergy(std::vector<int>& energy, int k) {
        int n = energy.size();

        // Gain the total energy you can get for each magician from their corresponding kth magician
        for(int magician = n-k-1; magician >= 0; --magician)
            energy[magician] += energy[magician + k];

        // Return the maximum possible energy you can gain
        return *max_element(begin(energy), end(energy));
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int n;
        std::cout<<"Enter the total number of magicians (size): ";
        std::cin>>n;

        // Input the k value
        int k;
        std::cout<<"Enter the value of K: ";
        std::cin>>k;

        // Check the given values are lying within the problem constraints or not
        if(n < 1 || n > 1e5) {
            std::cout<<"You must enter a size which lies between 1 and 10^5!";
        }
        else if(k < 1 || k > n-1) {
            std::cout<<"You must enter the value of K which lies between 1 and "<<n-1<<"!";
        }
        else {
            // Stores the array values
            std::vector<int> energy(n);

            // Input the array values
            std::cout<<'\n';
            for(int magician = 0; magician < n;) {
                std::cout<<"Enter the energy of "<<magician<<"th magician: ";
                std::cin>>energy[magician];
                // Check the given value is lying within the problem constraints or not
                if(energy[magician] < -1000 || energy[magician] > 1000) {
                    std::cout<<"You must enter the energy value which lies between -1000 and 1000!\n";
                }
                else {
                    magician++;
                }
            }

            // Call to find the maximum possible energy you can gain
            BottomUp bottomUp;
            int maxEnergy = bottomUp.maximumEnergy(energy, n);
            std::cout<<"\nThe maximum possible energy you can gain is: "<<maxEnergy;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application else it will exit: ";
        std::cin>>userChoice;
        userRunsApp = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Dynamic Programming
    Link: https://leetcode.com/problems/taking-maximum-energy-from-the-mystic-dungeon/description/
*/
