#pragma once

#include <list>
#include "FileLoader.h"
#include "Edge.h"

using namespace std;

class Graph {
private:
    int numOfVertices, numOfEdges, startVertice;
    list<Edge> listOfEdges;
public:
    Graph();

    int getNumOfVertices() const;
    void setNumOfVertices(int numOfVertices);
    int getNumOfEdges() const;
    void setNumOfEdges(int numOfEdges);
    int getStartVertice() const;
    void setStartVertice(int startVertice);
    list<Edge> getListOfEdges() const;
    void setListOfEdges(list<Edge> listOfEdges);

};
