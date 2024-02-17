// Program to perform the "range sum queries" using "fenwick tree / binary indexed tree" ~ coded by Hiren
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class NumArray {
private:
    vector<int>& inputArray;
    int N;   

    // O(N) Space for "BIT" array: Where N is the size of the "input array" 
    vector<int> BIT;

    // O(LogN) Time for each operation : Where N is the size of the "input array"
    void update(int index, int val) {
        while(index <= N) {
            BIT[index] += val;
            index += index & (-index);
        }
    }

    // O(LogN) Time for each operation : Where N is the size of the "input array"
    int getSum(int index) {
        int sum = 0;

        while(index) {
            sum += BIT[index];
            index = index & (index-1);
        }

        return sum;
    }

public:
    // O(NLogN) Time for "BIT" construction : Where N is the size of the "input array"
    NumArray(vector<int>& nums) : inputArray(nums), N(nums.size()), BIT(nums.size()+1, 0) {
        for(int i=1; i<=N; ++i) {
            update(i, inputArray[i-1]);
        }
    }
    
    // O(KLogN) Time for all operations : Where K is the number of calls made to the "sumRange()" and N is the size of the "input array"
    int sumRange(int L, int R) {
        return getSum(R+1) - getSum(L);
    }
};

// Driver code
int main() {
    // Tracks the user wants to perform the operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of the array
        int N;
        cout<<"Enter the size of the array: ";
        cin>>N;

        // Check the given size is valid or not
        if(N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        // Stores the array values
        vector<int> nums(N);
        
        // Input the array values
        cout<<"Enter the values of the array: ";
        for(int i=0; i<N; i++) {
            cin>>nums[i];
        }

        // Input the range value
        int L, R;
        cout<<"\nEnter the range value (0-based indexing): ";
        cin>>L>>R;

        NumArray numArray = NumArray(nums);

        // Section to hit the range sum query
        if(L > -1 && R < N && L <= R && R >= L) {
            int rangeSum = numArray.sumRange(L, R);
            cout<<"The sum of range ["<<L<<", "<<R<<"] is : "<<rangeSum;
        }
        else {
            cout<<"Enter a valid range, application expects a range within the size of the array!\n";
            return 0;
        }

        // Input section to control the flow of iterations of the application
        char userChoise;
        cout<<"\n\nPress \'Y\' to perform the same operation on an another array, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'Y' ? true : false);
    }

    return 0;
}
/*
    Topics: Array | Design | Binary Indexed Tree | Segment Tree
    Link: https://leetcode.com/problems/range-sum-query-immutable/description/
*/
