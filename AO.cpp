#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cfloat> // For FLT_MAX

using namespace std;

#define ROW 5
#define COL 5

typedef pair<int, int> Pair;

struct cell {
    int parent_i, parent_j;
    double f, g, h;
};

bool isValid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col) {
    return grid[row][col] == 1;
}

bool isDestination(int row, int col, Pair dest) {
    return (row == dest.first && col == dest.second);
}

double calculateHValue(int row, int col, Pair dest) {
    return sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second));
}

void tracePath(cell cellDetails[][COL], Pair dest) {
    cout << "The Path is ";
    int row = dest.first;
    int col = dest.second;

    vector<Pair> path;

    while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
        path.push_back(make_pair(row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    path.push_back(make_pair(row, col));

    while (!path.empty()) {
        Pair p = path.back();
        path.pop_back();
        cout << "(" << p.first << "," << p.second << ") ";
    }
    cout << endl;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest) {
    if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) {
        cout << "Source or destination is invalid" << endl;
        return;
    }

    if (!isUnBlocked(grid, src.first, src.second) || !isUnBlocked(grid, dest.first, dest.second)) {
        cout << "Source or destination is blocked" << endl;
        return;
    }

    if (isDestination(src.first, src.second, dest)) {
        cout << "We are already at the destination" << endl;
        return;
    }

    cell cellDetails[ROW][COL];

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cellDetails[i][j].f = FLT_MAX;
            cellDetails[i][j].g = FLT_MAX;
            cellDetails[i][j].h = FLT_MAX;
            cellDetails[i][j].parent_i = -1;
            cellDetails[i][j].parent_j = -1;
        }
    }

    int i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;

    priority_queue<pair<double, Pair>, vector<pair<double, Pair>>, greater<pair<double, Pair>>> openList;

    openList.push(make_pair(0.0, src));

    vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));

    bool foundDest = false;

    while (!openList.empty()) {
        pair<double, Pair> p = openList.top();
        openList.pop();

        i = p.second.first;
        j = p.second.second;
        closedList[i][j] = true;

        for (int row = -1; row <= 1; ++row) {
            for (int col = -1; col <= 1; ++col) {
                if (row == 0 && col == 0) continue;
                int newRow = i + row;
                int newCol = j + col;
                if (isValid(newRow, newCol) && isUnBlocked(grid, newRow, newCol) && !closedList[newRow][newCol]) {
                    double gNew = cellDetails[i][j].g + 1.0;
                    double hNew = calculateHValue(newRow, newCol, dest);
                    double fNew = gNew + hNew;
                    if (cellDetails[newRow][newCol].f == FLT_MAX || cellDetails[newRow][newCol].f > fNew) {
                        openList.push(make_pair(fNew, make_pair(newRow, newCol)));
                        cellDetails[newRow][newCol].f = fNew;
                        cellDetails[newRow][newCol].g = gNew;
                        cellDetails[newRow][newCol].h = hNew;
                        cellDetails[newRow][newCol].parent_i = i;
                        cellDetails[newRow][newCol].parent_j = j;
                    }
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
