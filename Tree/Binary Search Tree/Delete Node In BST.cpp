// Program to delete the node with the given key in the binary search tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

// Tree template
class Node {
public:
    int val;
    Node* left;
    Node* right;

    // Init constructor
    Node(int val, Node* left = nullptr, Node* right = nullptr)
    :
    val(val), left(left), right(right) {}

    // Method to insert a node in the tree, using constant auxiliary space - O(H) & O(1) : Where H let be the height of the tree
    Node* insertNode(Node* rootNode, int key) {
        if(!rootNode)
            return new Node(key);

        Node* parentNode = nullptr;
        Node* currNode   = rootNode;

        while(currNode) {
            if(currNode->val == key) {   
                return rootNode;
            }
            parentNode = currNode;
            currNode = (currNode->val < key) ? currNode->right : currNode->left;
        }

        Node* newNode = new Node(key);

        if(parentNode->val < key)
            parentNode->right = newNode;
        else
            parentNode->left = newNode;

        return rootNode;
    }

    // Method to delete the tree, using dfs - O(N) & O(H) : Where N let be the total number of nodes and H let be the height of the tree
    Node* deleteTree(Node* rootNode) {
        if(!rootNode)
            return nullptr;

        rootNode->left  = deleteTree(rootNode->left); 
        rootNode->right = deleteTree(rootNode->right);

        delete rootNode; rootNode = nullptr;

        return rootNode;
    }

    // Method to print the tree, using bfs - O(N) & O(N) : Where N let be the total number of nodes of the tree 
    void printTree(Node* rootNode) {
        if(!rootNode)
            return;

        std::queue<Node*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            std::cout<<"[";
            while(qSize--) {
                rootNode = q.front(); q.pop();
                if(rootNode->left)
                    q.push(rootNode->left);
                if(rootNode->right)
                    q.push(rootNode->right);
                (!qSize) ? std::cout<<rootNode->val : std::cout<<rootNode->val<<", ";
            }
            std::cout<<"]\n";
        }
    }
};

// #1 Solution class:
class Solution_A {
    // Tracks the root node of the newly constructed bst
    Node* newRoot = nullptr;

    // Method to traverse the tree and create the new tree from the nodes - O(N*N) & O(N) 
    void preOrder(Node* rootNode, int key) {
        if(rootNode) {
            // If the node's value is not equal to key, then create a new node of the value and set it into the new tree
            if(rootNode->val != key) {
                newRoot = newRoot->insertNode(newRoot, rootNode->val);
            }
            preOrder(rootNode->left, key);  // Recurse to the left subtree and do the same thing
            preOrder(rootNode->right, key); // Recurse to the right subtree and do the same thing
        }
    }

public:
    // Method to delete the node with value key in the tree, using dynamic node creation with dfs - O(N*N) & O(N) : Where N let be the total number of nodes of the tree
    Node* deleteNode(Node* rootNode, int key) {
        preOrder(rootNode, key);
        return newRoot;
    }
};
// Note: This solution can lead to the memory-leak issues as the new tree is created dynamically but never freed

// #2 Solution class:
class Solution_B {
public:
    // Method to delete the node with value key in the tree, using dfs and buffer - O(N) & O(N) : Where N let be the total number of nodes of the tree
    Node* deleteNode(Node* rootNode, int key) {
        std::vector<Node*> nodes;                         // Stores all the nodes of the tree
        inOrder(rootNode, key, nodes);                    // Traverse and store all the nodes to the buffer
        return constructBBST(nodes, 0, nodes.size() - 1); // Construct a balanced-binary-search-tree from the nodes and then return the root node of it 
    }

private:
    // Method to construct a height balanced binary search tree - O(N) & O(LogN)
    Node* constructBBST(std::vector<Node*>& nodes, int start, int end) {
        if(start > end)
            return nullptr;

        int mid = start + (end - start) / 2;

        Node* rootNode = nodes[mid];
        rootNode->left  = constructBBST(nodes, start, mid - 1);
        rootNode->right = constructBBST(nodes, mid + 1, end);

        return rootNode;
    }

    // Method to find and store all the nodes to the buffer, using dfs - O(N) & O(N)
    void inOrder(Node* rootNode, int key, std::vector<Node*>& nodes) {
        if(rootNode) {
            inOrder(rootNode->left, key, nodes);
            if(rootNode->val != key) nodes.push_back(rootNode);
            inOrder(rootNode->right, key, nodes);
        }
    }
};

