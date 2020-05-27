#include "Graph.h"
#include "Edge.h"
#include <list>

using namespace std;

Graph::Graph() {
}

int Graph::getNumOfVertices() const {
    return numOfVertices;
}

void Graph::setNumOfVertices(int numOfVertices) {
    Graph::numOfVertices = numOfVertices;
}

int Graph::getNumOfEdges() const {
    return numOfEdges;
}

void Graph::setNumOfEdges(int numOfEdges) {
    Graph::numOfEdges = numOfEdges;
}

int Graph::getStartVertice() const {
    return startVertice;
}

void Graph::setStartVertice(int startVertice) {
    Graph::startVertice = startVertice;
}

int Graph::getStopVertice() const {
    return stopVertice;
}

void Graph::setStopVertice(int stopVertice) {
    Graph::stopVertice = stopVertice;
}

list<Edge> Graph::getListOfEdges() const {
    return listOfEdges;
}

void Graph::setListOfEdges(list<Edge> listOfEdges) {
    Graph::listOfEdges = listOfEdges;
}
