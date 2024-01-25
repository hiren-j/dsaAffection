// Program to perform the "range sum queries" using "fenwick tree / binary indexed tree" ~ coded by Hiren
#include <iostream>
#include <vector>
using namespace std;

class NumArray {
private:
    vector<int>& inputArray;
    int N;   

    // O(N) Space for "BIT" array: Where N is the size of the "input array" 
    vector<int> BIT;

    // O(NLogN) Time for "BIT" construction : Where N is the size of the "input array"
    void constructBIT() {
        for(int i=1; i<=N; ++i) {
            update(i, inputArray[i-1]);
        }
    }

private:
    // O(LogN) Time for each operation : Where N is the size of the "input array"
    void update(int index, int val) {
        while(index <= N) {
            BIT[index] += val;
            index += index & (-index);
        }
    }

    // O(LogN) Time for each operation : Where N is the size of the "input array"
    int getRangeSum(int index) {
        int sum = 0;

        while(index) {
            sum += BIT[index];
            index = index & (index-1);
        }

        return sum;
    }

public:
    NumArray(vector<int>& nums) 
    :
    inputArray(nums), N(nums.size()), BIT(nums.size()+1, 0) {
        constructBIT();
    }
    
    // O(KLogN) Time for all operations : Where K is the number of calls made to the "sumRange()" and N is the size of the "input array"
    int sumRange(int L, int R) {
        return getRangeSum(R+1) - getRangeSum(L);
    }
};

// Driver code
int main() {
    bool userWantsOperation = true;

    while(userWantsOperation) {
        system("clear || cls");
        int N;
        cout<<"Enter the size of the array: ";
        cin>>N;

        if(N <= 0) {
            cout<<"Enter a valid size, application expects a positive integer!";
            return 0;
        }

        vector<int> nums(N);
        
        // Input section for array values
        for(int i=0; i<N; i++) {
            int num;
            cout<<"Enter the "<<i+1<<"th value for the array: ";
            cin>>num;
            nums[i] = num;
        }

        // Input section for range value
        int L, R;
        cout<<"\nEnter the range value (0-based indexing): ";
        cin>>L>>R;

        NumArray numArray = NumArray(nums);

        // Section to hit the range sum query
        if(L > 0 && R < N) {
            int rangeSum = numArray.sumRange(L, R);
            cout<<"\nThe sum of range ["<<L<<", "<<R<<"] is : "<<rangeSum;
        }
        else {
            cout<<"Enter a valid range value, application expects a positive integer!";
            return 0;
        }

        // Section to control the flow of iterations
        char userChoise;
        cout<<"\n\nPress \'Y\' to perform the same operation on an another array, else application will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'Y') ? true : false ;
    }

    return 0;
}
// Link: https://leetcode.com/problems/range-sum-query-immutable/description/
