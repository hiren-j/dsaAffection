// Program to add two non-negative numbers represented by linked lists ~ coded by Hiren 
#include <iostream>
#include <vector>

class ListNode { // Node template (user defined datatype)
public:
    int val;
    ListNode* next;

    // Init constructor 
    ListNode(int val, ListNode* next = nullptr)    
    :
    val(val), next(next) {}
};

class AddByCreatingNewList {
public:
    // Method to add two linked lists, using dynamic node creation - O(N+M) & O(N+M)
    ListNode* addTwoLists(ListNode* headNode1, ListNode* headNode2) {
        if(!headNode1 && !headNode2) // Edge case: If both lists are empty
            return nullptr;

        headNode1 = reverseList(headNode1);
        headNode2 = reverseList(headNode2);

        ListNode* dummyHead = new ListNode(-1);
        ListNode* dummyTail = dummyHead;

        int carry = 0;

        while(headNode1 || headNode2 || carry) {
            ListNode* nextNode1 = nullptr;
            ListNode* nextNode2 = nullptr;
            int sum = carry;

            if(headNode1)
                sum += headNode1->val, nextNode1 = headNode1->next;
            if(headNode2)
                sum += headNode2->val, nextNode2 = headNode2->next;

            carry = sum / 10;

            dummyTail->next = new ListNode(sum % 10);
            dummyTail = dummyTail->next;
            headNode1 = nextNode1;
            headNode2 = nextNode2;
        }

        ListNode* sumListHead = reverseList(dummyHead->next);

        while(sumListHead && sumListHead->val == 0) // Skip leading zeros
            sumListHead = sumListHead->next;

        return sumListHead;
    } 

private:
    ListNode* reverseList(ListNode* headNode) {
        ListNode* prevNode = nullptr;
        ListNode* nextNode = nullptr;

        while(headNode)
            nextNode = headNode->next,
            headNode->next = prevNode,
            prevNode = headNode,
            headNode = nextNode;

        return prevNode;
    }
};
// Note: This solution contains memory leak issues, as the new list is created dynamically but never freed

class AddWithoutCreatingList {
public:
    // Method to add two linked lists, using constant auxiliary space - O(N+M) & O(1)
    ListNode* addTwoLists(ListNode* headNode1, ListNode* headNode2) {
        if(!headNode1 && !headNode2) // Edge case: If both lists are empty
            return nullptr;  

        headNode1 = reverseList(headNode1);
        headNode2 = reverseList(headNode2);

        ListNode* dummyHead = new ListNode(-1);
        ListNode* dummyTail = dummyHead;

        int carry = 0;

        while(headNode1 || headNode2 || carry) {
            ListNode* nextNode1 = nullptr;
            ListNode* nextNode2 = nullptr;

            int sum = carry;

            if(headNode1)
                sum += headNode1->val, nextNode1 = headNode1->next;
            if(headNode2)
                sum += headNode2->val, nextNode2 = headNode2->next;

            carry = sum / 10;

            if(headNode1)
                headNode1->val = sum % 10, dummyTail->next = headNode1; 
            else if(headNode2)
                headNode2->val = sum % 10, dummyTail->next = headNode2;
            else    
                dummyTail->next = new ListNode(sum % 10);

            dummyTail = dummyTail->next;
            headNode1 = nextNode1;
            headNode2 = nextNode2;    
        }

        // Set tail node of sum list, get the head node of it and then delete to avoid memory leak issues
        dummyTail->next = nullptr;
        ListNode* sumListHead = reverseList(dummyHead->next);
        delete dummyHead;

        while(sumListHead && sumListHead->val == 0) // Skip leading zeros
            sumListHead = sumListHead->next;
        
        return sumListHead;
    }

private:
    ListNode* reverseList(ListNode* headNode) {
        ListNode* prevNode = nullptr;
        ListNode* nextNode = nullptr;

        while(headNode)
           nextNode = headNode->next,
           headNode->next = prevNode,
           prevNode = headNode,
           headNode = nextNode;

        return prevNode; 
    }
};
// Note: In this solution instead of reversing the input lists, we could also use stack

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
    // List1: creating, connecting nodes and initializing their data
    ListNode* headNode1 = new ListNode(1, new ListNode(2, new ListNode(3, new ListNode(4, nullptr))));

    // List2: creating, connecting nodes and intializing their data
    ListNode* headNode2 = new ListNode(4, new ListNode(9, new ListNode(9, nullptr)));

    // Print list1
    std::cout<<"List1: ";
    printList(headNode1);

    // Print list2
    std::cout<<"\nList2: ";
    printList(headNode2);

    // Addition call
    AddWithoutCreatingList obj;
    ListNode* sumListHead = obj.addTwoLists(headNode1, headNode2);

    // Print result list
    std::cout<<"\nSum List: ";
    printList(sumListHead);

    // Deletion call
    deleteList(sumListHead);

    return 0;
} 
// Link: https://www.geeksforgeeks.org/problems/add-two-numbers-represented-by-linked-lists/1 
