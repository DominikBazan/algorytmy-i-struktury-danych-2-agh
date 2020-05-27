#pragma once

#include "Graph.h"

using namespace std;

class Algorithm {
public:
    Algorithm(Graph graph);
    void calculateResult();
    void testing();
    void testIterowania();
private:
    Graph graph;
};
