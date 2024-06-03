#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to print the Tic Tac Toe board
void printBoard(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << endl;
        if (i < 2) cout << "---------" << endl;
    }
}

// Function to check if a player has won
bool checkWin(const vector<vector<char>>& board, char player) {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

// Function to check if the board is full
bool checkDraw(const vector<vector<char>>& board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == ' ') return false;
        }
    }
    return true;
}

// Function to play the Tic Tac Toe game
void playTicTacToe() {
    vector<vector<char>> board(3, vector<char>(3, ' '));
    char currentPlayer = 'X';

    while (true) {
        // Print the board
        cout << "Current board:" << endl;
        printBoard(board);

        // Get player's move
        int row, col;
        cout << "Player " << currentPlayer << ", enter your move (row and column): ";
        cin >> row >> col;

        // Check if the move is valid
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        // Make the move
        board[row][col] = currentPlayer;

        // Check if the current player has won
        if (checkWin(board, currentPlayer)) {
            cout << "Player " << currentPlayer << " wins!" << endl;
            printBoard(board);
            break;
        }

        // Check if the game is a draw
        if (checkDraw(board)) {
            cout << "It's a draw!" << endl;
            printBoard(board);
            break;
        }

        // Switch to the other player
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

int main() {
    cout << "Welcome to Tic Tac Toe!" << endl;
    playTicTacToe();
    return 0;
}


/*
Welcome to Tic Tac Toe!
Current board:
  |   |  
---------
  |   |  
---------
  |   |  
Player X, enter your move (row and column): 0 2
Current board:
  |   | X
---------
  |   |  
---------
  |   |  
Player O, enter your move (row and column): 1 1
Current board:
  |   | X
---------
  | O |  
---------
  |   |  
Player X, enter your move (row and column): 1 2
Current board:
  |   | X
---------
  | O | X
---------
  |   |  
Player O, enter your move (row and column): 2 2
Current board:
  |   | X
---------
  | O | X
---------
  |   | O
Player X, enter your move (row and column): 2 1
Current board:
  |   | X
---------
  | O | X
---------
  | X | O
Player O, enter your move (row and column): 1 1
Invalid move! Try again.
Current board:
  |   | X
---------
  | O | X
---------
  | X | O
Player O, enter your move (row and column): 0 0
Player O wins!
O |   | X
---------
  | O | X
---------
  | X | O
  
  */