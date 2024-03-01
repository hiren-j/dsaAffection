// Program to get the list containing the most frequent subtree sums of a binary tree (if there is a tie, get all the values with the highest frequency in any order) ~ coded by Hiren
#include <unordered_map>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

// Tree template
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // Initialize constructor
    TreeNode(int val, TreeNode* left = nullptr, TreeNode* right = nullptr) {
        this->val = val;
        this->left = left;
        this->right = right;
    }

    // Method to construct the tree - O(N) & O(H) : Where N is the total number of nodes and H is the height of the tree
    TreeNode* constructTree(vector<int>& nodes, int start, int end) {
        if(start > end)
            return nullptr;

        int mid = start + (end - start) / 2;

        TreeNode* rootNode = new TreeNode(nodes[mid]);
        rootNode->left  = constructTree(nodes, start, mid-1);
        rootNode->right = constructTree(nodes, mid+1, end);

        return rootNode;
    }

    // Method to delete the tree - O(N) & O(H) : Where N is the total number of nodes and H is the height of the tree
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode;

        return nullptr;
    }

    // Method to print the tree - O(N) & O(N) : Where N is the total number of nodes of the tree
    void printTree(TreeNode* rootNode) {
        if(!rootNode)
            return;

        queue<TreeNode*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            cout<<"[";
            while(qSize--) {
                rootNode = q.front(); q.pop();
                (qSize == 0) ? cout<<rootNode->val : cout<<rootNode->val<<", ";
                if(rootNode->left)
                    q.push(rootNode->left);
                if(rootNode->right)
                    q.push(rootNode->right);
            }
            cout<<"]\n";
        }
    }
};

// #1 Solution class:
class Solution_V1 {        
public:
    // Method to get the list containing the most frequent subtree sums - O(N*N) & O(N)
    vector<int> findFrequentTreeSum(TreeNode* rootNode) {
        // Maps the sum of each subtree with their frequency (number of occurences)
        unordered_map<int, int> freqMap;

        // Stores the list containing the most frequent subtree sum (result values)
        vector<int> output;

        // Stores the maximum frequency from all the frequency
        int maxFreq = 0;

        // Traverse and map each subtree sum with their frequency 
        mapSumWithFreq(rootNode, maxFreq, freqMap);

        // Iterate and get the most frequent subtree sum
        for(auto [sum, freq] : freqMap) {
            if(freq == maxFreq) {
                output.push_back(sum);
            }
        }

        // Return the list containing the most frequent subtree sum (result values)
        return output;
    }

private:
    // Method to map the sum of each subtree with their frequency in the map - O(N) & O(N)
    void mapSumWithFreq(TreeNode* rootNode, int& maxFreq, unordered_map<int, int>& freqMap) {
        if(rootNode) {
            int subtreeSum = getSubtreeSum(rootNode);    // Stores the sum of the current subtree (including the current node)
            freqMap[subtreeSum]++;                       // Update the frequency of the sum 
            maxFreq = max(maxFreq, freqMap[subtreeSum]); // Update the value by the maximum frequency each time
            mapSumWithFreq(rootNode->left, maxFreq, freqMap);  // Recurse to the left subtree of the current node and map the sum with their frequency
            mapSumWithFreq(rootNode->right, maxFreq, freqMap); // Recurse to the right subtree of the current node and map the sum with their frequency
        }
    }

    // Method to get the subtree sum of the given node - O(N) & O(H)
    int getSubtreeSum(TreeNode* rootNode) {
        if(!rootNode)
            return 0;

        return getSubtreeSum(rootNode->left) + rootNode->val + getSubtreeSum(rootNode->right); 
    }
};

// #2 Solution class:
class Solution_V2 {        
public:
    // Method to get the list containing the most frequent subtree sum - O(N) & O(N)
    vector<int> findFrequentTreeSum(TreeNode* rootNode) {
        // Maps the sum of each subtree with their frequency (number of occurences)
        unordered_map<int, int> freqMap;

        // Stores the list containing the most frequent subtree sum (result values)
        vector<int> output;

        // Stores the maximum frequency from all the frequency
        int maxFreq = 0;

        // Traverse and map each subtree sum with their frequency 
        mapSumWithFreq(rootNode, maxFreq, freqMap);

        // Iterate and get the most frequent subtree sum
        for(auto [sum, freq] : freqMap) {
            if(freq == maxFreq) {
                output.push_back(sum);
            }
        }

        // Return the list containing the most frequent subtree sum (result values)
        return output;
    }

private:
    // Method to map the sum of each subtree with their frequency in the map - O(N) & O(N)
    int mapSumWithFreq(TreeNode* rootNode, int& maxFreq, unordered_map<int, int>& freqMap) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return 0;

        int sumLeftSubtree  = mapSumWithFreq(rootNode->left, maxFreq, freqMap);  // Stores the sum of the left subtree of the current node
        int sumRightSubtree = mapSumWithFreq(rootNode->right, maxFreq, freqMap); // Stores the sum of the right subtree of the current node
        int subtreeSum = sumLeftSubtree + rootNode->val + sumRightSubtree;       // Stores the sum of the current subtree (including the current node)

        freqMap[subtreeSum]++;                       // Update the frequency of the sum 
        maxFreq = max(maxFreq, freqMap[subtreeSum]); // Update the value by the maximum frequency each time

        // Return the sum of the current subtree
        return subtreeSum;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the nodes
        int n;
        cout<<"Enter the number of nodes of the tree: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Store the nodes value
        vector<int> nodes(n);

        // Input the nodes value
        for(int node=1; node<=n; ++node) {
            cout<<"Enter the value of the "<<node<<"th node: ";
            cin>>nodes[node];
        }

        // Tree construction call
        TreeNode* rootNode = rootNode->constructTree(nodes, 0, n-1);
        
        // Print call (print each level of the tree)
        cout<<"\nLevel order traversal of the tree:\n";
        rootNode->printTree(rootNode);

        // Call to get the list containing the most frequent subtree sums
        Solution_V2 solution;
        vector<int> output = solution.findFrequentTreeSum(rootNode);

        // Print values (print each value of the "output" buffer)
        cout<<"\nList containing the most frequent subtree sums: ";
        for(int num : output) {
            cout<<num<<"  ";
        }

        // Deletion call
        rootNode = rootNode->deleteTree(rootNode);

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoice;
        userWantsOperation = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Hash Table | Tree | Depth-First Search | Binary Tree
    Link: https://leetcode.com/problems/most-frequent-subtree-sum/description/
*/
