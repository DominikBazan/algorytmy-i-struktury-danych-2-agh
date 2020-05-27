#include <string>
#include <fstream>
#include "Edge.h"
#include "Graph.h"

using namespace std;

FileLoader::FileLoader(const string path) {
    FileLoader::setPath(path);
}

void FileLoader::extractValues() {

    fstream file;
    int v1, v2, p;
    string filename = path;
    file.open(filename.c_str());

    file >> this->numOfVertices;
    file >> this->numOfEdges;
    file >> this->startVertice;

    while (file >> v1) {
        file >> v2;
        file >> p;
        listOfEdges.push_back(Edge(v1, v2, p));
    }
}

void FileLoader::setPath(const string path) {
    FileLoader::path = path;
}

int FileLoader::getNumOfVertices() const {
    return numOfVertices;
}

int FileLoader::getNumOfEdges() const {
    return numOfEdges;
}

int FileLoader::getStartVertice() const {
    return startVertice;
}

const list<Edge> FileLoader::getListOfEdges() const {
    return listOfEdges;
}
