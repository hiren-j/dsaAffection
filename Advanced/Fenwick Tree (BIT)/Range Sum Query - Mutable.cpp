// Program to perform the "range sum queries" using "fenwick tree / binary indexed tree" ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Class to implement the "BIT and its operations":
class NumArray {
    vector<int>& inputArray;
    int N;

    // O(N) Space for "BIT" array: Where N is the size of the "input array" 
    vector<int> BIT;

    // O(LogN) Time for each operation : Where N is the size of the "input array"
    void updateBIT(int index, int val) {
        index++;
        while(index <= N) {
            BIT[index] += val;
            index += index & (-index);
        }
    }

    // O(LogN) Time for each operation : Where N is the size of the "input array"
    int getSum(int index) {
        int cumulativeSum = 0;
        index++;

        while(index > 0) {
            cumulativeSum += BIT[index];
            index -= index & (-index);  // Alternative: index = index & (index-1); 
        }

        return cumulativeSum;
    }

public:
    // O(NLogN) Time for "BIT" construction : Where N is the size of the "input array"
    NumArray(vector<int>& nums) : inputArray(nums), BIT(nums.size()+1, 0), N(nums.size()) {
        for(int i=0; i<N; i++) {
            updateBIT(i, nums[i]);
        }
    }

    // O(KLogN) Time for all operations : Where K is the number of calls made to the "update()" and N is the size of the "input array"
    void update(int index, int val) {
        int diff = val - inputArray[index];
        inputArray[index] = val;
        updateBIT(index, diff);
    }

    // O(KLogN) Time for all operations : Where K is the number of calls made to the "sumRange()" and N is the size of the "input array"
    int sumRange(int L, int R) {
        return getSum(R) - getSum(L-1);
    }
};

// Class to implement the methods of "array creation" and "performing queries":
class ArrayQueryHandler {
public:
    // Method to create the array - O(N) & O(N) : Where N is the size of the "input array" 
    vector<int> getArray(void) {
        // Input the array size
        int N;
        cout<<"Enter the size of the array: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0) {    
            cout<<"Enter a valid size, application expects a positive integer!";
            exit(0);
        }

        // Stores the array values
        vector<int> nums(N);

        // Input section for array values
        cout<<"Enter the values of the array: "; 
        for(int i=0; i<N; i++) {
            cin>>nums[i];
        }

        // Return the array
        return nums;
    }

    // Method to perform the queries on the array - O(numOperations * LogN) & O(1) : Where N is the size of the "input array"
    void performQueries(vector<int>& nums) {
        int N = nums.size();
        NumArray numArray = NumArray(nums);

        // Input the number of queries the user wants to perform
        int numOperations;
        cout<<"Enter the number of queries to perform: ";
        cin>>numOperations;

        // When the given value is valid then display the prompts
        if(numOperations > 0) {
            cout<<": Range sum query (Press 1)";
            cout<<"\n: Update query (Press 2)\n";
        }

        while(numOperations-- > 0) {
            // Input the query related choise of the user
            int choise; 
            cout<<"\nEnter choise: ";
            cin>>choise;

            // Switch to the particular choise and work on it
            switch(choise) {
                // Case to handle the instructions of "range sum query"
                case 1:
                    // Input section for range value
                    int L, R;
                    cout<<"Enter the range value (0-based indexing): ";
                    cin>>L>>R;

                    // Section to hit the range sum query
                    if(L > -1 && R < N && L <= R && R >= L) {
                        int rangeSum = numArray.sumRange(L, R);
                        cout<<"The sum of range ["<<L<<", "<<R<<"] is: "<<rangeSum<<'\n';
                    }
                    else {
                        cout<<"Enter a valid range, application expects a range within the size of the array!\n";
                    }
                    break;

                // Case to handle the instructions of "update query"
                case 2: 
                    // Input section for the "index" and "new value"
                    int index, val;
                    cout<<"Enter the index value for updation (0-based indexing): ";
                    cin>>index;
                    cout<<"Enter the new value for updation: ";
                    cin>>val;

                    // Section to hit the update query
                    if(index > -1 && index < N) {
                        numArray.update(index, val);
                    }
                    else {
                        cout<<"Enter a valid index, application expects an index within the size of the array!\n";
                    }
                    break;

                // Handles the edge cases, when both the above cases are not performed
                default:
                    cout<<"Please enter a valid choise!\n";
            }
        }
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        ArrayQueryHandler aqh;

        cout<<"\n:-----------------------First Section-----------------------:\n\n";

        // Call to create an array
        vector<int> nums = aqh.getArray();
        
        cout<<"\n\n:-----------------------Operation Section-----------------------:\n\n";
        
        // Call the perform the "range sum" and "update" queries on the array
        aqh.performQueries(nums);

        cout<<"\n\n:-----------------------Last Section-----------------------:\n";

        // Input section to control the flow of iterations of the application
        char userChoise;
        cout<<"\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Design | Binary Indexed Tree | Segment Tree
    Link: https://leetcode.com/problems/range-sum-query-immutable/description/
*/
