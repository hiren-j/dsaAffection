// Program to reverse the odd levels of a binary tree ~ coded by Hiren
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <chrono>
using namespace std;

// Tree template
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    // Init constructor
    TreeNode(int val, TreeNode* left = nullptr, TreeNode* right = nullptr) 
    :
    val(val), left(left), right(right) {}
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to reverse the odd levels of the binary tree, using buffer with dfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    TreeNode* reverseOddLevels(TreeNode* rootNode) {
        // Stores the odd levels
        vector<vector<TreeNode*>> nodesLevelWise; 
        // Traverse the tree and store all the odd levels to the buffer
        storeOdds(rootNode, 0, 0, nodesLevelWise);
        // Reverse the odd levels
        reverseOdds(nodesLevelWise, 0, nodesLevelWise.size()); 
        // Return the root node of the tree
        return rootNode;
    }

private:
    // Method helper
    void storeOdds(TreeNode* currNode, int levelNumber, int countOdds, vector<vector<TreeNode*>>& nodesLevelWise) {
        // When the current node of the tree exist or when the tree is not empty
        if(currNode) {
            // When current is the odd level
            if(levelNumber % 2) {
                // When current level is the first ever odd level
                if(countOdds == nodesLevelWise.size()) {
                    // Store a new buffer in the 2D buffer to store the nodes of the current level
                    nodesLevelWise.push_back(vector<TreeNode*>());
                }
                // Store the current node at it's corrosponding level in the buffer
                nodesLevelWise[countOdds].push_back(currNode);
                // Update the number of odd levels seen till now
                countOdds++;
            }
            // Recurse to all the levels in the tree
            storeOdds(currNode->left, levelNumber+1, countOdds, nodesLevelWise);
            storeOdds(currNode->right, levelNumber+1, countOdds, nodesLevelWise);
        }
    }

    // Method helper
    void reverseOdds(vector<vector<TreeNode*>>& nodesLevelWise, int levelNumber, int size) {
        // When the level number is present in the buffer
        if(levelNumber < size) {
            // Extract the current level from the buffer
            auto& currLevel = nodesLevelWise[levelNumber];
            // Calculate and store the size of the current level
            int currLevelSize = currLevel.size();
            // Iterate and swap the node values (reverse the level)
            for(int node = 0; node < currLevelSize/2; ++node) {
                swap(currLevel[node]->val, currLevel[currLevelSize-node-1]->val);   
            }
            // Recurse to all the odd levels of the buffer
            reverseOdds(nodesLevelWise, levelNumber+1, size);
        }
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to reverse the odd levels of the binary tree, using buffer with bfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    TreeNode* reverseOddLevels(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return nullptr;

        // Maintains the nodes of the tree level wise
        queue<TreeNode*> q;
        q.push(rootNode);  
        
        // Tracks for the odd levels
        bool isOddLevel = false;

        while(!q.empty()) {
            int qSize = q.size();
            // Stores the nodes of the current level
            vector<TreeNode*> currLevel;  
            while(qSize--) {
                // Extract the first node of the queue
                TreeNode* currNode = q.front(); q.pop();
                // If current is the odd level then store the node to the buffer
                if(isOddLevel)
                    currLevel.push_back(currNode);
                // If the left child of the node exist then store it to the queue
                if(currNode->left)
                    q.push(currNode->left);
                // If the right child of the node exist then store it to the queue
                if(currNode->right)
                    q.push(currNode->right);
            }
            // Calculate and store the size of the current level
            int size = currLevel.size();
            // When current is the odd level
            if(isOddLevel) {
                // Iterate and swap the node values (reverse the level)
                for(int node = 0; node < size/2; ++node) {
                    swap(currLevel[node]->val, currLevel[size-node-1]->val); 
                }
            }
            // Toggle the value to even if its odd or vice versa
            isOddLevel = !isOddLevel;
        } 

        // Return the head node of the tree
        return rootNode;
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to reverse the odd levels of the binary tree, using dfs only - O(N) & O(H) : Where N is the total number of nodes of the tree
    TreeNode* reverseOddLevels(TreeNode* rootNode) {
        preOrder(rootNode->left, rootNode->right, 1);
        return rootNode;
    }

private:
    // Method helper
    void preOrder(TreeNode* currNode1, TreeNode* currNode2, int levelNumber) {
        // When both the nodes are present
        if(currNode1 && currNode2) {
            // When current is the odd level
            if(levelNumber % 2) {
                // Swap the nodes value
                swap(currNode1->val, currNode2->val);
            }
            // Recurse to all the childrens simultaneously in both the subtrees
            preOrder(currNode1->left, currNode2->right, levelNumber+1);
            preOrder(currNode1->right, currNode2->left, levelNumber+1);
        }
    }
};

// Class to wrap all the basic methods of the tree
class TreeCommonMethods {
public:
    // Method to insert a node in the binary tree, using constant auxiliary space - O(N) & O(1)
    TreeNode* insertNode(TreeNode* rootNode, int key) {
        if(!rootNode)
            return new TreeNode(key);

        TreeNode* parentNode = nullptr;
        TreeNode* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode = (currNode->val < key) ? currNode->right : currNode->left;
        }

        TreeNode* newNode = new TreeNode(key);

        (parentNode->val < key) ? parentNode->right = newNode : parentNode->left = newNode;

        return rootNode;
    }

    // Method to delete the binary tree, using dfs only - O(N) & O(H)
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode;

        return nullptr;
    }

    // Method to print the tree, using bfs only - O(N) & O(N)
    void printTree(TreeNode* rootNode) {
        if(!rootNode)
            return;

        queue<TreeNode*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            cout<<"[";
            while(qSize--) {
                TreeNode* currNode = q.front(); q.pop();
                (!qSize) ? cout<<currNode->val : cout<<currNode->val<<", ";
                if(currNode->left)
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
            }
            cout<<"]\n";
        }
    }
};

// Driver code
int main() {
    int testCases; 
    cout<<"Enter the number of testcases you want: ";
    cin>>testCases;

    while(testCases--) {
        // Handles console clearence for both "windows" and "linux" user
        system("cls || clear");
        int n; 
        cout<<"Enter the number of nodes for the tree: ";
        cin>>n;

        // Tracks the root node of the tree
        TreeNode* rootNode = nullptr;
        TreeCommonMethods tcm;

        // Input section for the nodes
        for(int node = 1; node <= n; ++node) {
            int key;
            cout<<"Enter the value of the "<<node<<"th node: ";
            cin>>key;
            rootNode = tcm.insertNode(rootNode, key);
        }

        // Print call
        cout<<"\nTree before level reversal:\n";
        tcm.printTree(rootNode);
        
        // Level reversal call
        Solution_V2 s;
        rootNode = s.reverseOddLevels(rootNode); 

        // Print call
        cout<<"\nTree after level reversal:\n";
        tcm.printTree(rootNode);

        // Deletion call
        rootNode = tcm.deleteTree(rootNode);

        // User based prompts for application flow
        if(testCases) {
            int userSeconds;
            cout<<"\nEnter the number of seconds which after you want to restart the application: ";
            cin>>userSeconds;
            cout<<"The application will restart in "<<userSeconds<<" seconds!";
            // Add 10-seconds of delay before the next iteration
            this_thread::sleep_for(chrono::seconds(userSeconds));
        }
        else {
            cout<<"\nThe application will close in 10 seconds!";
            // Add 10-seconds of delay before the next iteration
            this_thread::sleep_for(chrono::seconds(10));
        }
    }

    return 0;
}
// Link: https://leetcode.com/problems/reverse-odd-levels-of-binary-tree/
