// Program to find all the possible combinations of K numbers chosen from the range [1, N] ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// #1 Backtracking approach:
class Backtracking_V1 {
    vector<vector<int>> combinations;

    void getAllUniqueCombinations(int N, int K, int startIdx, vector<int>& currCombination) {
        // Edge case: When the K numbers from the range [1, N] are chosen
        if(K == 0) {
            combinations.push_back(currCombination);
            return;
        }

        // When the elements are remaining from the range [1, N]
        for(int J = startIdx; J <= N; J++) {
            currCombination.push_back(J); // Include the element (perform the action)
            getAllUniqueCombinations(N, K-1, J+1, currCombination);
            currCombination.pop_back();   // Exclude the element (revert the action)
        }
    }

public:
    // Method to find all the possible combinations of K numbers chosen from the range [1, N] - O(2^N * K) & O(M * K) : Where M is the total number of all the possible combinations
    vector<vector<int>> combine(int N, int K) {
        vector<int> currCombination;
        getAllUniqueCombinations(N, K, 1, currCombination);
        return combinations;
    }
};

// #2 Backtracking approach:
class Backtracking_V2 {
    vector<vector<int>> combinations;

    void getAllUniqueCombinations(int N, int K, int J, vector<int>& currCombination) {
        // Edge case: When the K numbers from the range [1, N] are chosen
        if(K == 0) {
            combinations.push_back(currCombination);
            return;
        }

        // When the elements are remaining from the range [1, N]
        if(J <= N) {
            // Include the element and move on
            currCombination.push_back(J);
            getAllUniqueCombinations(N, K-1, J+1, currCombination);
            currCombination.pop_back();

            // Exclude the element and move on
            getAllUniqueCombinations(N, K, J+1, currCombination);
        }
    }

public:
    // Method to find all the possible combinations of K numbers chosen from the range [1, N] - O(2^N * K) & O(M * K) : Where M is the total number of all the possible combinations
    vector<vector<int>> combine(int N, int K) {
        vector<int> currCombination;
        getAllUniqueCombinations(N, K, 1, currCombination);
        return combinations;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        // Input section for value K and N
        int N, K;
        cout<<"Enter the value of N: "; cin>>N;
        cout<<"Enter the value of K: "; cin>>K;

        // Check the given value is valid or not
        if(N < 1 || K < 1 || N > 20 || K > N) {
            cout<<"Enter a value which lies within the problem constraints! Application expects a positive integer!";
            return 0;
        }

        // Call to get the list of all possible combinations of K numbers chosen from the range [1, N]
        Backtracking_V2 bt;
        vector<vector<int>> combinations = bt.combine(N, K);

        // Print the values of each combination
        cout<<"\nList of all the possible combinations of "<<K<<" numbers chosen from the range [1, "<<N<<"]:\n";
        for(auto& currCombination : combinations) {
            int size = currCombination.size();
            cout<<"[";
            for(int J = 0; J < size; ++J) {
                cout<<currCombination[J];
                if(J < size-1) cout<<", ";
            }
            cout<<"]\n";
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Backtracking
    Link: https://leetcode.com/problems/combinations/description/
*/
