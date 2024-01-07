// Program to remove all the nodes of the linked list whose value is equal to the given "val" ~ coded by Hiren  
#include <iostream>
#include <vector>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}
};

// #1 Method to remove all the nodes whose value equals "val", using dynamic node creation - O(N) & O(N)
ListNode* removeElements_V1(ListNode* headNode, int val) {
    // Edge case: When the list is empty
    if(!headNode)
        return nullptr;

    ListNode* newHead    = nullptr; // Tracks the head node of the new list
    ListNode* newCurrent = nullptr; // Tracks the nodes of the new list

    // Iterate the list
    while(headNode) {
        ListNode* nextNode = headNode->next;
        // If the node value is not equal to the given "val" then create a new node of the value
        if(headNode->val != val) {
            ListNode* newNode = new ListNode(headNode->val);
            // If the new list is empty then set the head node of it
            if(!newHead)
                newHead = newNode, newCurrent = newNode;
            // Else set the current node in the new list
            else
                newCurrent->next = newNode, newCurrent = newCurrent->next;
            // Set the current node of the new list as the last node of it
            newCurrent->next = nullptr;
        }
        // Delete the node and move to the next node in the original list
        delete headNode; headNode = nextNode;
    }

    // Return the head node of the new list
    return newHead;
}
// Note: This solution can lead the "memory leak issues" as the list is created dynamically but never freed

// #2 Method to remove all the nodes whose value equals "val", using buffer only - O(N) & O(N)
ListNode* removeElements_V2(ListNode* headNode, int val) {
    // Stores all the nodes of the list whose value is not equal to the "val" 
    std::vector<ListNode*> buffer;

    // Iterate and store such nodes to the buffer
    while(headNode) {
        // If the node value is not equal to the given "val" then store the node to the buffer
        if(headNode->val != val) {
            buffer.push_back(headNode);
        }
        // Move to the next node in the original list
        headNode = headNode->next;
    }

    int size = buffer.size();

    // Iterate and link all the nodes of the buffer
    for(int node = 1; node < size; ++node)
        buffer[node-1]->next = buffer[node];

    // If the buffer is not empty then set the last node of the list
    if(size > 0)
        buffer[size-1]->next = nullptr;

    // If the buffer is not empty then return the head node of the list
    return (size > 0) ? buffer[0] : nullptr;
}

// #3 Method to remove all the nodes whose value equals "val", using constant auxiliary space - O(N) & O(1)
ListNode* removeElements_V3(ListNode* headNode, int val) {
    // Edge case: When the list is empty
    if(!headNode)
        return nullptr;

    ListNode* resHead    = nullptr; // Tracks the head node of the resultant list
    ListNode* resCurrent = nullptr; // Tracks the nodes of the resultant list

    // Iterate the list
    while(headNode) {
        ListNode* nextNode = headNode->next;
        // If the node value is equal to the given "val" then delete the node
        if(headNode->val == val) {
            delete headNode;
        }
        // ELse set the node in the resultant list
        else {
            // If the resultant list is empty then set the head node of it
            if(!resHead)
                resHead = headNode, resCurrent = headNode;
            // Else set the current node in the resultant list
            else
                resCurrent->next = headNode, resCurrent = resCurrent->next;
            // Set the current node of the resultant list as the last node of it
            resCurrent->next = nullptr;
        }
        // Move to the next node in the original list
        headNode = nextNode;
    }

    // Return the head node of the updated list
    return resHead;
}

// Method to delete the list - O(N) & O(1)
void deleteList(ListNode*& headNode) {
    while(headNode) {
        ListNode* nextNode = headNode->next;
        delete headNode;
        headNode = nextNode;
    }
}

// Method to print the list - O(N) & O(1)
void printList(ListNode* headNode) {
    while(headNode) {
        std::cout<<headNode->val<<' ';
        headNode = headNode->next;
    }
}

// Driver code
int main() {
    // Creating, connecting nodes and initializing their data
    ListNode* headNode = new ListNode(1);
    headNode->next = new ListNode(3);
    headNode->next->next = new ListNode(4);
    headNode->next->next->next = new ListNode(3);
    headNode->next->next->next->next = new ListNode(5);

    // Print call
    printList(headNode);
    std::cout<<'\n';

    // Removal call
    headNode = removeElements_V3(headNode, 3);

    // Print call
    printList(headNode);

    // Deletion call
    deleteList(headNode);

    return 0;
}
// Link: https://leetcode.com/problems/remove-linked-list-elements/description/
