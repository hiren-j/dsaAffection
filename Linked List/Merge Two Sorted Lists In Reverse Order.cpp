// Program to merge two sorted lists in decreasing order ~ coded by Hiren
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// List template
class ListNode {
public:
    int val;
    ListNode* next;

    // Initialize constructor
    ListNode(int val, ListNode* next)
    :
    val(val), next(next) {}

    // Method to input the list - O(K) & O(K) : Where N is the size of the list.
    ListNode* inputList(int number) {
        // Input the size of the list.
        int size;
        cout<<"Enter the number of nodes for the list"<<number<<": ";
        cin>>size;

        // Check the given size is valid or not.
        if(size <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!\n";
            return nullptr;
        }

        ListNode* headNode = nullptr; // Tracks the head node of the list.
        ListNode* tailNode = nullptr; // Tracks the last node of the list.

        // Input the nodes value for the list.
        for(int node=1; node<=size; ++node) {
            int key;
            cout<<"Enter the value of the "<<node<<"th node: ";
            cin>>key;
            headNode->insertNode(headNode, tailNode, key);
        }

        // Return the head node of the list.
        return headNode;
    }

    // Method to insert a node in the list - O(1) & O(1)
    void insertNode(ListNode*& headNode, ListNode*& tailNode, int key) {
        ListNode* newNode = new ListNode(key, nullptr);
        if(!headNode)
            headNode = newNode, tailNode = newNode;
        else   
            tailNode->next = newNode, tailNode = tailNode->next;
        tailNode->next = nullptr;
    }

    // Method to delete the list - O(K) & O(1) : Where K is the size of tht "list".
    void deleteList(ListNode*& headNode) {
        while(headNode) {
            ListNode* nextNode = headNode->next;
            headNode = nullptr;
            delete headNode;
            headNode = nextNode;
        }
    }

    // Method to print the list - O(K) & O(1) : Where K is the size of the "list".
    void printList(ListNode* headNode) {
        while(headNode) {
            cout<<headNode->val<<' ';
            headNode = headNode->next; 
        }
    }
};

