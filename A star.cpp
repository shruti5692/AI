#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cfloat>

using namespace std;

#define ROW 5
#define COL 5

typedef pair<int, int> Pair;

// Define cell structure to hold f, g, h values
struct cell {
    int parent_i, parent_j;
    double f, g, h;
};

// Check if cell is valid (inside grid)
bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

// Check if cell is unblocked
bool isUnBlocked(int grid[][COL], int row, int col) {
    return grid[row][col] == 1;
}

// Check if cell is destination
bool isDestination(int row, int col, Pair dest) {
    return (row == dest.first && col == dest.second);
}

// Calculate H value (Heuristic - Euclidean distance)
double calculateHValue(int row, int col, Pair dest) {
    return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
}

// Trace path from destination to source
void tracePath(cell cellDetails[][COL], Pair dest) {
    cout << "The Path is ";
    int row = dest.first;
    int col = dest.second;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        cout << "(" << row << "," << col << ") ";
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }
    cout << "(" << row << "," << col << ")" << endl;
}

// A* search algorithm
void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    // Check if source and destination cells are valid
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) {
        cout << "Source or destination is invalid" << endl;
        return;
    }

    // Check if source and destination cells are unblocked
    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)) {
        cout << "Source or destination is blocked" << endl;
        return;
    }

    // Check if source cell is destination cell
    if (isDestination(src.first, src.second, dest)) {
        cout << "We are already at the destination" << endl;
        return;
    }

    // Create cell details array to store f, g, h values and parent cells
    cell cellDetails[ROW][COL];

    // Initialize cell details
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cellDetails[i][j].f = DBL_MAX;
            cellDetails[i][j].g = DBL_MAX;
            cellDetails[i][j].h = DBL_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    // Initialize starting cell
    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    // Create priority queue to store open list
    priority_queue<pair<double, Pair>, vector<pair<double, Pair>>, greater<pair<double, Pair>>> openList;

    // Insert starting cell into open list
    openList.push(make_pair(0.0, src));

    // Flag to indicate if destination is found
    bool foundDest = false;

    // Iterate until open list is empty
    while (!openList.empty()) {
        // Get cell with minimum f value from open list
        pair<double, Pair> p = openList.top();
        openList.pop();

        // Get coordinates of current cell
        i = p.second.first;
        j = p.second.second;

        // Mark current cell as closed
        cellDetails[i][j].f = -1.0;

        // Generate all possible moves from current cell
        for (int row = -1; row <= 1; ++row) {
            for (int col = -1; col <= 1; ++col) {
                // Skip current cell
                if (row == 0 && col == 0) continue;
                int newRow = i + row;
                int newCol = j + col;
                // Check if new cell is valid and unblocked
                if (isValid(newRow, newCol) && isUnBlocked(grid, newRow, newCol)) {
                    // Update g, h, f values if necessary
                    double gNew = cellDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;
                    if (cellDetails[newRow][newCol].f == DBL_MAX || cellDetails[newRow][newCol].f > fNew) {
                        openList.push(make_pair(fNew, make_pair(newRow, newCol)));
                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                    }
                    // Check if destination cell is found
                    if (isDestination(newRow, newCol, dest)) {
                        cout << "The destination cell is found" << endl;
                        tracePath(cellDetails, dest);
                        foundDest = true;
                        return;
                    }
                }
            }
        }
    }

    // Check if destination cell is not found
    if (!foundDest)
        cout << "Failed to find the Destination Cell" << endl;
}

int main() {
    int grid[ROW][COL] = {
        {1, 0, 1, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1}
    };

    Pair src = make_pair(0, 0);
    Pair dest = make_pair(4, 4);

    aStarSearch(grid, src, dest);

    return 0;
}
