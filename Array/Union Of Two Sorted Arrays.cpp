// Program to find the union (common and distinct elements) of two sorted arrays ~ coded by Hiren
#include <iostream>
#include <vector>
#include <set>
using namespace std;

// #1 Solution class:
class Solution_A {
public:
    // Method to find the union of two sorted arrays, using set - O((N+M)*Log(N+M)) & O(N+M) : Where N let be the size of "nums1" and M of "nums2"
    vector<int> getUnion(vector<int>& nums1, vector<int>& nums2, int n, int m) {
        // Stores the union values
        set<int> st;
        
        st.insert(begin(nums1), end(nums1)); // Store the values of "nums1" to the set
        st.insert(begin(nums2), end(nums2)); // Store the values of "nums2" to the set
        
        // Store the values of the set to the result array
        vector<int> output(begin(st), end(st));
        
        // Return the result array
        return output;
    }
};

// #2 Solution class:
class Solution_B {
public:
    // Method to find the union of two sorted arrays, using constant auxiliary space - O(N+M) & O(1) : Where N let be the size of "nums1" and M of "nums2"
    vector<int> getUnion(vector<int>& nums1, vector<int>& nums2, int n, int m) {
        int i = 0; // Tracks the elements of "nums1"
        int j = 0; // Tracks the elements of "nums2"

        // Stores the union values
        vector<int> output;
        
        // Iterate the arrays
        while(i < n && j < m) {
            int element1 = nums1[i]; // Stores the ith (current) element of "nums1"
            int element2 = nums2[j]; // Stores the jth (current) element of "nums2"

            bool move_i = false; // Tracks to move further in the "nums1" or not
            bool move_j = false; // Tracks to move further in the "nums2" or not
            
            // When the ith element is lesser then the jth element then store the ith element to the result array and then allow to move further in the "nums1"
            if(nums1[i] < nums2[j]) {
                move_i = true;
                output.push_back(nums1[i]);
            }
            // Else when the ith element is greater then the jth element then store the jth element to the result array and then allow to move further in the "nums2"
            else if(nums1[i] > nums2[j]) {
                move_j = true;
                output.push_back(nums2[j]);
            }
            // Else when both the elements are equal then store any one of them to the result array and then allow to move further in both the arrays
            else {
                move_i = true; 
                move_j = true;
                output.push_back(nums1[i]);
            }
            
            if(move_i) while(i < n && nums1[i] == element1) i++; // If can move in "nums1" then skip all the duplicate elements and move on
            if(move_j) while(j < m && nums2[j] == element2) j++; // If can move in "nums2" then skip all the duplicate elements and move on
        }
        
        // Store the remaining distint elements of "nums1" to the result array
        while(i < n) {
            output.push_back(nums1[i]);
            int element = nums1[i];
            while(i < n && nums1[i] == element) i++; 
        }
        
        // Store the remaining distint elements of "nums2" to the result array
        while(j < m) {
            output.push_back(nums2[j]);
            int element = nums2[j];
            while(j < m && nums2[j] == element) j++; 
        }
        
        // Return the result array
        return output;
    }
};

// Class to implement the array operations:
class ArrayOperations {
public:
    // Method to create an array - O(S) & O(S) : Where S let be the size of array
    vector<int> createArray(int arrayNumber) {
        // Input the array size
        int size;
        cout<<"Enter the size of array"<<arrayNumber<<": ";
        cin>>size;

        // Stores the array values
        vector<int> nums;

        // Check the given size is lying within the problem constraints or not
        if(size <= 0 || size >= 1e5 + 1) {
            cout<<"You must enter a size which lies between 1 and 10^5!\n";
        }
        else {
            nums.resize(size);

            // Input the array values
            for(int index = 0; index < size;) {
                cout<<"Enter the value of "<<index<<"th index: ";
                cin>>nums[index];
                // Check the given value is lying within the problem constraints or not
                if(nums[index] <= -1e9 - 1 || nums[index] >= 1e9 + 1) {
                    cout<<"You must enter a value which lies between -10^9 and 10^9!\n";
                }
                else {
                    index++;
                }
            }
        }

        // Return the array
        return nums;
    }

    // Method to print the array - O(S) & O(1) : Where S let be the size of array
    void printArray(vector<int>& nums) {
        int size = nums.size();
        cout<<"[";
        for(int index = 0; index < size; ++index) {
            cout<<nums[index];
            if(index < size - 1) {
                cout<<", ";
            }
        }
        cout<<"]\n";
    }
};

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApplication = true;

    while(userRunsApplication) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        cout<<"Note: The application only accepts non-decimal numeric type value, unless specifed!\n\n";

        // Create the arrays
        ArrayOperations arrOperation;
        vector<int> nums1 = arrOperation.createArray(1); cout<<"\n";
        vector<int> nums2 = arrOperation.createArray(2); cout<<"\n";

        // Call to get the list containing the union of arrays
        Solution_B solution;
        vector<int> output = solution.getUnion(nums1, nums2, nums1.size(), nums2.size());

        // Print call
        cout<<"Array1: ";
        arrOperation.printArray(nums1);

        // Print call
        cout<<"Array2: ";
        arrOperation.printArray(nums2);

        // Print call
        cout<<"Result array: ";
        arrOperation.printArray(output);

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userRunsApplication = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Two Pointers
    Link: https://www.geeksforgeeks.org/problems/union-of-two-sorted-arrays-1587115621/1
*/
