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
#include "footway.h"
#include "footways.h"
#include "graph.h"
#include "node.h"
#include "nodes.h"
#include "osm.h"
#include "tinyxml2.h"
#include <iomanip>

using namespace std;
using namespace tinyxml2;

void sanityCheck(graph &G, Footways &footways, Nodes &nodes) {
	long long footwayID = 986532630;
  vector<long long> nodeIDs;
  for(int i = 0; i < footways.getNumMapFootways(); i++) {
    if(footways.MapFootways[i].ID == footwayID) {
      for(int j = 0; j < footways.MapFootways[i].NodeIDs.size(); j++) {
        nodeIDs.push_back(footways.MapFootways[i].NodeIDs[j]);
      }
    }
  }
  
  for(int i = 0; i < nodeIDs.size(); i++) {
    set <long long> neighbors = G.neighbors(nodeIDs[i]);
    for(auto it = neighbors.begin(); it != neighbors.end(); it++) {
      cout << "Node " << nodeIDs[i] << " has neighbor " << *it << endl;
    }
  }

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

  footways.addEdgesToGraph(G, nodes);

  nodes.addVerticesToGraph(G);

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
    cout << "Enter building name (partial or complete), or * to list, or $ to "
            "end> "
         << endl;

    getline(cin, name);

    if (name == "$") {
      break;
    } else if (name == "*") {
      buildings.print();
    } else if (name == "!") {
      sanityCheck(G, footways, nodes);
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
