// Program to return a list of sorted integers that contains the node values that are common in both the BST's ~ coded by Hiren
#include <iostream>
#include <vector>
#include <unordered_set>
#include <stack>
using namespace std;

// Tree template
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Init constructor
    Node(int data, Node* left = nullptr, Node* right = nullptr)
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
};

// #1 Solution class:
class Solution_V1 {
    // Stores the value of the intersection nodes
    vector<int> buffer;

    // Method helper 
    bool presentInTree2(Node* rootNode2, int target) {
        // Edge case: When the tree is empty, then no intersection node exist
        if(!rootNode2)
            return false;
        
        // If the node value is equal to the "target" value, then the intersection node exist
        if(rootNode2->data == target) {
            return true;
        }
        // Else when the node value is greater than the "target" value, then check for the presence at the left subtree of the node
        else if(rootNode2->data > target) {
            return presentInTree2(rootNode2->left, target);
        // Else when the node value is lesser than the "target" value, then check for the presence at the right subtree of the node
        }
        else {
            return presentInTree2(rootNode2->right, target);
        }
    }
    
public:
    // Method to find the intersection elements - O(N1*N2) & O(H1*H2)
    vector<int> findCommon(Node* rootNode1, Node* rootNode2) {
        if(rootNode1 && rootNode2) {
            findCommon(rootNode1->left, rootNode2);
            // If the intersection node is present, then store the node value to the buffer
            if(presentInTree2(rootNode2, rootNode1->data)) {
                buffer.push_back(rootNode1->data);
            }
            findCommon(rootNode1->right, rootNode2);
        }
        return buffer;
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to find the intersection elements - O(N1+N2) & O(N1+N2)
    vector<int> findCommon(Node* rootNode1, Node* rootNode2) {
        // Edge case: When either of them is empty, then no intersection node exist
        if(!rootNode1 || !rootNode2)
            return {};

        unordered_set<int> nodesTree1;                    // Stores the nodes of tree1
        vector<int> buffer;                               // Stores the value of the intersection nodes
        storeTree1Nodes(rootNode1, nodesTree1);           // Traverse and store all the nodes of tree1 to the set
        getAllCommonNodes(rootNode2, nodesTree1, buffer); // Traverse the tree2 and find all the intersection nodes

        return buffer;                                
    }
    
private:
    // Method helper
    void storeTree1Nodes(Node* rootNode1, auto& nodesTree1) {
        if(rootNode1) {
            nodesTree1.insert(rootNode1->data);
            storeTree1Nodes(rootNode1->left, nodesTree1);
            storeTree1Nodes(rootNode1->right, nodesTree1);
        }
    }
    
    // Method helper
    void getAllCommonNodes(Node* rootNode2, auto& nodesTree1, auto& buffer) {
        if(rootNode2) {
            getAllCommonNodes(rootNode2->left, nodesTree1, buffer);
            // If the intersection node is present, then store the node value to the buffer
            if(nodesTree1.count(rootNode2->data)) {
                buffer.push_back(rootNode2->data);
            }
            getAllCommonNodes(rootNode2->right, nodesTree1, buffer);
        }
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to find the intersection elements - O(N1+N2) & O(H1+H2)
    vector<int> findCommon(Node* rootNode1, Node* rootNode2) {
        // Edge case: When either of them is empty, then no intersection node exist
        if(!rootNode1 || !rootNode2)
            return {};
            
        // Require to maintain the recursive behaviour of visiting nodes
        stack<Node*> s1; // Stores the nodes of tree1
        stack<Node*> s2; // Stores the nodes of tree2

        // Stores the value of the intersection nodes
        vector<int> buffer;
        
        while(rootNode1 || rootNode2 || !s1.empty() || !s2.empty()) {
            // Store all the left nodes of tree1 to its corresponding stack
            while(rootNode1) {
                s1.push(rootNode1);
                rootNode1 = rootNode1->left;
            }
            // Store all the left nodes of tree2 to its corresponding stack
            while(rootNode2) {
                s2.push(rootNode2);
                rootNode2 = rootNode2->left;
            }
            
            Node* currNode1 = nullptr; // Stores the topmost node of the stack of tree1
            Node* currNode2 = nullptr; // Stores the topmost node of the stack of tree2
            
            // If exists then store the topmost node of the stacks
            if(!s1.empty()) currNode1 = s1.top(), s1.pop();
            if(!s2.empty()) currNode2 = s2.top(), s2.pop();

            // When both nodes exist, then check for the intersection node
            if(currNode1 && currNode2) {
                // If the intersection node is present, then store the node value to the buffer
                if(currNode1->data == currNode2->data) {
                    buffer.push_back(currNode1->data);
                    rootNode1 = currNode1->right; // Move to the right side of the node in tree1, as its possible to have nodes on that side
                    rootNode2 = currNode2->right; // Move to the right side of the node in tree2, as its possible to have nodes on that side
                }
                // If the node value of tree1 is lesser, then find the node with greater value from tree1
                else if(currNode1->data < currNode2->data) {
                    rootNode1 = currNode1->right; // Move to the right side of the node in tree1, as its possible to have nodes on that side.
                    s2.push(currNode2);
                }
                else {
                    rootNode2 = currNode2->right; // Move to the right side of the node in tree2, as its possible to have nodes on that side
                    s1.push(currNode1);
                }
            }
        }

        // Return the list of sorted integers containing the values of the intersection nodes   
        return buffer;
    }
};

// Method to print the tree using inOrder traversal - O(N) & O(H)
void printTree(Node* rootNode) {
    if(rootNode) {
        printTree(rootNode->left);
        cout<<rootNode->data<<' ';
        printTree(rootNode->right);
    }
}

// Driver code
int main() {
    // Creating tree1, connecting nodes and initializing their data
    Node* c3 = new Node(8);
    Node* c2 = new Node(4);
    Node* c1 = new Node(3, nullptr, c2);
    Node* rootNode1 = new Node(5, c1, c3);

    // Creating tree2, connecting nodes and initializing their data
    Node* c4_ = new Node(8);
    Node* c3_ = new Node(9, c4_);
    Node* c2_ = new Node(2);
    Node* c1_ = new Node(4, c2_);
    Node* rootNode2 = new Node(5, c1_, c3_);

    // Print call
    printTree(rootNode1);
                         cout<<'\n';
    printTree(rootNode2);

    // Call to find the intersection nodes
    Solution_V3 obj;
    vector<int> buffer = obj.findCommon(rootNode1, rootNode2); 

    cout<<'\n';

    // Print values
    for(int nodeValue : buffer)
        cout<<nodeValue<<' ';

    // Deletion call
    delete rootNode1; delete rootNode2;

    return 0;
}
/*
    Links: 
          https://practice.geeksforgeeks.org/problems/print-common-nodes-in-bst/1
          https://leetcode.com/discuss/interview-question/399396/Google-or-Phone-screen-or-Common-Elements-of-Two-Separate-BSTs  
*/
