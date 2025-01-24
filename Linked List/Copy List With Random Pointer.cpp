// Program to create the exact copy of a linked list containing nodes having next and random pointer ~ coded by Hiren
#include <unordered_map>
#include <iostream>

class ListNode { // Node template (user defined datatype)
public:
    int val;
    ListNode* next;
    ListNode* random;

    // Init constructor
    ListNode(int val, ListNode* next = nullptr, ListNode* random = nullptr) {
        this->val = val;
        this->next = next;
        this->random = random;
    }
};

class CopyListUsingHashTable {
public:
    // Method to create the exact copy of given list, using hashmap - O(N) & O(N)
    ListNode* createCopyOfList(ListNode* headNode) {
        if(!headNode) // Edge case: If the list is empty
            return nullptr; 

        std::unordered_map<ListNode*, ListNode*> copy;
        ListNode* currNode = headNode;

        while(currNode) { // Create copy of nodes and map nodes with their copies
            copy[currNode] = new ListNode(currNode->val);
            currNode = currNode->next;
        }

        currNode = headNode;
 
        while(currNode) { // Link nodes of copy list
            ListNode* origNext   = currNode->next;
            ListNode* origRandom = currNode->random;
            copy[currNode]->next = copy[origNext];
            copy[currNode]->random = copy[currNode->random];
            currNode = currNode->next; 
        }

        return copy[headNode];
    }
};

class CopyListInPlace {
public:
    // Method to create the exact copy of given list, using constant auxiliary space - O(N) & O(1)
    ListNode* createCopyOfList(ListNode* headNode) {
        if(!headNode) // Edge case: If the list is empty
            return nullptr;
            
        ListNode* currNode = headNode;

        while(currNode) { // Create copy of nodes and store it next to its original node
            ListNode* origNext = currNode->next;
            ListNode* newNode  = new ListNode(currNode->val);
            currNode->next = newNode;
            newNode->next  = origNext;
            currNode = origNext;
        }

        currNode = headNode;

        while(currNode) { // Link random pointer of all nodes of copy list
            ListNode* origNext   = currNode->next->next;
            ListNode* origRandom = currNode->random;
            ListNode* copyNode   = currNode->next;
            copyNode->random = (origRandom) ? origRandom->next : nullptr;
            currNode = origNext;
        }

        ListNode* copyListHead = nullptr;

        while(headNode) { // Link next pointer of all nodes of copy list and reset the original list
            ListNode* origNext   = headNode->next->next;
            ListNode* copyNode   = headNode->next;
            if(!copyListHead) copyListHead = copyNode;
            copyNode->next = (origNext) ? origNext->next : nullptr;
            headNode->next = origNext;
            headNode = origNext;
        }

        return copyListHead;
    }
};

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
    ListNode* fifthNode  = new ListNode(5, nullptr, nullptr);
    ListNode* fourthNode = new ListNode(4, fifthNode, nullptr);
    ListNode* thirdNode  = new ListNode(3, fourthNode, fifthNode);
    ListNode* secondNode = new ListNode(2, thirdNode, nullptr);
    ListNode* headNode   = new ListNode(1, secondNode, fourthNode);
    
    // Print call
    std::cout<<"Original List: ";
    printList(headNode);

    // Copy call
    CopyListInPlace obj;
    ListNode* copyListHead = obj.createCopyOfList(headNode);    

    // Print call
    std::cout<<"\nCopy List: ";
    printList(copyListHead);

    // Deletion call
    deleteList(headNode); deleteList(copyListHead);

    return 0;
}
// Link: https://leetcode.com/problems/copy-list-with-random-pointer/description/
