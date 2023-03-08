/*graph.h*/

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

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

using namespace std;


class graph
{
private:
  unordered_map<string, set<pair<string, double>>> adjacencyList;
  int numVertices;
  int numEdges;
  //
  // TODO:
  //

public:
  //
  // default constructor: no parameters
  //
  graph();

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const;

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const;

  //
  // addVertex
  //
  // Adds the vertex v to the graph and returns true. However,
  // if v is already in the graph, it is not added again and 
  // false is returned.
  //
  bool addVertex(string v);

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true. If the vertices do not exist then no edge is added
  // and false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(string from, string to, double weight);

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If 
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned. If the edge does not 
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(string from, string to, double& weight) const;

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge. If
  // v does not exist, an empty set is returned.
  //
  set<string> neighbors(string v) const;

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph. There is no guaranteed order to the vertices 
  // in the returned vector; the order should be considered 
  // random.
  //
  vector<string> getVertices() const;

  //
  // print
  // 
  // Prints the internal state of the graph to the given 
  // output stream for debugging purposes. The output will
  // contain the # of vertices, the # of edges, the vertices,
  // and the edges. Vertices are output as strings and the 
  // weights as doubles.
  //
  // Example:
  //    graph G;
  //    ...
  //    G.print(cout);  // print to console
  //
  void print(ostream& output) const;

};
