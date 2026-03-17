// Code to find maximum number of pages can buy without exceeding the total cost of x ~ coded by vHiren
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// O(N*GK) & O(GK) : Where GK = given_k
int solveBy1DTable(const vector<int>& nums, const vector<int>& cost, int given_k) {
    vector<int> nextRow(given_k + 1, 0), currRow(given_k + 1, 0); 
    
    for(int i = nums.size() - 1; i >= 0; --i) {
        for(int k = 1; k <= given_k; ++k) {
            int skipPages = nextRow[k];
            int buyPages = cost[i] <= k 
                            ? nums[i] + nextRow[k - cost[i]]
                            : 0;
            currRow[k] = max(skipPages, buyPages);  
        }
        swap(nextRow, currRow);
    }
    
    return nextRow[given_k];
}

// Driver code
int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(nullptr);

    int n, x;
    cin >> n >> x;

    vector<int> prices(n), pages(n);
    for(int& p : prices) cin >> p;
    for(int& p : pages)  cin >> p;

    cout << solveBy1DTable(pages, prices, x);

    return 0;
}
// Link: https://cses.fi/problemset/task/1158/
