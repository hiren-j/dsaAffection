// Program to merge two sorted lists in decreasing order ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

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

// #1 Solution class:
class Solution_V1 {
    // Method helper
    static bool comparator(ListNode* node1, ListNode* node2) {
        return node1->val < node2->val;
    }
    
public:
    // Method to merge two sorted lists in reverse order, using sorting with buffer - O(NLogN + MLogM) & O(N+M) : Where N is the size of "list1" and M of "list2".
    ListNode* mergeTwoLists(ListNode* headNode1, ListNode* headNode2) {
        // Edge case: When both the lists are empty.
        if(!headNode1 && !headNode2)
            return nullptr;

        // Stores all the nodes of both the lists.
        vector<ListNode*> buffer;
        
        // Iterate the lists.
        while(headNode1 || headNode2) {
            // If the node of "list1" exist then store it to the buffer.
            if(headNode1)
                buffer.push_back(headNode1), headNode1 = headNode1->next;
            // If the node of "list2" exist then store it to the buffer.
            if(headNode2)
                buffer.push_back(headNode2), headNode2 = headNode2->next;
        }
        
        // Sort all the nodes based on their values.
        sort(begin(buffer), end(buffer), comparator);

        int size = buffer.size();
        
        // Iterate and link all the nodes of the buffer.
        for(int node = size-2; node >= 0; --node)
            buffer[node+1]->next = buffer[node];
        
        // If the buffer is not empty then set the last node of the "merge list".
        if(size > 0) 
            buffer[0]->next = nullptr;
        
        // If the buffer is not empty then return the head node of the "merge list".
        return (size > 0) ? buffer[size-1] : nullptr;
    }
};

// #2 Solution class:
class Solution_V2 {
public:
    // Method to merge two sorted lists in reverse order, using buffer only - O(N+M) & O(N+M) : Where N is the size of "list1" and M of "list2".
    ListNode* mergeTwoLists(ListNode* headNode1, ListNode* headNode2) {
        // Edge case: When both the lists are empty.
        if(!headNode1 && !headNode2)
            return nullptr;
        
        vector<ListNode*> list1; // Stores all the nodes of "list1".
        vector<ListNode*> list2; // Stores all the nodes of "list2".
        
        // Iterate the lists.
        while(headNode1 || headNode2) {
            // If the node of "list1" exist then store it to the corresponding buffer.
            if(headNode1)
                list1.push_back(headNode1), headNode1 = headNode1->next;
            // If the node of "list2" exist then store it to corresponding buffer.
            if(headNode2)
                list2.push_back(headNode2), headNode2 = headNode2->next;
        }

        // Set the "merge list" and return the head node of it.        
        return setMergeList(list1, list2);
    }
    
private:
    // Method helper
    ListNode* setMergeList(vector<ListNode*>& list1, vector<ListNode*>& list2) {
        int size1 = list1.size(), size2 = list2.size();
        int i = size1-1, j = size2-1;
        
        ListNode* resHead    = nullptr; // Tracks the head node of the "merge list".
        ListNode* resCurrent = nullptr; // Tracks the nodes of the "merge list".
        
        // Iterate the lists.
        while(i >= 0 && j >= 0) {
            // If the node value of "list1" is greater then set it to the "merge list".
            if(list1[i]->val > list2[j]->val) {
                updateLinks(i, list1, resHead, resCurrent);
                i--; 
            }
            // Else when the node value of "list2" is greater then set it to the "merge list".
            else {
                updateLinks(j, list2, resHead, resCurrent); 
                j--;
            }
        }
        
        // If the nodes of "list1" are remaining then set them to the "merge list".
        while(i >= 0) {
            updateLinks(i, list1, resHead, resCurrent);
            i--;
        }
        
        // If the nodes of "list2" are remaining then set them to the "merge list".
        while(j >= 0) {
            updateLinks(j, list2, resHead, resCurrent);
            j--;
        }
        
        // Return the head node of the "merge list".
        return resHead;
    }    
    
    // Method helper
    void updateLinks(int node, vector<ListNode*>& list, ListNode*& resHead, ListNode*& resCurrent) {
        // If the "merge list" is empty then set the head node of it.
        if(!resHead)
            resHead = list[node], resCurrent = list[node];
        // Else set the current node in the "merge list".
        else
            resCurrent->next = list[node], resCurrent = resCurrent->next;
        // Set the current node of the "merge list" as the last node of it.
        resCurrent->next = nullptr; 
    }
};

