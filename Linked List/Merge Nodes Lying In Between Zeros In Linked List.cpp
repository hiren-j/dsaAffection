// Program to merge the nodes lying in between zeros in a linked list ~ coded by Hiren
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

    // Init destructor
    ~ListNode() {
        if(next) {
            delete next;
        }
    }
};

// #1 Method to merge the nodes lying in between zeros using dynamic node creation - O(N) & O(N)
ListNode* mergeNodes_V1(ListNode* headNode) {
    ListNode* newHead = nullptr;    // Tracks the head node of the new list
    ListNode* newCurrent = nullptr; // Tracks any node of the new list
    int subListSum = 0;             // Tracks the sum of any sublist with nodes value other than zero

    // Iterate the list
    while(headNode) {
        // When we reach the node with value zero
        if(headNode->val == 0) {
            // Create a new node its because a sublist with values other than zero is processed already 
            if(subListSum != 0) {
                ListNode* newNode = new ListNode(subListSum);
                // If the new list is empty then set the head node of the new list
                if(!newHead)
                    newHead = newNode, newCurrent = newNode;
                // Else then set the current node in the new list
                else
                    newCurrent->next = newNode, newCurrent = newCurrent->next;
            }
            // Reset the sum to zero as we're forwarding to a new sublist
            subListSum = 0;
        }
        // Else sum the value of the node of the sublist
        else {
            subListSum += headNode->val;
        }
        // Move to the next node in the list
        headNode = headNode->next;
    }

    // Return the head node of the new list
    return newHead;
}
// Note: This solution can lead to the "memory leak issues" as the new list is created dynamically but never freed

// #2 Method to merge the nodes lying in between zeros using buffer - O(N) & O(N)
ListNode* mergeNodes_V2(ListNode* headNode) {
    // Stores the nodes of the resultant list
    std::vector<ListNode*> buffer;

    // Iterate the list
    while(headNode) {
        // Mark the node as the start point of a sublist with values other than zero
        ListNode* startNode = headNode;
        // Store the sum of the sublist in the start point of the sublist
        while(headNode->next && headNode->val != 0) {
            startNode->val += headNode->next->val;
            headNode = headNode->next;
        }
        // If the value of the start point is not zero then store the node into the buffer
        if(startNode->val != 0) {
            buffer.push_back(startNode);
        }
        // Move to the next node in the list
        headNode = headNode->next;
    }

    int size = buffer.size();

    // Link all the nodes of the resultant list
    for(int node = 0; node < size; ++node) {
        buffer[node]->next = nullptr;
        if(node > 0) buffer[node-1]->next = buffer[node];
    }   

    // If the list is not empty then return the head node of the resultant list
    return (size > 0) ? buffer[0] : nullptr;
}

// #3 Method to merge the nodes lying in between zeros using constant auxiliary space - O(N) & O(1)
ListNode* mergeNodes_V3(ListNode* headNode) {
    ListNode* newHead = nullptr;    // Tracks the head node of the resultant list
    ListNode* newCurrent = nullptr; // Tracks any node of the resultant list

    // Iterate the list
    while(headNode) {
        // Mark the node as the start point of a sublist with values other than zero
        ListNode* startNode = headNode;
        // Store the sum of the sublist in the start point of the sublist
        while(headNode->next && headNode->val != 0) {
            startNode->val += headNode->next->val;
            headNode = headNode->next;
        }
        // If the value of the start point is not zero then set the "start point node" in the resultant list
        if(startNode->val != 0) {
            // If the resultant list is empty then set the head node of the list
            if(!newHead)
                newHead = startNode, newCurrent = startNode;
            // Else then set the current node in the resultant list
            else
                newCurrent->next = startNode, newCurrent = newCurrent->next;
            newCurrent->next = nullptr;
        }
        // Move to the next node in the list
        headNode = headNode->next;
    }

    // Return the head node of the resultant list
    return newHead;
}

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
    ListNode* headNode = new ListNode(0);
    headNode->next = new ListNode(4);
    headNode->next->next = new ListNode(5);
    headNode->next->next->next = new ListNode(0);
    headNode->next->next->next->next = new ListNode(3);
    headNode->next->next->next->next->next = new ListNode(2);
    headNode->next->next->next->next->next->next = new ListNode(0);

    // Print call
    printList(headNode);

    // Merge call
    headNode = mergeNodes_V3(headNode);

    // Print call
    printList(headNode); 

    // Delete the head node (and recursively the entire list)
    delete headNode;

    return 0;
}
// Link: https://leetcode.com/problems/merge-nodes-in-between-zeros/description/
