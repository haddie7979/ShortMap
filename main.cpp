#include <iostream>
#include "graph.h"
using namespace std;

int main() {
    cout << "Welcome to ShortMap!" << endl;
    cout << "This program finds the shortest route in imaginary maps" << endl;
    cout << endl;

    int choice = 0;
    Graph g;

    while (choice != 4) {
        cout << "What would you like to do?" << endl;
        cout << "1. Create a new map" << endl;
        cout << "2. View the current map" << endl;
        cout << "3. Show the shortest path between two nodes" << endl;
        cout << "4. Exit" << endl;

        string value;
        cin >> value;
        if (value.size() == 1 && isdigit(value[0])) {
            choice = stoi(value);
        }

        switch (choice) {
            // create map
            case 1:
                cout << "\n"
                     << "What size map would you like to create?" << endl;
                cin >> value;

                int mapSize;
                if (std::all_of(value.begin(), value.end(), ::isdigit)) {
                    mapSize = stoi(value);
                } else {
                    cout << "invalid map size, map creation failed." << endl;
                    break;
                }
                // map gets created here
                if (mapSize > 0) {
                    cout << "Generating..." << endl;
                    g.init(mapSize);
                    cout << "map created successfully" << endl;
                } else {
                    cout << "invalid map size, map creation failed" << endl;
                }
                break;

                // view map
            case 2:
                if (g.getSize() < 200 && g.getSize() > 0) {
                    cout << "map: " << endl;
                    g.printAdjList();
                } else
                    cout << "map size must be less than 200 nodes and greater than 0 nodes "
                            "to print"
                         << endl;
                break;

                // shortest path
            case 3:
                if (g.getSize() == 0) {
                    cout << "map does not exist" << endl;
                    break;
                }
                int from, to;
                cout << "\n" << "Choose your nodes " << endl;
                cout << "Source Node: " << endl;
                cin >> value;
                if (std::all_of(value.begin(), value.end(), ::isdigit)) {
                    from = stoi(value);
                } else {
                    cout << "Invalid source node." << endl;
                    break;
                }

                cout << "Destination Node: " << endl;
                cin >> value;
                if (std::all_of(value.begin(), value.end(), ::isdigit)) {
                    to = stoi(value);
                } else {
                    cout << "invalid destination node." << endl;
                    break;
                }

                // if to and from are within the bounds of the map
                if (from >= 0 && from < g.getSize() && to >= 0 && to < g.getSize()) {
                    cout << "\n" << "Account for traffic delays?" << endl;
                    int traffic;
                    cout << "1. Account for traffic delays" << endl;
                    cout << "2. Do not account for traffic delays" << endl;
                    cin >> value;
                    if (value.size() == 1 && isdigit(value[0])) {
                        traffic = stoi(value);
                    }

                    if (traffic == 1) {
                        // find the path considering traffic
                        g.dijkstraAlgorithm(from,to);
                       // cout << "the shortest path is:" << endl;
                    } else if (traffic == 2) {
                        g.shortestPathWithoutTraffic(from, to);
                    } else {
                        cout << "invalid choice" << endl;
                    }
                } else {
                    cout << "at least one node does not exist in map" << endl;
                    break;
                }
                break;

                // exit
            case 4:
                break;

                // invalid input
            default:
                cout << "please choose a valid option" << endl;
                break;
        }

        cout << endl;
    }
}

/*
a.Responsibility:Creating graph implementation thatis backed by an adjacency
matrix
 - Members: Jordan
b.Responsibility:Writing algorithm that randomly generates the graph, i.e.
randomly deciding connections between vertices and weights for edges
 - Members:Divyashi
c.Responsibility:Writing Dijkstra’s algorithm to find the shortest path between
nodes
 - Members:Everyone
d.Responsibility:Creating input/output system for takingin start and ending
locations and printing all relevant info the user
        TODO:
          -- print map
          -- ensure to and from are within bounds of map
          -- print paths when calculated
 - Members:Lindsay
e. bfs
 - Members:Whomever
*/

/*
2 ways-> one with traffic and one without traffic
*/