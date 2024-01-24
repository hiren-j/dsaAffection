// Program to find the "list of players" with "no losses" and having "exactly one losses" ~ coded by Hiren
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

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
    int testCases; 
    std::cout<<"Enter the number of testcases you want: ";
    std::cin>>testCases;

    if(testCases <= 0) {
        std::cout<<"Enter an valid number for the testcases, application expects a positive integer!";
        return 0;
    }

    while(testCases--) {
        system("clear || cls"); 
        int n;
        std::cout<<"Enter the number of matches: ";
        std::cin>>n;

        std::vector<std::vector<int>> matches(n, std::vector<int>(2));

        std::cout<<"\nEnter the lists of players in this format: [winner, loser]\n";

        for(int match = 0; match < n; ++match) {
            int winner, loser;
            std::cout<<"Enter the list for "<<match+1<<"th match: ";
            std::cin>>winner>>loser;
            matches[match][0] = winner;
            matches[match][1] = loser;
        }

        // Call to find the "list of players"
        Solution obj;
        std::vector<std::vector<int>> answer = obj.getWinners_V2(matches);

        std::cout<<"\nList of winners (players that have not lost any matches): ";
        printList(answer[0]);

        std::cout<<"\nList of losers (players that have lost exactly one match): ";
        printList(answer[1]);

        if(testCases != 0)
            std::cout<<"\n\nApplication will restart in 10 seconds!";
        else
            std::cout<<"\n\nApplication will close in 10 seconds!";
            
        // Add a 10-second delay before the next iteration.
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
// Link: https://leetcode.com/problems/find-players-with-zero-or-one-losses/
