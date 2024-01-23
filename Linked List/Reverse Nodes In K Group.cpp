// Program to reverse each sublist of size equal to k. If the number of nodes is not a multiple of k then left-out nodes, in the end, should remain as it is in the linked list ~ coded by Hiren
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

// Class to wrap all the basic methods of the list:
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

    // Method to find the length of the list - O(N) & O(1)
    int getListLength(ListNode* headNode) {
        int count = 0;
        while(headNode) headNode = headNode->next, count++;
        return count;
    }

    // Method to print the list - O(N) & O(1)
    void printList(ListNode* headNode) {
        while(headNode) {
            std::cout<<headNode->val<<' ';
            headNode = headNode->next;
        }
    }
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to reverse each sublist of size k, using 1 stack - O(N) & O(N)
    ListNode* reverseKGroup(ListNode* headNode, int k) {
        // Edge case: When the "list is empty" or "single noded" or "k is zero, negative"
        if(!headNode || !headNode->next || k <= 0)
            return headNode;

        // Calculate and store the length of the list
        ListCommonMethods cm;
        int length = cm.getListLength(headNode);

        ListNode* resHead    = nullptr; // Tracks the head node of the resultant list
        ListNode* resCurrent = nullptr; // Tracks the latest node of the resultant list
        std::stack<ListNode*> s;        // Requires to maintain the sublist in the reverse order

        // Iterate the list
        while(headNode) {
            // If the sublist size is not equal to k then set the last node of the resultant list
            if(length < k) {
                resCurrent->next = headNode; 
                return resHead;
            }

            // Push k nodes of the sublist to the stack
            for(int node=1; node<=k && headNode; ++node) {
                s.push(headNode);
                headNode = headNode->next;
                length--;
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
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to reverse each sublist of size k, using recursion only - O(N) & O(N)
    ListNode* reverseKGroup(ListNode* headNode, int k) {
        ListCommonMethods cm;
        int length = cm.getListLength(headNode);
        return reverseGroupEqualK(headNode, k, length);
    }

private:
    // Method helper
    ListNode* reverseGroupEqualK(ListNode* headNode, int k, int length) {
        // Edge case: When the "list is empty" or "single noded" or "k is zero, negative" or "sublist size is not equal to k"
        if(!headNode || !headNode->next || k <= 0 || length < k)
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
            length--;
        }

        // Recurse to all the sublists then link the last node of the current sublist to the head node of the next sublist
        subListTail->next = reverseGroupEqualK(headNode, k, length);

        // Return the head node of the current sublist
        return subListHead;
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to reverse each sublist of size k, using constant auxiliary space - O(N) & O(1)
    ListNode* reverseKGroup(ListNode* headNode, int k) {
        // Edge case: When the "list is empty" or "single noded" or "k is zero, negative"
        if(!headNode || !headNode->next || k <= 0)
            return headNode;
        
        // Calculate and store the length of the list
        ListCommonMethods cm;
        int length = cm.getListLength(headNode);

        ListNode* resHead         = nullptr; // Tracks the head node of the resultant list
        ListNode* prevSubListTail = nullptr; // Tracks the last node of the previously reversed sublist

        // Iterate the list
        while(headNode) {
            // If the sublist size is not equal to k then set the last node of the resultant list
            if(length < k) {
                prevSubListTail->next = headNode; 
                return resHead;
            }

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
                length--;
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
        std::cout<<"\nList before groups reversal: ";
        commonMethods.printList(headNode);

        // Reversal call
        Solution_V3 solution;
        headNode = solution.reverseKGroup(headNode, k);

        // Print call
        std::cout<<"\nList after groups reversal: ";
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
// Link: https://leetcode.com/problems/reverse-nodes-in-k-group/
