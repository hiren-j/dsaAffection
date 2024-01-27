// Program to find the maximized product difference in an array ~ coded by Hiren 
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>

// Solution class:
class Solution {
public:
    // #1 Method to find the maximized product difference using sorting - O(NLogN) & O(1)
    int maxProductDifference_V1(std::vector<int>& nums) {
        int n = nums.size();
        std::sort(begin(nums), end(nums));
        return (nums[n-1] * nums[n-2]) - (nums[0] * nums[1]);
    }
    
    // #2 Method to find the maximized product difference using constant auxiliary space - O(N) & O(1)
    int maxProductDifference_V2(std::vector<int>& nums) {
        int n = nums.size();

        int maxElement1 = INT_MIN; // Stores the first largest element
        int maxElement2 = INT_MIN; // Stores the second largest element
        int max1Idx = -1;          // Stores the index of the first largest element

        int minElement1 = INT_MAX; // Stores the first smallest element
        int minElement2 = INT_MAX; // Stores the second smallest element
        int min1Idx = -1;          // Stores the index of the first smallest element

        // Iterate and find the first largest and first smallest element
        for(int i=0; i<n; i++) {
            (nums[i] > maxElement1) ? maxElement1 = nums[i], max1Idx = i : 0;
            (nums[i] < minElement1) ? minElement1 = nums[i], min1Idx = i : 0;
        }

        int diff1 = INT_MAX; // Tracks the smallest difference needed to find the second largest element
        int diff2 = INT_MAX; // Tracks the smallest difference needed to find the second smallest element

        // Iterate and find the second largest and second smallest element
        for(int i=0; i<n; i++) {
            int currDiff1 = abs(nums[i] - maxElement1); // Stores the difference between ith and the first largest element
            int currDiff2 = abs(nums[i] - minElement1); // Stores the difference between ith and the first smallest element
            // If the current difference is lesser than the smallest difference seen till now
            if(i != max1Idx && currDiff1 < diff1) {
                maxElement2 = nums[i]; // Update the second largest element as the ith element
                diff1 = currDiff1;     // Update the smallest difference needed to find the second largest element
            }
            // If the current difference is lesser than the smallest difference seen till now
            if(i != min1Idx && currDiff2 < diff2) {
                minElement2 = nums[i]; // Update the second smallest element as the ith element
                diff2 = currDiff2;     // Update the smallest difference needed to find the second smallest element
            }
        }

        // Return the maximized product difference
        return (maxElement1 * maxElement2) - (minElement1 * minElement2);
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input section for the size of the array
        int n; 
        std::cout<<"Enter the size of the array: ";
        std::cin>>n;

        // Check for the given size of the array is valid or not
        if(n <= 0) {
            std::cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        std::vector<int> nums(n, 0);

        std::cout<<"\nEnter the array elements: ";

        // Input the array values
        for(int i=0; i<n; i++) {
            std::cin>>nums[i];
        }

        // Call to find the maximized product difference
        Solution solution;
        int output = solution.maxProductDifference_V2(nums);
        std::cout<<"\nThe maximized product difference is : "<<output;

        // Input section to handle the flow of iterations of the application
        char userChoise;
        std::cout<<"\n\nDo you want to perform the same operation on an another array! (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
// Link: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/description/?envType=daily-question&envId=2023-12-18
