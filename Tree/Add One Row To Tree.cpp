// Program to add a row of nodes with value (val) at the given depth in a binary tree ~ coded by Hiren
#include <iostream>
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
    Node* addOneRow(Node* rootNode, int val, int depth) {
        if(depth == 1) {
            Node* newRoot = new Node(val, rootNode, nullptr);
            return newRoot;
        }
        return dfs(rootNode, val, depth, 1);
    }

private:
    // Method helper
    Node* dfs(Node* currNode, int val, int depth, int currentDepth) {
        if(!currNode) {
            return nullptr;
        }

        if(currentDepth == depth-1) {
            Node* newLeft  = new Node(val, currNode->left, nullptr);
            Node* newRight = new Node(val, nullptr, currNode->right);
            currNode->left = newLeft, currNode->right = newRight;
        }
        else {
            currNode->left  = dfs(currNode->left, val, depth, currentDepth+1);
            currNode->right = dfs(currNode->right, val, depth, currentDepth+1);
        }

        return currNode;
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to add a row of nodes with value (val) at the given depth, using bfs only - O(N) & O(N) : Where N is the total number of nodes of the tree
    Node* addOneRow(Node* rootNode, int val, int depth) {
        if(depth == 1) {
            Node* newRoot = new Node(val, rootNode, nullptr);
            return newRoot;
        }

        std::queue<Node*> q;
        q.push(rootNode);
        bool isRowAdded = false; int currDepth = 1; 

        while(!q.empty()) {
            int qSize = q.size();
            while(qSize--) {
                Node* currNode = q.front(); q.pop();
                if(currDepth == depth-1) {
                    Node* newLeft  = new Node(val, currNode->left, nullptr);
                    Node* newRight = new Node(val, nullptr, currNode->right);
                    currNode->left = newLeft, currNode->right = newRight;
                    isRowAdded = true;
                }
                if(currNode->left) {
                    q.push(currNode->left);
                }
                if(currNode->right) {
                    q.push(currNode->right);
                }
            }
            if(isRowAdded) {
                return rootNode;
            }
            currDepth++;
        }

        return rootNode;
    }
};

// Driver code
int main() {
    bool userWantsOperation = true;

    while(userWantsOperation) {
        system("cls || clear");
        int N;
        std::cout<<"Enter the number of nodes for the tree: ";
        std::cin>>N;

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
        std::cout<<"\nEnter the depth value: "; 
        std::cin>>depth;
        std::cout<<"Enter the value to be inserted at the depth: "; 
        std::cin>>val;

        // Print call
        std::cout<<"\nLevel order traversal of the tree before adding the row:\n";
        rootNode->printTree(rootNode);
        
        // Call to add the row
        Solution_V2 solution;
        rootNode = solution.addOneRow(rootNode, val, depth);

        // Print call
        std::cout<<"\nLevel order traversal of the tree after adding the row:\n";
        rootNode->printTree(rootNode);

        // Delete the root node (and recursively the entire tree)
        delete rootNode; rootNode = nullptr;

        // Input section to handle the flow of iterations
        char userChoise;
        std::cout<<"\nDo you want to perform the same operation on an another tree? (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
// Link: https://leetcode.com/problems/add-one-row-to-tree/description/
