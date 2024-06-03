#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<int>>& board, int row, int col, int n) {
    // Check if there's a queen in the same row
    for (int i = 0; i < col; ++i)
        if (board[row][i])
            return false;

    // Check upper diagonal on left side
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j])
            return false;

    // Check lower diagonal on left side
    for (int i = row, j = col; j >= 0 && i < n; ++i, --j)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQueensUtil(vector<vector<int>>& board, int col, int n) {
    // If all queens are placed, return true
    if (col >= n)
        return true;

    // Consider this column and try placing this queen in all rows one by one
    for (int i = 0; i < n; ++i) {
        if (isSafe(board, i, col, n)) {
            board[i][col] = 1; // Place queen

            // Recur to place the rest of the queens
            if (solveNQueensUtil(board, col + 1, n))
                return true;

            // If placing queen in board[i][col] doesn't lead to a solution, then remove queen from board[i][col]
            board[i][col] = 0;
        }
    }

    // If queen can't be placed in any row in this column col, then return false
    return false;
}

void solveNQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));

    if (solveNQueensUtil(board, 0, n)) {
        // Print the solution
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                cout << board[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "Solution does not exist for the given board size." << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of queens (n): ";
    cin >> n;

    solveNQueens(n);

    return 0;
}
