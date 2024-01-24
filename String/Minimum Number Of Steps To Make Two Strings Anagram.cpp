// Program to find the minimum number of steps required to make the two strings anagram ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// Solution class:
class Solution {
public:
    // #1 Method to find the minimum number of steps, using (stl) map - O(N) & O(1) : Where N is size of the string "s" (s1.size == s2.size) 
    int minSteps_V1(const std::string& s, const std::string& t) {
        std::unordered_map<char, int> mp;

        for(char ch : s)
            mp[ch]++;

        for(char ch : t)
            mp[ch]--;

        int output = 0;

        for(auto [ch, count] : mp)
            output += (count > 0) ? count : 0;

        return output;
    }

    // #2 Method to find the minimum number of steps, using buffer only - O(N) & O(1) : Where N is size of the string "s" (s1.size == s2.size)
    int minSteps_V2(const std::string& s, const std::string& t) {
        int n = s.size();
        
        std::vector<int> mp(26);

        for(int i=0; i<n; i++) 
            mp[s[i]-'a']++, mp[t[i]-'a']--;

        int output = 0;

        for(int count : mp)
            output += (count > 0) ? count : 0;

        return output;
    }
};

// Driver code
int main() {
    int testCases; 
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter a valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        // Handles console clearence for both "windows" and "linux" user
        system("cls || clear");

        // Input section for string
        std::string s, t;
        std::cout<<"Enter the first string: " ; std::cin>>s;
        std::cout<<"Enter the second string: "; std::cin>>t;

        // Call to find the minimum number of steps
        Solution obj;
        int output = obj.minSteps_V2(s, t);
        std::cout<<"\nThe minimum number of steps needed to make \""<<s<<"\" and \""<<t<<"\" anagram is: "<<output;
        
        // Prompts for application flow
        if(testCases)
            std::cout<<"\n\nThe application will restart in 10 seconds!";
        else
            std::cout<<"\n\nThe application will close in 10 seconds!";

        // Add 10-seconds of delay before the next iteration
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
// Link: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/description/
