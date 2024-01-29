// Program to invert a binary tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <queue>

// Tree template
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Init constructor
    TreeNode(int data, TreeNode* left, TreeNode* right)
    :
    data(data), left(left), right(right) {}

    // Init destructor
    ~TreeNode() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
    }

    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1) : Where N is the total number of nodes of the tree
    TreeNode* insertNodeInTree(TreeNode* rootNode, int key) {
        if(!rootNode)
            return new TreeNode(key, nullptr, nullptr); 

        TreeNode* parentNode = nullptr;
        TreeNode* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode   = (currNode->data > key) ? currNode->left : currNode->right;
        }

        TreeNode* newNode = new TreeNode(key, nullptr, nullptr);

        (parentNode->data > key) ? parentNode->left = newNode : parentNode->right = newNode;

        return rootNode;
    }

    // Method to delete the tree, using dfs only - O(N) & O(H) : Where N is the total number of nodes and H is height of the tree
    TreeNode* deleteTree(TreeNode* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left);
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode;

        return nullptr;
    }

    // Method to print the tree, using bfs - O(N) & O(N) : Where N is the total number of nodes and H is height of the tree
    void printTree(TreeNode* rootNode) {
        if(!rootNode)
            return;

        std::queue<TreeNode*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            std::cout<<"[";
            while(qSize--) {
                TreeNode* currNode = q.front(); q.pop();
                (!qSize) ? std::cout<<currNode->data : std::cout<<currNode->data<<", " ;
                if(currNode->left)
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
            }
            std::cout<<"]\n";
        }
    }
};

// Solution class:
class Solution {
public:
    // Method to invert the binary tree, using dfs only - O(N) & O(H) : Where N is the total number of nodes and H is height of the tree
    TreeNode* invertTree(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return nullptr;

        TreeNode* nodeLeft  = rootNode->left;  // Tracks the left node of the current node
        TreeNode* nodeRight = rootNode->right; // Tracks the right node of the current node

        rootNode->left  = invertTree(nodeRight); // Recurse and set the right node to the left side of the current node
        rootNode->right = invertTree(nodeLeft);  // Recurse and set the left node to the right side of the current node

        // Return the current node
        return rootNode;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        // Input section to get the number of nodes of the tree
        int N;
        std::cout<<"Enter the number of nodes for the tree: ";
        std::cin>>N;

        // Check for the given value is valid or not
        if(N <= 0) {
            std::cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }
        
        // Tracks the root node of the tree
        TreeNode* rootNode = nullptr;

        // Input the nodes value of the tree
        for(int node = 1; node <= N; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            rootNode = rootNode->insertNodeInTree(rootNode, key);
        }

        // Print call
        std::cout<<"\nTree before inversion:\n";
        rootNode->printTree(rootNode);

        // Inversion call 
        Solution solution;
        rootNode = solution.invertTree(rootNode);

        // Print call
        std::cout<<"\nTree after inversion:\n";
        rootNode->printTree(rootNode);

        rootNode = rootNode->deleteTree(rootNode);

        // Input section to handle the flow of iterations of the application
        char userChoise;
        std::cout<<"\nDo you want to perform the same operation on an another tree? (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
/*
    Topics: Tree | Breadth-First-Search | Depth-First-Search | Binary Tree
    Link: https://leetcode.com/problems/invert-binary-tree/
*/
