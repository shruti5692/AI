#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

struct Edge {
    int destination;
    int weight;
};

struct Node {
    int id;
    vector<Edge> edges;
};

// Function to perform Best-First Search from start node to target node
void bestFirstSearch(const vector<Node>& graph, int start, int target) {
    // Priority queue to select the node with the smallest weight first
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // Set to keep track of visited nodes
    unordered_set<int> visited;

    // Start with the initial node
    pq.push({0, start});
    visited.insert(start);

    // Continue searching until the queue is empty
    while (!pq.empty()) {
        int current = pq.top().second;
        int distance = pq.top().first;
        pq.pop();

        // Print the current node being processed
        cout << "Processing node " << current << " with distance " << distance << endl;

        // Check if the target node is reached
        if (current == target) {
            cout << "Target found at position " << current << "!" << endl;
            return;
        }

        // Explore all adjacent nodes (neighbors)
        for (const Edge& edge : graph[current].edges) {
            int neighbor = edge.destination;
            int weight = edge.weight;

            // If the neighbor has not been visited, add it to the queue
            if (visited.find(neighbor) == visited.end()) {
                cout << "  Visiting neighbor " << neighbor << " with edge weight " << weight << endl;
                pq.push({weight, neighbor});
                visited.insert(neighbor);
            }
        }
    }

    // If the target node was not found
    cout << "Target not found!" << endl;
}

int main() {
    int numNodes, numEdges;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;
    cout << "Enter the number of edges: ";
    cin >> numEdges;

    vector<Node> graph(numNodes);

    // Initialize nodes with their IDs
    for (int i = 0; i < numNodes; ++i) {
        graph[i].id = i;
    }

    // Read edges from the user
    cout << "Enter the edges (source destination weight) one per line:" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph[source].edges.push_back({destination, weight});
    }

    int start, target;
    cout << "Enter the start node: ";
    cin >> start;
    cout << "Enter the target node: ";
    cin >> target;

    // Print initial message
    cout << "Starting Best-First Search from node " << start << " to node " << target << endl;

    // Call the search function
    bestFirstSearch(graph, start, target);

    return 0;
}

/*
Enter the number of nodes: 5
Enter the number of edges: 7
Enter the edges (source destination weight) one per line:
0 1 2
0 2 4
1 3 1
1 4 7
2 4 3
3 5 5
4 5 1
Enter the start node: 0
Enter the target node: 5
Starting Best-First Search from node 0 to node 5
Processing node 0 with distance 0
  Visiting neighbor 1 with edge weight 2
  Visiting neighbor 2 with edge weight 4
Processing node 1 with distance 2
  Visiting neighbor 3 with edge weight 1
  Visiting neighbor 4 with edge weight 7
Processing node 3 with distance 1
  Visiting neighbor 5 with edge weight 5
Processing node 2 with distance 4
Processing node 5 with distance 5
Target found at position 5!*/