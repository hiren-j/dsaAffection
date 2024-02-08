// Program to verify is if "word1" and "word2" are close or not ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Solution class:
class Solution {
public:
    // #1 Method to verify is if "word1" and "word2" are close or not, using map only : O(N+M) & O(1) : Where N is the size of "word1" and M of "word2"
    bool closeStrings_V1(const string& word1, const string& word2) {
        // If the size of both the strings are not equal then its not possible to attain one string from the other
        if(word1.size() != word2.size())
            return false;

        // If both the strings are equal then consider them as close
        if(word1 == word2)
            return true;
        
        unordered_map<char, int> freq1; // Maps the "letters with their frequency" of the "word1"
        unordered_map<char, int> freq2; // Maps the "letters with their frequency" of the "word2"

        // Iterate over the letters of "word1"
        for(char ch : word1)
            freq1[ch]++; // Increase the frequency of the letter in the "freq1" map
    
        // Iterate over the letters of "word2"
        for(char ch : word2)
            freq2[ch]++; // Increase the frequency of the letter in the "freq2" map

        for(auto& [ch1, count1] : freq1) {
            // Tracks the frequency of a letter in both the strings are same or not
            bool isFreqNotSame = true;
            // If the letter of the "word1" is not present in "word2" then the strings are not close
            if(!freq2.count(ch1)) {
                return false;
            }
            // Iterate the "freq2" map and look for the "same letter having the same frequency" in it
            for(auto& [ch2, count2] : freq2) {
                if(count1 == count2) {
                    isFreqNotSame = false;
                    count2 = -1;
                    break;
                }
            }
            // If the frequency is not same then both the strings are not close
            if(isFreqNotSame) {
                return false;
            }
        }

        // Return true, if reached here
        return true;
    }
    
    // #2 Method to verify is if "word1" and "word2" are close or not, using buffer only : O(N+M) & O(1) : O(N+M) & O(1) : Where N is the size of "word1" and M of "word2"
    bool closeStrings_V2(const string& word1, const string& word2) {
        // If the size of both the strings are not equal then its not possible to attain one string from the other
        if(word1.size() != word2.size())
            return false;
    
        // If both the strings are equal then consider them as close
        if(word1 == word2)
            return true;
    
        vector<int> freq1(26); // Maps the "letters with their frequency" of the "word1" to their corresponding index
        vector<int> freq2(26); // Maps the "letters with their frequency" of the "word2" to their corresponding index
    
        // Iterate over the letters of "word1"
        for(char ch : word1)
            freq1[ch - 'a']++; // Increase the frequency of the letter in the "freq1" map
    
        // Iterate over the letters of "word2"
        for(char ch : word2)
            freq2[ch - 'a']++; // Increase the frequency of the letter in the "freq2" map
    
        // Iterate the buffers
        for(int i = 0; i < 26; ++i) {
            // If the ith letter of the "word1" is not present in "word2" then the strings are not close
            if(freq1[i] == 0 && freq2[i] != 0) {
                return false;
            }
        }
    
        for(int i = 0; i < 26; ++i) {
            if(freq1[i] > 0) {
                // Tracks the frequency of a letter in both the strings are same or not
                bool isFreqNotSame = true;
                // Iterate the "freq2" buffer and look for the "same letter having the same frequency" in it
                for(int j = 0; j < 26; ++j) {
                    if(freq1[i] == freq2[j]) {
                        isFreqNotSame = false;
                        freq2[j] = -1;
                        break;
                    }
                }
                // If the frequency is not same then both the strings are not close
                if(isFreqNotSame) {
                    return false;
                }
            }
        }
    
        // Return true, if reached here
        return true;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the words
        string word1, word2; 
        cout<<"Enter the first word: " ; cin>>word1;
        cout<<"Enter the second word: "; cin>>word2;

        // Verification call
        Solution obj;
        if(obj.closeStrings_V2(word1, word2))
            cout<<"\n\""<<word1<<"\" and \""<<word2<<"\" are close!";
        else
            cout<<"\n\""<<word1<<"\" and \""<<word2<<"\" are not close!";

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        canPerformOperation = (userChoise == 'R') ? true : false ;
    }

    return 0;
}
/*
    Topics: Hash Table | String | Counting
    Link: https://leetcode.com/problems/determine-if-two-strings-are-close/description/
*/
