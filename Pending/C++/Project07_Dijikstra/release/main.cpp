/*main.cpp*/

//
// Program to input Nodes (positions), Buildings and Footways
// from an Open Street Map file.
//
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
//

#include <iostream>
#include <string>

#include "building.h"
#include "buildings.h"
#include "dist.h"
#include "footway.h"
#include "footways.h"
#include "graph.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "queue"
#include "tinyxml2.h"
#include <iomanip>

using namespace std;
using namespace tinyxml2;

void sanityCheck(graph &G, Footways &footways, Nodes &nodes) {
  vector<long long> from;
  vector<long long> to;
  vector<double> weights;
  long long footwayID = 986532630;
  vector<long long> nodeIDs;
  for (int i = 0; i < footways.getNumMapFootways(); i++) {
    if (footways.MapFootways[i].ID == footwayID) {
      for (int j = 0; j < (int)footways.MapFootways[i].NodeIDs.size(); j++) {
        nodeIDs.push_back(footways.MapFootways[i].NodeIDs[j]);
      }
      break;
    }
  }

  cout << "Graph check of Footway ID " << footwayID << endl;
  for (int i = 0; i < (int)nodeIDs.size(); i++) {
    set<long long> neighbors = G.neighbors(nodeIDs[i]);
    for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
      for (int j = 0; j < (int)nodeIDs.size(); j++) {
        if (nodeIDs[j] == *it) {
          double lat1, lon1, lat2, lon2;
          bool isEntrance = false;
          nodes.find(nodeIDs[i], lat1, lon1, isEntrance);
          nodes.find(nodeIDs[j], lat2, lon2, isEntrance);
          double dist = distBetween2Points(lat1, lon1, lat2, lon2);

          from.push_back(nodeIDs[i]);
          to.push_back(nodeIDs[j]);
          weights.push_back(dist);
        }
      }
    }
  }
  // bubble sort
  for (int i = 0; i < (int)weights.size(); i++) {
    for (int j = 0; j < (int)weights.size() - 1; j++) {
      if (weights[j] > weights[j + 1]) {
        double temp = weights[j];
        weights[j] = weights[j + 1];
        weights[j + 1] = temp;

        long long temp2 = from[j];
        from[j] = from[j + 1];
        from[j + 1] = temp2;

        temp2 = to[j];
        to[j] = to[j + 1];
        to[j + 1] = temp2;
      }
    }
  }
  for (int i = 0; i < (int)weights.size(); i++) {
    cout << "  Edge: (" << from[i] << ", " << to[i] << ", " << weights[i] << ")"
         << endl;
  }
}

vector<long long> dijkstra(graph g, long long start, long long destination,
                           Nodes nodes) {
  vector<long long> vertices = g.getVertices();
  vector<long long> path;
  vector<long long> unvisited;
  map<long long, long long> previous;
  map<long long, double> distance;
  int numberOfVisitedNodes = 0;

  for (int i = 0; i < g.NumVertices(); i++) {
    distance[vertices[i]] = INFINITY;
    previous[vertices[i]] = -1;
  }
  distance[start] = 0;
  unvisited.push_back(start);

  while (!unvisited.empty()) {
    long long current = unvisited[0];
    unvisited.erase(unvisited.begin());

    numberOfVisitedNodes++;

    set<long long> neighbors = g.neighbors(current);
    for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
      double lat1, lon1, lat2, lon2;
      bool isEntrance = false;
      nodes.find(current, lat1, lon1, isEntrance);
      nodes.find(*it, lat2, lon2, isEntrance);
      double dist = distBetween2Points(lat1, lon1, lat2, lon2);
      if (distance[*it] > distance[current] + dist) {
        distance[*it] = distance[current] + dist;
        previous[*it] = current;
        unvisited.push_back(*it);
      }
    }

    // bubble sort unvisited
    for (int i = 0; i < unvisited.size(); i++) {
      for (int j = 0; j < unvisited.size() - 1; j++) {
        if (distance[unvisited[j]] > distance[unvisited[j + 1]]) {
          long long temp = unvisited[j];
          unvisited[j] = unvisited[j + 1];
          unvisited[j + 1] = temp;
        }
      }
    }
  }

  cout << "Shortest weighted path:" << endl;
  if (distance[destination] == INFINITY) {
    cout << "**Sorry, destination path unreachable" << endl;
    return path;
  } else {
    cout << "  # of visited nodes: " << numberOfVisitedNodes << endl;
    cout << "  Distance: " << distance[destination] << " miles" << endl;

    long long current = destination;
    while (current != start) {
      path.push_back(current);
      current = previous[current];
    }
    path.push_back(start);

    return path;
  }
}

