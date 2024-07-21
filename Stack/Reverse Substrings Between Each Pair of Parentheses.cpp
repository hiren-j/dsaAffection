// Code to reverse the strings in each pair of matching parentheses, starting from the innermost one. So that the result should not contain any brackets ~ coded by Hiren

---------------------------------------------------------------------------------------------------------------

class Solution {
public:
    // Method to reverse the string in specified way using 1 stack - O(N*N) & O(N)
    string reverseParentheses(const string& s) {
        int n = s.size(), countTotalParentheses = 0;

        vector<int> countLeft(n), countRight(n);

        // Iterate and count the total number of parentheses present at the left side of each index
        for(int i = 0; i < n; ++i) {
            if(s[i] == ')' || s[i] == '(') countTotalParentheses++;
            countLeft[i] = countTotalParentheses;
        }

        countTotalParentheses = 0;

        // Iterate and count the total number of parentheses present at the right side of each index
        for(int i = n-1; i >= 0; --i) {
            if(s[i] == ')' || s[i] == '(') countTotalParentheses++;
            countRight[i] = countTotalParentheses;
        }

        stack<pair<char, int>> stack;
        string output;

        for(int j = 0; j < n; ++j) {
            // If the jth letter is a closing parentheses then reverse the valid part of the string
            if(s[j] == ')') {
                auto [p, i] = stack.top(); stack.pop();
                int substringLength   = j-i-1;
                int countValidLetters = countTotalParentheses - countLeft[i] - countRight[j];
                int lettersToReverse  = substringLength - countValidLetters;
                int size = output.size();
                reverseString(output, size-lettersToReverse, size-1);  
            }
            // Else if the jth letter is a opening parentheses then store it with it's index to the stack
            else if(s[j] == '(') {
                stack.push({s[j], j});
            }
            // Else it's a lowercase english letter hence store it to the output string
            else {
                output.push_back(s[j]);
            }
        }

        return output;
    }

private:
    // Method to reverse a string - O(N) & O(1)
    void reverseString(string& str, int start, int end) {
        while(start < end) {
            swap(str[start], str[end]);
            start++;
            end--;
        }
    }
};

---------------------------------------------------------------------------------------------------------------

/*
    Topics: String | Stack
    Link  : https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/description/
*/
