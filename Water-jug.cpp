#include <iostream>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

struct State {
    int jug1, jug2, steps;
};

bool isGoal(State s, int target) {
    return s.jug1 == target || s.jug2 == target;
}

bool isValid(State s, int maxJug1, int maxJug2) {
    return s.jug1 >= 0 && s.jug1 <= maxJug1 && s.jug2 >= 0 && s.jug2 <= maxJug2;
}

void printSolution(State s) {
    cout << "Solution found in " << s.steps << " steps." << endl;
}

void printState(State s) {
    cout << "Jug1: " << s.jug1 << " Jug2: " << s.jug2 << " Steps: " << s.steps << endl;
}

int solveWaterJug(int jug1Capacity, int jug2Capacity, int target) {
    set<pair<int, int>> visited;
    queue<State> q;
    
    State start = {0, 0, 0};
    q.push(start);
    visited.insert({0, 0});
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        printState(current);
        
        if (isGoal(current, target)) {
            printSolution(current);
            return current.steps;
        }
        
        // Possible next states
        State nextStates[] = {
            {jug1Capacity, current.jug2, current.steps + 1}, // Fill jug1
            {current.jug1, jug2Capacity, current.steps + 1}, // Fill jug2
            {0, current.jug2, current.steps + 1},            // Empty jug1
            {current.jug1, 0, current.steps + 1},            // Empty jug2
            {current.jug1 - min(current.jug1, jug2Capacity - current.jug2), current.jug2 + min(current.jug1, jug2Capacity - current.jug2), current.steps + 1}, // Pour jug1 to jug2
            {current.jug1 + min(current.jug2, jug1Capacity - current.jug1), current.jug2 - min(current.jug2, jug1Capacity - current.jug1), current.steps + 1}  // Pour jug2 to jug1
        };
        
        for (State nextState : nextStates) {
            if (isValid(nextState, jug1Capacity, jug2Capacity) && visited.find({nextState.jug1, nextState.jug2}) == visited.end()) {
                q.push(nextState);
                visited.insert({nextState.jug1, nextState.jug2});
            }
        }
    }
    
    cout << "No solution found." << endl;
    return -1;
}

int main() {
    int jug1Capacity, jug2Capacity, target;
    cout << "Enter the capacity of jug1: ";
    cin >> jug1Capacity;
    cout << "Enter the capacity of jug2: ";
    cin >> jug2Capacity;
    cout << "Enter the target amount of water: ";
    cin >> target;
    
    solveWaterJug(jug1Capacity, jug2Capacity, target);
    
    return 0;
}