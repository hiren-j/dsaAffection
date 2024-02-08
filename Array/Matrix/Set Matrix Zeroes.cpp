// Program to set the entire row and column to 0 if the element is 0 ~ coded by Hiren
#include <unordered_set>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// Solution class
class Solution {
public:
    // #1 Method to set the zeroes, using 2d buffer - O(M*N*(M+N)) & O(M*N)
    void setZeroes_V1(vector<vector<int>>& matrix) {
        int M = matrix.size(), N = matrix[0].size();

        // Stores the values of the given matrix
        vector<vector<int>> newMatrix = matrix;

        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If the element is 0
                if(newMatrix[R][C] == 0) {
                    // Set the entire column to 0
                    for(int C=0; C<N; C++) {
                        matrix[R][C] = 0;
                    }
                    // Set the entire row to 0
                    for(int R=0; R<M; R++) {
                        matrix[R][C] = 0;
                    }
                }
            }
        }
    }

    // #2 Method to set the zeroes, using set - O(M*N*(M+N)) & O(M+N)
    void setZeroes_V2(vector<vector<int>>& matrix) {
        int M = matrix.size(), N = matrix[0].size();

        unordered_set<int> columns; // Stores the "index of the column" which have value 0 in it
        unordered_set<int> rows;    // Stores the "index of the row" which have value 0 in it    
        
        for(int R=0; R<M; R++)
            for(int C=0; C<N; C++) 
                // If the element is 0 then store the index of the "row" and "column"
                if(matrix[R][C] == 0)
                    rows.insert(R), columns.insert(C);

        for(int R=0; R<M; R++) 
            for(int C=0; C<N; C++) 
                // If its the index of "row" or "column" that we're looking for then set the element to 0
                if(rows.count(R) || columns.count(C)) 
                    matrix[R][C] = 0;         
    }

    // #3 Method to set the zeroes, using 1d buffer - O(M*N) & O(M+N)
    void setZeroes_V3(vector<vector<int>>& matrix) {
        int M = matrix.size(), N = matrix[0].size();

        vector<bool> columns(N); // Stores the "index of the column" which have value 0 in it
        vector<bool> rows(M);    // Stores the "index of the row" which have value 0 in it    
        
        for(int R=0; R<M; R++)
            for(int C=0; C<N; C++) 
                // If the element is 0 then store the index of the "row" and "column"
                if(matrix[R][C] == 0)
                    rows[R] = 1, columns[C] = 1;

        for(int R=0; R<M; R++) 
            for(int C=0; C<N; C++) 
                // If its the index of "row" or "column" that we're looking for then set the element to 0
                if(rows[R] || columns[C]) 
                    matrix[R][C] = 0;         
    }

    // #4 Method to set the zeroes, using constant auxiliary space - O(M*N) & O(1)
    void setZeroes_V4(vector<vector<int>>& matrix) {
        int M = matrix.size(), N = matrix[0].size();

        // Tracks the value of the "0th column / first column" of the "0th row / first row"
        int col0 = 1;
        
        // Iterate and mark the index of "rows" and "columns" which have element 0 in them
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                // If the element is 0 then mark the "row" and "column" of it
                if(matrix[R][C] == 0) {
                    matrix[R][0] = 0;
                    (C == 0) ? col0 = 0 : matrix[0][C] = 0;
                }
            }
        }

        // Iterate and set the zeroes
        for(int R=1; R<M; R++) {
            for(int C=1; C<N; C++) {
                // If the element is 1 then check the current "row or column" have any 0 in it
                if(matrix[R][C] != 0) {
                    // If it contains then set the element to 0
                    if(matrix[R][0] == 0 || matrix[0][C] == 0) {
                        matrix[R][C] = 0;
                    }
                }
            }
        }

        // If the first column contains 0 in it then set the entire column to 0
        if(matrix[0][0] == 0) {
            for(int C=0; C<N; C++) {
                matrix[0][C] = 0;
            }
        }

        // If the first row contains 0 in it then set the entire row to 0
        if(col0 == 0) {
            for(int R=0; R<M; R++) {
                matrix[R][0] = 0;
            }
        }
    }
};

// Driver code
int main() {
    // Tracks the user wants to peform operation or not
    bool userWantsOperation = true;

    while(userWantsOperation) {
        // Handles console clearance for both "windows" and "linux" user
        system("cls || clear");

        // Input the size of row and column
        int M, N;
        cout<<"Enter the number of rows of the matrix: " ; cin>>M;
        cout<<"Enter the number of columns of the matrix: "; cin>>N;

        // Check the given value is valid or not
        if(M <= 0 || N <= 0) {
            cout<<"Enter a valid value, application expects a positive integer!";
            return 0;
        }

        // Stores the values of the matrix
        vector<vector<int>> matrix(M, vector<int>(N, 0));
        cout<<"\nEnter the values of the matrix:\n";

        // Input the values of the matrix
        for(int R=0; R<M; R++) {
            for(int C=0; C<N; C++) {
                cin>>matrix[R][C];
            }
        }

        // Call to set the zeroes in the matrix
        Solution solution;
        solution.setZeroes_V4(matrix);
        
        // Print the values of the matrix
        cout<<"\nMatrix after setting the zeros:\n";
        for(int R=0; R<M; R++) {
            cout<<"[";
            for(int C=0; C<N; C++) {
                cout<<matrix[R][C];
                if(C < N-1) cout<<", ";
            }
            cout<<"]\n";
        }

        // Input section to handle the flow of iterations of the application
        char userChoise;
        cout<<"\nPress \'R\' to restart the application, else it will exit automatically: ";
        cin>>userChoise;
        userWantsOperation = (userChoise == 'R') ? true : false ;
    }

    return 0;
}
/* 
    Topics: Array | Hash Table | Matrix 
    Link: https://leetcode.com/problems/set-matrix-zeroes/    
*/
