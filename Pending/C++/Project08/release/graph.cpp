/*graph.cpp*/

//
// Graph class implemented as ...
//
//    ?????????
//
// For this implementation of graph, the vertices are
// string, and the weights are doubles.  Example:
//
//   graph  G;
//   G.addVertex("Chicago");
//   G.addVertex("New York");
//   G.addEdge("Chicago", "New York", -999.99);
//
// Kareem Shahbandar
//
// Northwestern University
// CS 211: Winter 2023
//

#include "graph.h"

graph::graph() : numVertices(0), numEdges(0) {}

int graph::NumVertices() const { return numVertices; }

int graph::NumEdges() const { return numEdges; }

bool graph::addVertex(string vertex) {
  if (adjacencyList.find(vertex) != adjacencyList.end()) {
    return false;
  }
  adjacencyList[vertex] = map<string, double>();
  numVertices++;
  return true;
}

bool graph::addEdge(string vertex1, string vertex2, double weight) {
  if (adjacencyList.find(vertex1) == adjacencyList.end() ||
      adjacencyList.find(vertex2) == adjacencyList.end()) {
    return false;
  }

  // overwriting weight if edge already exists
  if (adjacencyList[vertex1].find(vertex2) == adjacencyList[vertex1].end()) {
    numEdges++;
  }

  adjacencyList[vertex1][vertex2] = weight;

  return true;
}

bool graph::getWeight(string vertex1, string vertex2, double &weight) const {
  if (adjacencyList.find(vertex1) == adjacencyList.end() ||
      adjacencyList.find(vertex2) == adjacencyList.end()) {
    return false;
  }
  if (adjacencyList.at(vertex1).find(vertex2) ==
      adjacencyList.at(vertex1).end()) {
    return false;
  }
  weight = adjacencyList.at(vertex1).at(vertex2);
  return true;
}

set<string> graph::neighbors(string vertex) const {
  set<string> neighbors;
  if (adjacencyList.find(vertex) == adjacencyList.end()) {
    return neighbors;
  }
  for (auto it = adjacencyList.at(vertex).begin();
       it != adjacencyList.at(vertex).end(); it++) {
    neighbors.insert(it->first);
  }
  return neighbors;
}

vector<string> graph::getVertices() const {
  vector<string> vertices;
  for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
    vertices.push_back(it->first);
  }
  return vertices;
}

void graph::print(ostream &output) const {
  output << "# of Vertices: " << numVertices << endl;
  output << "# of Edges: " << numEdges << endl;

  for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
    output << it->first << ": ";
    for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
      output << it2->first << "(" << it2->second << ") ";
    }
    output << endl;
  }
}