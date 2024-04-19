// Program to find the numbers which are present in the first array "nums1", but not present in the second array "nums2" ~ coded by Hiren
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>

// #1 Solution class: 
class Solution_A {
public:
    // Method to find the missing numbers in the second array, using linear search - O(N*M) & O(1) : Where N let be the size of "nums1" and M of "nums2"
	std::vector<int> getMissingNumbers(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Stores the result values
	    std::vector<int> result;
	    
        // Iterate the first array
	    for(int num1 : nums1) {
            // Tracks the "num" exists in the second array or not
	        bool isNotPresent = true;
            // Iterate the second array and find the "num"
	        for(int num2 : nums2) {
	            if(num1 == num2) {
	                isNotPresent = false;
	                break;
	            }
	        }
            // If the "num" is not present in the second array then store it to the result array
	        if(isNotPresent) {
	            result.push_back(num1);
	        }
	    }

        // Return the result array
	    return result;
	} 
};

// #2 Solution class: 
class Solution_B {
public:
    // Method to find the missing numbers in the second array, using binary search - O(NLogM) & O(1) : Where N let be the size of "nums1" and M of "nums2"
	std::vector<int> getMissingNumbers(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Sort the second array to perform the binary search on it
	    std::sort(std::begin(nums2), std::end(nums2));

        // Stores the result values
	    std::vector<int> result;
	    
        // Iterate the first array
	    for(int num : nums1) {
            // If the "num" is not present in the second array then store it to the result array
	        if(!binarySearch(nums2, nums2.size(), num)) {
	            result.push_back(num);
	        }
	    }

        // Return the result array 
	    return result;
	} 
	
private:
    // Method to check the given key is present in the given array or not - O(LogM) & O(1)
    bool binarySearch(std::vector<int>& nums, int size, int key) {
        int start = 0, end = size - 1;
        
        while(start <= end) {
            int mid = start + (end - start) / 2;
            if(nums[mid] == key) {
                return true;
            }
            else if(nums[mid] < key) {
               start = mid + 1; 
            }
            else {
                end = mid - 1;
            }
        }
        
        return false;
    }
};

// #3 Solution class: 
class Solution_C {
public:
    // Method to find the missing numbers in the second array, using set - O(N+M) & O(M) : Where N let be the size of "nums1" and M of "nums2"
	std::vector<int> getMissingNumbers(std::vector<int>& nums1, std::vector<int>& nums2) {
        // Stores the values of the second array
	    std::unordered_set<int> visited;

        // Stores the result values
	    std::vector<int> result;
    
        // Iterate the second array and store the values to the set
	    for(int num : nums2) {
	        visited.insert(num);
	    }

        // Iterate the first array
	    for(int num : nums1) {
            // If the "num" is not present in the second array then store it to the result array
	        if(!visited.count(num)) {
	            result.push_back(num);
	        }
	    }

        // Return the result array
	    return result;
	} 
};    

// Class to implement the array operations:
class ArrayOperations {
public:
    // Method to create an array - O(S) & O(S) : Where S let be the size of the array
    std::vector<int> createArray(int arrayNumber) {
        // Input the array size
        int size;
        std::cout<<"Enter the size of array"<<arrayNumber<<": ";
        std::cin>>size;

        // Stores the array values
        std::vector<int> nums;

        // Check the given size is lying within the problem constraints or not
        if(size <= 0 || size >= 1e5 + 1) {
            std::cout<<"You must enter a size which lies between 1 and 10^5!\n";
        }
        else {
            nums.resize(size);

            // Input the array values
            for(int index = 0; index < size;) {
                std::cout<<"Enter value of the "<<index<<"th index: ";
                std::cin>>nums[index];
                // Check the given value is lying within the problem constraints or not
                if(nums[index] <= -1e9 - 1 || nums[index] >= 1e9 + 1) {
                    std::cout<<"You must enter a value which lies between -10^9 and 10^9!\n";
                }
                else {
                    index++;
                }
            }
        }

        // Return the array
        return nums;
    }

    // Method to print the array - O(S) & O(1) : Where S let be the size of the array
    void printArray(std::vector<int>& nums) {
        int size = nums.size();
        std::cout<<"[";
        for(int index = 0; index < size; ++index) {
            std::cout<<nums[index];
            if(index < size - 1) {
                std::cout<<", ";
            }
        }
        std::cout<<"]\n";
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Controls console clearance for both "windows" and "linux" user
        std::system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Create the arrays
        ArrayOperations operation;
        std::vector<int> nums1 = operation.createArray(1); std::cout<<'\n';
        std::vector<int> nums2 = operation.createArray(2); 

        // Call to find the missing numbers in the second array 
        Solution_C solution;
        std::vector<int> result = solution.getMissingNumbers(nums1, nums2);

        // Print call
        std::cout<<"\nArray1: "; 
        operation.printArray(nums1);

        // Print call
        std::cout<<"Array2: "; 
        operation.printArray(nums2);

        // Print call
        std::cout<<"Result array: "; 
        operation.printArray(result);

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Hash Table | Binary Search
    Link: https://www.geeksforgeeks.org/problems/in-first-but-second5423/1
*/