void navigate(graph G, Buildings &buildings, Footways &footways, Nodes &nodes) {
  string start, end;
  cout << "Enter start building name  (partial or complete)> " << endl;
  getline(cin, start);
  double lat1 = -1, lon1 = -1, lat2 = -1, lon2 = -1;
  long long startNodeID = -1, endNodeID = -1;
  Building startBuilding(-1, "startBuilding", "");
  if (!buildings.findBuildingByNameAndPrint(startNodeID, start, lat1, lon1,
                                            footways, nodes)) {
    cout << "**Start Building not found" << endl;
    return;
  }

  cout << "Enter destination building name (partial or complete)> " << endl;
  getline(cin, end);
  if (!buildings.findBuildingByNameAndPrint(endNodeID, end, lat2, lon2,
                                            footways, nodes)) {
    cout << "**Destination Building not found" << endl;
    return;
  }

  vector<long long> path = dijkstra(G, startNodeID, endNodeID, nodes);
  if (path.size() > 0) {
    cout << "  Path: ";
    for (int i = path.size() - 1; i >= 0; i--) {
      if (i == 0) {
        cout << path[i];
      } else {
        cout << path[i] << "->";
      }
    }
  }
  cout << endl;
}

//
// main
//
int main() {
  XMLDocument xmldoc;
  Nodes nodes;
  Buildings buildings;
  Footways footways;
  graph G;

  cout << setprecision(12);
  cout << "** NU open street map **" << endl;

  string filename;

  cout << endl;
  cout << "Enter map filename> " << endl;
  getline(cin, filename);

  //
  // 1. load XML-based map file
  //
  if (!osmLoadMapFile(filename, xmldoc)) {
    // failed, error message already output
    return 0;
  }

  //
  // 2. read the nodes, which are the various known positions on the map:
  //
  nodes.readMapNodes(xmldoc);

  //
  // NOTE: let's sort so we can use binary search when we need
  // to lookup nodes.
  //
  nodes.sortByID();

  //
  // 3. read the university buildings:
  //
  buildings.readMapBuildings(xmldoc);

  //
  // 4. read the footways, which are the walking paths:
  //
  footways.readMapFootways(xmldoc);

  nodes.addVerticesToGraph(G);

  footways.addEdgesToGraph(G, nodes);

  //
  // 5. stats
  //
  cout << "# of nodes: " << nodes.getNumMapNodes() << endl;
  cout << "# of buildings: " << buildings.getNumMapBuildings() << endl;
  cout << "# of footways: " << footways.getNumMapFootways() << endl;
  cout << "# of graph vertices: " << G.NumVertices() << endl;
  cout << "# of graph edges: " << G.NumEdges() << endl;
  //
  // now let the user for search for 1 or more buildings:
  //
  while (true) {
    string name;

    cout << endl;
    cout << "Enter building name, * to list, @ to navigate, or $ to end>"
         << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    } else if (name == "*") {
      buildings.print();
    } else if (name == "!") {
      sanityCheck(G, footways, nodes);
    } else if (name == "@") {
      navigate(G, buildings, footways, nodes);
    } else {
      buildings.findAndPrint(name, nodes, footways);
    }
  } // while

  //
  // done:
  //
  cout << endl;
  cout << "** Done  **" << endl;
  cout << "# of calls to getID(): " << Node::getCallsToGetID() << endl;
  cout << "# of Nodes created: " << Node::getCreated() << endl;
  cout << "# of Nodes copied: " << Node::getCopied() << endl;
  cout << endl;

  return 0;
}
