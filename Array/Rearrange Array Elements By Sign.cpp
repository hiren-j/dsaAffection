// Program to return the modified array after rearranging the elements to satisfy the aforementioned conditions ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>

// Solution class:
class Solution {
public:
    // #1 Method to rearrange the elements as mentioned, using multiple buffers - O(N) & O(N)
    std::vector<int> rearrangeArray_V1(std::vector<int>& nums) {
        int n = nums.size();

        std::vector<int> posNumbers; // Stores the positive values of the array
        std::vector<int> negNumbers; // Stores the negative values of the array

        // Iterate the array and store the values
        for(int num : nums)
            (num > 0) ? posNumbers.push_back(num) : negNumbers.push_back(num);

        int i = 0;

        // Iterate and store the positive values at the even index
        for(int num : posNumbers)
            nums[i] = num, i += 2;
        
        i = 1;

        // Iterate and store the negative values at the odd index
        for(int num : negNumbers)
            nums[i] = num, i += 2;

        // Return the "modified array / result array"
        return nums;
    }

    // #2 Method to rearrange the elements as mentioned, using single buffer - O(N) & O(N)
    std::vector<int> rearrangeArray_V2(std::vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = 1;

        // Stores the result values
        std::vector<int> output(n, 0);

        // Iterate the array
        for(int num : nums) {
            // Store the positive value at the even index of the "output array"
            (num > 0) ? output[i] = num, i += 2 : 0; 
            // Store the negative value at the odd index of the "output array"
            (num < 0) ? output[j] = num, j += 2 : 0; 
        }

        // Return the "output array"
        return output;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the array
        int size;
        std::cout<<"Enter size of the array: ";
        std::cin>>size;

        // Check the given size is valid or not
        if(size <= 0) {
            std::cout<<"Enter a valid size, applicatin expects a positive integer!";
            return 0;
        }

        // Stores the array values
        std::vector<int> nums(size, 0);

        // Input the array values
        std::cout<<"Enter values of the array: ";
        for(int i=0; i<size; i++)
            std::cin>>nums[i];

        // Rearrangement call
        Solution obj;
        nums = obj.rearrangeArray_V2(nums);

        // Print values
        std::cout<<"Result array: ";
        for(int num : nums) 
            std::cout<<num<<' ';

        // Input section to handle the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        std::cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Two Pointers | Simulation
    Link: https://leetcode.com/problems/rearrange-array-elements-by-sign/description/
*/
