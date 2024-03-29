// Program to rotate the linked list to the right by k places ~ coded by Hiren
#include <iostream>
#include <vector>

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

// Solution class:
class Solution {
public:
    // #1 Method to rotate the list to the right by k places, using buffer - O(N) & O(N)
    ListNode* rotateRight_V1(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded or k is zero, negative
        if(!headNode || !headNode->next || k <= 0)
            return headNode;

        // Stores all the nodes of the list
        std::vector<ListNode*> nodes;

        // Iterate and store the nodes to the buffer
        while(headNode) nodes.push_back(headNode), headNode = headNode->next;

        int listLength = nodes.size();

        // Calculate and store the number of nodes for rotation
        k = k % listLength; 

        // If k is zero then return the head node node of the list
        if(k == 0) return nodes[0];

        // Set the final links for the rotation
        nodes[listLength-k-1]->next = nullptr;
        nodes[listLength-1]->next = nodes[0];

        // Return the head node node of the list after rotation
        return nodes[listLength-k];
    }

    // #2 Method to rotate the list to the right by k places, using constant auxiliary space - O(N) & O(1)
    ListNode* rotateRight_V2(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* nodeLast = headNode; // Require to track the last node of the list
        int listLength = 1;

        // Iterate and find the last node
        while(nodeLast && nodeLast->next) {
            nodeLast = nodeLast->next, listLength++;
        } 

        // Calculate and store the number of nodes for rotation
        k = k % listLength;

        // If k is zero then return the head node node of the list
        if(k == 0) return headNode;

        ListNode* prevNode = nullptr;     // Require to track the previous node of the kTh node (if seen from the end-side)
        ListNode* currNode = headNode;    // Require to track the kTh node (if seen from the end-side)
        int nodesToSkip = listLength - k; // Calculate and store the number of nodes to skip from the front-side

        // Iterate and find the previous node of the kTh node and itself
        while(currNode && nodesToSkip--) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        // Set the final links for the rotation
        prevNode->next = nullptr;
        nodeLast->next = headNode;
        headNode = currNode;

        // Return the head node node of the list after rotation
        return headNode; 
    }
};

// Method to print the list - O(N) & O(1)
void printList(ListNode* headNode) {
    if(headNode) {
        std::cout<<headNode->val<<' ';
        printList(headNode->next);
    }
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data
    ListNode* headNode = new ListNode(0, new ListNode(1, new ListNode(2, nullptr)));

    // Print call
    printList(headNode);
    std::cout<<'\n';

    // Rotation call
    Solution solution;
    headNode = solution.rotateRight_V2(headNode, 8);

    // Print call
    printList(headNode);

    // Deletion call (delete the head node and recursively the entire list)
    delete headNode; headNode = nullptr;

    return 0;
}
/*
    Topics: Linked List | Two Pointers | Maths
    Link: https://leetcode.com/problems/rotate-list/description/
*/
