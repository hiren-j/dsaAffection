// Program to return an array "ans" of length "nums1.length" such that "ans[i]" is the "next greater element" as described in the problem description ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

// #1 Solution class
class Solution_V1 {
public:
    // Method to return an array "ans" such that "ans[i]" is the "next greater element", using map and nested loop - O(N*M) & O(M)
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();

        // Stores the "elements" of "nums2" associated with their "index"
        unordered_map<int, int> indeces;

        // Iterate and the map the "elements" to their "index"
        for(int i = 0; i < m; ++i) {
            indeces[nums2[i]] = i;
        }

        // Iterate "nums1"
        for(int i = 0; i < n; ++i) {
            // Stores the next largest element of the ith element
            int nextLargest = -1;
            // Iterate and find the next largest element from "nums2"
            for(int j = indeces[nums1[i]] + 1; j < m; ++j) {
                if(nums2[j] > nums1[i]) {
                    nextLargest = nums2[j];
                    break;
                }
            }
            // Replace the ith element by its next largest element or -1 if not found
            nums1[i] = nextLargest;
        }

        // Return the result array
        return nums1;
    }
};  

// #2 Solution class
class Solution_V2 {
public:
    // Method to return an array "ans" such that "ans[i]" is the "next greater element", using map and 1 stack - O(N+M) & O(M)
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size(), m = nums2.size();

        // Stores the "elements" of "nums2" associated with their "index"
        unordered_map<int, int> indeces;

        // Iterate and the map the "elements" to their "index"
        for(int i = 0; i < m; ++i) {
            indeces[nums2[i]] = i;
        }

        // Replace each element of the "nums2" by its "next largest element" 
        updateNGE(nums2, m);
        
        // Replace each element of the "nums1" by its "next largest element" from "nums2"
        for(int i = 0; i < n; ++i) {
            int j = indeces[nums1[i]];
            if(j < m) {
                nums1[i] = nums2[j];
            }
        }

        // Return the result array
        return nums1;
    }

private:
    // Method to replace all the elements of the array by their next largest element - O(Size) & O(Size) : Where "Size" let be the size of the array
    void updateNGE(vector<int>& nums, int size) {
        // Stores the elements in monotonic fashion (decreasing order)
        stack<int> st;

        // Iterate the array from the back side
        for(int i=size-1; i>=0; --i) {
            // Pop all the elements lesser than or equal to the ith element
            while(!st.empty() && st.top() <= nums[i]) {
                st.pop();
            }
            // If the stack is not empty then replace the ith element by its next largest element
            int tmp = nums[i];
            nums[i] = (!st.empty() ? st.top() : -1);
            st.push(tmp);
        }        
        
    }
};

// Class to wrap basic methods of the array
class ArrayBasicMethods {
public:
    // Method to create an array - O(Size) & O(Size) : Where "Size" let be the size of the array
    vector<int> getArray(int number) {
        // Input the size of the array
        int size;
        cout<<"Enter the size of array"<<number<<": ";
        cin>>size;

        // Check the given size is valid or not
        if(size <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!\n\n";
            return {};
        }

        // Stores the array values
        vector<int> nums(size, 0);

        cout<<"Enter the values of array"<<number<<": ";

        // Input the array values
        for(int i=0; i<size; ++i) {
            cin>>nums[i];
        }
        cout<<'\n';

        // Return the array
        return nums;
    }

    // Method to print the array - O(Size) & O(1) : Where "Size" let be the size of the array
    void printArray(vector<int>& nums) {
        for(int num : nums) {
            cout<<num<<' ';
        }
        cout<<'\n';
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Create the arrays and store them
        ArrayBasicMethods basicMethods;
        vector<int> nums1 = basicMethods.getArray(1); 
        vector<int> nums2 = basicMethods.getArray(2);

        // Print call
        cout<<"Array1: "; basicMethods.printArray(nums1);
        cout<<"Array2: "; basicMethods.printArray(nums2);

        // Call to get the result array
        Solution_V2 solution;
        vector<int> ans = solution.nextGreaterElement(nums1, nums2);

        // Print call
        cout<<"Result array: "; 
        basicMethods.printArray(ans);

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Hash Table | Stack | Monotonic Stack
    Link: https://leetcode.com/problems/next-greater-element-i/description/ 
*/
