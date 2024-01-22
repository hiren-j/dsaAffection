// Program to reverse each sublist of size "lesser than equal to k" of a linked list ~ coded by Hiren
#include <iostream>
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
};

// Solution class
class Solution {
public:
    // #1 Method to reverse each sublist of size lesser than equal to k, using 1 stack - O(N) & O(N)
    ListNode* reverseGroupsByK_V1(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded or k is zero, negative
        if(!headNode || !headNode->next || k <= 0)
            return headNode;

        ListNode* resHead    = nullptr; // Tracks the head node of the resultant list
        ListNode* resCurrent = nullptr; // Tracks the latest node of the resultant list
        std::stack<ListNode*> s;        // Requires to maintain the sublist in the reverse order

        // Iterate the list
        while(headNode) {
            // Push k nodes of the sublist to the stack
            for(int node=1; node<=k && headNode; ++node) {
                s.push(headNode);
                headNode = headNode->next;
            }
            // If the stack is not empty then set the nodes in the resultant list
            while(!s.empty()) {
                // If the resultant list is empty then set the head node of it
                if(!resHead)
                    resHead = s.top(), resCurrent = s.top();
                // Else then set the current node in the resultant list
                else    
                    resCurrent->next = s.top(), resCurrent = resCurrent->next;
                // Set the current node of the resultant list as the last node of it
                resCurrent->next = nullptr; s.pop();
            }
        }

        // Return the head node of the resultant list
        return resHead;
    }

    // #2 Method to reverse each sublist of size lesser than equal to k, using recursion only - O(N) & O(N)
    ListNode* reverseGroupsByK_V2(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded or k is zero, negative
        if(!headNode || !headNode->next || k <= 0)
            return headNode;

        ListNode* subListHead = nullptr; // Tracks the head node (head node of after reversal) of a sublist
        ListNode* subListTail = nullptr; // Tracks the last node (last node of after reversal) of a sublist

        // Iterate and reverse the sublist of size k
        for(int node=1; node<=k && headNode; ++node) {
            class ListNode* nextNode = headNode->next;
            // If its the first node of the sublist then set the node as the last node of the sublist
            if(!subListTail)
                subListTail = headNode;
            headNode->next = subListHead;
            subListHead = headNode;
            headNode = nextNode;
        }

        // Recurse to all the sublists then link the last node of the current sublist to the head node of the next sublist
        subListTail->next = reverseGroupsByK_V2(headNode, k);

        // Return the head node of the current sublist
        return subListHead;
    }

    // #3 Method to reverse each sublist of size lesser than equal to k, using constant auxiliary space - O(N) & O(1)
    ListNode* reverseGroupsByK_V3(ListNode* headNode, int k) {
        // Edge case: When the list is empty or single noded or k is zero, negative
        if(!headNode || !headNode->next || k <= 0)
            return headNode;

        ListNode* resHead         = nullptr; // Tracks the head node of the resultant list
        ListNode* prevSubListTail = nullptr; // Tracks the last node of the previously reversed sublist

        // Iterate the list
        while(headNode) {
            ListNode* subListHead = nullptr; // Tracks the head node (head node of after reversal) of a sublist
            ListNode* subListTail = nullptr; // Tracks the last node (last node of after reversal) of a sublist

            // Iterate and reverse the sublist of size k
            for(int node=1; node<=k && headNode; ++node) {
                class ListNode* nextNode = headNode->next;
                // If its the first node of the sublist then set the node as the last node of the sublist
                if(!subListTail)
                    subListTail = headNode;
                headNode->next = subListHead;
                subListHead = headNode;
                headNode = nextNode;
            }

            // If the resultant list is empty then set the head node of the current sublist as the head node of the resultant list
            if(!resHead)
                resHead = subListHead;
            // If the previous sublist exist then link the last node of it to the head node of the current sublist
            if(prevSubListTail)
                prevSubListTail->next = subListHead;
                
            // Mark the last node of the current sublist for the upcoming sublist
            prevSubListTail = subListTail;
        }

        // Return the head node of the resultant list
        return resHead;
    }
};

// Class to wrap all the basic methods of the list
class ListCommonMethods {
public:
    // Method to insert a node in the list - O(1) & O(1)
    void insertNodeInList(ListNode*& headNode, ListNode*& resCurrent, int val) {
        ListNode* newNode = new ListNode(val);
        if(!headNode)
            headNode = newNode, resCurrent = newNode;
        else
            resCurrent->next = newNode, resCurrent = resCurrent->next;
        resCurrent->next = nullptr;
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
};

// Driver code
int main() {
    bool userWantsOperation = true;
    
    while(userWantsOperation) { 
        system("cls || clear");
        int size; 
        std::cout<<"Enter the number of nodes for the list: ";
        std::cin>>size;

        ListNode* headNode = nullptr; // Tracks the head node of the list
        ListNode* currNode = nullptr; // Tracks the latest inserted node of the list
        
        ListCommonMethods commonMethods;
        
        // Input the nodes value of the list
        for(int node=1; node<=size; ++node) {
            int val;
            std::cout<<"Enter the value of the "<<node<<"th node: ";
            std::cin>>val;
            commonMethods.insertNodeInList(headNode, currNode, val);
        }

        // Input section for k value
        int k;
        std::cout<<"\nEnter the value of k: ";
        std::cin>>k;

        // Print call
        std::cout<<"\nList before reversal: ";
        commonMethods.printList(headNode);

        // Reversal call
        Solution solution;
        headNode = solution.reverseGroupsByK_V3(headNode, k);

        // Print call
        std::cout<<"\nList after reversal: ";
        commonMethods.printList(headNode);

        // Deletion call
        commonMethods.deleteList(headNode);

        // Input section to handle flow of iterations of the application
        char userChoise;
        std::cout<<"\n\nDo you want to perform the same operation on an another list? (Write Y for \"Yes\" else application will exit automatically): ";
        std::cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false;
    }

    return 0;
}
// Link: https://www.geeksforgeeks.org/problems/reverse-a-linked-list-in-groups-of-given-size/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=bottom_sticky_on_article
