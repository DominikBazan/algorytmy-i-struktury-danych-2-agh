#pragma once

#include <string>
#include "Edge.h"

using namespace std;

class FileLoader {
private:
    string path;
    int numOfVertices, numOfEdges, startVertice;
    list<Edge> listOfEdges;

public:
    FileLoader(string path);
    void extractValues();

    void setPath(const string path);

    int getNumOfVertices() const;
    int getNumOfEdges() const;
    int getStartVertice() const;
    const list<Edge> getListOfEdges() const;

};
