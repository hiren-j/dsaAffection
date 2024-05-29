// Program to check is if there exists a triple of indices (i, j, k) such that (i < j < k) and (nums[i] < nums[j] < nums[k]) ~ coded by Hiren
#define ll long long
#include <iostream>
#include <climits>
#include <vector>

// Solution class:
class Solution {
public:
    // #1 Method to check is there exists any triplet subsequence which satisies the specified conditions - O(N^3) & O(1) : Where N let be the size of the array
    bool increasingTriplet_A(std::vector<ll>& nums) {
        int n = nums.size();

        // Iterate and generate every triplet subsequence and return true if there exists any triplet subsequence which satisfies the specified conditions
        for(int i = 0; i < n; ++i) {
            for(int j = i+1; j < n; ++j) {
                for(int k = j+1; k < n; ++k) {
                    if(nums[i] < nums[j] && nums[j] < nums[k]) {
                        return true;
                    }
                }
            }
        }

        // If reached here then there doesn't exist any triplet subsequence which meets the specified conditions
        return false;
    }
    // Note: This solution can lead to the time-limit-exceed

    // #2 Method to check is there exists any triplet subsequence which satisies the specified conditions - O(N) & O(N) : Where N let be the size of the array
    bool increasingTriplet_B(std::vector<ll>& nums) {
        int n = nums.size();
        
        // Tracks the strictly minimum value which can be found at the left side of any index element
        std::vector<ll> minLeftSide(n);
        ll minElement = nums[0];       

        // Iterate and find the strictly minimum value of each element
        for(int index = 0; index < n; ++index) {
            minLeftSide[index] = minElement;
            minElement = std::min(minElement, nums[index]);
        }

        // Tracks the strictly maximum value which can be found at the right side of any index element
        std::vector<ll> maxRightSide(n);
        ll maxElement = nums[n - 1]; 

        // Iterate and find the strictly maximum value of each element
        for(int index = n - 1; index >= 0; --index) {
            maxRightSide[index] = maxElement;
            maxElement = std::max(maxElement, nums[index]);
        }

        // Iterate and check is there exists any triplet subsequence which satisies the specified conditions, if it is then return true
        for(int index = 0; index < n; ++index) {
            if(minLeftSide[index] < nums[index] && nums[index] < maxRightSide[index]) {
                return true;
            }
        }

        // If reached here then there doesn't exist any triplet subsequence which meets the specified conditions
        return false;
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApp = true;

    while(userRunsApp) {
        // Controls console clearance for both windows and linux user
        system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int n;
        std::cout<<"Enter size of the array: ";
        std::cin>>n;

        // Check the given size is lying within the problem constraints or not
        if(n < 1 || n > 5*1e5) {
            std::cout<<"You must enter a size which lies between 1 and 50^5!";
        }
        else {
            // Stores the array values
            std::vector<ll> nums(n);

            // Input the array values
            for(int index = 0; index < n;) {
                std::cout<<"Enter the value of "<<index<<"th index: ";
                std::cin>>nums[index];
                // Check the given value is lying within the problem constraints or not
                if(nums[index] < INT_MIN || nums[index] > INT_MAX) {
                    std::cout<<"You must enter a value which lies between "<<INT_MIN<<" and "<<INT_MAX<<"!\n";
                }
                else {
                    ++index;
                }
            }

            // Verification call
            Solution solution;
            if(solution.increasingTriplet_B(nums)) {
                std::cout<<"\nThere exists such triplet subsequence!";
            }
            else {
                std::cout<<"\nThere doesn't exist such triplet subsequence!";
            }
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
    Topics: Array | Greedy 
    Link: https://leetcode.com/problems/increasing-triplet-subsequence/description/
*/
