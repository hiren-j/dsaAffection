// Program to return an array "answer" such that answer[i] is equal to the product of all the elements of "nums" except nums[i] ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>

// #1 Solution class:
class Solution_A {
public:
    // Method to return an array "answer" such that answer[i] is equal to the product of all the elements of "nums" except nums[i], using nested loop - O(N*N) & O(1) : Where N let be the size of "nums"
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        int n = nums.size();

        // Stores the "result products / result values"
        std::vector<int> answer;

        // Iterate and find the result product of each value by excluding the value in the product and then store the result product to the result array
        for(int index1 = 0; index1 < n; ++index1) {
            int product = 1;
            for(int index2 = 0; index2 < n; ++index2) {
                product *= (index1 != index2) ? nums[index2] : 1;
            }
            answer.push_back(product);
        }

        // Return the "array containing the result products"
        return answer;
    }
};

// #2 Solution class:
class Solution_B {
public:
    // Method to return an array "answer" such that answer[i] is equal to the product of all the elements of "nums" except nums[i], using buffers - O(N) & O(N) : Where N let be the size of "nums"
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        int n = nums.size();

        // Stores the prefix product and suffix product of each value of the array
        std::vector<int> prefProduct(n), suffProduct(n);
        
        // Iterate and compute the prefix product of each value of the array
        for(int index = 0; index < n; ++index) {
            prefProduct[index] = (index > 0) ? nums[index] * prefProduct[index - 1] : nums[index];
        }

        // Iterate and compute the suffix product of each value of the array
        for(int index = n - 1; index >= 0; --index) {
            suffProduct[index] = (index < n - 1) ? nums[index] * suffProduct[index + 1] : nums[index];
        }

        // Iterate and find the result product of each value and then update the value by the result product of it
        for(int index = 0; index < n; ++index) {
            int num1 = (index > 0) ? prefProduct[index - 1] : 1;
            int num2 = (index < n - 1) ? suffProduct[index + 1] : 1;
            nums[index] = num1 * num2;
        }

        // Return the "array containing the result products / updated array"
        return nums;
    }
};

// #3 Solution class:
class Solution_C {
public:
    // Method to return an array "answer" such that answer[i] is equal to the product of all the elements of "nums" except nums[i], using constant auxiliary space - O(N) & O(1) : Where N let be the size of "nums"
    std::vector<int> productExceptSelf(std::vector<int>& nums) {
        int n = nums.size();        

        // Tracks the prefix product of any index value
        int productTillNow = 1; 
            
        // Stores the "result products / result values"
        std::vector<int> answer;

        // Iterate and compute the prefix product of each value and then store it to the result array
        for(int index = 0; index < n; ++index) {
            productTillNow *= nums[index];
            answer.push_back(productTillNow);
        }

        // Tracks the suffix product of any index value
        productTillNow = 1;

        // Iterate and find the suffix product of each value and then compute the result product of it and then store it to the result array
        for(int index = n - 1; index >= 1; --index) {   
            int prefProduct = answer[index - 1];
            answer[index] = prefProduct * productTillNow;
            productTillNow *= nums[index];
        }

        // Store the suffix product of the value at the 0th index
        answer[0] = productTillNow;

        // Return the "array containing the result products"
        return answer;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userNeedOperation = true;

    while(userNeedOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the array size
        int n;
        std::cout<<"Enter size of the array: ";
        std::cin>>n;

        // Check the given size is lying within the problem constraints or not
        if(n <= 1 || n >= 1e5 + 1) {
            std::cout<<"Enter a size which lies between 2 and 10^5!";
        }
        else {
            // Stores the array values
            std::vector<int> nums(n);

            // Input the array values
            for(int index = 0; index < n;) {
                std::cout<<"Enter the value of "<<index<<"th index: ";
                std::cin>>nums[index];
                if(nums[index] <= -31 || nums[index] >= 31) {
                    std::cout<<"You must enter a value which lies between -30 and 30!\n";
                }
                else {
                    ++index;
                }
            }

            // Call to get the array containing the result products
            Solution_C solution;
            nums = solution.productExceptSelf(nums);

            // Print values
            std::cout<<"\nResult products: ";
            for(int resProduct : nums) {
                std::cout<<resProduct<<" ";
            }
        }

        // Input section to handle the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userNeedOperation = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: Array | Prefix Sum 
    Link: https://leetcode.com/problems/product-of-array-except-self/description/?envType=daily-question&envId=2024-03-15
*/
