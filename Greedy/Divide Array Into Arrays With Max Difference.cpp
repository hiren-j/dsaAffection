// Program to divide the array into one or more arrays of size 3 satisfying the specified conditions ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Solution class:
class Solution {
public:
    // Method to divide the array into one or more arrays of size 3, using sorting - O(NLogN) & O(1) : Where N is the size of the array.
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        int n = nums.size();

        // Edge case: When the size of the array is not a multiple of 3 then its not possible to divide the array
        if(n % 3 != 0)
            return {};
        
        sort(begin(nums), end(nums)); // Sort the array to handle the specified conditions more easily
        vector<vector<int>> arrays;   // Stores the resultant arrays

        // Iterate the array
        for(int i=0; i<n; i+=3) {
            int num1 = nums[i], num2 = nums[i+1], num3 = nums[i+2];
            // If the difference between any two elements in one array is not less than or equal to k, then its not possible to divide the array
            if(num3 - num1 > k) 
                return {};
            // If reached here, then its possible to divide the array, store the 3 values as an array 
            arrays.push_back({num1, num2, num3});
        }

        // Return the 2d array containing the resultant arrays 
        return arrays;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the array
        int size;
        cout<<"Enter the size of the array: ";
        cin>>size;  

        // Check the given size is valid or not
        if(size <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        vector<int> nums(size, 0);
        
        // Input the values of the array
        for(int i=0; i<size; ++i) {
            cout<<"Enter the "<<i+1<<"th value of the array: ";
            cin>>nums[i];            
        }

        // Input the value of k
        int k;
        cout<<"\nEnter the value of k: ";
        cin>>k; 
        
        // Call to divide the array
        Solution solution;
        vector<vector<int>> arrays = solution.divideArray(nums, k);

        // Print values
        for(auto& array : arrays) {
            cout<<"[";
            for(int i=0; i<3; i++) {
                cout<<array[i];
                if(i < 2) cout<<", ";
            }
            cout<<"]\n";
        }

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\nPress \'Y\' to perform the same operation on an another array, else application will exit automatically: ";
        cin>>userChoise;
        canPerformOperation = (userChoise == 'Y') ? true : false ;
    }

    return 0;
}
/*
    Topics: Array | Sorting | Greedy
    Link: https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/description/?envType=daily-question&envId=2024-02-01
*/
