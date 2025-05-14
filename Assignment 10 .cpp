//
//  main.cpp
//  Assignment 6
//
//  Created by Kevin Chavez on 5/13/25.
//

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    // Add an edge to the graph
    void addEdge(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // For undirected graph
    }

    // Breadth-First Traversal
    void BFS(int startVertex) {
        std::unordered_map<int, bool> visited;
        std::queue<int> q;

        // Mark the starting vertex as visited and enqueue it
        visited[startVertex] = true;
        q.push(startVertex);

        std::cout << "BFS Traversal: ";

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            std::cout << currentVertex << " ";

            // Visit all adjacent vertices
            for (int adjacentVertex : adjacencyList[currentVertex]) {
                if (!visited[adjacentVertex]) {
                    visited[adjacentVertex] = true;
                    q.push(adjacentVertex);
                }
            }
        }
        std::cout << std::endl;
    }

    // Depth-First Traversal (iterative)
    void DFS(int startVertex) {
        std::unordered_map<int, bool> visited;
        std::stack<int> s;

        // Mark the starting vertex as visited and push to stack
        visited[startVertex] = true;
        s.push(startVertex);

        std::cout << "DFS Traversal: ";

        while (!s.empty()) {
            int currentVertex = s.top();
            bool hasUnvisitedNeighbor = false;

            // Find first unvisited adjacent vertex
            for (int adjacentVertex : adjacencyList[currentVertex]) {
                if (!visited[adjacentVertex]) {
                    visited[adjacentVertex] = true;
                    s.push(adjacentVertex);
                    std::cout << adjacentVertex << " ";
                    hasUnvisitedNeighbor = true;
                    break;
                }
            }

            // If no unvisited neighbors, pop the vertex
            if (!hasUnvisitedNeighbor) {
                s.pop();
            }
        }
        std::cout << std::endl;
    }

    // Utility function to print the graph
    void printGraph() {
        for (const auto& pair : adjacencyList) {
            std::cout << pair.first << ": ";
            for (int vertex : pair.second) {
                std::cout << vertex << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Graph g;

    // Create a sample graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);
    g.addEdge(3, 7);
    g.addEdge(4, 7);
    g.addEdge(5, 7);
    g.addEdge(6, 7);

    std::cout << "Graph Structure:" << std::endl;
    g.printGraph();
    std::cout << std::endl;

    // Test BFS
    g.BFS(0);

    // Test DFS
    g.DFS(0);

    return 0;
}