// #3 Solution class:
class Solution_C {
public:
    // Method to delete the node with value key in the tree, using dfs - O(H) & O(H) : Where H let be the height of the tree
    Node* deleteNode(Node* rootNode, int key) {
        // Edge case: If the tree is empty, then the key does not exist in the tree
        if(!rootNode)
            return nullptr;

        // If the key is lesser than the root node's value, then search the key to the left side of the node
        if(key < rootNode->val) {       
            rootNode->left = deleteNode(rootNode->left, key);
        }
        // Else if the key is greater than the root node's value, then search the key to the right side of the node
        else if(key > rootNode->val) {
            rootNode->right = deleteNode(rootNode->right, key);
        }
        // Else when the node with value key is found, then perform the deletion strategy
        else {
            Node* initialRoot = rootNode;        // Tracks the initial root node
            Node* leftChild   = rootNode->left;  // Tracks the left child of the initial root node
            Node* rightChild  = rootNode->right; // Tracks the right child of the initial root node

            // Delete the initial root node
            delete initialRoot; initialRoot = nullptr;

            // If the right child does not exist, then mark the left child as the new root node
            if(!rightChild) {
                rootNode = leftChild;
            }
            // Else if the left child does not exist, then mark the right child as the new root node
            else if(!leftChild) {
                rootNode = rightChild;
            }
            // Else when both the child's exist, then find the right-most-node of the left child and then set the right child as the right node of the right-most-node and then mark the left child as the new root node
            else {
                Node* rightMostNode = getRightMostNode(leftChild);
                rightMostNode->right = rightChild;
                rootNode = leftChild;
            }
        }

        // Return the root node of the current subtree
        return rootNode;
    }

private:
    // Method to find the right-most-node of the given node - O(M) & O(1) : Where M let be the total number of nodes to the right side of the given node
    Node* getRightMostNode(Node* rootNode) {
        while(rootNode->right) {
            rootNode = rootNode->right;
        }
        return rootNode;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Controls console clearance for both "windows" and "linux" user
        system("cls || clear");

        std::cout<<"The application only accepts non-decimal numeric type value, unless specified!\n\n";

        // Input the size of the tree
        int n;
        std::cout<<"Enter the total number of nodes: ";
        std::cin>>n;

        // Input the key value
        int key;
        std::cout<<"Enter the value of key which will be deleted: ";
        std::cin>>key;

        // Check the given values are lying within the problem constraints or not
        if(n <= -1 || n >= 1e4 + 1) {
            std::cout<<"You must enter a size which lies between 0 and 10^4!\n";
        }
        else if(key <= -1e5 - 1 || key >= 1e5 + 1) {
            std::cout<<"You must enter a key which lies between -10^5 and 10^5!\n";
        }
        else {
            // Tracks the root node of the tree
            Node* rootNode = nullptr;

            // Input the value of the nodes
            for(int node = 1; node <= n;) {
                int value;
                std::cout<<"Enter the value of the "<<node<<"th node: ";
                std::cin>>value;
                if(value <= -1e5 - 1 || value >= 1e5 + 1) {
                    std::cout<<"You must enter a value which lies between -10^5 and 10^5!\n";
                }
                else {
                    rootNode = rootNode->insertNode(rootNode, value);
                    node++;
                }
            }

            // Print call (print each level of the tree)
            std::cout<<"\nTree before key deletion:\n";
            rootNode->printTree(rootNode);

            // Call to delete the node with value equal to key
            Solution_C solution;
            rootNode = solution.deleteNode(rootNode, key);

            // Print call (print each level of the tree)
            std::cout<<"\nTree after key deletion:\n";
            rootNode->printTree(rootNode);

            // Deletion call (delete each node of the tree)
            rootNode = rootNode->deleteTree(rootNode);
        }

        // Input section to control the flow of iterations of the application
        char userChoice;
        std::cout<<"\nPress \'R\' to restart the application, else it will exit: ";
        std::cin>>userChoice;
        userWantsOperation = (userChoice == 'R');
    }
    
    return 0;
}
/*
    Topics: Tree | Binary Search Tree | Binary Tree | Depth-first-search
    Link: https://leetcode.com/problems/delete-node-in-a-bst/description/
*/
