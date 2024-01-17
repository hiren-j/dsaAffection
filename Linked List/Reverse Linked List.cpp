// Program to reverse a linked list ~ coded by Hiren
#include <iostream>
#include <vector>
#include <stack>

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr)
    :
    val(val), next(next) {}

    // Method to insert a node in the linked list - O(1) & O(1)
    void insertNode(ListNode*& headNode, int val) {
        ListNode* newNode = new ListNode(val);
        if(!headNode)
            headNode = newNode;
        else
            newNode->next = headNode->next, headNode->next = newNode;
    }

    // Method to delete the linked list - O(N) & O(1)
    void deleteList(ListNode*& headNode) {
        while(headNode) {
            ListNode* nextNode = headNode->next;
            delete headNode;
            headNode = nextNode;
        }
    }

    // Method to print the linked list - O(N) & O(1)
    void printList(ListNode* headNode) {
        while(headNode) {
            std::cout<<headNode->val<<' ';
            headNode = headNode->next;
        }
        std::cout<<'\n';
    }
};

// Solution class:
class Solution {
public:
    // #1 Method to reverse the linked list, using buffer only - O(N) & O(N)
    ListNode* reverseList_V1(ListNode* headNode) {
        if(!headNode || !headNode->next)
            return headNode;

        std::vector<ListNode*> buffer;

        while(headNode) {
            buffer.emplace_back(headNode);
            headNode = headNode->next;
        }
        
        int size = buffer.size();

        for(int node = size-1; node >= 1; --node) {
            buffer[node]->next = buffer[node-1];
        }

        buffer[0]->next = nullptr;

        return buffer[size-1];
    }

    // #2 Method to reverse the linked list, using 1 stack - O(N) & O(N)
    ListNode* reverseList_V2(ListNode* headNode) {
        if(!headNode || !headNode->next)
            return headNode;

        std::stack<ListNode*> s;

        while(headNode) {
            s.push(headNode);
            headNode = headNode->next;
        }

        ListNode* currNode = nullptr; headNode = nullptr; 

        while(!s.empty()) {
            if(!headNode)
                headNode = s.top(), currNode = s.top();
            else
                currNode->next = s.top(), currNode = currNode->next;

            currNode->next = nullptr; s.pop();
        }

        return headNode;
    }

    // #3 Method to reverse the linked list, using recursion only - O(N) & O(N)
    ListNode* reverseList_V3(ListNode* headNode, ListNode* prevNode = nullptr) {
        if(!headNode)
            return nullptr;

        if(!headNode->next) {
            headNode->next = prevNode; 
            return headNode;
        }

        ListNode* nextNode = headNode->next;
        headNode->next = prevNode;

        return reverseList_V3(nextNode, headNode);
    }

    // #4 Method to reverse the linked list, using constant auxiliary space - O(N) & O(1)
    ListNode* reverseList_V4(ListNode* headNode) {
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* dummyNode = new ListNode(0);
        ListNode* currNode  = dummyNode;

        while(headNode) {
            ListNode* nextNode = headNode->next;
            ListNode* dummyNext = dummyNode->next;
            dummyNode->next = headNode;
            headNode->next = dummyNext;
            headNode = nextNode;
        }

        headNode = dummyNode->next; 
        delete dummyNode;

        return headNode;
    }

    // #5 Method to reverse the linked list, using constant auxiliary space - O(N) & O(1)
    ListNode* reverseList_V5(ListNode* headNode) {
        if(!headNode || !headNode->next)
            return headNode;

        ListNode* prevNode = nullptr;
        ListNode* currNode = headNode;

        while(currNode) {
            ListNode* nextNode = currNode->next;
            currNode->next = prevNode;
            prevNode = currNode;
            currNode = nextNode;
        } 

        return prevNode;
    }
};

// Driver code
int main() {
    bool userWantsOp = true;

    while(userWantsOp) {
        // Handles console clearance for both "windows" and "linux" user
        system("clear || cls");

        int n; 
        std::cout<<"Enter the number of nodes for the list: "; 
        std::cin>>n;

        // Tracks the head node of the list
        ListNode* headNode = nullptr;

        // Input the nodes value one by one
        for(int i = 1; i <= n; ++i) {
            int val;
            std::cout<<"Enter the value of the "<<i<<" node: "; 
            std::cin>>val;
            headNode->insertNode(headNode, val);
        }

        // Print call
        std::cout<<'\n';
        headNode->printList(headNode);

        // Reversal call
        Solution obj;
        headNode = obj.reverseList_V5(headNode);

        // Print call
        headNode->printList(headNode);

        // Deletion call
        headNode->deleteList(headNode);

        // Input section to handle flow of iterations
        char userChoice;
        std::cout<<"\nDo you want to perform the same operation on an another list? (Write Y - \"Yes\" | Else application will exit automatically): ";
        std::cin>>userChoice;
        userWantsOp = (userChoice == 'Y') ? true : false;
    }
    
    return 0;
}
// Link: https://leetcode.com/problems/reverse-linked-list/editorial/
