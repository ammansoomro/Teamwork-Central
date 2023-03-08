#include <iostream>
#include "gtest/gtest.h"
#include "graph.h"

using namespace std;

TEST(testing, test01)
{
    graph G;
    // ADDING UNIQUE VERTICES AND EDGES
    ASSERT_TRUE(G.addVertex("Chicago"));
    ASSERT_TRUE(G.addVertex("New York"));
    ASSERT_TRUE(G.addVertex("Los Angeles"));
    ASSERT_TRUE(G.addVertex("San Francisco"));
    ASSERT_TRUE(G.addVertex("Seattle"));
    ASSERT_TRUE(G.addVertex("Boston"));
    ASSERT_TRUE(G.addVertex("Atlanta"));
    ASSERT_TRUE(G.addVertex("Denver"));

    ASSERT_TRUE(G.addEdge("Chicago", "New York", 800));
    ASSERT_TRUE(G.addEdge("Chicago", "Los Angeles", 2000));
    ASSERT_TRUE(G.addEdge("Chicago", "Boston", 900));
    ASSERT_TRUE(G.addEdge("Chicago", "Denver", 1000));
    ASSERT_TRUE(G.addEdge("New York", "Los Angeles", 2800));
    ASSERT_TRUE(G.addEdge("New York", "San Francisco", 2600));
    ASSERT_TRUE(G.addEdge("New York", "Seattle", 3300));
    ASSERT_TRUE(G.addEdge("Seattle", "Boston", 3000));
    ASSERT_TRUE(G.addEdge("Seattle", "Atlanta", 2900));
    ASSERT_TRUE(G.addEdge("Boston", "Atlanta", 1000));
    ASSERT_TRUE(G.addEdge("Atlanta", "Los Angeles", 2100));
    ASSERT_TRUE(G.addEdge("Atlanta", "San Francisco", 1900));
    ASSERT_TRUE(G.addEdge("Los Angeles", "San Francisco", 400));
    ASSERT_TRUE(G.addEdge("Los Angeles", "Seattle", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Seattle", 2700));
    ASSERT_TRUE(G.addEdge("San Francisco", "Boston", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Denver", 1700));
    ASSERT_TRUE(G.addEdge("Denver", "Boston", 1600));

    //  Check that the graph has the correct number of vertices and edges;
    ASSERT_TRUE( G.NumVertices() == 8 );
    ASSERT_TRUE( G.NumEdges() == 18 );
}

TEST(testing, test02)
{
    graph G;
    // ADDING A DUPLICATE VERTEX
    ASSERT_TRUE(G.addVertex("Chicago"));
    ASSERT_TRUE(G.addVertex("New York"));
    ASSERT_TRUE(G.addVertex("Los Angeles"));
    ASSERT_TRUE(G.addVertex("San Francisco"));
    ASSERT_TRUE(G.addVertex("Seattle"));
    ASSERT_TRUE(G.addVertex("Boston"));
    ASSERT_TRUE(G.addVertex("Atlanta"));
    ASSERT_TRUE(G.addVertex("Denver"));
    ASSERT_FALSE(G.addVertex("Denver"));


    ASSERT_TRUE(G.addEdge("Chicago", "New York", 800));
    ASSERT_TRUE(G.addEdge("Chicago", "Los Angeles", 2000));
    ASSERT_TRUE(G.addEdge("Chicago", "Boston", 900));
    ASSERT_TRUE(G.addEdge("Chicago", "Denver", 1000));
    ASSERT_TRUE(G.addEdge("New York", "Los Angeles", 2800));
    ASSERT_TRUE(G.addEdge("New York", "San Francisco", 2600));
    ASSERT_TRUE(G.addEdge("New York", "Seattle", 3300));
    ASSERT_TRUE(G.addEdge("Seattle", "Boston", 3000));
    ASSERT_TRUE(G.addEdge("Seattle", "Atlanta", 2900));
    ASSERT_TRUE(G.addEdge("Boston", "Atlanta", 1000));
    ASSERT_TRUE(G.addEdge("Atlanta", "Los Angeles", 2100));
    ASSERT_TRUE(G.addEdge("Atlanta", "San Francisco", 1900));
    ASSERT_TRUE(G.addEdge("Los Angeles", "San Francisco", 400));
    ASSERT_TRUE(G.addEdge("Los Angeles", "Seattle", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Seattle", 2700));
    ASSERT_TRUE(G.addEdge("San Francisco", "Boston", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Denver", 1700));
    ASSERT_TRUE(G.addEdge("Denver", "Boston", 1600));

    //  Check that the graph has the correct number of vertices and edges;
    ASSERT_TRUE( G.NumVertices() == 8 );
    ASSERT_TRUE( G.NumEdges() == 18 );
}

TEST(testing, test03)
{
    graph G;
    // ADDING A DUPLICATE EDGE
    // SHOULD JUST UPDATE THE WEIGHT OF DUPLICATE EDGE
    ASSERT_TRUE(G.addVertex("Chicago"));
    ASSERT_TRUE(G.addVertex("New York"));
    ASSERT_TRUE(G.addVertex("Los Angeles"));
    ASSERT_TRUE(G.addVertex("San Francisco"));
    ASSERT_TRUE(G.addVertex("Seattle"));
    ASSERT_TRUE(G.addVertex("Boston"));
    ASSERT_TRUE(G.addVertex("Atlanta"));
    ASSERT_TRUE(G.addVertex("Denver"));

    ASSERT_TRUE(G.addEdge("Chicago", "New York", 800));
    ASSERT_TRUE(G.addEdge("Chicago", "Los Angeles", 2000));
    ASSERT_TRUE(G.addEdge("Chicago", "Boston", 900));
    ASSERT_TRUE(G.addEdge("Chicago", "Denver", 1000));
    ASSERT_TRUE(G.addEdge("New York", "Los Angeles", 2800));
    ASSERT_TRUE(G.addEdge("New York", "San Francisco", 2600));
    ASSERT_TRUE(G.addEdge("New York", "Seattle", 3300));
    ASSERT_TRUE(G.addEdge("Seattle", "Boston", 3000));
    ASSERT_TRUE(G.addEdge("Seattle", "Atlanta", 2900));
    ASSERT_TRUE(G.addEdge("Boston", "Atlanta", 1000));
    ASSERT_TRUE(G.addEdge("Atlanta", "Los Angeles", 2100));
    ASSERT_TRUE(G.addEdge("Atlanta", "San Francisco", 1900));
    ASSERT_TRUE(G.addEdge("Los Angeles", "San Francisco", 400));
    ASSERT_TRUE(G.addEdge("Los Angeles", "Seattle", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Seattle", 2700));
    ASSERT_TRUE(G.addEdge("San Francisco", "Boston", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Denver", 1700));
    ASSERT_TRUE(G.addEdge("Denver", "Boston", 1600));
    ASSERT_TRUE(G.addEdge("Denver", "Boston", 1800));

    //  Check that the graph has the correct number of vertices and edges
    ASSERT_TRUE( G.NumVertices() == 8 );
    ASSERT_TRUE( G.NumEdges() == 18 );
    double weight; 
    ASSERT_TRUE(G.getWeight("Denver", "Boston", weight));
    ASSERT_TRUE( weight == 1800);
}

TEST(testing, test04) {
    // GET NON EXISTING EDGE WEIGHT
    graph G;
    ASSERT_TRUE(G.addVertex("Chicago"));
    ASSERT_TRUE(G.addVertex("New York"));
    ASSERT_TRUE(G.addVertex("Los Angeles"));
    ASSERT_TRUE(G.addVertex("San Francisco"));
    ASSERT_TRUE(G.addVertex("Seattle"));
    ASSERT_TRUE(G.addVertex("Boston"));
    ASSERT_TRUE(G.addVertex("Atlanta"));
    ASSERT_TRUE(G.addVertex("Denver"));

    ASSERT_TRUE(G.addEdge("Chicago", "New York", 800));
    ASSERT_TRUE(G.addEdge("Chicago", "Los Angeles", 2000));
    ASSERT_TRUE(G.addEdge("Chicago", "Boston", 900));
    ASSERT_TRUE(G.addEdge("Chicago", "Denver", 1000));
    ASSERT_TRUE(G.addEdge("New York", "Los Angeles", 2800));
    ASSERT_TRUE(G.addEdge("New York", "San Francisco", 2600));
    ASSERT_TRUE(G.addEdge("New York", "Seattle", 3300));
    ASSERT_TRUE(G.addEdge("Seattle", "Boston", 3000));
    ASSERT_TRUE(G.addEdge("Seattle", "Atlanta", 2900));
    ASSERT_TRUE(G.addEdge("Boston", "Atlanta", 1000));
    ASSERT_TRUE(G.addEdge("Atlanta", "Los Angeles", 2100));
    ASSERT_TRUE(G.addEdge("Atlanta", "San Francisco", 1900));
    ASSERT_TRUE(G.addEdge("Los Angeles", "San Francisco", 400));
    ASSERT_TRUE(G.addEdge("Los Angeles", "Seattle", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Seattle", 2700));
    ASSERT_TRUE(G.addEdge("San Francisco", "Boston", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Denver", 1700));
    ASSERT_TRUE(G.addEdge("Denver", "Boston", 1600));

    double weight;
    ASSERT_TRUE( G.NumVertices() == 8 );
    ASSERT_TRUE( G.NumEdges() == 18 );
    ASSERT_TRUE(G.getWeight("Chicago", "New York", weight));
    ASSERT_FALSE(G.getWeight("Denver", "New York", weight));

}

TEST(testing, test05) {
    // GET NON EXISTING EDGE WEIGHT
    graph G;
    ASSERT_TRUE(G.addVertex("Chicago"));
    ASSERT_TRUE(G.addVertex("New York"));
    ASSERT_TRUE(G.addVertex("Los Angeles"));
    ASSERT_TRUE(G.addVertex("San Francisco"));
    ASSERT_TRUE(G.addVertex("Seattle"));
    ASSERT_TRUE(G.addVertex("Boston"));
    ASSERT_TRUE(G.addVertex("Atlanta"));
    ASSERT_TRUE(G.addVertex("Denver"));

    ASSERT_TRUE(G.addEdge("Chicago", "New York", 800));
    ASSERT_TRUE(G.addEdge("Chicago", "Los Angeles", 2000));
    ASSERT_TRUE(G.addEdge("Chicago", "Boston", 900));
    ASSERT_TRUE(G.addEdge("Chicago", "Denver", 1000));
    ASSERT_TRUE(G.addEdge("New York", "Los Angeles", 2800));
    ASSERT_TRUE(G.addEdge("New York", "San Francisco", 2600));
    ASSERT_TRUE(G.addEdge("New York", "Seattle", 3300));
    ASSERT_TRUE(G.addEdge("Seattle", "Boston", 3000));
    ASSERT_TRUE(G.addEdge("Seattle", "Atlanta", 2900));
    ASSERT_TRUE(G.addEdge("Boston", "Atlanta", 1000));
    ASSERT_TRUE(G.addEdge("Atlanta", "Los Angeles", 2100));
    ASSERT_TRUE(G.addEdge("Atlanta", "San Francisco", 1900));
    ASSERT_TRUE(G.addEdge("Los Angeles", "San Francisco", 400));
    ASSERT_TRUE(G.addEdge("Los Angeles", "Seattle", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Seattle", 2700));
    ASSERT_TRUE(G.addEdge("San Francisco", "Boston", 2500));
    ASSERT_TRUE(G.addEdge("San Francisco", "Denver", 1700));
    ASSERT_TRUE(G.addEdge("Denver", "Boston", 1600));

    //  Check that the graph has the correct number of vertices and edges
    ASSERT_TRUE( G.NumVertices() == 8 );
    ASSERT_TRUE( G.NumEdges() == 18 );
    double weight;
    ASSERT_TRUE(G.getWeight("Chicago", "New York", weight));
    ASSERT_TRUE( weight == 800);
    ASSERT_TRUE(G.getWeight("Chicago", "Los Angeles", weight));
    ASSERT_TRUE( weight == 2000);
    ASSERT_TRUE(G.getWeight("Chicago", "Boston", weight));
    ASSERT_TRUE( weight == 900);
    ASSERT_TRUE(G.getWeight("Atlanta", "Los Angeles", weight));
    ASSERT_TRUE( weight == 2100);

}

int main()
{
    ::testing::InitGoogleTest();

    //
    // run all the tests, returns 0 if they
    // all pass and 1 if any fail:
    //
    int result = RUN_ALL_TESTS();

    return result;
}

