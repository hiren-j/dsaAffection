// Program to return a list of sorted integers that contains the node values that are common in both the BST's ~ coded by Hiren
#include <unordered_set>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
using namespace std;

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
    TreeNode* insertInBST(TreeNode* rootNode, int key) {
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

    // Method to input the nodes of the tree - O(N*N) & O(N) : Where N is the total number of nodes of the tree
    TreeNode* getTree(int number) {
        int N;
        cout<<"Enter the number of nodes for the tree"<<number<<": ";
        cin>>N;

        if(N <= 0) {
            cout<<"Enter a valid value, application expects a positive integer!\n";
            return nullptr;
        }

        TreeNode* rootNode = nullptr;

        for(int node=1; node<=N; ++node) {
            int key;
            cout<<"Enter the value of the "<<node<<"th node: ";
            cin>>key;
            rootNode = rootNode->insertInBST(rootNode, key);
        }
        
        return rootNode;
    }

    // Method to print the tree, using preOrder traversal - O(N) & O(H) : Where N is total number of nodes and H is height of the tree
    void printTree(TreeNode* rootNode) {
        if(rootNode) {
            cout<<rootNode->data<<' ';
            printTree(rootNode->left);
            printTree(rootNode->right);
        }
    }
};

// #1 Solution class:
class Solution_V1 {
    // Stores the value of the intersection nodes
    vector<int> buffer;

