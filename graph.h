#pragma once

#include <algorithm>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <random>
#include <set>
#include <unordered_set>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Graph {
private:
    // Same concept as adjacency list
    // The rows are the "from" vertices and the columns are the "to" vertices
    // e.g. "matrix[0][1] = 15" means there is an edge from 0 to 1 w/ weight 15
    // vector<vector<int>> matrix;
    unordered_map<int, unordered_map<int, int>> adjList;
    vector<int> bfs(int src);
    int generateRandomNode(int max);
    int generateRandomWeight();

public:
    void init(int size);
    int getSize();
    void printAdjList();
    void shortestPathWithoutTraffic(int src, int dest);
    void dijkstraAlgorithm(int src, int dest);
    int minDist(vector<int> d, vector<bool> v);
};

int Graph::getSize() { return adjList.size(); }

void Graph::printAdjList() {
    for (auto member : adjList) {
        cout << "Vertex: " << member.first << endl;
        for (auto vertex : member.second) {
            cout << "Adjacent vertex: " << vertex.first
                 << " (Weight: " << vertex.second << ")" << endl;
        }
        cout << endl;
    }
}

// References:
// https://cplusplus.com/reference/random/uniform_real_distribution/
// https://stackoverflow.com/questions/12885356/random-numbers-with-different-probabilities
// http://www.gitta.info/Accessibiliti/en/html/Dijkstra_learningObject1.html
// Separate functions for generating random nodes and weights because the
// int distributions are static (persist for lifecycle of the graph obj)
// This means the range of random numbers cannot be changed once the random
// function is called
int Graph::generateRandomNode(int max) {
    random_device rd;
    static mt19937 engine(rd());
    static uniform_int_distribution<> dist(0, max);
    return dist(engine);
}

int Graph::generateRandomWeight() {
    random_device rd;
    static mt19937 engine(rd());
    static uniform_int_distribution<> dist(1, 10);
    return dist(engine);
}

vector<int> Graph::bfs(int src) {
    set<int> visited;
    queue<int> q;
    vector<int> d(adjList.size(), INT_MAX); // distance vector
    vector<int> p(adjList.size(), -1);      // predecessors vector

    visited.insert(src);
    q.push(src);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited.insert(u);

        unordered_map<int, int> adj = adjList[u];

        for (pair<int, int> v : adj) {
            if (visited.count(v.first) == 0) {
                visited.insert(v.first);

                if (d[u] + 1 < d[v.first]) {
                    d[v.first] = d[u] + 1;
                    p[v.first] = u;
                    q.push(v.first);
                }
            }
        }
    }

    return p;
}

void Graph::shortestPathWithoutTraffic(int src, int dest) {

    vector<int> p = bfs(src);

    // Trace back shortest path using predecessor vector and reverse order
    // by using a stack for printing
    stack<int> s;
    int totalTraffic = 0;
    int predTracker = dest;

    while (predTracker != -1) {
        s.push(predTracker);
        predTracker = p[predTracker];
    }

    // If top of the stack is not the source node, then the source node was not
    // found in the trace back, meaning the source and dest vertices are not
    // connected
    if (s.top() != src) {
        cout << "Node " << src << " and node " << dest << "are not connected."
             << endl;
        return;
    }

    // Print shortest path & calculate total traffic simultaneously
    cout << "\n"
         << "The shortest path between node " << src << " and node " << dest
         << " is:" << endl;
    int prevTop = s.top();
    cout << s.top();
    s.pop();
    while (!s.empty()) {
        totalTraffic += adjList[prevTop][s.top()];
        cout << " -> " << s.top();
        prevTop = s.top();
        s.pop();
    }
    cout << endl;
    cout << "Total traffic on this route is: " << totalTraffic << " minutes"
         << endl;
}
int Graph:: minDist(vector<int> d, vector<bool> v){
    int max = INT_MAX;
    int ret = -1;
  for (int i = 0; i < d.size(); i++){
      if (d[i] < max && v[i] == false){
          max = d[i];
          ret = i;
      }
  }
    return ret;
}
void Graph::dijkstraAlgorithm(int src, int dest){
    vector<int> d(adjList.size(), INT_MAX); // distance vector
    vector<int> p(adjList.size(), -1);      // predecessors vector
    vector<bool> valVisited (adjList.size(), false);

    d[src] = 0;

    for (int i = 0; i < adjList.size(); i++) {   // 7 -> 2 3 4
        // smallest -> helper function -> returns index
        int minIndex = minDist(d, valVisited);
        valVisited[minIndex] = true;
        
        for (auto j: adjList[minIndex]) {
            int temp = d[minIndex] + j.second;
            if (temp < d[j.first]) {
                d[j.first] = temp;
                p[j.first] = minIndex;
            }
        }
    }
    
  int totalTraffic = d[dest];
    
    stack <int> path;
    int pfind = dest;
    while (pfind != -1){
        path.push(pfind);
        pfind = p[pfind];
    }

    // If top of the stack is not the source node, then the source node was not
    // found in the trace back, meaning the source and dest vertices are not
    // connected
    if (path.top() != src) {
        cout << "Node " << src << " and node " << dest << "are not connected."
             << endl;
        return;
    }

    // Print shortest path & calculate total traffic simultaneously
    cout << "\n"
         << "The shortest path between node " << src << " and node " << dest
         << " is:" << endl;
    int prevTop = path.top();
    cout << path.top();
    path.pop();
    while (!path.empty()) {
        cout << " -> " << path.top();
        prevTop = path.top();
        path.pop();
    }
    cout << endl;
    cout << "Total traffic on this route is: " << totalTraffic << " minutes"
         << endl;

}



void Graph::init(int size) {
    srand(time(NULL)); // Seed random generation once

    set<pair<int, int>> edges;

    // Randomly generate graph
    for (int i = 0; i < size; i++) {
        set<int> adjNodes;
        int adjacentMaxSize = 2;
        while (true) {
            int adj = generateRandomNode(size - 1);

            if (i == adj)
                continue;

            if (adjNodes.count(adj) != 0)
                continue;
            if (edges.count(make_pair(i, adj)) != 0 ||
                edges.count(make_pair(adj, i)) != 0)
                continue;

            adjList[i][adj] = generateRandomWeight();
            adjList[adj][i] = generateRandomWeight();

            adjNodes.insert(adj);
            edges.insert(make_pair(i, adj));

            if (adjNodes.size() == adjacentMaxSize)
                break;
        }
    }
}