// #3 Solution class:
class Solution_V3 {
public:
    // Method to merge two sorted lists in reverse order, using constant auxiliary space - O(N+M) & O(1) : Where N is the size of "list1" and M of "list2".
    ListNode* mergeTwoLists(ListNode* headNode1, ListNode* headNode2) {
        // Edge case: When both the lists are empty.
        if(!headNode1 && !headNode2)
            return nullptr;
            
        headNode1 = reverseList(headNode1); // Reverse the "list1" and store the head node of it.
        headNode2 = reverseList(headNode2); // Reverse the "list2" and store the head node of it.
        
        // Set the "merge list" and return the head node of it.
        return setMergeList(headNode1, headNode2);
    }
    
private:
    // Method helper
    ListNode* reverseList(ListNode* headNode) {
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

    // Method helper
    ListNode* setMergeList(ListNode* headNode1, ListNode* headNode2) {
        ListNode* nodeList1 = headNode1; // Tracks the nodes of "list1".
        ListNode* nodeList2 = headNode2; // Tracks the nodes of "list2".
        ListNode* resHead    = nullptr;  // Tracks the head node of the "merge list".
        ListNode* resCurrent = nullptr;  // Tracks the nodes of the "merge list".
        
        // Iterate the lists.
        while(nodeList1 && nodeList2) {
            ListNode* nextNode1 = nodeList1->next;
            ListNode* nextNode2 = nodeList2->next;
            // If the node value of "list1" is greater then set it to the "merge list".
            if(nodeList1->val > nodeList2->val) {
                updateLinks(nodeList1, resHead, resCurrent);
                nodeList1 = nextNode1;
            }
            // Else when the node value of "list2" is greater then set it to the "merge list".
            else {
                updateLinks(nodeList2, resHead, resCurrent);
                nodeList2 = nextNode2;
            }
        }
        
        // If the nodes of "list1" are remaining then set them to the "merge list".
        while(nodeList1) {
            ListNode* nextNode1 = nodeList1->next;
            updateLinks(nodeList1, resHead, resCurrent);
            nodeList1 = nextNode1;
        }
        
        // If the nodes of "list2" are remaining then set them to the "merge list".
        while(nodeList2) {
            ListNode* nextNode2 = nodeList2->next;
            updateLinks(nodeList2, resHead, resCurrent);
            nodeList2 = nextNode2;
        }
        
        // Return the head node of the "merge list".
        return resHead;
    }

    // Method helper
    void updateLinks(ListNode* givenNode, ListNode*& resHead, ListNode*& resCurrent) {
        // If the "merge list" is empty then set the head node of it.
        if(!resHead)
            resHead = givenNode, resCurrent = givenNode;
        // Else set the current node in the "merge list".
        else
            resCurrent->next = givenNode, resCurrent = resCurrent->next;
        // Set the current node of the "merge list" as the last node of it.
        resCurrent->next = nullptr; 
    }
};

// #4 Solution class:
class Solution_V4 {
public:
    // Method to merge two sorted lists in reverse order, using constant auxiliary space - O(N+M) & O(1) : Where N is the size of "list1" and M of "list2".
    ListNode* mergeTwoLists(ListNode* headNode1, ListNode* headNode2) {
        // Edge case: When both the lists are empty.
        if(!headNode1 && !headNode2)
            return nullptr;
            
        ListNode* nodeList1 = headNode1; // Tracks the nodes of "list1".
        ListNode* nodeList2 = headNode2; // Tracks the nodes of "list2".
        ListNode* resHead    = nullptr;  // Tracks the head node of the "merge list".
        ListNode* resCurrent = nullptr;  // Tracks the nodes of the "merge list".
        
        // Iterate the lists.
        while(nodeList1 && nodeList2) {
            ListNode* nextNode1 = nodeList1->next;
            ListNode* nextNode2 = nodeList2->next;
            // If the node value of "list2" is greater then set it to the "merge list".
            if(nodeList1->val < nodeList2->val) {
                updateLinks(nodeList1, resHead, resCurrent);
                nodeList1 = nextNode1;
            }
            // Else when the node value of "list1" is greater then set it to the "merge list".
            else {
                updateLinks(nodeList2, resHead, resCurrent);
                nodeList2 = nextNode2;
            }
        }
        
        // If the nodes of "list1" are remaining then set them to the "merge list".
        while(nodeList1) {
            ListNode* nextNode1 = nodeList1->next;
            updateLinks(nodeList1, resHead, resCurrent);
            nodeList1 = nextNode1;
        }
        
        // If the nodes of "list2" are remaining then set them to the "merge list".
        while(nodeList2) {
            ListNode* nextNode2 = nodeList2->next;
            updateLinks(nodeList2, resHead, resCurrent);
            nodeList2 = nextNode2;
        }
        
        // Return the head node of the "merge list".
        return resHead;
    }
    
private:
    // Method helper
    void updateLinks(ListNode* givenNode, ListNode*& resHead, ListNode*& resCurrent) {
        resCurrent = givenNode;
        givenNode->next = resHead;
        resHead = givenNode;
    }
};

// Method to print the list - O(K) & O(1) : Where K is the size of the list.
void printList(ListNode* headNode) {
    while(headNode) {
        cout<<headNode->val<<' ';
        headNode = headNode->next;
    }
    cout<<'\n';
}

// Driver code
int main() {
    // Creating list1, connecting nodes and initializing their data.
    ListNode* headNode1 = new ListNode(5, new ListNode(10, new ListNode(15, new ListNode(40, nullptr))));

    // Creating list2, connecting nodes and initializing their data.
    ListNode* headNode2 = new ListNode(2, new ListNode(3, new ListNode(20, nullptr)));

    // Print call
    printList(headNode1); printList(headNode2);

    // Merge call
    Solution_V4 obj;
    ListNode* headNode = obj.mergeTwoLists(headNode1, headNode2); 

    // Print call
    printList(headNode);

    // Deletion call
    delete headNode;

    return 0;
}
// Link: https://www.geeksforgeeks.org/problems/merge-2-sorted-linked-list-in-reverse-order/1
