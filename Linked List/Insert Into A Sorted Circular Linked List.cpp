// Program to insert a node into a sorted circular linked list ~ coded by Hiren
#include <iostream>
#include <vector>
#include <algorithm>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next)
    :
    val(val), next(next) {}

    // Init destructor
    ~ListNode() {
        if(next) {
            delete next;
        }
    }
};

// #1 Solution class:
class Solution_V1 {
    // Method helper
    static bool comparator(ListNode* node1, ListNode* node2) {
        return node1->val < node2->val;
    }

public:
    // Method to insert the node into the list, using sorting with buffer - O(NLogN) & O(N) : Where N is the size of the list.
    ListNode* sortedInsertToList(ListNode* headNode, int key) {
        // Edge case: When the list is empty.
        if(!headNode) {
            ListNode* newHead = new ListNode(key, nullptr);
            newHead->next = newHead;
            return newHead;
        }

        // Stores the nodes of the list.
        std::vector<ListNode*> nodes;
        nodes.push_back(new ListNode(key, nullptr));

        // Tracks the nodes of the list.
        ListNode* currNode = headNode;

        // Iterate and store all the nodes to the buffer.
        while(currNode->next != headNode) {
            nodes.push_back(currNode);
            currNode = currNode->next;
        }
        // Store the last node of the list to the buffer.
        nodes.push_back(currNode);

        // Sort all the nodes based on their values.
        std::sort(begin(nodes), end(nodes), comparator);

        // Iterate and link all the nodes.
        for(int i=1; i<nodes.size(); i++) {
            nodes[i-1]->next = nodes[i];
        }
        // Lastly, set the circular point of the list.
        nodes[nodes.size()-1]->next = nodes[0];

        // Return the head node of the list.
        return nodes[0];
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to insert the node into the list, using buffer only - O(N) & O(N) : Where N is the size of the list.
    ListNode* sortedInsertToList(ListNode* headNode, int key) {
        // Edge case: When the list is empty.
        if(!headNode) {
            ListNode* newHead = new ListNode(key, nullptr);
            newHead->next = newHead;
            return newHead;
        }

        std::vector<ListNode*> nodes;  // Stores the nodes of the list in sorted order.
        ListNode* currNode = headNode; // Tracks the nodes of the list.
        bool keyIsInserted = false;    // Tracks the node with value "key" is inserted or not.

        while(currNode->next != headNode) {
            // If the node with value "key" is not inserted yet and has to be inserted before the current node.
            if(key <= currNode->val && !keyIsInserted) {  
                // Create it and store it to the buffer.
                nodes.push_back(new ListNode(key, nullptr));
                // Mark it inserted for the next time to avoid the duplicate creations.
                keyIsInserted = true; 
            }
            nodes.push_back(currNode); // Store the current node of the list to the buffer.
            currNode = currNode->next; // Move to the next node in the list.
        }

        // If the node with value "key" is not inserted yet and has to be inserted before the last node.
        if(key <= currNode->val && !keyIsInserted) {
            // Create it and store it to the buffer.
            nodes.push_back(new ListNode(key, nullptr));
            // Now, store the last node of the list to ensure the sorted order.
            nodes.push_back(currNode);
            // Mark the new node with value key as inserted for the next time to avoid the duplicate creations.
            keyIsInserted = true;
        }
        // If the node with value "key" is not inserted yet and has to be inserted after the last node.
        if(key >= currNode->val && !keyIsInserted) {
            // Create it and store it to the buffer.
            nodes.push_back(currNode);
            // Now, store the last node of the list to ensure the sorted order.
            nodes.push_back(new ListNode(key, nullptr));
            // Mark the new node with value key as inserted for the next time to avoid the duplicate creations.
            keyIsInserted = true;
        }
        // If the node with value "key" is inserted ever-before, then just store the last node to the buffer.
        if(keyIsInserted) {
            nodes.push_back(currNode);
        }

        // Iterate and link all the nodes.
        for(int i=1; i<nodes.size(); i++) {
            nodes[i-1]->next = nodes[i];
        }
        // Lastly, set the circular point of the list.
        nodes[nodes.size()-1]->next = nodes[0];

        // Return the head node of the list.
        return nodes[0];
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to insert the node into the list, using constant auxiliary space - O(N) & O(1) : Where N is the size of the list.
    ListNode* sortedInsertToList(ListNode* headNode, int key) {
        // Edge case: When the list is empty.
        if(!headNode) {
            ListNode* newHead = new ListNode(key, nullptr);
            newHead->next = newHead;
            return newHead;
        }
        
        // Tracks the nodes of the list.
        ListNode* currNode = headNode;

        // Edge case: When the node with value "key" has to be inserted before the head node.
        if(key < headNode->val) {
            while(currNode->next != headNode) currNode = currNode->next;
            ListNode* tmp = headNode;
            headNode = new ListNode(key, tmp);
            currNode->next = headNode;
            return headNode;
        }
        
        // Tracks the previous node of any node in the list.
        ListNode* prevNode = nullptr; currNode = headNode;
        
        // Iterate and find the node with its previous node, in which the node with value "key" has to be inserted.
        while(currNode->next != headNode && key > currNode->val) {
            prevNode = currNode;
            currNode = currNode->next;
        }
        
        // If the current node is not the last node of the list, then insert the new node with value "key" before the current node.
        if(currNode->next != headNode) {
            prevNode->next = new ListNode(key, currNode);
        }
        // Else when the current node is the last node of the list, then insert the new node with value "key" after the current node.
        else {
            ListNode* tmp = currNode->next;
            currNode->next = new ListNode(key, tmp);
        }

        // Return the head node of the updated list.  
        return headNode;
    }
};

// Method to print the list - O(N) & O(1) : Where N is the size of the list.
void printList(ListNode* headNode) {
    if(headNode) {
        ListNode* currNode = headNode;
        while(currNode->next != headNode) {
            std::cout<<currNode->val<<' ';
            currNode = currNode->next;
        }
        std::cout<<currNode->val;
    }
    std::cout<<'\n';
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data.
    ListNode* headNode = new ListNode(10, new ListNode(20, new ListNode(40, new ListNode(50, nullptr))));

    // Setting the circular point.
    headNode->next->next->next->next = headNode;

    // Print call
    printList(headNode);

    // Insertion call
    Solution_V3 obj;
    headNode = obj.sortedInsertToList(headNode, 30);

    // Print call
    printList(headNode);

    // Removing the circular point.
    headNode->next->next->next->next = nullptr;

    // Delete the head node and recursively the entire list.
    delete headNode;

    return 0;
}
/*
Links:
      https://leetcode.com/discuss/interview-question/435345/Google-or-Phone-or-Insert-into-a-Sorted-Circular-Linked-List
      https://leetcode.com/discuss/interview-question/429160/Facebook-or-Phone-Screen-or-Insert-into-a-Sorted-Circular-Linked-list
      https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/description/
*/
