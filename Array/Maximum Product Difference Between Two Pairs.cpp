// Program to find the maximized product difference in an array ~ coded by Hiren 
#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <thread>
#include <chrono>

// #1 Method to find the maximized product difference using sorting - O(NLogN) & O(1)
int maxProductDifference_V1(std::vector<int>& nums) {
    int n = nums.size();
    std::sort(begin(nums), end(nums));
    return (nums[n-1] * nums[n-2]) - (nums[0] * nums[1]);
}

// #2 Method to find the maximized product difference using constant auxiliary space - O(N) & O(1)
int maxProductDifference_V2(std::vector<int>& nums) {
    int n = nums.size();

    int maxElement1 = INT_MIN, max1Idx = -1, maxElement2 = INT_MIN;
    int minElement1 = INT_MAX, min1Idx = -1, minElement2 = INT_MAX;

    for(int i=0; i<n; i++) {
        (nums[i] > maxElement1) ? maxElement1 = nums[i], max1Idx = i : 0;
        (nums[i] < minElement1) ? minElement1 = nums[i], min1Idx = i : 0;
    }

    int diff1 = INT_MAX, diff2 = INT_MAX;

    for(int i=0; i<n; i++) {
        int currDiff1 = abs(nums[i] - maxElement1);
        int currDiff2 = abs(nums[i] - minElement1);
        if(i != max1Idx && currDiff1 < diff1) {
            maxElement2 = nums[i];
            diff1 = currDiff1;
        }
        if(i != min1Idx && currDiff2 < diff2) {
            minElement2 = nums[i];
            diff2 = currDiff2;
        }
    }

    return (maxElement1 * maxElement2) - (minElement1 * minElement2);
}

// Driver code
int main() {
    int testCases; 
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter a valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        // Handles console clearence for both "windows" and "linux" user
        system("clear || cls");
        
        int n; 
        std::cout<<"Enter the size of the array: ";
        std::cin>>n;

        std::vector<int> nums(n);

        std::cout<<"\nEnter the array elements: ";

        for(int i=0; i<n; i++) {
            std::cin>>nums[i];
        }

        // Method call
        int output = maxProductDifference_V2(nums);
        std::cout<<"\nThe maximized product difference is : "<<output;

        if(testCases != 0)
            std::cout<<"\n\nApplication will restart in 10 seconds!";
        else
            std::cout<<"\n\nApplication will close in 10 seconds!";
            
        // Add a 10-second delay before the next iteration
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
// Link: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/description/?envType=daily-question&envId=2023-12-18
