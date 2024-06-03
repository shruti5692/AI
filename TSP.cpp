#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

pair<int, vector<int>> travellingSalesmanProblem(vector<vector<int>>& graph, int s) {
    int V = graph.size();
    vector<int> vertex;
    for (int i = 0; i < V; ++i) {
        if (i != s) {
            vertex.push_back(i);
        }
    }

    int min_path = INT_MAX;
    vector<int> best_permutation;

    do {
        int current_pathweight = 0;
        int k = s;
        for (int i : vertex) {
            current_pathweight += graph[k][i];
            k = i;
        }
        current_pathweight += graph[k][s];

        if (current_pathweight < min_path) {
            min_path = current_pathweight;
            best_permutation = vertex;
        }
    } while (next_permutation(vertex.begin(), vertex.end()));

    vector<int> shortest_path = {s};
    shortest_path.insert(shortest_path.end(), best_permutation.begin(), best_permutation.end());
    shortest_path.push_back(s);

    return {min_path, shortest_path};
}

int main() {
    int V;
    cout << "Enter the number of vertices in the graph: ";
    cin >> V;
    
    vector<vector<int>> graph(V, vector<int>(V));
    cout << "Enter the adjacency matrix of the graph:" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            cin >> graph[i][j];
        }
    }

    int s;
    cout << "Enter the source vertex (0-based indexing): ";
    cin >> s;

    auto [min_cost, shortest_path] = travellingSalesmanProblem(graph, s);

    cout << "Minimum cost: " << min_cost << endl;
    cout << "Shortest path: ";
    for (size_t i = 0; i < shortest_path.size(); ++i) {
        if (i > 0) {
            cout << " -> ";
        }
        cout << shortest_path[i];
    }
    cout << endl;

    return 0;
}

/*
Enter the number of vertices in the graph: 4
Enter the adjacency matrix of the graph:
0 10 15 20
10 0 15 30
15 25 0 35
20 30 35 0
Enter the source vertex (0-based indexing): 0
Minimum cost: 80
Shortest path: 0 -> 1 -> 2 -> 3 -> 0
*/