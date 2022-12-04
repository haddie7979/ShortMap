#include "graph.h"
using namespace std;

int main() {
  cout << "Welcome to ShortMap!" << endl;
  cout << "This program finds the shortest route in imaginary maps." << endl;
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
        cout << "Error: Invalid map size - map creation failed." << endl;
        break;
      }
      // map gets created here
      if (mapSize > 0) {
        cout << "Generating..." << endl;
        g.init(mapSize);
        cout << "Map created successfully." << endl;
      } else {
        cout << "Error: Invalid map size - map creation failed." << endl;
      }
      break;

    // view map
    case 2:
      if (g.getSize() <= 100 && g.getSize() > 0) {
        cout << "***NOTE: Visualization only works locally with external "
                "library Graphviz installed.***"
             << endl;
        g.visualize();
      } else {
        cout << "Error: Map size must be greater than 0 and less than or equal "
                "to 100 "
                "to visualize."
             << endl;
      }
      break;

      // shortest path
    case 3:
      if (g.getSize() == 0) {
        cout << "Error: Map does not exist." << endl;
        break;
      }
      int from, to;
      cout << "\n"
           << "Choose your nodes:" << endl;
      cout << "Source Node: ";
      cin >> value;
      if (std::all_of(value.begin(), value.end(), ::isdigit)) {
        from = stoi(value);
      } else {
        cout << "Error: Invalid source node." << endl;
        break;
      }

      cout << "Destination Node: ";
      cin >> value;
      if (std::all_of(value.begin(), value.end(), ::isdigit)) {
        to = stoi(value);
      } else {
        cout << "Error: Invalid destination node." << endl;
        break;
      }

      // if to and from are within the bounds of the map
      if (from >= 0 && from < g.getSize() && to >= 0 && to < g.getSize()) {
        cout << "\n"
             << "Account for traffic delays?" << endl;
        int traffic;
        cout << "1. Account for traffic delays" << endl;
        cout << "2. Do not account for traffic delays" << endl;
        cin >> value;
        if (value.size() == 1 && isdigit(value[0])) {
          traffic = stoi(value);
        }

        if (traffic == 1) {
          // find the path considering traffic
          g.shortestPathWithTraffic(from, to);
        } else if (traffic == 2) {
          g.shortestPathWithoutTraffic(from, to);
        } else {
          cout << "Error: Invalid choice" << endl;
        }
      } else {
        cout << "Error: At least one node does not exist in map." << endl;
        break;
      }
      break;

      // exit
    case 4:
      break;

      // invalid input
    default:
      cout << "Error: Please choose a valid option." << endl;
      break;
    }

    cout << endl;
  }
}