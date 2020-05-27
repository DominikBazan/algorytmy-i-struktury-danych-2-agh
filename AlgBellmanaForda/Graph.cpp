#include "Graph.h"

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

list<Edge> Graph::getListOfEdges() const {
    return listOfEdges;
}

void Graph::setListOfEdges(list<Edge> listOfEdges) {
    Graph::listOfEdges = listOfEdges;
}
