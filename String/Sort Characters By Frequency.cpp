// Program to sort the given string in decreasing order based on the frequency of the characters ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

// Solution class
class Solution {
public:
    // #1 Method to sort the given string in decreasing order based on the frequency of the characters - O(NLogK) & O(K) : Where N let be the size of "s" and K of the "freq" map and "maxHeap" which can be 62 in the worst case
    std::string frequencySort_V1(std::string& s) {
        // Stores the "letters having maximum frequency" at the top of the "maxHeap"
        std::priority_queue<std::pair<int, char>> maxHeap;

        // Maps the "letters with their frequencies"
        std::unordered_map<char, int> freq;

        // Iterate the string
        for(char ch : s) {
            freq[ch]++; // Increase the frequency of the letter in "freq" map
        }

        // Iterate the "freq" map
        for(auto [ch, count] : freq) {
            // Store the information of the "letter with its frequency" in the "maxHeap"
            maxHeap.push({count, ch});
        }

        int i = 0;

        // Extract each "letter with its frequency" from the "maxHeap" and fill the letter for the "frequency" times in the string
        while(!maxHeap.empty()) {
            auto [count, ch] = maxHeap.top();
            maxHeap.pop();
            while(count--) {
                s[i++] = ch;
            }
        }

        // Return the result string
        return s;
    }
    // Note: The brute force solution can be made using easy sorting

    // #2 Method to sort the given string in decreasing order based on the frequency of the characters - O(NLogK) & O(K) : Where N let be the size of "s" and K of the "maxHeap" which can be 62 in the worst case
    std::string frequencySort_V2(std::string& s) {
        std::vector<int> smallLetters(26); // Stores the frequency for "each lowercase letter" to their corresponding index
        std::vector<int> capLetters(26);   // Stores the frequency for "each uppercase letter" to their corresponding index
        std::vector<int> digits(10);       // Stores the frequency for "each digits" to their corresponding index
        
        // Stores the "letters having maximum frequency" at the top of the "maxHeap"
        std::priority_queue<std::pair<int, char>> maxHeap;

        // Iterate the string and map the "letters with their frequency" in their corresponding buffer 
        for(char ch : s) {
            if(ch >= 'A' && ch <= 'Z')
                capLetters[ch - 'A']++; 
            else if(ch >= 'a' && ch <= 'z')
                smallLetters[ch - 'a']++;
            else
                digits[ch - '0']++;
        }

        // Iterate the buffers and store the information of "letter with its frequency" in the "maxHeap"
        for(int i=0; i<26; ++i) {
            if(capLetters[i] != 0)
                maxHeap.push({capLetters[i], i + 'A'});
            if(smallLetters[i] != 0)
                maxHeap.push({smallLetters[i], i + 'a'});
            if(i < 10 && digits[i] != 0)
                maxHeap.push({digits[i], i + '0'});
        }

        int i = 0;

        // Extract each "letter with its frequency" from the "maxHeap" and fill the letter for the "frequency" times in the string
        while(!maxHeap.empty()) {
            auto [count, ch] = maxHeap.top();
            maxHeap.pop();
            while(count--) {
                s[i++] = ch;
            }
        }

        // Return the result string
        return s;
    }
};

// Driver code
int main() {
    // Input section to handle the flow of iterations of the application
    int testCases;
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    while(testCases-- > 0) {
        std::cout<<"\nEnter a string: ";
        std::string s; 
        std::cin>>s;
        Solution solution;
        s = solution.frequencySort_V2(s);
        std::cout<<"Result string: "<<s<<'\n';
    }

    return 0;
}
/*
    Topics: Hash Table | String | Sorting | Heap (Priority Queue) | Counting
    Link: https://leetcode.com/problems/sort-characters-by-frequency/
*/
