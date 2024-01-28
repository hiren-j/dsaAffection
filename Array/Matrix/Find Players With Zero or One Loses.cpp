// Program to find the "list of players" with "no losses" and having "exactly one losses" ~ coded by Hiren
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>

// Solution class:
class Solution {
public:
    // #1 Method to find the "list of players", using map with set - O(NLogN + MLogM) & O(N+M) : Where N, M is the total number of "winnersList" and "losers".
    std::vector<std::vector<int>> getWinners_V1(std::vector<std::vector<int>>& matches) {
        std::vector<std::vector<int>> answer(2);
        std::unordered_map<int, int> losers;
        std::unordered_set<int> winnersList;

        for(auto& match : matches) {
            losers[match[1]]++;
        }

        for(auto& match : matches) {
            if(!losers.count(match[0]) && !winnersList.count(match[0])) {
                answer[0].emplace_back(match[0]);
            }
            winnersList.insert(match[0]);
        }

        for(auto& [loser, numLoses] : losers) {
            if(numLoses == 1) {
                answer[1].emplace_back(loser);
            }
        }

        std::sort(begin(answer[0]), end(answer[0]));
        std::sort(begin(answer[1]), end(answer[1]));

        return answer;
    }

    // #2 Method to find the "list of players", using map only - O(NLogN + MLogM) & O(M) : Where N, M is the total number of "winnersList" and "losers".
    std::vector<std::vector<int>> getWinners_V2(std::vector<std::vector<int>>& matches) {
        std::unordered_map<int, int> losers;

        for(auto& match : matches) {
            losers[match[1]]++;
        }

        std::vector<int> winnersList, oneLoseList;

        for(auto& match : matches) {
            int winner = match[0], loser = match[1];
            if(!losers.count(winner)) {
                winnersList.push_back(winner);
                losers[winner] = 2;
            }
            if(losers[loser] == 1) {
                oneLoseList.push_back(loser);
            }
        }

        std::sort(begin(winnersList), end(winnersList));
        std::sort(oneLoseList.begin(), oneLoseList.end());

        return {winnersList, oneLoseList};   
    }
};

// Method to print the given list - O(K) & O(1) : Where K is the size of the list.
void printList(std::vector<int>& list) {
    for(int player : list) {
        std::cout<<player<<' ';
    }
}

// Driver code
int main() {
    bool userWantsOperation = true; 

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user.
        system("cls || clear"); 

        // Input section for the "number of matches".
        int n;
        std::cout<<"Enter the number of matches: ";
        std::cin>>n;

        // Check for the given value is valid or not.
        if(n <= 0) {
            std::cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }

        std::vector<std::vector<int>> matches(n, std::vector<int>(2));

        std::cout<<"\nEnter the lists of players in this format: [winner, loser]\n";

        // Input section to get the "lists of players" for the matches.
        for(int match = 0; match < n; ++match) {
            int winner, loser;
            std::cout<<"Enter the list for "<<match+1<<"th match: ";
            std::cin>>winner>>loser;
            matches[match][0] = winner;
            matches[match][1] = loser;
        }

        // Call to find the "list of players" with "no losses" and having "exactly one losses".
        Solution solution;
        std::vector<std::vector<int>> answer = solution.getWinners_V2(matches);

        // Print call.
        std::cout<<"\nList of winners (players that have not lost any matches): ";
        printList(answer[0]);

        // Print call.
        std::cout<<"\nList of losers (players that have lost exactly one match): ";
        printList(answer[1]);

        // Input section to handle the flow of iterations of the application.
        char userChoise;
        std::cout<<"\n\nPress \'R\' to restart the application, else application will exit automatically: ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false;
    }

    return 0;
}
/*
    Topics: Array | Hash Table | Sorting | Counting
    Link: https://leetcode.com/problems/maximum-product-difference-between-two-pairs/description/?envType=daily-question&envId=2023-12-18
*/