// #1 Solution class:
class Solution_V1 {
    // Method helper
    static bool comparator(ListNode* nodeA, ListNode* nodeB) {
        return nodeA->val < nodeB->val;
    }
    
public:
    // Method to merge two sorted lists in reverse order, using sorting with buffer - O(NLogN + MLogM) & O(N+M) : Where N is the size of "list1" and M of "list2".
    ListNode* mergeTwoLists(ListNode* headNodeA, ListNode* headNodeB) {
        // Edge case: When both the lists are empty.
        if(!headNodeA && !headNodeB)
            return nullptr;

        // Stores all the nodes of both the lists.
        vector<ListNode*> buffer;
        
        // Iterate the lists.
        while(headNodeA || headNodeB) {
            // If the node of "list1" exist then store it to the buffer.
            if(headNodeA)
                buffer.push_back(headNodeA), headNodeA = headNodeA->next;
            // If the node of "list2" exist then store it to the buffer.
            if(headNodeB)
                buffer.push_back(headNodeB), headNodeB = headNodeB->next;
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
    ListNode* mergeTwoLists(ListNode* headNodeA, ListNode* headNodeB) {
        // Edge case: When both the lists are empty.
        if(!headNodeA && !headNodeB)
            return nullptr;
        
        vector<ListNode*> list1; // Stores all the nodes of "list1".
        vector<ListNode*> list2; // Stores all the nodes of "list2".
        
        // Iterate the lists.
        while(headNodeA || headNodeB) {
            // If the node of "list1" exist then store it to the corresponding buffer.
            if(headNodeA)
                list1.push_back(headNodeA), headNodeA = headNodeA->next;
            // If the node of "list2" exist then store it to corresponding buffer.
            if(headNodeB)
                list2.push_back(headNodeB), headNodeB = headNodeB->next;
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
    ListNode* mergeTwoLists(ListNode* headNodeA, ListNode* headNodeB) {
        // Edge case: When both the lists are empty.
        if(!headNodeA && !headNodeB)
            return nullptr;
            
        headNodeA = reverseList(headNodeA); // Reverse the "list1" and store the head node of it.
        headNodeB = reverseList(headNodeB); // Reverse the "list2" and store the head node of it.
        
        // Set the "merge list" and return the head node of it.
        return setMergeList(headNodeA, headNodeB);
    }
    
private:
    // Method helper
    ListNode* setMergeList(ListNode* headNodeA, ListNode* headNodeB) {
        ListNode* nodeListA = headNodeA; // Tracks the nodes of "list1".
        ListNode* nodeListB = headNodeB; // Tracks the nodes of "list2".
        ListNode* resHead    = nullptr;  // Tracks the head node of the "merge list".
        ListNode* resCurrent = nullptr;  // Tracks the nodes of the "merge list".
        
        // Iterate the lists.
        while(nodeListA && nodeListB) {
            ListNode* nextNodeA = nodeListA->next;
            ListNode* nextNodeB = nodeListB->next;
            // If the node value of "list1" is greater then set it to the "merge list".
            if(nodeListA->val > nodeListB->val) {
                updateLinks(nodeListA, resHead, resCurrent);
                nodeListA = nextNodeA;
            }
            // Else when the node value of "list2" is greater then set it to the "merge list".
            else {
                updateLinks(nodeListB, resHead, resCurrent);
                nodeListB = nextNodeB;
            }
        }
        
        // If the nodes of "list1" are remaining then set them to the "merge list".
        while(nodeListA) {
            ListNode* nextNodeA = nodeListA->next;
            updateLinks(nodeListA, resHead, resCurrent);
            nodeListA = nextNodeA;
        }
        
        // If the nodes of "list2" are remaining then set them to the "merge list".
        while(nodeListB) {
            ListNode* nextNodeB = nodeListB->next;
            updateLinks(nodeListB, resHead, resCurrent);
            nodeListB = nextNodeB;
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
};

// #4 Solution class:
class Solution_V4 {
public:
    // Method to merge two sorted lists in reverse order, using constant auxiliary space - O(N+M) & O(1) : Where N is the size of "list1" and M of "list2".
    ListNode* mergeTwoLists(ListNode* headNodeA, ListNode* headNodeB) {
        // Edge case: When both the lists are empty.
        if(!headNodeA && !headNodeB)
            return nullptr;
            
        ListNode* nodeListA = headNodeA; // Tracks the nodes of "list1".
        ListNode* nodeListB = headNodeB; // Tracks the nodes of "list2".
        ListNode* resHead    = nullptr;  // Tracks the head node of the "merge list".
        ListNode* resCurrent = nullptr;  // Tracks the nodes of the "merge list".
        
        // Iterate the lists.
        while(nodeListA && nodeListB) {
            ListNode* nextNodeA = nodeListA->next;
            ListNode* nextNodeB = nodeListB->next;
            // If the node value of "list2" is greater then set it to the "merge list".
            if(nodeListA->val < nodeListB->val) {
                updateLinks(nodeListA, resHead, resCurrent);
                nodeListA = nextNodeA;
            }
            // Else when the node value of "list1" is greater then set it to the "merge list".
            else {
                updateLinks(nodeListB, resHead, resCurrent);
                nodeListB = nextNodeB;
            }
        }
        
        // If the nodes of "list1" are remaining then set them to the "merge list".
        while(nodeListA) {
            ListNode* nextNodeA = nodeListA->next;
            updateLinks(nodeListA, resHead, resCurrent);
            nodeListA = nextNodeA;
        }
        
        // If the nodes of "list2" are remaining then set them to the "merge list".
        while(nodeListB) {
            ListNode* nextNodeB = nodeListB->next;
            updateLinks(nodeListB, resHead, resCurrent);
            nodeListB = nextNodeB;
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

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not.
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user.
        system("cls || clear");

        // Input the lists and store the head node of them.
        ListNode* headNodeA = headNodeA->inputList(1); cout<<'\n';
        ListNode* headNodeB = headNodeA->inputList(2);
        
        // Print call
        if(headNodeA) {
            cout<<"\nList1: ";
            headNodeA->printList(headNodeA);
        }

        // Print call
        if(headNodeB) {
            cout<<"\nList2: ";
            headNodeB->printList(headNodeB);
        }

        // Merge call
        Solution_V4 solution;
        ListNode* mergeHead = solution.mergeTwoLists(headNodeA, headNodeB);

        // Print call
        if(mergeHead) {
            cout<<"\nMerge list: ";
            mergeHead->printList(mergeHead);
        }

        // Deletion call
        headNodeA->deleteList(headNodeA);
        headNodeB->deleteList(headNodeB);
        mergeHead->deleteList(mergeHead);

        // Input section to handle the flow of iterations of the application.
        char userChoise;
        cout<<"\n\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false ;
    }

    return 0;
}
/*
    Topics: Linked List | Two Pointers
    Link: https://www.geeksforgeeks.org/problems/merge-2-sorted-linked-list-in-reverse-order/1
*/
