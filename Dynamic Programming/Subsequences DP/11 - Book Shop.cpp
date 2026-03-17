// Code to find maximum number of pages can buy without exceeding the total prices of x ~ coded by vHiren
#include <iostream>
#include <climits>
#include <vector>
using namespace std;

// O(N*X) & O(X)
int solveBy1DTable(const vector<int>& pages, const vector<int>& prices, int x) {
    vector<int> nextRow(x + 1, 0), currRow(x + 1, 0); 
    
    for(int i = pages.size() - 1; i >= 0; --i) {
        for(int k = 1; k <= x; ++k) {
            int skipPages = nextRow[k];
            int buyPages  = prices[i] <= k 
                            ? pages[i] + nextRow[k - prices[i]]
                            : 0;
            currRow[k] = max(skipPages, buyPages);  
        }
        swap(nextRow, currRow);
    }
    
    return nextRow[x];
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
