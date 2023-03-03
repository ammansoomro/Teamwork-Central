/*footways.cpp*/

//
// A collection of footways / paths in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211: Winter 2023
// 

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

#include "footways.h"
#include "osm.h"
#include "tinyxml2.h"
#include "dist.h"

using namespace std;
using namespace tinyxml2;


//
// readMapFootways
//
// Given an XML document, reads through the document and 
// stores all the footways / paths into the given vector.
//
void Footways::readMapFootways(XMLDocument& xmldoc)
{
  XMLElement* osm = xmldoc.FirstChildElement("osm");
  assert(osm != nullptr);

  //
  // Parse the XML document way by way, looking for footways:
  //
  XMLElement* way = osm->FirstChildElement("way");

  while (way != nullptr)
  {
    const XMLAttribute* attr = way->FindAttribute("id");
    assert(attr != nullptr);

    // 
    // if this is a footway, collect the node ids and store another
    // footway object in the vector:
    //
    if (osmContainsKeyValue(way, "highway", "footway") ||
      osmContainsKeyValue(way, "area:highway", "footway"))
    {
      long long id = attr->Int64Value();

      Footway footway(id);

      XMLElement* nd = way->FirstChildElement("nd");

      while (nd != nullptr)
      {
        const XMLAttribute* ndref = nd->FindAttribute("ref");
        assert(ndref != nullptr);

        long long id = ndref->Int64Value();

        footway.add(id);

        // advance to next node ref:
        nd = nd->NextSiblingElement("nd");
      }

      this->MapFootways.push_back(footway);
    }//if

    way = way->NextSiblingElement("way");
  }//while

  //
  // done:
  //
}


//
// intersectWithBuilding
// 
// Outputs all the footways that intersect --- i.e. share
// a common node --- with Building B.
//
void Footways::intersectWithBuilding(Building& B)
{
  vector<long long> footwayIDs;

  cout << "Footways that intersect:" << endl;

  for (Footway& F : this->MapFootways)
  {
    if (F.intersectWithBuilding(B))
    {
      footwayIDs.push_back(F.ID);
    }
  }

  //
  // did any intersect?
  //
  if (footwayIDs.empty())
  {
    cout << "  None" << endl;
    return;
  }

  //
  // sort the footway ids, if any:
  //
  sort(footwayIDs.begin(), footwayIDs.end(),
    [](long long id1, long long id2)
    {
      if (id1 < id2)
        return true;
      else 
        return false;
    }
  );

  //
  // output the pairs of intersections:
  //
  for (long long id : footwayIDs) {
    cout << "  Footway " << id << endl;
  }
}


//
// accessors / getters
//
int Footways::getNumMapFootways() {
  return (int)this->MapFootways.size();
}

void Footways::addEdgesToGraph(graph& G, Nodes &N) {
  int count = 1;
  for(int i = 0; i < this->MapFootways.size(); i++) {
    for(int j = 0; j < this->MapFootways[i].NodeIDs.size() - 1; j++) {
      long long node1 = this->MapFootways[i].NodeIDs[j];
      long long node2 = this->MapFootways[i].NodeIDs[j + 1];
      double lat1 = -1, lat2 = -1, lon1 = -1, lon2 = -1;
      bool isEntrance = false;
      N.find(node1, lat1, lon1, isEntrance);
      N.find(node2, lat2, lon2, isEntrance);
      double weight = distBetween2Points(lat1, lon1, lat2, lon2);
      bool isAdded1 = G.addEdge(node1, node2, weight);
      bool isAdded2 = G.addEdge(node2, node1, weight);
      cout << count++ << ": " << node1 << " -> " << node2 << "(" << weight << ") "  << isAdded1 <<endl;
      cout << count++ << ": " << node2 << " -> " << node1 << "(" << weight << ") "  << isAdded2 <<endl;
    }
  }
}

