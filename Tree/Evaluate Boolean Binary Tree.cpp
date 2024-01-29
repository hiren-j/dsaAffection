// Program to find the boolean result of evaluating the root node of the binary tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>

// Tree template
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Initialize constructor
    Node(int data, Node* left, Node* right)
    :
    data(data), left(left), right(right) {}

    // Initialize destructor
    Node() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
    }

    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1)
    Node* insertNodeInTree(Node* rootNode, int key) {
        if(!rootNode) 
            return new Node(key, nullptr, nullptr);

        Node* parentNode = nullptr;
        Node* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode   = (parentNode->data < key) ? parentNode->right : parentNode->left;
        }

        Node* newNode = new Node(key, nullptr, nullptr);

        (parentNode->data < key) ? parentNode->right = newNode : parentNode->left = newNode;

        return rootNode;
    }

    // Method to print the tree, using preOrder traversal - O(N) & O(H)
    void printTree(Node* rootNode) {
        if(rootNode) {
            std::cout<<rootNode->data<<' ';
            printTree(rootNode->left);
            printTree(rootNode->right);
        }
    }
};

// Solution class:
class Solution {
public:
    // Method to evaluate the root node of the binary tree, using dfs only - O(N) & O(H)
    bool evaluateTree(Node* rootNode) {
        // Edge case: Return true, if the tree is empty
        if(!rootNode)
            return true;

        // Edge case: If it's a leaf node, then return the node's value
        if(!rootNode->left && !rootNode->right)
            return rootNode->data;

        // Recursively evaluate the left and right subtrees
        bool sideLeft  = evaluateTree(rootNode->left);
        bool sideRight = evaluateTree(rootNode->right);

        // If the node's value is 2, then evaluate the OR operation
        if(rootNode->data == 2 && (sideLeft || sideRight))
            return true;

        // If the node's value is 3, then evaluate the AND operation
        if(rootNode->data == 3 && sideLeft && sideRight)
            return true;

        // Return false, if no conditions mets
        return false;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the number of nodes for the tree
        int N;
        std::cout<<"Enter the number of nodes for the tree: ";
        std::cin>>N;

        // Check the given value is valid or not
        if(N <= 0) {
            std::cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }

        // Tracks the root node of the tree
        Node* rootNode = nullptr;

        // Input the nodes value of the tree
        for(int node=1; node<=N; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            rootNode = rootNode->insertNodeInTree(rootNode, key);
        }

        // Print call
        std::cout<<"\nThe preOrder traversal of the tree is: ";
        rootNode->printTree(rootNode);

        // Evaluation call
        Solution solution;
        (solution.evaluateTree(rootNode)) ? std::cout<<"\nEvaluation result is \"True\"!" : std::cout<<"\nEvaluation result is \"False\"!";

        // Deletion call (delete the root node and recursively the entire tree)
        delete rootNode;
        rootNode = nullptr;

        // Input section to handle the flow of iterations
        char userChoise;
        std::cout<<"\n\nPress \'Y\' to perform the same operation on an another tree: ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
/*
    Topics: Tree | Depth-First-Search | Binary Tree
    Link: https://leetcode.com/problems/evaluate-boolean-binary-tree/description/
*/