    // Method helper 
    bool checkInTreeB(TreeNode* rootNodeB, int target) {
        // Edge case: When the tree is empty, then no intersection node exist
        if(!rootNodeB)
            return false;
        
        // If the node value is equal to the "target" value, then the intersection node exist
        if(rootNodeB->data == target)
            return true;

        // Else when the node value is greater than the "target" value, then check for the presence at the left subtree of the node
        else if(rootNodeB->data > target)
            return checkInTreeB(rootNodeB->left, target);

        // Else when the node value is lesser than the "target" value, then check for the presence at the right subtree of the node
        else 
            return checkInTreeB(rootNodeB->right, target);
    }
    
public:
    // Method to find the intersection elements - O(N1*N2) & O(H1*H2)
    vector<int> getIntersection(TreeNode* rootNodeA, TreeNode* rootNodeB) {
        if(rootNodeA && rootNodeB) {
            getIntersection(rootNodeA->left, rootNodeB);
            // If the intersection node is present, then store the node value to the "buffer"
            if(checkInTreeB(rootNodeB, rootNodeA->data)) {
                buffer.push_back(rootNodeA->data);
            }
            getIntersection(rootNodeA->right, rootNodeB);
        }
        // Return the list of sorted integers containing the values of the intersection nodes   
        return buffer;
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to find the intersection elements - O(N1+N2) & O(N1+N2)
    vector<int> getIntersection(TreeNode* rootNodeA, TreeNode* rootNodeB) {
        // Edge case: When either of them is empty, then no intersection node exist
        if(!rootNodeA || !rootNodeB)
            return {};

        unordered_set<int> nodesTreeA;                    // Stores the nodes of tree1
        vector<int> buffer;                               // Stores the value of the intersection nodes
        storeTreeA(rootNodeA, nodesTreeA);                // Traverse and store all the nodes of tree1 to the set
        getAllCommonNodes(rootNodeB, nodesTreeA, buffer); // Traverse the tree2 and find all the intersection nodes

        // Return the list of sorted integers containing the values of the intersection nodes   
        return buffer;                                
    }
    
private:
    // Method helper
    void storeTreeA(TreeNode* rootNodeA, auto& nodesTreeA) {
        if(rootNodeA) {
            nodesTreeA.insert(rootNodeA->data);
            storeTreeA(rootNodeA->left, nodesTreeA);
            storeTreeA(rootNodeA->right, nodesTreeA);
        }
    }
    
    // Method helper
    void getAllCommonNodes(TreeNode* rootNodeB, auto& nodesTreeA, auto& buffer) {
        if(rootNodeB) {
            getAllCommonNodes(rootNodeB->left, nodesTreeA, buffer);
            // If the intersection node is present, then store the node value to the buffer
            if(nodesTreeA.count(rootNodeB->data)) {
                buffer.push_back(rootNodeB->data);
            }
            getAllCommonNodes(rootNodeB->right, nodesTreeA, buffer);
        }
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to find the intersection elements - O(N1+N2) & O(H1+H2)
    vector<int> getIntersection(TreeNode* rootNodeA, TreeNode* rootNodeB) {
        // Edge case: When either of them is empty, then no intersection node exist
        if(!rootNodeA || !rootNodeB)
            return {};
            
        // Require to maintain the recursive behaviour of visiting nodes
        stack<TreeNode*> s1; // Stores the nodes of tree1
        stack<TreeNode*> s2; // Stores the nodes of tree2

        // Stores the value of the intersection nodes
        vector<int> buffer;
        
        while(rootNodeA || rootNodeB || !s1.empty() || !s2.empty()) {
            // Store all the left nodes of tree1 to its corresponding stack
            while(rootNodeA) {
                s1.push(rootNodeA);
                rootNodeA = rootNodeA->left;
            }
            // Store all the left nodes of tree2 to its corresponding stack
            while(rootNodeB) {
                s2.push(rootNodeB);
                rootNodeB = rootNodeB->left;
            }
            
            TreeNode* currNode1 = nullptr; // Stores the topmost node of the stack of tree1
            TreeNode* currNode2 = nullptr; // Stores the topmost node of the stack of tree2
            
            // If exists then store the topmost node of the stacks
            if(!s1.empty()) currNode1 = s1.top(), s1.pop();
            if(!s2.empty()) currNode2 = s2.top(), s2.pop();

            // When both nodes exist, then check for the intersection node
            if(currNode1 && currNode2) {
                // If the intersection node is present, then store the node value to the buffer
                if(currNode1->data == currNode2->data) {
                    buffer.push_back(currNode1->data);
                    rootNodeA = currNode1->right; // Move to the right side of the node in tree1, as its possible to have nodes on that side
                    rootNodeB = currNode2->right; // Move to the right side of the node in tree2, as its possible to have nodes on that side
                }
                // If the node value of tree1 is lesser, then find the node with greater value from tree1
                else if(currNode1->data < currNode2->data) {
                    rootNodeA = currNode1->right; // Move to the right side of the node in tree1, as its possible to have nodes on that side.
                    s2.push(currNode2);
                }
                else {
                    rootNodeB = currNode2->right; // Move to the right side of the node in tree2, as its possible to have nodes on that side
                    s1.push(currNode1);
                }
            }
        }

        // Return the list of sorted integers containing the values of the intersection nodes   
        return buffer;
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles the console clearance for both "windows" and "linux" user
        system("cls || clear");
        
        // Input the trees and store the root node of them
        TreeNode* rootNodeA = rootNodeA->getTree(1); cout<<'\n';
        TreeNode* rootNodeB = rootNodeB->getTree(2);

        // Print call
        if(rootNodeA) {
            cout<<"\nThe preOrder traversal of the tree1 is: ";
            rootNodeA->printTree(rootNodeA);
        }

        // Print call
        if(rootNodeB) {
            cout<<"\nThe preOrder traversal of the tree2 is: ";
            rootNodeB->printTree(rootNodeB);
        }

        // Call to find the intersection elements
        Solution_V3 solution;
        vector<int> buffer = solution.getIntersection(rootNodeA, rootNodeB); 
        
        // Print values
        cout<<"\nThe value of the intersection nodes are: ";
        for(int num : buffer) 
            cout<<num<<' ';

        // Deletion call (delete the root node and recursively the entire tree)
        delete rootNodeA; rootNodeA = nullptr; 
        delete rootNodeB; rootNodeB = nullptr;

        // Input section to handle the flow of iterations
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else application exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false;
    }

    return 0;
}
/*
    Topics: Binary Search Tree | Stack | Hash Table | Depth-First-Search
    Links: https://leetcode.com/discuss/interview-question/399396/Google-or-Phone-screen-or-Common-Elements-of-Two-Separate-BSTs  
           https://practice.geeksforgeeks.org/problems/print-common-nodes-in-bst/1
*/
