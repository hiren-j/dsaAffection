// Program to find the level order traversal of the nodes value of a binary tree ~ coded by Hiren
#include <iostream>
#include <vector>
#include <queue>

// Tree template
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Init constructor
    TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr) 
    : 
    data(data), left(left), right(right) {}
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to find the level order traversal of the nodes value, using buffer with dfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    std::vector<std::vector<int>> getLevelOrder(TreeNode* rootNode) {
        // Stores the nodes in level wise order
        std::vector<std::vector<int>> nodesLevelWise;
        // Traverse and store the level order of nodes in the 2D buffer
        dfs(rootNode, 0, nodesLevelWise);
        // Return the 2D buffer containing the level order of nodes
        return nodesLevelWise;
    }

private:
    // Method helper
    void dfs(TreeNode* rootNode, int currentDepth, std::vector<std::vector<int>>& nodesLevelWise) {
        if(rootNode) {
            // If the depth value is equal to the size of the 2D buffer, then create a 1D buffer and store it to the 2D buffer
            if(currentDepth == nodesLevelWise.size()) {
                nodesLevelWise.emplace_back(std::vector<int>());
            }
            // Store the node value at its corresponding level in the 2D buffer
            nodesLevelWise[currentDepth].emplace_back(rootNode->data);
            // Recurse to both the subtrees and store the nodes at their corresponding level in the 2D buffer
            dfs(rootNode->left, currentDepth+1, nodesLevelWise);
            dfs(rootNode->right, currentDepth+1, nodesLevelWise);
        } 
    } 
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to find the level order traversal of the nodes value, using bfs - O(N) & O(N) : Where N is the total number of nodes of the tree
    std::vector<std::vector<int>> getLevelOrder(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return {};

        // Requires to maintain the nodes in level wise order
        std::queue<TreeNode*> q;
        q.push(rootNode);

        // Stores the nodes in level wise order
        std::vector<std::vector<int>> nodesLevelWise;

        // Explore the nodes of the tree
        while(!q.empty()) {
            int qSize = q.size();
            // Stores the nodes value of the current level
            std::vector<int> currLevel;
            // Explore the nodes of the current level
            while(qSize--) {
                // Extract the front node of the queue
                TreeNode* currNode = q.front(); q.pop();
                // Store the node value in the 1D buffer
                currLevel.emplace_back(currNode->data);
                // If the left child of the node exist, then store it to the queue
                if(currNode->left) 
                    q.push(currNode->left);
                // If the right child of the node exist, then store it to the queue
                if(currNode->right)
                    q.push(currNode->right);
            }
            // Store the 1D buffer (containing the nodes of the current level) into the 2D buffer
            nodesLevelWise.emplace_back(currLevel);
        }

        // Return the 2D buffer containing the level order of nodes
        return nodesLevelWise;
    }
};

// Class to wrap all the basic methods of the tree:
class TreeCommonMethods {
public:
    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1)
    TreeNode* insertNodeInTree(TreeNode* rootNode, int key) {
        if(!rootNode)
            return new TreeNode(key);

        TreeNode* parentNode = nullptr;
        TreeNode* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode = (currNode->data < key) ? currNode->right : currNode->left;
        }

        TreeNode* newNode = new TreeNode(key);

        (parentNode->data < key) ? parentNode->right = newNode : parentNode->left = newNode;

        return rootNode;
    }

    // Method to delete the tree, using dfs only - O(N) & O(H)
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode;

        return nullptr;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool canPerformOperation = true;

    while(canPerformOperation) {
        // Handles the console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the number of nodes for the tree
        int N;
        std::cout<<"Enter the number of nodes for the tree: ";
        std::cin>>N;

        // Tracks the root node of the tree
        TreeNode* rootNode = nullptr;
        TreeCommonMethods commonMethods;

        // Input the nodes value of the tree
        for(int node = 1; node <= N; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            rootNode = commonMethods.insertNodeInTree(rootNode, key);
        }

        // Call to find the level order traversal
        Solution_V2 solution;
        auto nodesLevelWise = solution.getLevelOrder(rootNode);

        // Print values
        std::cout<<"\nLevel order traversal of the tree is:\n";
        for(auto& currLevel : nodesLevelWise) {
            int size = currLevel.size();
            std::cout<<"[";
            for(int node = 0; node < size; ++node) {
                (node < size-1) ? std::cout<<currLevel[node]<<", " : std::cout<<currLevel[node];
            }
            std::cout<<"]\n";
        }

        // Deletion call
        rootNode = commonMethods.deleteTree(rootNode);

        // Input section to handle the flow of iterations of the application
        char userChoise;
        std::cout<<"\nDo you want to perform the same operation on an another tree? (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        canPerformOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
/*
    Topics: Tree | Breadth-First-Search | Binary Tree
    Link: https://leetcode.com/problems/binary-tree-level-order-traversal/description/
*/
