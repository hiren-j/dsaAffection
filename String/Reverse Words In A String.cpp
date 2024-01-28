// Program to return a string of the words in reverse order concatenated by a single space ~ coded by Hiren
#include <iostream>
#include <sstream>
#include <vector>
#include <stack>

// #Solution class:
class Solution {
public:
    // #1 Method to return a string of the words in reverse order, using 1 stack - O(N) & O(N)
    std::string reverseWords_V1(const std::string& s) {
        int n = s.size();
    
        std::stack<std::string> st; // Stores the words in reverse order
        std::string tmp = "";       // Stores the resultant string (output)
    
        // Iterate and store each word to the stack
        for(int i=0; i<n; i++) {
            if(s[i] != ' ')
                tmp.push_back(s[i]);
    
            if((i == n-1 || s[i] == ' ') && !tmp.empty())
                st.push(tmp), tmp = "";
        }
    
        // Pop each word one by one from the stack and append it to the output string "tmp"
        while(!st.empty()) {
            tmp.append(st.top()); 
            st.pop();
            tmp.push_back(' ');
        }
    
        // Remove the additional single space 
        tmp.pop_back();
    
        // Return the resultant string (output)
        return tmp;
    }
        
    // #2 Method to return a string of the words in reverse order, using tokenization and buffer - O(N) & O(N)
    std::string reverseWords_V2(const std::string& s) {
        std::vector<std::string> words; // Stores the words of string "s"
        std::stringstream ss(s);        // Initialize the stringstream object by string "s"
        std::string tmp = "";           // Stores the resultant string (output)
    
        // Extract each word of the string "s" and store them to the buffer "words"
        while(ss >> tmp) {
            words.push_back(tmp);
        }
    
        tmp = "";
    
        // Append each word to the output string "tmp"
        for(int i = words.size()-1; i >= 0; --i) {
            tmp.append(words[i]);
            tmp.push_back(' ');
        }
    
        // Remove the additional single space 
        tmp.pop_back();    
    
        // Return the resultant string (output)
        return tmp;
    }
    
    // #3 Method to return a string of the words in reverse order, using constant auxiliary space - O(N) & O(1)
    std::string reverseWords_V3(const std::string& s) {
        int n = s.size();
        int i = n-1;
    
        // Require to store the resultant string (output)
        std::string output = "";
    
        while(i >= 0) {
            // Skip all the consecutive spaces and find the "end point" of a word
            while(i >= 0 && s[i] == ' ') i--;
            int endPoint = i;
    
            // Skip all the consecutive characters and find the "start point" of that word
            while(i >= 0 && s[i] != ' ') i--;
            int startPoint = i+1;
    
            // Store the word to the resultant string (output)
            output.append(s.substr(startPoint, endPoint - startPoint + 1));
            output.push_back(' ');
        }
    
        // Iterate and remove the additional spaces
        while(!output.empty() && output.back() == ' ') {
            output.pop_back();
        }
    
        // Return the resultant string (output)
        return output;
    }
};

// Driver code
int main() {
    std::cout<<"Enter the number of testcases: ";
    int testCases; 
    std::cin>>testCases;
    std::cin.ignore(); // Ignore the newline character left in the input buffer.
    
    if(testCases <= 0) {
        std::cout<<"Enter a valid number for the testcases, application expects a positive integer!";
        return 0;
    }
        
    while(testCases--) {
        std::string s; 
        std::cout<<"\nEnter a sentence: "; getline(std::cin, s);
        Solution solution;
        std::string output = solution.reverseWords_V3(s);        
        std::cout<<"Sentence after words reversal: "<<output<<'\n';
    }

    return 0;
}
/*
    Topics: String | Two Pointers | Stack
    Link: https://leetcode.com/problems/reverse-words-in-a-string/description/
*/
