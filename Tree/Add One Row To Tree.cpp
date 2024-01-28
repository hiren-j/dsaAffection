// Program to add a row of nodes with value (val) at the given depth in a binary tree ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <queue>

// Tree template
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Init constructor
    Node(int data, Node* left, Node* right)
    :
    data(data), left(left), right(right) {}

    // Init destructor
    ~Node() {
        if(left) {
            delete left;
        }
        if(right) {
            delete right;
        }
    }

    // Method to insert a node in the tree, using constant auxiliary space - O(N) & O(1) : Where N is the total number of nodes of the tree
    Node* insertNodeInBT(Node* rootNode, int key) {
        if(!rootNode)
            return new Node(key, nullptr, nullptr); 

        Node* parentNode = nullptr;
        Node* currNode   = rootNode;

        while(currNode) {
            parentNode = currNode;
            currNode   = (currNode->data > key) ? currNode->left : currNode->right;
        }

        Node* newNode = new Node(key, nullptr, nullptr);

        (parentNode->data > key) ? parentNode->left = newNode : parentNode->right = newNode;

        return rootNode;
    }

    // Method to print the tree, using bfs - O(N) & O(N) : Where N is the total number of nodes and H is height of the tree
    void printTree(Node* rootNode) {
        if(!rootNode)
            return;

        std::queue<Node*> q;
        q.push(rootNode);

        while(!q.empty()) {
            int qSize = q.size();
            std::cout<<"[";
            while(qSize--) {
                Node* currNode = q.front(); q.pop();
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

// #1 Solution class:
class Solution_V1 {
public:
    // Method to add a row of nodes with value (val) at the given depth, using dfs only - O(N) & O(H) : Where N is the total number of nodes and H is height of the tree
    Node* addOneRow(Node* rootNode, int val, int givenDepth) {
        // If the given depth is 1 then add "a new row of single node" at the depth, then set the original root node to the left side of it and mark the new node as the root node of the tree
        if(givenDepth == 1) {
            Node* newRoot = new Node(val, rootNode, nullptr);
            return newRoot;
        }
        // Else then add the new "row of nodes" at the given depth and the return the root node of the tree
        return dfs(rootNode, val, givenDepth, 1);
    }

private:
    // Method helper
    Node* dfs(Node* currNode, int val, int givenDepth, int currentDepth) {
        // Edge case: If the tree is empty
        if(!currNode) {
            return nullptr;
        }

        // If the current depth is equal to the given depth, then add a new "row of nodes" just below the current row
        if(currentDepth == givenDepth-1) {
            Node* newLeft  = new Node(val, currNode->left, nullptr);
            Node* newRight = new Node(val, nullptr, currNode->right);
            currNode->left = newLeft, currNode->right = newRight;
        }
        // Else then recurse and find the "previous row" of the "row at the given depth"
        else {
            currNode->left  = dfs(currNode->left, val, givenDepth, currentDepth+1);
            currNode->right = dfs(currNode->right, val, givenDepth, currentDepth+1);
        }

        // Return the root node of the current subtree
        return currNode;
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to add a row of nodes with value (val) at the given depth, using bfs only - O(N) & O(N) : Where N is the total number of nodes of the tree
    Node* addOneRow(Node* rootNode, int val, int givenDepth) {
        // If the given depth is 1 then add "a new row of single node" at the depth, then set the original root node to the left side of it and mark the new node as the root node of the tree
        if(givenDepth == 1) {
            Node* newRoot = new Node(val, rootNode, nullptr);
            return newRoot;
        }

        // Requires to maintain the nodes in level wise order
        std::queue<Node*> q;
        q.push(rootNode);

        bool isRowAdded  = false; // Tracks for the "new row of nodes" is added or not 
        int currentDepth = 1;     // Tracks the depth which is currently being seen

        // Explore the nodes of the tree
        while(!q.empty()) {
            int qSize = q.size();
            // Explore the nodes of the current level
            while(qSize--) {
                // Extract the front node of the queue
                Node* currNode = q.front(); q.pop();
                // If the current depth is equal to the given depth, then add a new "row of nodes" just below the current row
                if(currentDepth == givenDepth-1) {
                    Node* newLeft  = new Node(val, currNode->left, nullptr);
                    Node* newRight = new Node(val, nullptr, currNode->right);
                    currNode->left = newLeft, currNode->right = newRight;
                    isRowAdded = true; 
                }
                // If the left side of the node exist, then push it to the queue
                if(currNode->left) {
                    q.push(currNode->left);
                }
                // If the right side of the node exist, then push it to the queue
                if(currNode->right) {
                    q.push(currNode->right);
                }
            }
            // If the new "row of nodes" is added then return the root node of the tree
            if(isRowAdded) {
                return rootNode;
            }
            // As we're moving to the upcoming level hence update the depth number
            currentDepth++;
        }

        // Return the root node of the tree
        return rootNode;
    }
};

// Driver code
int main() {
    // Tracks for the user wants to perform the operation or not
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
        Node* rootNode = nullptr;

        // Input the nodes value of the tree
        for(int node = 1; node <= N; ++node) {
            int key;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>key;
            rootNode = rootNode->insertNodeInBT(rootNode, key);
        }
        
        // Input section for the (key) and the (depth)
        int val, depth;
        std::cout<<"\nEnter the depth value (1-based): "; 
        std::cin>>depth;
        std::cout<<"Enter the value to be inserted at the depth: "; 
        std::cin>>val;

        // Print call
        std::cout<<"\nLevel order traversal of the tree before adding the row:\n";
        rootNode->printTree(rootNode);
        
        // Call to add the new "row of nodes"
        Solution_V2 solution;
        rootNode = solution.addOneRow(rootNode, val, depth);

        // Print call
        std::cout<<"\nLevel order traversal of the tree after adding the row:\n";
        rootNode->printTree(rootNode);

        // Delete the root node (and recursively the entire tree)
        delete rootNode; rootNode = nullptr;

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
    Link: https://leetcode.com/problems/add-one-row-to-tree/description/
*/
