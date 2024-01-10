// Program to add two non-negative linked lists and return the sum as a linked list ~ coded by Hiren
#include <iostream>

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

// #1 Solution class:
class Solution_V1 {
public:
    // Method to add two non-negative lists, using dynamic node creation - O(N+M) & O(N+M) : Where N is the size of "list1" and M of "list2"
    ListNode* addTwoNumbers(ListNode* headNode1, ListNode* headNode2) {
        ListNode* sumListHead    = nullptr; // Tracks the head node of the new list (sum list)
        ListNode* sumListCurrent = nullptr; // Tracks the nodes of the new list (sum list)
        int carry = 0;                      // Stores the "carry value" get by adding the value of two nodes

        while(headNode1 || headNode2 || carry) {
            // At the beginning, update the "sum value" by "carry value"
            int sum = carry;

            // If the node of "list1" exists then add its value to the sum
            if(headNode1)
                sum += headNode1->val, headNode1 = headNode1->next;
            // If the node of "list2" exists then add its value to the sum
            if(headNode2)
                sum += headNode2->val, headNode2 = headNode2->next;
            
            // Calculate and store the "remainder" and "carry" value
            int rem = sum % 10; carry = sum / 10;
            
            // Create the new node of the "remainder value"
            ListNode* newNode = new ListNode(rem);
            
            // If the new list is empty then set the head node of it
            if(!sumListHead)
                sumListHead = newNode, sumListCurrent = newNode;
            // Else set the current node in the new list
            else
                sumListCurrent->next = newNode, sumListCurrent = sumListCurrent->next;
        }

        // Return the head node of the new list
        return sumListHead;
    }
};
// Note: This solution can lead to the "memory leak issues" as the list is created dynamically but never freed 

// #2 Solution class:
class Solution_V2 {
public:
    // Method to add two non-negative lists, using constant auxiliary space - O(N+M) & O(1) : Where N is the size of "list1" and M of "list2"
    ListNode* addTwoNumbers(ListNode* headNode1, ListNode* headNode2) {
        int length1 = getListLength(headNode1); // Calculate and store the length of "list1"
        int length2 = getListLength(headNode2); // Calculate and store the length of "list2"
        int carry = 0;                          // Stores the "carry value" get by adding the value of two nodes

        ListNode* sumListHead    = nullptr; // Tracks the head node of the resultant list (sum list)
        ListNode* sumListCurrent = nullptr; // Tracks the nodes of the resultant list (sum list)

        while(headNode1 || headNode2) {
            ListNode* currNode1 = headNode1; // Tracks the current node of the "list1"
            ListNode* currNode2 = headNode2; // Tracks the current node of the "list2"
            int sum = carry;                 // At the beginning, update the "sum value" by "carry value"
            
            // If the node of "list1" exists then add its value to the sum
            if(headNode1)
                sum += headNode1->val, headNode1 = headNode1->next;
            // If the node of "list2" exists then add its value to the sum
            if(headNode2)
                sum += headNode2->val, headNode2 = headNode2->next;
            
            // Calculate and store the "remainder" and "carry" value
            int rem = sum % 10; carry = sum / 10;

            // If the length of "list1" is greater then set the node of "list1" in the resultant list 
            if(length1 > length2)
                currNode1->val = rem, updateLinks(currNode1, sumListHead, sumListCurrent);
            // Else when the length of "list2" is greater then set the node of "list2" in the resultant list 
            else
                currNode2->val = rem, updateLinks(currNode2, sumListHead, sumListCurrent);
        }

        // If the "carry value" is remaining then create a new node of it and set it as the last node of the resultant list
        if(carry)
            sumListCurrent->next = new ListNode(carry);
        // Else then set the last node of the resultant list
        else
            sumListCurrent->next = nullptr;

        // Return the head node of the resultant list 
        return sumListHead;
    }

private:
    // Method helper
    int getListLength(ListNode* headNode) {
        int count = 0;
        while(headNode) headNode = headNode->next, count++;
        return count;
    }

    // Method helper
    void updateLinks(ListNode* givenNode, ListNode*& sumListHead, ListNode*& sumListCurrent) {
        // If the resultant list is empty then set the head node of it
        if(!sumListHead)
            sumListHead = givenNode, sumListCurrent = givenNode;
        // Else then set the current node in the resultant list
        else
            sumListCurrent->next = givenNode, sumListCurrent = sumListCurrent->next;
    }
};

// Method to print the list - O(K) & O(1) : Where K is the size of the list
void printList(ListNode* headNode) {
    while(headNode) {
        std::cout<<headNode->val<<' ';
        headNode = headNode->next;
    }
    std::cout<<'\n';
}

// Driver code
int main() {
    // Creating list1, connecting nodes and initializing their data
    ListNode* headNode1 = new ListNode(3, new ListNode(4, new ListNode(2)));

    // Creating list2, connecting nodes and initializing their data
    ListNode* headNode2 = new ListNode(4, new ListNode(8, new ListNode(7)));

    // Print call
    printList(headNode1); printList(headNode2);

    // Addition call
    Solution_V2 obj;
    ListNode* sumListHead = obj.addTwoNumbers(headNode1, headNode2);

    // Print call
    printList(sumListHead);

    // Deletion call
    delete headNode1; delete headNode2;

    return 0;
}
// Link: https://leetcode.com/problems/add-two-numbers/description/
