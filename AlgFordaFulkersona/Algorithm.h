#pragma once

#include <iostream>
#include "Graph.h"
#include "Edge.h"
#include <list>

using namespace std;

class Algorithm {
public:
    Algorithm(Graph graph);
    void calculateFMax();
    void calucateFMaxNewTableAlgo();
    void calucateFMaxNewListAlgo();
    void testing();
    int getFMax() const;
    int getFMaxNewTable() const;
    int getFMaxNewList() const;
    void testIterowania();
private:
    Graph graph;
    int finalFMax, finalFMaxNewTable, finalFMaxNewList;
    const int BIG_NUMBER = 2000000000;
};
