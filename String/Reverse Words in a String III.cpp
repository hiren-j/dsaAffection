// Program to reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order ~ coded by Hiren
#include <iostream>
#include <stack>
using namespace std;

// #1 Method to reverse the words of a string, using 1 stack - O(N) & O(N)
string reverseWords_V1(const string& s) {
    int n = s.length();

    stack<char> st;     // Stores the word in reverse order
    string output = ""; // Stores the resultant string (output)

    // Iterate and store the words to the stack
    for(int i=0; i<n; i++) {
        // If the character is not a space then store it to stack
        if(s[i] != ' ') 
            st.push(s[i]);

        // Pop the characters of the word and store it to the resultant string (output) 
        if(s[i] == ' ' || i == n-1) {
            while(!st.empty()) {
                output.push_back(st.top());
                st.pop();
            }
            output.push_back(' ');
        }   
    }

    // Remove the additional single space
    output.pop_back();

    // Return the resultant string (output)
    return output;
}

// #2 Method to reverse the words of a string, using two-pointer technique - O(N) & O(1)
string reverseWords_V2(const string& s) {
    int n = s.length();

    int start = 0, end = 0;
    string output = ""; // Stores the resultant string (output)

    while(start < n) {
        // Skip all the consecutive spaces and find the end-point of a word 
        end = start;
        while(end < n && s[end] != ' ')
            end++;

        // Store all the consecutive characters of that word to the resultant string (output)
        int tmp = end - 1;
        while(tmp >= start)
            output.push_back(s[tmp--]);
        
        output.push_back(' ');
        start = end + 1;
    }

    // Remove the additional single space
    output.pop_back();
    
    // Return the resultant string (output)
    return output;
}

// Driver code
int main() {
    cout<<"Enter the number of testcases: ";
    int testCases; 
    cin>>testCases;
    cin.ignore(); // Ignore the newline character left in the input buffer.

    if(testCases <= 0) {
        std::cout<<"Enter a valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        string s; 
        getline(cin, s);
        s = reverseWords_V2(s);        
        cout<<s<<'\n';
    }

    return 0;
}
// Link: https://leetcode.com/problems/reverse-words-in-a-string-iii/description/
