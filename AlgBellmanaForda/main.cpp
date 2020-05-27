#include <iostream>
#include <string>
#include "Graph.h"
#include "FileLoader.h"
#include "Algorithm.h"

using namespace std;

void writeResult(string path) {
    FileLoader fileLoader(path);
    fileLoader.extractValues();

    Graph graph1_fromVideo_res_19;
    graph1_fromVideo_res_19.setNumOfVertices(fileLoader.getNumOfVertices());
    graph1_fromVideo_res_19.setNumOfEdges(fileLoader.getNumOfEdges());
    graph1_fromVideo_res_19.setStartVertice(fileLoader.getStartVertice());
    graph1_fromVideo_res_19.setListOfEdges(fileLoader.getListOfEdges());

    Algorithm algorithm(graph1_fromVideo_res_19);
    algorithm.calculateResult();
    //testowanie
//    algorithm.testing();
}

int main() {

    string path1 =  "../grafy/graf1_internet1.txt";

    cout << "Plik z grafem: \"" << path1.substr(9) << endl << "Ścieżki wynikowe:" << endl;
    writeResult(path1);

    return 0;
}