// Program to left-shift the linked list by k nodes ~ coded by Hiren 
#include <iostream>
#include <vector>

// List template
struct ListNode {
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

// Solutions
struct Solution {
    // #1 Method to left-shift the list by k nodes, using buffer - O(N) & O(N)
    ListNode* rotateList_V1(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        std::vector<ListNode*> nodes;  // Require to store the k nodes
        ListNode* currNode = headNode; // Require to track the nodes 

        // Iterate and store k nodes to the vector
        while(currNode && k--) {
            nodes.push_back(currNode);
            currNode = currNode->next;
        }

        // If the value of k exceeds or equal to the length of the list
        if(!currNode) 
            return headNode;

        headNode = currNode;

        // Iterate and find the last node
        while(currNode && currNode->next) {
            currNode = currNode->next;
        }

        // Update and set the remaining links
        currNode->next = nodes[0];
        nodes[nodes.size()-1]->next = nullptr;

        // Return the headNode node of the list 
        return headNode;
    }

    // #2 Method to left-shift the list by k nodes, using constant auxiliary space - O(N) & O(1)
    ListNode* rotateList_V2(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* dummyNode1 = new ListNode(0, nullptr); // Require to track the sublist of k nodes
        ListNode* dummyNode2 = new ListNode(0, nullptr); // Require to track the sublist of remaining nodes
        ListNode* currNode1  = dummyNode1;
        ListNode* currNode2  = dummyNode2;

        // Iterate and seperate the sublist of k nodes
        while(headNode && k--) {
            currNode1->next = headNode;
            currNode1 = currNode1->next;
            headNode = headNode->next;
        }
        currNode1->next = nullptr;

        // If the value of k exceeds or equal to the length of the list
        if(!currNode1) {
            headNode = dummyNode1->next;
            dummyNode1->next = nullptr; dummyNode2->next = nullptr;
            delete dummyNode1; delete dummyNode2;
            return headNode;
        }

        // Iterate and seperate the sublist of remaining nodes
        while(headNode) {
            currNode2->next = headNode;
            currNode2 = currNode2->next;
            headNode = headNode->next;
        }
        currNode2->next = dummyNode1->next;

        // Update the headNode node of the list
        headNode = dummyNode2->next;

        // Delete to avoid the memory leaks
        dummyNode1->next = nullptr; dummyNode2->next = nullptr;
        delete dummyNode1; delete dummyNode2;

        // Return the headNode node of the list 
        return headNode;
    }

    // #3 Method to left-shift the list by k nodes, using constant auxiliary space - O(N) & O(1)
    ListNode* rotateList_V3(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* prevNode = nullptr;
        ListNode* currNode = headNode;  
        ListNode* tmpNode  = headNode;   

        // Iterate and find the previous node of the kTh node and itself
        while(currNode && k--) {
            prevNode = currNode;
            currNode = currNode->next;
        }

        // If the value of k exceeds or equal to the length of the list
        if(!currNode) 
            return headNode;

        // Iterate and find the last node
        while(currNode && currNode->next) {
            currNode = currNode->next;
        }

        // Update the links of the headNode, previous and current node 
        headNode = prevNode->next;
        prevNode->next = nullptr;
        currNode->next = tmpNode;

        // Return the headNode node of the list
        return headNode;
    }
};

// Method to print the list - O(N) & O(1)
void printList(ListNode* headNode) {
    while(headNode) {
        std::cout<<headNode->val<<' ';
        headNode = headNode->next;
    }
    std::cout<<'\n';
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data
    ListNode* headNode = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, nullptr))));

    // Print call
    printList(headNode);

    // Rotation call
    Solution solution;
    headNode = solution.rotateList_V3(headNode, 3);

    // Print call
    printList(headNode);

    // Deletion call (delete the head node and recursively the entire list)
    delete headNode; headNode = nullptr;

    return 0;
}
/*
    Topics: Linked List | Two Pointers
    Link: https://practice.geeksforgeeks.org/problems/rotate-a-linked-list/1
*/
