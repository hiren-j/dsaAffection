// Program to find the node at which the two linked lists intersects ~ coded by Hiren
#include <iostream>
#include <unordered_set>
using namespace std;

// List template
class ListNode {
public:
    int data;
    ListNode* next;

    // Init constructor
    ListNode(int data, ListNode* next = nullptr) 
    : 
    data(data), next(next) {};

    // Init destructor
    ~ListNode() {
        if(next) {
            delete next;
        }
    };
};

// #1 Solution class:
class Solution_V1 {
public:
    // Method to find the intersection node, using (stl) set - O(M+N) & O(M) : Where M let be the length of "list1" and N of "list2"
    ListNode* getIntersectionNode(ListNode* headNodeA, ListNode* headNodeB) {
        // Stores the nodes of "list1"
        unordered_set<ListNode*> st;

        // Iterate the "list1" and insert all of its nodes to the set
        while(headNodeA) {
            st.insert(headNodeA);
            headNodeA = headNodeA->next;
        }

        // Iterate the "list2" and check for the presence of intersection node in the set
        while(headNodeB) {
            if(st.count(headNodeB))
                return headNodeB;

            headNodeB = headNodeB->next;
        }

        // When the list is empty or no intersection node exist
        return nullptr;
    }
};
// Note: Brute force solution can be made using nested loops

// #2 Solution class:
class Solution_V2 {  
public:
    // Method to find the intersection node, using constant auxiliary space - O(M+N) & O(1) : Where M let be the length of "list1" and N of "list2"
    ListNode* getIntersectionNode(ListNode* headNodeA, ListNode* headNodeB) {
        int lengthA = listLength(headNodeA); // Find and store the length of "list1" 
        int lengthB = listLength(headNodeB); // Find and store the length of "list2"

        // Skip the additional nodes of "list1" to set both the lists of equal sized
        while(headNodeA && lengthA > lengthB)
            lengthA--, headNodeA = headNodeA->next;

        // Skip the additional nodes of "list2" to set both the lists of equal sized
        while(headNodeB && lengthA < lengthB)
            lengthB--, headNodeB = headNodeB->next;

        // Iterate both the lists and find the intersection node
        while(headNodeA && headNodeB) {
            if(headNodeA == headNodeB)
                return headNodeA;

            headNodeA = headNodeA->next;
            headNodeB = headNodeB->next;
        }

        // When the list is empty or no intersection node exist
        return nullptr;
    }

private:
    // Method helper to find the length of the list - O(K) & O(1) : Where K let be the length of given list
    int listLength(ListNode* headNode) {
        int length = 0;

        while(headNode)
            length++, headNode = headNode->next;

        return length;
    }
};

// Method to print the list - O(K) & O(1) : Where K let be the length of given list
void printList(ListNode* headNode) {
    while(headNode)
        cout<<headNode->data<<' ',
        headNode = headNode->next;
        
    cout<<'\n';
}

// Driver code
int main() {
    // Creating "list1", connecting nodes and initializing their data
    ListNode* headNodeA = new ListNode(20, new ListNode(10, new ListNode(8, new ListNode(7, new ListNode(5)))));

    // Creating "list2", connecting nodes and initializing their data
    ListNode* headNodeB = new ListNode(2, headNodeA->next->next);

    // Print call
    printList(headNodeA); printList(headNodeB);

    // Call to find the intersection node
    Solution_V2 obj;
    ListNode* intersectionNode = obj.getIntersectionNode(headNodeA, headNodeB);
    cout<<"The node value at which both the lists intersect is : "<<intersectionNode->data;

    // Remove the link from the intersection node
    headNodeB->next = nullptr;

    // Deletion call
    delete headNodeA; delete headNodeB;

    return 0;
}
// Link: https://leetcode.com/problems/intersection-of-two-linked-lists/
