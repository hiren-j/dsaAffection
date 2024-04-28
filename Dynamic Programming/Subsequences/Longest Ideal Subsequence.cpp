// Program to find the length of the longest ideal string ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <vector>

// #1 Class to implement the Top-down approach:
class TopDown_A {
public:
    // Method to find the length of the longest ideal string, using recursion with memoization - O(N) & O(N) : Where N let be the size of the string "s"
    int longestIdealString(const std::string& s, int k) {
        int size = s.size();
        std::vector<std::vector<int>> memory(123, std::vector<int>(size, -1));
        return solveWithMemo(memory, s, k, '\0', size, 0);
    }

private:
    // O(123*N) & O(123*N)
    int solveWithMemo(std::vector<std::vector<int>>& memory, const std::string& s, int k, char prevLetter, int size, int index) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(index == size) 
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevLetter][index] != -1)
            return memory[prevLetter][index];

        // There are always two possibilities to perform at each letter
        int currSkip = solveWithMemo(memory, s, k, prevLetter, size, index + 1); // Is to skip the letter and move on
        int currTake = 0;                                                        // Is to pick the letter and move on

        // If the absolute difference between the previous and the current letter is valid then pick the current letter into the subsequence and then move on
        if(prevLetter == '\0' || abs(prevLetter - s[index]) <= k)
            currTake = 1 + solveWithMemo(memory, s, k, s[index], size, index + 1);
        
        // Store the value of the maximum length to the memoization table and then return it
        return memory[prevLetter][index] = std::max(currSkip, currTake);
    }
    
    // O(2^N) & O(N)
    int solveWithoutMemo(const std::string& s, int k, char prevLetter, int size, int index) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(index == size) 
            return 0;

        // There are always two possibilities to perform at each letter
        int currSkip = solveWithoutMemo(s, k, prevLetter, size, index + 1); // Is to skip the letter and move on
        int currTake = 0;                                                   // Is to pick the letter and move on 

        // If the absolute difference between the previous and the current letter is valid then pick the current letter into the subsequence and then move on
        if(prevLetter == '\0' || abs(prevLetter - s[index]) <= k)
            currTake = 1 + solveWithoutMemo(s, k, s[index], size, index + 1);
        
        // As we're striving for the maximum length hence return the maximum value
        return std::max(currSkip, currTake);
    }
};

// #2 Class to implement the Top-down approach:
class TopDown_B {
public:
    // Method to find the length of the longest ideal string, using recursion with memoization - O(N) & O(N) : Where N let be the size of the string "s"
    int longestIdealString(const std::string& s, int k) {
        int size = s.size();
        std::vector<std::vector<int>> memory(123, std::vector<int>(size, -1));
        return solveWithMemo(memory, s, k, '\0', size, 0);
    }

private:
    // O(123*N) & O(123*N)
    int solveWithMemo(std::vector<std::vector<int>>& memory, const std::string& s, int k, char prevLetter, int size, int startIndex) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(startIndex == size) 
            return 0;

        // Memoization table: If the current state is already computed then return the computed value
        if(memory[prevLetter][startIndex] != -1)
            return memory[prevLetter][startIndex];

        // Store the length of the longest ideal subsequence
        int maxLength = 0;

        // Iterate and generate all the possible subsequences
        for(int index = startIndex; index < size; ++index) {
            // If the absolute difference between the previous and the current letter is valid then pick the current letter into the subsequence and then move on
            if(prevLetter == '\0' || abs(prevLetter - s[index]) <= k) {
                maxLength = std::max(maxLength, 1 + solveWithMemo(memory, s, k, s[index], size, index + 1));
            }
        }
        
        // Store the value of the maximum length to the memoization table and then return it
        return memory[prevLetter][startIndex] = maxLength;
    }

    // O(2^N) & O(N)
    int solveWithoutMemo(const std::string& s, int k, char prevLetter, int size, int startIndex) {
        // Edge case: If all the letters are exhausted then you can't pick any more
        if(startIndex == size) 
            return 0;

        // Store the length of the longest ideal subsequence
        int maxLength = 0;

        // Iterate and generate all the possible subsequences
        for(int index = startIndex; index < size; ++index) {
            // If the absolute difference between the previous and the current letter is valid then pick the current letter into the subsequence and then move on
            if(prevLetter == '\0' || abs(prevLetter - s[index]) <= k) {
                maxLength = std::max(maxLength, 1 + solveWithoutMemo(s, k, s[index], size, index + 1));
            }
        }
        
        // As we're striving for the maximum length hence return the maximum value
        return maxLength;
    }
};
// Note: This solution can lead to the time-limit exceed

// Driver code
int main() {
    // Tracks the user wants to run the application or not
    bool userRunsApplication = true;

    while(userRunsApplication) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the value of k
        int k;
        std::cout<<"Enter the value of k: ";
        std::cin>>k;

        // Input the size of the string
        int size;
        std::cout<<"Enter size of the string: ";
        std::cin>>size;

        // Check the given values are lying within the problem constraints or not
        if(k < 0 || k > 25) {
            std::cout<<"You must enter the value of k lying between 0 and 25!";
        }
        else if(size < 1 || size > 1e5) {
            std::cout<<"You must enter the string of size lying between 1 and 10^5!";
        }
        else {
            // Create the string of given size
            std::string s; 
            s.resize(size);

            // Input the values of string
            std::cout<<"\nEnter the values of string! The application only accepts lowercase english letters!\n";
            for(int index = 0; index < size;) {
                std::cout<<"Enter the value of "<<index<<"th index: ";
                std::cin>>s[index];
                // Check the given value is lying within the problem constraints or not
                if(!islower(s[index])) {
                    std::cout<<"You must enter a lowercase english letter!\n";
                }
                else {
                    index++;
                }
            }
            
            // Call to find the length of the longest ideal string
            TopDown_A topDown;
            int maxLength = topDown.longestIdealString(s, k);
            std::cout<<"\nThe length of the longest ideal string is: "<<maxLength;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userRunsApplication = (userChoice == 'R');
    }

    return 0;
}
/*
    Topics: String | Dynamic Programming
    Link: https://leetcode.com/problems/longest-ideal-subsequence/description/?envType=daily-question&envId=2024-04-25
*/
