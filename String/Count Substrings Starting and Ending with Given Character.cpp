// Program to find the total number of substrings of "s" that start and end with character 'c' ~ coded by Hiren
#include <iostream>
#define ll long long

// Solution class:
class Solution {
public:
    // #1 Method to find the total number of substrings of "s" that start and end with character 'c' - O(N*N) & O(1) : Where N let be the size of "s"
    ll countSubstrings_V1(const std::string& s, char c) {
        int n = s.size();

        // Stores the "result count / result value"
        ll count = 0;

        for(int index1 = 0; index1 < n; ++index1) {
            // If the letter at index1 matches the given character 'c'
            if(s[index1] == c) {
                count++;
                // Iterate and count all the possible substrings ending with character 'c'
                for(int index2 = index1 + 1; index2 < n; ++index2) {
                    // If the letter at index2 matches the given character 'c', then increase the count value by one
                    count += (s[index2] == c) ? 1 : 0;
                }  
            }
        }

        // Return the count of the total number of substrings of "s" that start and end with character 'c' 
        return count;
    }

    // #2 Method to find the total number of substrings of "s" that start and end with character 'c' - O(N) & O(1) : Where N let be the size of "s"
    ll countSubstrings_V2(const std::string& s, char c) {
        // Stores the "result count / result value"
        ll count = 0;
        
        // Iterate "s" and count the total number of letters equal to the character 'c'
        for(char ch : s)
            count += (ch == c);
        
        // Return the count of the total number of substrings of "s" that start and end with character 'c' 
        return (count * (count + 1)) / 2;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the string size
        int n;
        std::cout<<"Enter size of the string: ";
        std::cin>>n;

        // Input the character 'c'
        char c;
        std::cout<<"Enter a character: ";
        std::cin>>c;

        // Check the size of the string and character lies within the problem constraints or not
        if(n <= 0 || n >= 100001) {
            std::cout<<"You must enter a string of length lying between 1 and 10^5!";
        }
        else if(!islower(c)) {
            std::cout<<"You must enter a character in lower case english letter!";
        }
        else {   
            // String to store the input letters
            std::string s;

            // Input the letters of the string
            for(int index = 0; index < n;) {
                char letter;
                std::cout<<"Enter the "<<index<<"th letter: ";
                std::cin>>letter;
                if(!islower(letter)) {
                    std::cout<<"You must enter a letter in lower case english letter!\n";
                    continue;
                }
                s += letter;
                index++;
            }

            std::cout<<"\nYour string: "<<s;

            // Call to find the total number of substrings of "s" that start and end with character 'c'
            Solution solution;
            int count = solution.countSubstrings_V2(s, c);
            std::cout<<"\nThe total number of substrings that start and end with character \'"<<c<<"\' is: "<<count;
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\n\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: String | Math
    Link: https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/description/
*/
