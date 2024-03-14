// Program to find the length of the diameter of the tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
using namespace std;

// Tree template
class TreeNode {
public:
    int data;
    TreeNode* left; TreeNode* right;

    // Initialize constructor
    TreeNode(int data, TreeNode* left = nullptr, TreeNode* right = nullptr) {
        this->data  = data;
        this->left  = left;
        this->right = right;
    }

    // Initialize destructor
    ~TreeNode() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
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
                TreeNode* currNode = q.front(); q.pop();
                (!qSize) ? cout<<currNode->data : cout<<currNode->data<<", ";
                if(currNode->left)   
                    q.push(currNode->left);
                if(currNode->right)
                    q.push(currNode->right);
            }
            cout<<"]\n";
        }
    }
}; 

// #1 Solution class:
class Solution_V1 {
    // Stores the diameter value (length of the longest path between any two nodes in a tree)
    int diameter = 0;
    
    // Method to find the maximum depth of the given node - O(N) & O(H)
    int getMaxDepth(TreeNode* rootNode) {
        if(!rootNode)
            return 0;
        
        return 1 + max(getMaxDepth(rootNode->left), getMaxDepth(rootNode->right));
    }

public:
    // Method to find the length of the diameter of the tree - O(N*N) & O(H)
    int diameterOfBinaryTree(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return 0;

        // Update the diameter value by the maximum value only
        diameter = max(diameter, getMaxDepth(rootNode->left) + getMaxDepth(rootNode->right));

        diameterOfBinaryTree(rootNode->left); // Look for the diameter value from each node of the left subtree
        diameterOfBinaryTree(rootNode->right);// Look for the diameter value from each node of the right subtree 

        // Return the diameter value
        return diameter;
    }
};

// #2 Solution class:
class Solution_V2 {
    // Stores the diameter value (length of the longest path between any two nodes in a tree)
    int diameter = 0;

    // Method to find the maximum depth of each node and to update the diameter each time - O(N) & O(H)
    int getMaxDepth(TreeNode* rootNode) {
        // Edge case: When the tree is empty
        if(!rootNode)
            return 0;

        int maxDepthLeft  = getMaxDepth(rootNode->left);  // Stores the maximum depth from the left subtree of the current node
        int maxDepthRight = getMaxDepth(rootNode->right); // Stores the maximum depth from the right subtree of the current node

        // Update the diameter value by the maximum value only
        diameter = max(diameter, maxDepthLeft + maxDepthRight);

        // Return the maximum depth of the current node
        return 1 + max(maxDepthLeft, maxDepthRight);
    }

public:
    // Method to find the length of the diameter of the tree - O(N) & O(H)
    int diameterOfBinaryTree(TreeNode* rootNode) {
        getMaxDepth(rootNode);
        return diameter;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOp = true;

    while(userWantsOp) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the nodes
        int n;
        cout<<"Enter the number of nodes of the tree: ";
        cin>>n;

        // Check the given size is valid or not
        if(n <= 0 || n >= 10001) {
            cout<<"Enter a size which lies within the problem constraints, application expects a positive integer!";
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
        cout<<"\nLevel order traversal of the tree is:\n";
        rootNode->printTree(rootNode);

        // Call to get the length of the diameter of the tree
        Solution_V2 solution;
        int diameter = solution.diameterOfBinaryTree(rootNode);
        cout<<"\nThe diameter value (length of the longest path between any two nodes in a tree) is: "<<diameter;

        // Deletion call (delete the root node and recursively the entire tree)
        delete rootNode; rootNode = nullptr;

        // Input section to control the flow of iterations of the application
        char userChoice;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoice;
        userWantsOp = (userChoice == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Tree | Depth-First Search | Binary Tree
    Link: https://leetcode.com/problems/diameter-of-binary-tree/description/?envType=daily-question&envId=2024-02-27
*/
