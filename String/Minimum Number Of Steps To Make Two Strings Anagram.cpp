// Program to find the minimum number of steps required to make the two strings anagram ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>

// Solution class:
class Solution {
public:
    // #1 Method to find the minimum number of steps, using (stl) map - O(N) & O(1) : Where N is size of the string "s" (s1.size == s2.size) 
    int minSteps_V1(const std::string& s, const std::string& t) {
        // Stores the letters with their frequencies
        std::unordered_map<char, int> mp;

        // Iterate the string "s" and map the letters with their frequencies
        for(char ch : s)
            mp[ch]++;

        // Iterate the string "t" and reduce the frequency of the letters which are also present in string "s"
        for(char ch : t)
            mp[ch]--;

        // Stores the minimum number of steps (resultant value)
        int output = 0;

        // Iterate and count the resultant value
        for(auto [ch, count] : mp)
            output += (count > 0) ? count : 0;

        // Return the minimum number of steps (resultant value)
        return output;
    }

    // #2 Method to find the minimum number of steps, using buffer only - O(N) & O(1) : Where N is size of the string "s" (s1.size == s2.size)
    int minSteps_V2(const std::string& s, const std::string& t) {
        int n = s.size();
        
        // Stores the frequencies of the letters at their corresponding index 
        std::vector<int> mp(26);

        // Iterate the strings
        for(int i=0; i<n; i++) 
            mp[s[i]-'a']++, // Increase the frequency for the ith letter of the string "s"
            mp[t[i]-'a']--; // Decrease the frequency for the ith letter of the string "t"

        // Stores the minimum number of steps (resultant value)
        int output = 0;

        // Iterate and count the resultant value
        for(int count : mp)
            output += (count > 0) ? count : 0;

        // Return the minimum number of steps (resultant value)
        return output;
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles console clearence for both "windows" and "linux" user
        system("cls || clear");

        // Input section for strings
        std::string s, t;
        std::cout<<"Enter the first string: " ; std::cin>>s;
        std::cout<<"Enter the second string: "; std::cin>>t;

        // Call to find the minimum number of steps
        Solution solution;
        int output = solution.minSteps_V2(s, t);
        std::cout<<"The minimum number of steps needed to make \""<<s<<"\" and \""<<t<<"\" anagram is: "<<output;

        // Input section to handle the flow of iterations of the application
        char userChoise;
        std::cout<<"\n\nDo you want to perform the same operation on an another string! (Write \'Y\' for \"Yes\", else application will exit automatically): ";
        std::cin>>userChoise;
        canPerformOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Hash Table | String | Counting
    Link: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/description/
*/
